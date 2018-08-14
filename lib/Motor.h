/* Motor.h
 * Por Coralinæ Turtle
 * 
 * Classe responsável pelo movimento dos motores CC
 */

#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public:
  // Construtor: configura a pinagem
  Motor(int m1, int m2, int en);

  // vel: valor do PWM
  void mover(uint8_t vel);
  
  void travar();

  // Direção atual de rotação (-1, 0 ou +1)
  int dir() { return dir; }

private:
  // Pinos
  int m1, m2, en;

  int dir;
}

#endif // MOTOR_H