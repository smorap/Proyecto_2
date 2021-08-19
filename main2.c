

#include "nuestrostimers.h" 
//#include "display.h"
#include "definiciones.h"


void main(void){
Tm_Periodico timerS1;

timerS1.contador

// inicialización de estructura de tiempo
Tm_Inicie_periodico (&timerS1,CONTEOSTIMERS1);


for(;;){
    if (/*condicion del timer por hardware de 1ms*/){
        //Reset del timer por hardware

        //atencion del timer por hardware
        Tm_Procese_tiempo (&timerS1);
    }
    if(/*condición del timer por software*/Tm_Hubo_periodico (&timerS1)){
        //reset del timer por software
        Tm_Baje_periodico (&timerS1);
        //
        /*haga lo que tenga que hacer cada segundo...*/

    }
}









}
