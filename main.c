// main 
#include "displays.h" 
//#include <iostream>
#include "mcc.h"
#include "definiciones.h" 
#include "nuestrostimers.h"
#include "eusart.h"
//#define bool B_T_1ms
//#define Estados_Main
char Estados_Main = S0;
uint16_t ADC_Value =0 ;
adc_channel_t AN1_Channel;
uint16_t Valor_Convertido=0;
uint8_t Pack[6];
uint8_t Pp;
uint16_t xxx=123;

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
	ADC_Initialize();
	Ds_Iniciar_displays (&My_Display, Valor_Inicial0, Valor_Inicial1, Valor_Inicial2, T_On, T_Off);
    
    TMR6_StartTimer();

    

	while (1){
        
		if(TMR6_HasOverflowOccured()){
				Tm_Procese_tiempo(&My_Per_1ms);
                //Tm_Procese_tiempo(&My_Per_1000ms);
                Ds_Procese_displays(&My_Display);
			}
        
        if(Tm_Hubo_periodico(&My_Per_1ms)){						
				Tm_Baje_periodico(&My_Per_1ms); //bajo bandera
				//ADC_Initialize();
                ADC_StartConversion();
                
                //ADC_Value = ADC_GetConversion(AN1_Channel);
                //ADC_SelectChannel(AN1_Channel);
                
                //ADC_Value = ADC_GetConversion(AN1_Channel);
                //xxx=xxx+1;
        if(EUSART_is_tx_ready())
            {
                    Pack[0]=(My_Display.D3 + '0');
                    Pack[1]=(',');   
                    Pack[2]=(My_Display.D2 + '0');
                    Pack[3]=(My_Display.D1 + '0');
                    Pack[5]=0x0D;
                    Pack[4]= '\n';
                     EUSART_Write(Pack[0]);
                     EUSART_Write(Pack[1]);
                     EUSART_Write(Pack[2]);
                     EUSART_Write(Pack[3]); 
                     EUSART_Write(Pack[4]);
                     EUSART_Write(Pack[5]);
            } 
            
			}
			if(ADC_IsConversionDone()){
                //ADC_Initialize();
				//ADC_Value = ADC_GetConversion(AN1_Channel);
                ADC_Value = ADC_GetConversionResult();
                //ADC_Value = 1023;
                
				Valor_Convertido = Ds_Regla_de_3(ADC_Value);
                //Valor_Convertido =ADC_Value ;
				Ds_Separar_Digito(&My_Display, Valor_Convertido);
			}
	};
}