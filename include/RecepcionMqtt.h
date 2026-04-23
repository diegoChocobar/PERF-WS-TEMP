#include <Arduino.h>

void parseConfigI(String msg);

//////////////////////////////////////////////////////////////////////
/////////////// Recepcion de Datod MQTT /////////////////////////////
/////////////////////////////////////////////////////////////////////
//void callback(char* topic, byte* payload, unsigned int length) {}
///*
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
    payload[length] = '\0';
    String strTopic = String((char*)topic);
    String Topic_partes[4]; // asumiendo que siempre hay 4 partes separadas por "/"
    //user:Topic_partes[0]; ubicacion:Topic_partes[1]; lugar:Topic_partes[2]; tipo:Topic_partes[3]; name:Topic_partes[4]
    String mensaje = ""; //Creamos un String para almacenar el payload
    String str_nserie = (String)nSerie;

    // Iteramos sobre cada byte del payload y lo agregamos al String
    for (unsigned int i = 0; i < length; i++) {
        mensaje += (char)payload[i];
    }

    // Llamamos a la función split() para separar el string
    separar(strTopic, '/', Topic_partes, 4);
     
    if(Topic_partes[0]=="SEV_C" && Topic_partes[1]=="SEV_I" && Topic_partes[2]=="Hold" && Topic_partes[3]=="Status"){
        pulsoPin(output_led,output_zumbador,-1,-1,250);
        EnviarHold("ON");
    }
     
    if(Topic_partes[0]=="SEV_C" && Topic_partes[1]=="SEV_I" && Topic_partes[2]=="Check" && Topic_partes[3]=="?"){
        pulsoPin(output_led,output_zumbador,-1,-1,250);
        EnviarStatus("ON");
        pulsoPin(output_led,output_zumbador,-1,-1,250);
    }
    
    if(Topic_partes[0]=="SEV_C" && Topic_partes[1]=="SEV_I" && Topic_partes[2]=="Disparo" && Topic_partes[3]=="ON"){
        event[DISPARO].estado = true;
        bandDisparo = true;
        pulsoPin(output_led,output_zumbador,-1,-1,250);
    }
    
    if(Topic_partes[0]=="SEV_C" && Topic_partes[1]=="SEV_I" && Topic_partes[2]=="Disparo" && Topic_partes[3]=="OFF"){
        event[DISPARO].estado = true;
        bandDisparo = false;
        pulsoPin(output_led,output_zumbador,-1,-1,250);
    }

    if(Topic_partes[0]=="SEV_C" && Topic_partes[1]=="SEV_I" && Topic_partes[2]=="Config" && Topic_partes[3]=="Values"){
            parseConfigI(mensaje);
            isEnvieDataFull = true;
    }

    if(Topic_partes[0]=="SEV_C" && Topic_partes[1]=="SEV_I" && Topic_partes[2]=="Config" && Topic_partes[3]=="OFF"){
            isEnvieDataFull = false;
    }

    if(Topic_partes[0]=="SEV_C" && Topic_partes[1]=="SEV_X" && Topic_partes[2]=="Hold" && Topic_partes[3]=="ON"){
        event[HOLD].estado = true;
        bandHold = true;
        pulsoPin(output_led,output_zumbador,-1,-1,250);
    }

    if(Topic_partes[0]=="SEV_C" && Topic_partes[1]=="SEV_X" && Topic_partes[2]=="Hold" && Topic_partes[3]=="OFF"){
        event[HOLD].estado = true;
        bandHold = false;
        pulsoPin(output_led,output_zumbador,-1,-1,250);
    }

}
//*//////////////////////////////////////////////////////////////////////////


// Función para dividir un string en partes usando un delimitador
void separar(String str, char delimiter, String parts[], int maxSize) {
    int partIndex = 0; // Índice de la parte actual
    int startIndex = 0; // Índice de inicio de la parte actual

    // Recorremos el string
    for (unsigned int i = 0; i < str.length(); i++) {
        // Si encontramos el delimitador o llegamos al final del string
        if (str.charAt(i) == delimiter || i == str.length() - 1) {
            // Extraemos la parte actual
            if (i == str.length() - 1) {
                parts[partIndex] = str.substring(startIndex, i + 1);
            } else {
                parts[partIndex] = str.substring(startIndex, i);
            }
            // Incrementamos el índice de la parte actual
            partIndex++;
            // Actualizamos el índice de inicio para la próxima parte
            startIndex = i + 1;
        }
        // Si alcanzamos el máximo de partes, salimos del bucle
        if (partIndex >= maxSize) {
            break;
        }
    }
}

void parseConfigI(String msg) {
  int pos1, pos2;

  // Buscar y extraer Iteraciones (entero)
  pos1 = msg.indexOf("\"Iteraciones\":") + 14;
  pos2 = msg.indexOf(",", pos1);
  int iteraciones = msg.substring(pos1, pos2).toInt();
  Iteraciones = iteraciones;

  // Buscar y extraer Frecuencia_ADS (entero)
  pos1 = msg.indexOf("\"Frecuencia_ADS\":") + 17;
  pos2 = msg.indexOf(",", pos1);
  int frecuencia = msg.substring(pos1, pos2).toInt();
  ADS_Frec = frecuencia;
  //*
  if (ADS_Frec==8){ads.setDataRate(RATE_ADS1115_8SPS);}//8;16;32;64;128;250;475;860
  if (ADS_Frec==16){ads.setDataRate(RATE_ADS1115_16SPS);}//8;16;32;64;128;250;475;860
  if (ADS_Frec==32){ads.setDataRate(RATE_ADS1115_32SPS);}//8;16;32;64;128;250;475;860
  if (ADS_Frec==64){ads.setDataRate(RATE_ADS1115_64SPS);}//8;16;32;64;128;250;475;860
  if (ADS_Frec==128){ads.setDataRate(RATE_ADS1115_128SPS);}//8;16;32;64;128;250;475;860
  //*/

  // Buscar y extraer Escala (entero)
  pos1 = msg.indexOf("\"Escala\":") + 9;
  pos2 = msg.indexOf(",", pos1);
  int escale = msg.substring(pos1, pos2).toInt();
  
  //*
  if (escale==2000){escala =4;}
  if (escale==1000){escala =16;}
  if (escale==250){escala =2;}
  EscalaSwitch(escala);
  //*/

  // Buscar y extraer Confianza (float)
  pos1 = msg.indexOf("\"Confianza\":") + 12;
  pos2 = msg.indexOf("}", pos1);
  float confianza = msg.substring(pos1, pos2).toFloat();
  confianza_h = confianza;

  // Aquí podés asignarlos a variables globales o usarlos
}
