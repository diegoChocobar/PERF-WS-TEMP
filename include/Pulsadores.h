#include <Arduino.h>
#include <Variables.h>
void ProfundidadMas();
void ProfundidadMenos();
void ResetProfundidad();

void ProfundidadMas(){
  event[PROFUNDIDAD_MAS].estado = false;
  Prof.offset += 0.01;
}

void ProfundidadMenos(){
  event[PROFUNDIDAD_MENOS].estado = false;
  Prof.offset -= 0.01;
}

void ResetProfundidad(){
  event[OFFSET_PROF].estado = false;
  Prof.pulsos = 0;
  Prof.offset = 0;
}