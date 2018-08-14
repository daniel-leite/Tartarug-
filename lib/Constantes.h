/* Constantes.h
 * Por Coralinæ Turtle
 *
 * Contém as constantes do modelo e do controlador do réptil
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H

#ifdef ENCODER_H

# define N  2  // Quantidade de amostras na média do filtro de referência
# define A1 1  // Coeficientes do filtro de saída
# define A2 1
# define B0 1
# define B1 1
# define B2 1

#endif

/* Parâmetros físicos */
#define RAIO_RODA   (.044)
#define ENC_BPR     (2*24)   // Bordas por rotação do encoder
#define DIST_RODAS  (.092)   // Distância entre as rodas

#endif // CONSTANTES_H
