#include <Arduino.h>
#include <Wire.h>

//#include <WebSocketsClient.h>
//#include <ArduinoWebsockets.h>

#include <Hash.h>

#include <stdarg.h>
#include <avr/dtostrf.h>

unsigned int nSerie = 9001;

struct  ValueADS
{
    float valor;
    float promedio;
    float desvio_standar;
    int tamaño;//tamño del numero de iteraciones para la obtencion de una medida
    int n;//tamaño del valor que queda despues de tratar la señal
    unsigned long tiempo_individual;
};

struct  Corrientes
{
    float valor;
    float promedio;
    float desvio_standar;
    int tamaño;//tamño del numero de iteraciones para la obtencion de una medida
    int n;//tamaño del valor que queda despues de tratar la señal
    unsigned long tiempo_individual;
    float offset;
};

struct  Temperaturas
{
    float valor;
    float promedio;
    float desvio_standar;
    int tamaño;//tamño del numero de iteraciones para la obtencion de una medida
    int n;//tamaño del valor que queda despues de tratar la señal
    unsigned long tiempo_individual;
    float offset;
};

struct  Profundidad
{
    float valor;
    float offset;
};

enum TipoEvento {
    SIN_EVENTO,        // 0
    HOLD,              // 1
    DISPARO,           // 2
    OFFSET_I,          // 3
    ESCALA_I,
    OFFSET_PROF,       
    PROFUNDIDAD_MAS,
    PROFUNDIDAD_MENOS,
    MEDIRCORRIENTE, 
    MEDIRTEMPERATURA,
    MEDIRPROFUNDIDAD, 
    ENVIODATOS,
    PRINT,
    TEST_CONECT_MQTT,
    
       

    TOTALEVENTOS
};
struct  Eventos
{
    TipoEvento tipo;
    boolean estado;
    String mensaje;
    boolean print_status;
    
};
Eventos event[TOTALEVENTOS] = {
    {SIN_EVENTO,           false,"********************",false},/////sin eventos
    {HOLD,                 false,"*******HOLD*********",false},///// Envento Hold
    {DISPARO,              false,"******DISPARO*******",false},
    {OFFSET_I,             false,"******OFFSET I******",false},
    {ESCALA_I,             false,"****CAMBIO ESCALA***",false},
    {OFFSET_PROF,          false,"****OFFSET PROF*****",false},
    {PROFUNDIDAD_MAS,      false,"***PROFUNDIDAD + ***",false},
    {PROFUNDIDAD_MENOS,    false,"***PROFUNDIDAD - ***",false},
    {MEDIRCORRIENTE,       false,"**MEDIR CORRIENTE **",false},
    {MEDIRTEMPERATURA,     false,"**MEDIR TEMPERATURA*",false},
    {MEDIRPROFUNDIDAD,     false,"**MEDIR PROFUNDIDAD*",false},
    {ENVIODATOS,           false,"****ENVIO DATOS*****",false},
    {PRINT,                false,"***ESCALA      mA***",false},
    {TEST_CONECT_MQTT,     false,"**TEST CONECT MQTT**",false}
};


////////////////VARIABLES PARA MANEJO DEL LCD //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 o 0x20 o 0x3F

const int pos1_unidad=17,pos1_decena=12,pos1_centena=8,pos1_mil=4,pos1_diezmil=0;
const int pos2_unidad=17,pos2_decena=13,pos2_centena=8,pos2_mil=4,pos2_diezmil=0;
const int pos3_unidad=17,pos3_decena=13,pos3_centena=9,pos3_mil=4,pos3_diezmil=0;

//Vector formador de los segmentos para el LCD
byte LT[8] ={B01111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};
byte UB[8] ={B11111,  B11111,  B11111,  B00000,  B00000,  B00000,  B00000,  B00000};
byte RT[8] ={B11110,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};
byte LL[8] ={B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B01111};
byte LB[8] ={B00000,  B00000,  B00000,  B00000,  B00000,  B11111,  B11111,  B11111};
byte LR[8] ={B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11110};
byte UMB[8] ={B11111,  B11111,  B11111,  B00000,  B00000,  B00000,  B11111,  B11111};
byte LMB[8] ={B11111,  B00000,  B00000,  B00000,  B00000,  B11111,  B11111,  B11111};
/////////////////////////////////////////////////////////////////////////////////////


// Adafruit_ADS1115 ads(0x48);  /* Use this for the 16-bit version */ /*Dir I2C 0x48 (gnd) */
Adafruit_ADS1115 ads;
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

float constanteADS;
int escala;
int escala_ant=100;//iniciamos con un valor de escala_ant que no corresponda a ninguna escala para forzar a que se imprima la escala en el primer ciclo de impresión del LCD
int canal=1;
int Iteraciones=15;
float confianza_h = 1.25; ///variable de alejamiento del desvio standar
int ADS_Frec = 64; ///frecuencia de muestreo del ADS1115, en muestras por segundo. 8;16;32;64;128;250;475;860


/////// Variables Globales Medidas  ////////////////////////////////
Corrientes offset_1 ={0,0,0,0,0,0,0};
Corrientes offset_2 ={0,0,0,0,0,0,0};
Corrientes deltaI = {0,0,0,0,0,0,0};
Corrientes deltaIPrint={1,0,0,0,0,0,0};

Temperaturas Temp_t = {0,0,0,0,0,0,0};
Temperaturas Temp_t_print = {1,0,0,0,0,0,0};
Temperaturas Temp_offset = {0,0,0,0,0,0,0};

Profundidad  Prof_p = {0,0};
Profundidad  Prof_p_print = {1,0};
Profundidad  Prof_offset = {0,0};


//////////////Variables para definicion de Pines//////////////////////////////////
int pulsador_escala = 16;             //pin utilizado para el pulsador de cambio de escala
int pulsador_zero = 14;               //pin utilizado para pulsador de puesta a cero la medicion
int pulsador_hold = 13;             //pin utilizado para pulsador selector de potencia de salida
int pulsador_disparo = 12;            //pin utilizado para pulsador selector de potencia de salida


int output_led = 2;     //pin de salida led indicador
int output_zumbador = 3; //pin de salida zumbador
int output_disparo = 1; //pin de salida disparo
//////////////////////////////////////////////////////////////////////////////////

/// @Variables de banderas para acciones ///////
boolean bandZero=true;//sirve para indicar si el offset de corriente esta activo o no, true significa que el offset de corriente no esta activo, y false que el offset de corriente esta activo
boolean bandDisparo=false;
boolean bandHold = false;
boolean bandCalibracion = false;
boolean bandModoADS = false;

boolean bandMedirCorriente = false;
boolean bandPulsadorDisparo = true;
boolean bandPulsadorHold = true;
boolean bandTestConectMqtt = true;
////////////////////////////////////////////////

/////////////Variables para los manejos de tiempo de acciones ////////////////////
unsigned long tiempo_actual = 0;
unsigned long tiempo_LCD = 0;
unsigned long tiempo_Ping = 0;
unsigned long tiempo_DataFull = 0;
unsigned long tiempo_pulsadores = 0;
unsigned long tiempo_MedirCorriente = 0;
unsigned long tiempo_EnvioDatos = 0;
unsigned long tiempo_testConectMqtt = 0;

unsigned long tiempo_medida_total = 0;  //pulsador para congelar la señal
unsigned long tiempo_medida_indiv = 0;  //pulsador para congelar la señal
//////////////////////////////////////////////////////////////////////////////////

////////////////INCIALIZAR wifi /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////    
const char* ssid = "SEV_WiFi";
const char* password = "ChDi1088";

int Num_Dispositivos = 0;
int Num_Disp_Check = 0;

bool isEnvieDataFull = false;


////////////////////////////////////////////////////////////////////////////////

////////////////INCIALIZAR MQTT /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////// 
const char *mqtt_user = "";
const char *mqtt_pass = "";
unsigned int mqtt_reconect = 0;

const char *mqtt_server = "10.42.0.1";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

String str_topicPublic="SEV_C/SEV_I/Default/Default";
////////////////////////////////////////////////////////////////////////////////

////////////// Definicion de Funciones ///////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length);
void separar(String str, char delimiter, String parts[], int maxSize);
////////////////////////////////////////////////////////////////////////////
