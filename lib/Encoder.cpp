/* Encoder.cpp
 * Por Coralinæ Turtle
 * 
 * Classe responsável pela leitura dos encoders óticos
 */

#include "Encoder.h"

#include <Arduino.h>

#define PASSO_ENCODER (TWO_PI * RAIO_RODA / ENC_BPR)

Encoder::Encoder()
  : cont(0), buffer{}, ind(0)
{
}

void Encoder::atualiza()
{
  // Atualiza buffer:

  buffer[ind++] = cont;

  if(ind == N){
    ind = 0;
  }

  // Soma dos valores do buffer:
  // Precisa-se, de fato, da média, mas os B já estão divididos por N.

  float soma = 0;

  for(int val : buffer) {
    soma += val;
  }

  // Filtro derivativo:

  vel = B0 * soma + B1 * pos_anterior[0] + B2 * pos_anterior[1]
        - A1 * vel_anterior[0] - A2 * vel_anterior[1];

  pos_anterior[1] = pos_anterior[0];
  pos_anterior[0] = soma;

  vel_anterior[1] = vel_anterior[0];
  vel_anterior[0] = vel;
}

float Encoder::odometria()
{
  return cont * PASSO_ENCODER;
}

float estima_distancia(const Encoder& esq, const Encoder& dir)
{
  return (dir.odometria() + esq.odometria()) / 2;
}

float estima_orientacao(const Encoder& esq, const Encoder& dir)
{
  float angulo = (dir.odometria() - esq.odometria()) / DIST_RODAS;

  // Traz o retorno para o intervalo (-PI, PI]
  while(angulo > PI) {
    angulo -= PI;
  }
  while(angulo <= -PI) {
    angulo += PI;
  }

  return angulo;
}