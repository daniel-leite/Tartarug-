/* Encoder.h
 * Por Coralinæ Turtle
 * 
 * Classe responsável pela leitura dos encoders óticos
 */

#ifndef ENCODER_H
#define ENCODER_H

#include "Constantes.h"

class Encoder
{
public:
  // Construtor
  Encoder();

  // Incrementa o passo atual. Chamado quando encontrada uma borda do encoder
  void incr(int8_t dir) { cont += dir; }

  int passo_atual() { return cont; }

  float velocidade() { return vel; }

  // Atualiza o buffer e a velocidade
  void atualiza();

  // Distância total girada pela roda, em metros
  float odometria();

private:
  // Passo atual
  volatile int cont;

  // Velocidade
  float vel;

  // Vetor que armazena as N últimas posições
  int buffer[N];

  // Índice atual no buffer
  uint8_t ind;

  // Valores passados de posição e velocidade
  float pos_anterior[2];
  float vel_anterior[2];
}

// Distância total percorrida pelo robô, em metros, estimada
float estima_distancia(const Encoder& esq, const Encoder& dir);

// Ângulo atual de orientação do robô, em radianos, estimado
float estima_orientacao(const Encoder& esq, const Encoder& dir);

#endif // ENCODER_H