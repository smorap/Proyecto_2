// main 
#include "displays.h" 
//#include "mcc.h"
#include "mcc_generated_files/mcc.h"
#include "definiciones.h" 
#include "nuestrostimers.h"
#include "mcc_generated_files/eusart.h"

volatile uint16_t Valor_ADC=0;
volatile char Bandera_ADC = FALSE;
volatile char Bandera_Timer = FALSE;

// funcion interrupciones para el ADC
void Funcion_a_llamar_ADC_Interruciones (void){
	Valor_ADC = ADC_GetConversionResult();
	Bandera_ADC = TRUE;
}

void Funcion_a_llamar_Timer6_Interruciones (void){
	Bandera_Timer = TRUE;
}


void main(void){
	
    uint16_t ADC_Value =0;
    uint16_t Valor_Convertido=0;
    uint8_t Pack[6];
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
	
	    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
	
	
	ADC_SetInterruptHandler(Funcion_a_llamar_ADC_Interruciones);
	TMR6_SetInterruptHandler(Funcion_a_llamar_Timer6_Interruciones);
	
    while (1){        
		if(Bandera_Timer){
            Bandera_Timer = FALSE;
            Tm_Procese_tiempo(&My_Per_1000ms);
            Ds_Procese_displays(&My_Display);
			} 
        
        if(Tm_Hubo_periodico(&My_Per_1000ms)){						
				Tm_Baje_periodico(&My_Per_1000ms); //bajo bandera
                ADC_StartConversion();                
                enviar = TRUE;
		}
        
        if(enviar && EUSART_is_tx_ready()){
            enviar = FALSE;
            Pack[0]=(My_Display.D3 + '0');
            Pack[1]=(',');   
            Pack[2]=(My_Display.D2 + '0');
            Pack[3]=(My_Display.D1 + '0');
            Pack[5]=0x0D;

            EUSART_Write(Pack[0]);
            EUSART_Write(Pack[1]);
            EUSART_Write(Pack[2]);
            EUSART_Write(Pack[3]); 
            EUSART_Write(Pack[4]);
            EUSART_Write(Pack[5]);
        }
        
        if(Bandera_ADC){//bandera activada en la interrupcion 
			Bandera_ADC = FALSE;
            //ADC_Value = ADC_GetConversionResult();//interrupcion 
			ADC_Value = Valor_ADC;
            Valor_Convertido = Ds_Regla_de_3(ADC_Value);// esto se queda aqui 
            Ds_Separar_Digito(&My_Display, Valor_Convertido);// esto se queda aqui 
        }
	}
}