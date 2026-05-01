#pragma once// Salva que se incluya mas de una vez. Permite incluir este achivo en varios otros
#include <Arduino.h>
#include <Variables.h>

// factor metros por pulso (ajustable)
const float factorProfundidad = 0.000523;

// ISR
void IRAM_ATTR encoderISR() {
    if (digitalRead(pinEncoderB)) {
        Prof.pulsos++;
    } else {
        Prof.pulsos--;
    }
}

// Init encoder
void initEncoder() {
    pinMode(pinEncoderA, INPUT_PULLUP);
    pinMode(pinEncoderB, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(pinEncoderA), encoderISR, RISING);
}

// Cálculo de profundidad
void calcularProfundidad() {
    event[MEDIRPROFUNDIDAD].estado = false;
    long pulsos_local;

    noInterrupts();
    pulsos_local = Prof.pulsos;
    interrupts();

    Prof.valor = (pulsos_local * factorProfundidad) + Prof.offset;
}