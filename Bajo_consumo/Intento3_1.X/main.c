// main 
#include "displays.h" 
#include "mcc.h"
#include "definiciones.h" 
#include "nuestrostimers.h"
#include "eusart.h"

void main(void){
    uint16_t ADC_Value =0 ;
    uint16_t Valor_Convertido=0;
    uint8_t Pack[6];
    	char Apagar_7seg=11;
	char Apagar_Tr=0;
	char Bandera_Sleep=0;
    char enviar =FALSE;
	SYSTEM_Initialize();
	Ds_Display My_Display;
	Tm_Periodico My_Per_1000ms;
	Tm_Inicie_periodico (&My_Per_1000ms, Tiempo_timer);
	ADC_Initialize();
    ADCON0 = ADCON0 | 0b00100001;
    ADCON0 = ADCON0 & 0b10100011;
    ADCON1 = 0b11100000;
	Ds_Iniciar_displays (&My_Display, Valor_Inicial0, Valor_Inicial1, Valor_Inicial2, T_On, T_Off);    
    TMR6_StartTimer();
	
    while (1){
        ADC_StartConversion();                
		enviar = TRUE;
        
		while(!ADC_IsConversionDone()){
			//esperar a que termine la conversión 
		}
		
		ADC_Value = ADC_GetConversionResult();
		Valor_Convertido = Ds_Regla_de_3(ADC_Value);
		Ds_Separar_Digito(&My_Display, Valor_Convertido);
		
		Pack[0]=(My_Display.D3 + '0');
		Pack[1]=(',');   
		Pack[2]=(My_Display.D2 + '0');
		Pack[3]=(My_Display.D1 + '0');
		Pack[5]=0x0D;

		EUSART_Write(Pack[0]);
		CLRWDT();// reseteo WDT
		Bandera_Sleep=1;
		EUSART_Write(Pack[1]);
		EUSART_Write(Pack[2]);
		EUSART_Write(Pack[3]); 
		EUSART_Write(Pack[4]);
		EUSART_Write(Pack[5]);
		
		if (Bandera_Sleep){
			Bandera_Sleep = 0;
            Ds_BCD(Apagar_7seg);
            Ds_Encienda_Disp(Apagar_Tr);
            SLEEP();
		}
        
	}
}