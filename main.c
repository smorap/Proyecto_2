#include <math.h># está en el PATH de compilación osea la ruta donde busca el copilador por defecto
#include"nuestrostimers.h" # está en el mismo directorio donde está el main
#include"nuestrostimers.h" # Yo puedo incluir esto dos veces sin tener error de redefinición

void setup(void){
    /*Codigo que configura un timer a 1 milisegundo*/

    /*Cada milisegundo el timer levanta el bit 0 del registro TIMERYA*/
}

#define CONTEOS1SEGUNDO 1000

void main(void){
    int contador=0;
    int YaPasOUnSegundo=0;
    int YaPasOUnSegundo=0;
    int YaPasOUnMiliSegundo=0;
    setup();

    /*
    while(1){
        loop();
    }
    */
   for(;;){
        if (YaPasOUnSegundo/*EVENTO_1 ocurre cada segundo*/){
            /*
            Resetear El Evento
            Atención al EVENTO_1
            Convertir un dato del ADC y...
            Enviar un ese dato al display para mostrar y
            Enviar el dato al serial
            */
            PasoUnSegundo=0;
            Convertir_de_ADC(/*entrada*/);
            RefrescarDisplay(/*entrada*/);
            EnviarPorSerial(/*entrada*/);
        }
        if (YaPasOUnMiliSegundo/*EVENTO_1*/){
            /*Atención al EVENTO_1*/
            PasoUnMiliSegundo=0;
            MostrarDisplay(/*Entradas*/);
        }
        if (TIMERYA & 0b00000001/*está en 0 si el bit 0 está en 0 y en 1 si el bit 0 está en 1*/){
            /*Restet de bandera*/
            TIMERYA=(TIMERYA & 0b11111110);/*baja la bandera del timer*/
            /*Atiendo el evento*/
            YaPasOUnMiliSegundo=1;/*o en True*/
            contador++;
            if(contador>=CONTEOS1SEGUNDO){
                contador=0;
                YaPasOUnSegundo=1;
            }
        }
   }
}