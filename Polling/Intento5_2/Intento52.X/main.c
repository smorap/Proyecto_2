// main 
#include "displays.h" 
//#include <iostream>
#include "mcc.h"
#include "definiciones.h" 
#include "nuestrostimers.h"
//#define bool B_T_1ms
//#define Estados_Main
char Estados_Main = S0;
uint16_t ADC_Value =0 ;
adc_channel_t AN1_Channel;
int Valor_Convertido=0;
int xxx=123;

void main(void){
    /*Codigo que configura un timer a 1 milisegundo*/
	SYSTEM_Initialize();
    
	Ds_Display My_Display;
	Tm_Periodico My_Per_1ms;
    Tm_Periodico My_Per_1000ms;
	Tm_Inicie_periodico (&My_Per_1ms, 1000);
	ADC_SelectChannel (AN1_Channel);
	Tm_Periodico My_ADC_1000ms;
	Tm_Inicie_periodico (&My_Per_1000ms, 1000);
	
	Ds_Iniciar_displays (&My_Display, Valor_Inicial0, Valor_Inicial1, Valor_Inicial2, T_On, T_Off);
    
    TMR6_StartTimer();

    

	while (1){
		
		switch (Estados_Main){
			
			case S0:
			// Timer hardware
			if(TMR6_HasOverflowOccured()){
				Tm_Procese_tiempo(&My_Per_1ms);
                //Tm_Procese_tiempo(&My_Per_1000ms);
                Ds_Procese_displays(&My_Display);
			}
			Estados_Main = S1;
			break;
			
			case S1:
			// displays
             /*
			if(Tm_Hubo_periodico(&My_Per_1ms)){
				Tm_Baje_periodico(&My_Per_1ms);
				//Ds_Procese_displays(&My_Display);
			}
              */
			Estados_Main = S2;
			break;
			
			case S2:
			// ADC
			if(Tm_Hubo_periodico(&My_Per_1ms)){							
				Tm_Baje_periodico(&My_Per_1ms); //bajo bandera
				// ADC_StartConversion();
                ADC_Value = ADC_GetConversion(AN1_Channel);
                //ADC_SelectChannel(AN1_Channel);
                
                //ADC_Value = ADC_GetConversion(AN1_Channel);
                //xxx=xxx+1;
			}
			if(ADC_IsConversionDone()){
                
				//ADC_Value = ADC_GetConversion(AN1_Channel);
                //ADC_Value = ADC_GetConversionResult();
                //ADC_Value = 1023;
                //xxx=xxx+1;
				Valor_Convertido = Ds_Regla_de_3(ADC_Value);
                //Valor_Convertido = ADC_Value;
				Ds_Separar_Digito(&My_Display, Valor_Convertido);
			}
			
			Estados_Main = S3;
			break;
			
			case S3:
			// USART
			Estados_Main = S0;
			break;
		}
	};
}