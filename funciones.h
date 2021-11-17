#ifndef FUNCIONES_H
#define FUNCIONES_H

/*Parametros del filtro IIR*/

typedef struct coef_iir_2_ord {// este va a ser el nombre de la estructura
  float gainc ;
  float num[3]; // numerador
  float den[3]; // denominador
  float w[3];   // Valores a almacenar primer etapa
  float w2[3];  // Valores a almacenar segunda etapa
} coef_iir_2_ord;// este va a ser el nombre del typedef
//crear coficientes 
void inicializar_IIR(float*num, float*den, float*w, coef_iir_2_ord* ir,float ganan);
//inicia a filtrar segun coeficientes
float filtrarIIR(float in,coef_iir_2_ord* etapa1, coef_iir_2_ord* etapa2);
#endif