#pragma once// Salva que se incluya mas de una vez. Permite incluir este achivo en varios otros
#include <Arduino.h>
#include <Wire.h>

#include <Hash.h>
#include <stdarg.h>
#include <avr/dtostrf.h>

unsigned int nSerie = 9001;
String Cliente = "ClienteX";

struct  ValueADS
{
    float valor;
    float promedio;
    float desvio_standar;
    int tamaño;//tamño del numero de iteraciones para la obtencion de una medida
    int n;//tamaño del valor que queda despues de tratar la señal
    unsigned long tiempo_individual;
};


struct  Temperaturas
{
    float valor;
    float promedio;
    float desvio_standar;
    int tamaño;//tamño del numero de iteraciones para la obtencion de una medida
    int n;//tamaño del valor que queda despues de tratar la señal
    unsigned long tiempo_individual;
};

struct  Profundidad
{
    volatile long pulsos;
    float valor;
    float offset;
};

enum TipoEvento {
    SIN_EVENTO,
    HOLD,
    OFFSET_PROF,
    PROFUNDIDAD_MAS,
    PROFUNDIDAD_MENOS,
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

    {SIN_EVENTO, false,"******MIDIENDO******",false},

    {HOLD,              false,"*******HOLD*********",true},

    {OFFSET_PROF,       false,"****OFFSET PROF*****",true},

    {PROFUNDIDAD_MAS,   false,"***PROFUNDIDAD +****",false},

    {PROFUNDIDAD_MENOS, false,"***PROFUNDIDAD -****",false},

    {MEDIRTEMPERATURA,  false,"",false},

    {MEDIRPROFUNDIDAD,  false,"",false},

    {ENVIODATOS,        false,"",false},

    {PRINT,             false,"",false},

    {TEST_CONECT_MQTT,  false,"*****TEST MQTT******",false}
};


////////////////VARIABLES PARA MANEJO DEL LCD //////////////////////////////////
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 o 0x20 o 0x3F

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

/////////////////////// Variables Globales ADS1115  ////////////////////////////////
// Adafruit_ADS1115 ads(0x48);  /* Use this for the 16-bit version */ /*Dir I2C 0x48 (gnd) */
Adafruit_ADS1115 ads;

float constanteADS;
int escala;
int escala_ant=100;//iniciamos con un valor de escala_ant que no corresponda a ninguna escala para forzar a que se imprima la escala en el primer ciclo de impresión del LCD
int canal=1;
int Iteraciones=15;
float confianza_h = 1.25; ///variable de alejamiento del desvio standar
int ADS_Frec = 64; ///frecuencia de muestreo del ADS1115, en muestras por segundo. 8;16;32;64;128;250;475;860
//////////////////////////////////////////////////////////////////////////////////

/////// Variables Globales Medidas  ////////////////////////////////
Temperaturas Temp = {0,0,0,0,0,0};
Temperaturas Temp_print = {1,0,0,0,0,0};

Profundidad  Prof = {0,0.0,0.0};
Profundidad  Prof_print = {9999,9999.0,1.5}; //valores imposibles para forzar primer print
//////////////////////////////////////////////////////////////////////////////////

//////////////Variables para definicion de Pines//////////////////////////////////
int pulsador_mas = 16;
int pulsador_menos = 14;
const int pinEncoderA = 12;
const int pinEncoderB = 13;

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
////////////////////////////////////////////////

/////////////Variables para los manejos de tiempo de acciones ////////////////////
unsigned long tiempo_actual = 0;
unsigned long tiempo_LCD = 0;
unsigned long tiempo_Ping = 0;
unsigned long tiempo_pulsadores = 0;
unsigned long tiempo_MedirTemperatura = 0;
unsigned long tiempo_EnvioDatos = 0;
unsigned long tiempo_testConectMqtt = 0;
unsigned long tiempo_MedirProfundidad = 0;

unsigned long tiempo_medida_indiv = 0;  //pulsador para congelar la señal
//////////////////////////////////////////////////////////////////////////////////

////////////////INCIALIZAR wifi /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////    
const char* ssid = "SEV_WiFi";
const char* password = "ChDi1088";

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
////////////////////////////////////////////////////////////////////////////////

////////////// Definicion de Funciones ///////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length);
void separar(String str, char delimiter, String parts[], int maxSize);
////////////////////////////////////////////////////////////////////////////
