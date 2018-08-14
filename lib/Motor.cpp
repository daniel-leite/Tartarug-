/* Motor.cpp
 * Por Coralinæ Turtle
 * 
 * Implementação da classe responsável pelo movimento dos motores CC
 */

#include "Motor.h"

#include <Arduino.h>

Motor::Motor(int m1, int m2, int en)
  : m1(m1), m2(m2), en(en), dir(0)
{
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(en, OUTPUT);
}

Motor::mover(uint8_t vel)
{
  dir = (vel > 0);

  digitalWrite(m1, dir);
  digitalWrite(m2, !dir);
  analogWrite(en, vel);
}

Motor::travar()
{
  dir = 0;

  digitalWrite(m1, HIGH);
  digitalWrite(m2, HIGH);
  digitalWrite(en, HIGH);
}
