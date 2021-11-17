// main 
#include "mcc_generated_files/mcc.h"
#include "funciones.h"

volatile uint8_t V_Recibido[7];
volatile char Transmision_Error=0;
volatile char Transmision_Completada=0;
volatile uint8_t conteo=0;
volatile uint16_t recibido=0;
volatile uint16_t recibidoo=0;
volatile uint16_t ADC_Value = 0;
volatile uint16_t DAC_Value=0;
volatile uint16_t ADC_ValueFiltrado = 0;
volatile uint8_t TengoDatoADC=0;
volatile uint8_t bloque[2];
volatile int16_t palabraSPI=0b0011000000000000;
volatile int16_t palabra_SPI=0b0011000000000000;
volatile coef_iir_2_ord PRIMERETAPA;
volatile coef_iir_2_ord SEGUNDAETAPA;


typedef struct Maquinita Maquinita;
struct Maquinita
{
	int posicion;
	char inicio;
	char finall;
	char estados;
};

typedef struct Paquete_Salida Paquete_Salida;
struct Paquete_Salida
{	
	char Pack[4];
};


void Inicializar_Maquinita (Maquinita *mqnt){
	mqnt-> posicion = 0;
	mqnt-> inicio = '#';
	mqnt-> finall = '*';
	mqnt-> estados = 0;
}


void Inicializar_Paquete (Paquete_Salida *mqnt){
	mqnt-> Pack[0] = 0;
	mqnt-> Pack[1] = 0;
	mqnt-> Pack[2] = 0;
	mqnt-> Pack[3] = 0;
}

void Procese_UART(Maquinita *mqnt ){
	
	switch (mqnt->estados) {
		case 0:
			V_Recibido[mqnt-> posicion] = EUSART1_Read();
			if (V_Recibido[mqnt-> posicion]== mqnt->inicio){

                mqnt->estados = 1;
				mqnt-> posicion = mqnt-> posicion + 1;
			}
			Transmision_Error=0;
		break;
		
		case 1:
            
			V_Recibido[mqnt-> posicion] = EUSART1_Read();
			mqnt->estados = 2;
			mqnt-> posicion = mqnt-> posicion + 1;
		break;
		
		case 2:
			V_Recibido[mqnt-> posicion] = EUSART1_Read();
			mqnt->estados = 3;
			mqnt-> posicion = mqnt-> posicion + 1;
		break;
		
		case 3:
			V_Recibido[mqnt-> posicion] = EUSART1_Read();
			mqnt->estados = 4;
			mqnt-> posicion = mqnt-> posicion + 1;
		break;
		
		case 4:
			V_Recibido[mqnt-> posicion] = EUSART1_Read();
			mqnt->estados = 5;
			mqnt-> posicion = mqnt-> posicion + 1;
		break;
		
		case 5:
			V_Recibido[mqnt-> posicion] = EUSART1_Read();
			mqnt->estados = 6;
			mqnt-> posicion = mqnt-> posicion + 1;
		break;
		
		case 6:
			V_Recibido[mqnt-> posicion] = EUSART1_Read();
            
			if (V_Recibido[mqnt-> posicion] == mqnt->finall){
				Transmision_Completada = 1;
			}else {
				Transmision_Error = 1;
			}
			mqnt->estados = 0;
			mqnt-> posicion = 0;
		break;
	}
}

void Procese_Dato_Rebido(void){

	recibido=((V_Recibido[5]-'0')*1 + (V_Recibido[4]-'0')*10 + (V_Recibido[3]-'0')*100 + (V_Recibido[2]-'0')*1000+(V_Recibido[1]-'0')*10000);
    if(recibido >= 500 && recibido <= 4100){
		T6CON = 0xF0; // aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 16; // este valor va al registro de conteo (T6PR)
	}
		
	if(recibido > 4100 && recibido <= 8200){
		T6CON = 0xF1;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 32; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 8200 && recibido <= 12200){
		T6CON = 0xF2;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 48; // este valor va al registro de conteo (T6PR) 
	}
		
	if(recibido > 12200 && recibido <= 16200){
		T6CON = 0xF3;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 64; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 16200 && recibido <= 20400){
		T6CON = 0xF4;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 80; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 20400 && recibido <= 24500){
		T6CON = 0xF5;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 96; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 24500 && recibido <= 28600){
		T6CON = 0xF6;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 112; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 28600 && recibido <= 32700){
		T6CON = 0xF7;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 128; // este valor va al registro de conteo (T6PR) 
		//Tm_Procese_tiempo(&My_Per_1000ms);
	}
	
	if(recibido > 32700 && recibido <= 36800){
		T6CON = 0xF8;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 144; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 36800 && recibido <= 40100){
		T6CON = 0xF9;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 160; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 40100 && recibido <= 45000){
		T6CON = 0xFA;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 176; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 45000 && recibido <= 49100){
		T6CON = 0xFB;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 192; // este valor va al registro de conteo (T6PR) 
	}
	
	if(recibido > 49100 && recibido <= 53200){
		T6CON = 0xFC;// aqui se modifican los registros del preescaler y posescaler (T6CON)  
		conteo = recibido / 208; // este valor va al registro de conteo (T6PR) 
	}
    T6PR=conteo;
}


void Ds_Separar_Digito (Paquete_Salida *dsp, uint16_t datto){
                dsp-> Pack[3] = datto % 10; //unidades
                //datto = datto/10;
				//dsp->Pack[2] = datto % 10;//decenas
                dsp->Pack[2] = datto % 100;//decenas
				//datto = datto/10;
				//dsp->Pack[1] = datto % 10;//centenas
                dsp->Pack[1] = datto % 1000;//centenas
				//datto = datto/10;
				//dsp->Pack[0] = datto % 10;
}

void NuestraAtencionADC(void){
    TengoDatoADC=1;
    IO_RB3_Toggle();
    ADC_Value=((adc_result_t)((ADRESH << 8) + ADRESL));
    //SI IIR
    int valor=(int)ADC_Value;
    int Respuesta_filtro=  filtrarIIR(valor,&PRIMERETAPA,&SEGUNDAETAPA);
    ADC_ValueFiltrado=(uint16_t)Respuesta_filtro;
    DAC_Value=ADC_ValueFiltrado;
    palabra_SPI = palabraSPI + ADC_ValueFiltrado;
    
    //SPI
    bloque[1]=palabra_SPI;
    bloque[0]=palabra_SPI>>8;
    IO_RE0_SetLow();
    SPI1_WriteBlock(bloque,2);
    IO_RE0_SetHigh();
    IO_RB4_SetLow();
    __delay_us(4);
    IO_RB4_SetLow();
    IO_RB4_SetHigh();
    //Termina SPI
}


void main(void){
	
    SYSTEM_Initialize();
    Maquinita My_Maquinita;
	Inicializar_Maquinita(&My_Maquinita);
	Paquete_Salida My_Paquete_Salida;
	Inicializar_Paquete(&My_Paquete_Salida);
	ADCC_Initialize();
    ADCC_SetADIInterruptHandler(NuestraAtencionADC);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
	char enviar = 0;
    IO_RE0_SetHigh();
    IO_RB4_SetHigh();
    SPI1_Open(SPI1_DEFAULT);
	IO_RD0_SetLow();
	IO_RD1_SetLow();
	IO_RB3_SetLow();
	IO_RD5_SetLow();
    
    //------------------------------Coeficientes filtro IIR-------------------//
    // Rechazabanda Fs 220 hz FC 58-62   PUNTO 1-------------------------------//
    /*float gain1 =0.9604125519268;
    float num1[3] = {                 1,   0.2850946362695,                 1  };   
    float den1[3] = {                 1,    0.350602358178,    0.922831664871  };      
    float w1[3] = {0, 0, 0};
    
    float gain2 =0.9604125519268;
    float num2[3] = {             1,   0.2850946362695,                 1  };   
    float den2[3] = {                1,   0.1966015133424,   0.9219629412186   };         
    float w2[3] = {0, 0, 0};
    */
    // pasa bajas Fs 220 hz FC 44hz   PUNTO 2----------------------------------//
    /*float gain1 =0.2533015125277;
    float num1[3] = {  1,                 2,                 1 };   
    float den1[3] = {                  1,  -0.4531195206524,   0.4663255707632};      
    float w1[3] = {0, 0, 0};
    
    float gain2 =0.1839029943864;
    float num2[3] = {    1,                 2,                 1};   
    float den2[3] = {                   1,   -0.328975677371,  0.06458765491644 };      
    float w2[3] = {0, 0, 0};
    */ 
    // pasa altas Fs 220 hz FC 55hz   PUNTO 3----------------------------------//
    float gain1 =0.3616156730429;
    float num1[3] = {                 1,                -2,                 1 };   
    float den1[3] = {                   1,-3.211792370221e-16,   0.4464626921717 };      
    float w1[3] = {0, 0, 0};
    
    float gain2 =0.2598915324741;
    float num2[3] = {                1,                -2,                 1 };   
    float den2[3] = {                   1,-2.308300506063e-16,  0.03956612989658 };      
    float w2[3] = {0, 0, 0};
    
    //Funciones para inicializar cada una de las dos etapas
    inicializar_IIR(num1, den1, w1, &PRIMERETAPA,gain1 );
    inicializar_IIR(num2, den2, w2, &SEGUNDAETAPA,gain2 );
    while (1){
		if (EUSART1_is_rx_ready()){            
			Procese_UART (&My_Maquinita);
           }
		
		if (Transmision_Completada==1){
            Transmision_Completada = 0;		
			Procese_Dato_Rebido(); //esta funcion procesa el dato recibido y calcula el conteo en entero 
			
		}
		if (TengoDatoADC){
            TengoDatoADC=0;
            IO_RD5_Toggle();
			Ds_Separar_Digito(&My_Paquete_Salida, ADC_Value);
			enviar = 1;	
		}		
		if(enviar==1){//400 us
			enviar = 0;
			EUSART1_Write(My_Paquete_Salida.Pack[0] + '0');
			EUSART1_Write(My_Paquete_Salida.Pack[1] + '0');
			EUSART1_Write(My_Paquete_Salida.Pack[2] + '0');
			EUSART1_Write(My_Paquete_Salida.Pack[3] + '0');
            EUSART1_Write(My_Paquete_Salida.Pack[3] + '0');
            EUSART1_Write(0x0D);
		}
		
	}
}