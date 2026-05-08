#include <Arduino.h>

void PrintValoresLCD(Temperaturas temp, Profundidad prof);
void PrintADS(Temperaturas temp);
void PrintEscala(void);
void PrintEvento(void);
void PrintEscalaADS(void);

void PrintValoresLCD(Temperaturas temp, Profundidad prof)
{
  char buffer[10]; // necesario para imprimir datos reservando lugar vacío al inicio XXXX.XX
  float RES_OFFSET = 0.0005;
  float RES_TEMP = 0.01;
  float RES_PROF = 0.005;
  event[PRINT].estado = false;

  if (bandHold == true)
  { // si el hold esta activo, no actualizamos los valores de corriente, temperatura y profundidad en el LCD.
    if (event[HOLD].print_status)
    {
      PrintEvento();
    }
    return;
  }

  ////////actualizamos el LCD solo si el cambio en los valores de corriente, temperatura o profundidad es mayor a una resolución predefinida para evitar actualizar el LCD con cambios menores a la resolución de cada medida
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (fabs(prof.offset - Prof_print.offset) > RES_OFFSET)
  { // acturalizamos el valor de corriente, teniendo en cuenta el valor anterior para evitar actualizar el LCD con cambios menores a RES_CORR
    Prof_print.offset = prof.offset;
    dtostrf(prof.offset, 4, 2, buffer); // 7 caracteres: 4 enteros, 1punto y 2 decimales
    lcd.setCursor(0, 2);
    lcd.print("Offset Prof:");
    lcd.print(buffer);
    lcd.print("m");
  }
  if (fabs(temp.valor - Temp_print.valor) > RES_TEMP)
  { // acturalizamos el valor de temperatura, teniendo en cuenta el valor anterior para evitar actualizar el LCD con cambios menores a RES_TEMP
    Temp_print.valor = temp.valor;
    dtostrf(temp.valor, 7, 2, buffer); // 7 caracteres: 4 enteros, 1punto y 2 decimales
    lcd.setCursor(0, 1);
    lcd.print("Temp:");
    lcd.print(buffer);
    lcd.print("C");
  }
  if (fabs(prof.valor - Prof_print.valor) > RES_PROF)
  { // acturalizamos el valor de profundidad, teniendo en cuenta el valor anterior para evitar actualizar el LCD con cambios menores a RES_PROF
    Prof_print.valor = prof.valor;
    dtostrf(prof.valor, 7, 2, buffer); // 7 caracteres: 4 enteros, 1punto y 2 decimales
    lcd.setCursor(0, 0);
    lcd.print("Prof:");
    lcd.print(buffer);
    lcd.print("m");
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  PrintEscala();
  PrintEvento();
}

void PrintADS(Temperaturas temp)
{
  char buffer[10]; // necesario para imprimir datos reservando lugar vacío al inicio XXXX.XX
  float RES_TEMP = 0.01;
  event[PRINT].estado = false;

  if (bandHold == true)
  { // si el hold esta activo, no actualizamos los valores de corriente, temperatura y profundidad en el LCD.
    if (event[HOLD].print_status)
    {
      PrintEvento();
    }
    return;
  }
  ////////actualizamos el LCD solo si el cambio en los valores de corriente, temperatura o profundidad es mayor a una resolución predefinida para evitar actualizar el LCD con cambios menores a la resolución de cada medida
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (fabs(temp.valor - Temp_print.valor) > RES_TEMP)
  { // acturalizamos el valor de corriente, teniendo en cuenta el valor anterior para evitar actualizar el LCD con cambios menores a RES_CORR

    Temp_print.valor = temp.valor;

    lcd.setCursor(0, 0);
    lcd.print("** MEDIR  ADS1115 **");
    lcd.print(buffer);
    dtostrf(temp.valor, 9, 3, buffer); // 9 caracteres: 5 enteros, 1punto y 3 decimales
    lcd.setCursor(0, 1);
    lcd.print("V");
    lcd.print(buffer);

    dtostrf(temp.desvio_standar, 6, 3, buffer); // 6 caracteres: 3 enteros, 1punto y 3 decimales
    lcd.setCursor(10, 1);
    lcd.print("d");
    lcd.print(buffer);

    lcd.setCursor(17, 1);
    lcd.print("n");
    lcd.print(temp.n, 0);

    dtostrf(temp.promedio, 9, 3, buffer); // 9 caracteres: 5 enteros, 1punto y 3 decimales
    lcd.setCursor(0, 2);
    lcd.print("P");
    lcd.print(buffer);

    lcd.setCursor(10, 2);
    lcd.print("t");
    lcd.print(temp.tiempo_individual);
    lcd.setCursor(17, 2);
    lcd.print("m");
    lcd.print(temp.tamaño, 0);
  }

  lcd.setCursor(0, 3);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("E:");
  PrintEscalaADS();
  lcd.setCursor(9, 3);
  lcd.print("k:");
  lcd.print(constanteADS * 1000, 1);
  lcd.setCursor(17, 3);
  lcd.print("c");
  lcd.print(canal, 0); // canal ad

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  PrintEvento();
}

void PrintEscala(void)
{

  if (escala != escala_ant)
  {
    escala_ant = escala;
    lcd.setCursor(0, 3);
    lcd.print(event[PRINT].mensaje);
    switch (escala)
    {
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

void PrintEscalaADS(void)
{

  switch (escala)
  {
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

void PrintEvento(void)
{
  if (bandHold) //no uso la bandera de print_status del evento hold porque quiero que el mensaje de hold se imprima cada vez que se llama a PrintEvento mientras el hold este activo, y no solo la primera vez que se activa el hold.
  {
    lcd.setCursor(0, 3);
    lcd.print(event[HOLD].mensaje);
    return;
  }
  static unsigned long t_evento = 0;
  static bool mostrando_evento = false;

  static unsigned long t_blink = 0;
  static bool blink = true;

  // EVENTOS


  if (event[OFFSET_PROF].print_status)
  {
    event[OFFSET_PROF].print_status = false;

    lcd.setCursor(0, 3);
    lcd.print(event[OFFSET_PROF].mensaje);

    t_evento = millis();
    mostrando_evento = true;
  }

  if (event[PROFUNDIDAD_MAS].print_status)
  {
    event[PROFUNDIDAD_MAS].print_status = false;

    lcd.setCursor(0, 3);
    lcd.print(event[PROFUNDIDAD_MAS].mensaje);

    t_evento = millis();
    mostrando_evento = true;
  }

  if (event[PROFUNDIDAD_MENOS].print_status)
  {
    event[PROFUNDIDAD_MENOS].print_status = false;

    lcd.setCursor(0, 3);
    lcd.print(event[PROFUNDIDAD_MENOS].mensaje);

    t_evento = millis();
    mostrando_evento = true;
  }

  // DESPUÉS DE 3 SEGUNDOS VOLVER A "SIN_EVENTO"

  if (mostrando_evento && (millis() - t_evento > 3000))
  {
    mostrando_evento = false;
    blink = true;
  }

  // HEARTBEAT PARPADEANTE

  if (!mostrando_evento)
  {
    if (millis() - t_blink > 1500)
    {
      t_blink = millis();
      blink = !blink;

      lcd.setCursor(0, 3);

      if (!blink)
      {
        lcd.print(event[SIN_EVENTO].mensaje);
      }
      else
      {
        lcd.setCursor(6, 3);
        lcd.print("        ");
      }
    }
  }
}