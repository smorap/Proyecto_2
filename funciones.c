#include "funciones.h"
/*Funciones del filtro IIR*/

void inicializar_IIR(float*num, float*den, float*w, coef_iir_2_ord* ir,float ganan)
{
  ir->gainc  = ganan ;
  for (int i = 0; i < 3; i++) {
    ir->num[i] = num[i];
    ir->den[i] = den[i];
    ir->w[i] = w[i];
  }
}

/*ver la ayuda de matlab de dfilt.df2 para ver la estructura implementada en este filtro*/
float filtrarIIR(float in, coef_iir_2_ord* ir, coef_iir_2_ord* ir2 ) {
  //Formula para cada seccion: "forma directa II secciones de segundo orden "
  //w[0] = (1/(a1)*(((gain * x) - (a2 * w[1])) - (a3 * w[2]));
  //y = ((b1 * w[0]) + (b2 * w[1]) + (b3 * w[2]));
 
  float y,y2;
  
  //seccion 1
  ir->w[0] = (1/(ir->den[0]))*(((ir->gainc * in) - (ir->den[1] * ir->w[1])) - (ir->den[2] * ir->w[2])); // OJO QUE EL MENOS YA ESTA EN LA ECUACION ver en  la ayuda de filterDesign en "show filter structure" si esta es o no la ecuación que implementan en ese software
  y = ((ir->num[0] * ir->w[0]) + (ir->num[1] * ir->w[1]) + (ir->num[2] * ir->w[2]));
  ir->w[2] = ir->w[1];//debe ser primero este
  ir->w[1] = ir->w[0];// y luego este para no sobreescribir
  
  //seccion 2
  ir2->w2[0] = (1/(ir2->den[0]))*(((ir2->gainc * y) - (ir2->den[1] * ir2->w2[1])) - (ir2->den[2] * ir2->w2[2])); // OJO QUE EL MENOS YA ESTA EN LA ECUACION ver en  la ayuda de filterDesign en "show filter structure" si esta es o no la ecuación que implementan en ese software
  y2 = ((ir2->num[0] * ir2->w2[0]) + (ir2->num[1] * ir2->w2[1]) + (ir2->num[2] * ir2->w2[2]));
  ir2->w2[2] = ir2->w2[1];//debe ser primero este
  ir2->w2[1] = ir2->w2[0];// y luego este para no sobreescribir
  return y2;
}

