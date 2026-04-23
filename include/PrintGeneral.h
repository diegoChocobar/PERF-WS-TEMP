#include <Arduino.h>

void PrintValoresLCD(Corrientes x, Temperaturas temp, Profundidad prof);
void PrintADS(Corrientes x);
void PrintEscala(void);
void PrintEvento(void);
void PrintEscalaADS(void);

void PrintValoresLCD(Corrientes x, Temperaturas temp, Profundidad prof){
   char buffer[10]; //necesario para imprimir datos reservando lugar vacío al inicio XXXX.XX
   float RES_CORR = 0.02;
   float RES_TEMP = 0.05;
   float RES_PROF = 0.05;
  event[PRINT].estado = false;

  if(bandHold ==true){//si el hold esta activo, no actualizamos los valores de corriente, temperatura y profundidad en el LCD.
      if(event[HOLD].print_status){
        PrintEvento();
      }
    return;
  }

////////actualizamos el LCD solo si el cambio en los valores de corriente, temperatura o profundidad es mayor a una resolución predefinida para evitar actualizar el LCD con cambios menores a la resolución de cada medida
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(fabs(x.valor - deltaIPrint.valor) > RES_CORR){//acturalizamos el valor de corriente, teniendo en cuenta el valor anterior para evitar actualizar el LCD con cambios menores a RES_CORR
    deltaIPrint.valor = x.valor;
    dtostrf(x.valor, 7, 2, buffer);//7 caracteres: 4 enteros, 1punto y 2 decimales
    lcd.setCursor(0, 2);lcd.print("Corr:");lcd.print(buffer);lcd.print("mA");
  }
  if(fabs(temp.valor - Temp_t_print.valor) > RES_TEMP){//acturalizamos el valor de temperatura, teniendo en cuenta el valor anterior para evitar actualizar el LCD con cambios menores a RES_TEMP
    Temp_t_print.valor = temp.valor;
    dtostrf(temp.valor, 7, 2, buffer);//7 caracteres: 4 enteros, 1punto y 2 decimales
    lcd.setCursor(0, 1);lcd.print("Temp:");lcd.print(buffer);lcd.print("C");
  }
  if(fabs(prof.valor - Prof_p_print.valor) > RES_PROF){//acturalizamos el valor de profundidad, teniendo en cuenta el valor anterior para evitar actualizar el LCD con cambios menores a RES_PROF
    Prof_p_print.valor = prof.valor;
    dtostrf(prof.valor, 7, 2, buffer);//7 caracteres: 4 enteros, 1punto y 2 decimales
    lcd.setCursor(0, 0);lcd.print("Prof:");lcd.print(buffer);lcd.print("m");
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PrintEscala();
  PrintEvento();
  

}

void PrintADS(Corrientes x){
   char buffer[10]; //necesario para imprimir datos reservando lugar vacío al inicio XXXX.XX
   float RES_CORR = 0.02;
   event[PRINT].estado = false;

  if(bandHold ==true){//si el hold esta activo, no actualizamos los valores de corriente, temperatura y profundidad en el LCD.
      if(event[HOLD].print_status){
        PrintEvento();
      }
    return;
  }
  ////////actualizamos el LCD solo si el cambio en los valores de corriente, temperatura o profundidad es mayor a una resolución predefinida para evitar actualizar el LCD con cambios menores a la resolución de cada medida
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(fabs(x.valor - deltaIPrint.valor) > RES_CORR){//acturalizamos el valor de corriente, teniendo en cuenta el valor anterior para evitar actualizar el LCD con cambios menores a RES_CORR
    
    deltaIPrint.valor = x.valor;
    
    lcd.setCursor(0, 0);lcd.print("** MEDIR  ADS1115 **");lcd.print(buffer);
    dtostrf(x.valor, 9, 3, buffer);//9 caracteres: 5 enteros, 1punto y 3 decimales
    lcd.setCursor(0, 1);lcd.print("V");lcd.print(buffer);

    dtostrf(x.desvio_standar, 6, 3, buffer);//6 caracteres: 3 enteros, 1punto y 3 decimales
    lcd.setCursor(10, 1);lcd.print("d");lcd.print(buffer);

    lcd.setCursor(17, 1);lcd.print("n");lcd.print(x.n,0);

    dtostrf(x.promedio, 9, 3, buffer);//9 caracteres: 5 enteros, 1punto y 3 decimales
    lcd.setCursor(0, 2);lcd.print("P");lcd.print(buffer);
    
    lcd.setCursor(10, 2);lcd.print("t");lcd.print(x.tiempo_individual);
    lcd.setCursor(17, 2);lcd.print("m");lcd.print(x.tamaño,0);

  }

  lcd.setCursor(0,3);lcd.print("                    ");
  lcd.setCursor(0,3);lcd.print("E:");PrintEscalaADS();
  lcd.setCursor(9, 3);lcd.print("k:");lcd.print(constanteADS*1000,1);
  lcd.setCursor(17, 3);lcd.print("c");lcd.print(canal,0);//canal ad

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

  PrintEvento();

}


void PrintEscala(void){

  if(escala != escala_ant){
    escala_ant = escala;
    lcd.setCursor(0, 3);
    lcd.print(event[PRINT].mensaje);
    switch (escala) {
          case 1:
            lcd.setCursor(10, 3);
            lcd.print("4000");
          break; 

          case 2:
            lcd.setCursor(10, 3);
            lcd.print("2000");
          break;

          case 4:
            lcd.setCursor(10, 3);
            lcd.print("1000");
          break;  

          case 8:
            lcd.setCursor(10, 3);
            lcd.print("500");
          break;

          case 16:
            lcd.setCursor(10, 3);
            lcd.print("250");
          break;

          default:
            lcd.setCursor(10, 3);
            lcd.print("2000");
          break;
        }
  }
}

void PrintEscalaADS(void){

    switch (escala) {
          case 1:
            lcd.print("4000");
          break; 

          case 2:
            lcd.print("2000");
          break;

          case 4:
            lcd.print("1000");
          break;  

          case 8:
            lcd.print("500");
          break;

          case 16:
            lcd.print("250");
          break;

          default:
            lcd.print("2000");
          break;
        }
}


void PrintEvento(void){
  escala_ant = 100;//forzamos a que se imprima la escala en el siguiente ciclo de impresión del LCD
  if(event[OFFSET_I].print_status){
    event[OFFSET_I].print_status = false;
    lcd.setCursor(0, 3);
    lcd.print(event[OFFSET_I].mensaje);
  }
  if(event[ESCALA_I].print_status){
    event[ESCALA_I].print_status = false;
    lcd.setCursor(0, 3);
    lcd.print(event[ESCALA_I].mensaje);
  }
  if(event[DISPARO].print_status){
    event[DISPARO].print_status = false;
    lcd.setCursor(0, 3);
    lcd.print(event[DISPARO].mensaje);
  }
  if(event[HOLD].print_status){
    event[HOLD].print_status = false;
    lcd.setCursor(0, 3);
    lcd.print(event[HOLD].mensaje);
  }

  lcd.setCursor(19, 3);lcd.print(" ");
  delay(150);
  lcd.setCursor(19, 3);lcd.print("*");
}
