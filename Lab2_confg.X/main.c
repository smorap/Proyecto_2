// main 
#include "mcc_generated_files/mcc.h"
//#include "definiciones.h" 
//#include "eusart1.h"

volatile uint8_t V_Recibido[7];
volatile char Transmision_Error=0;
volatile char Transmision_Completada=0;
volatile uint8_t conteo=0;
volatile uint16_t recibido=0;
volatile uint16_t recibidoo=0;

typedef struct Maquinita Maquinita;
struct Maquinita
{
	int posicion;
	char inicio;
	char finall;
	char estados;
};

void Inicializar_Maquinita (Maquinita *mqnt){
	mqnt-> posicion = 0;
	mqnt-> inicio = '#';
	mqnt-> finall = '*';
	mqnt-> estados = 0;
}

typedef struct Paquete_Salida Paquete_Salida;
struct Paquete_Salida
{	
	char Pack[4];
};
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
                datto = datto/10;
				dsp->Pack[2] = datto % 10;//decenas
				datto = datto/10;
				dsp->Pack[1] = datto % 10;//centenas
				datto = datto/10;
				dsp->Pack[0] = datto % 10;
}





void main(void){	
    SYSTEM_Initialize();
    
	Maquinita My_Maquinita;
	Inicializar_Maquinita(&My_Maquinita);
	
	Paquete_Salida My_Paquete_Salida;
	Inicializar_Paquete(&My_Paquete_Salida);
	
	ADCC_Initialize();
	
    uint16_t ADC_Value = 0;
	char enviar = 0;
	
	// inicia con un periodo de 25ms
	T6PR = 0x4F; //registro de conteo del TIMER6 ( inicia en 25ms) 
	T6CON = 0xF6; //configiracion de prescaler y postscaler para 25ms
	IO_RD0_SetLow();
	IO_RD1_SetLow();
	IO_RB3_SetLow();
	IO_RD5_SetLow();
    while (1){
		if (EUSART1_is_rx_ready()){            
			Procese_UART (&My_Maquinita);
            //IO_RD0_SetHigh();
		}
		
		if (Transmision_Completada==1){
            IO_RD0_Toggle();
			Transmision_Completada = 0;		
			Procese_Dato_Rebido(); //esta funcion procesa el dato recibido y calcula el conteo en entero 
			//funcion que convierte a Hex y modifica el registro (T6PR)
		}
        if (TMR6_HasOverflowOccured()){
            IO_RD0_SetHigh();
            // Turn on the ADC module
            ADCON0bits.ADON = 1;

            // Start the conversion
            ADCON0bits.ADGO = 1;
            IO_RB3_Toggle();

        }
		if (!ADCC_IsConversionDone()){
            IO_RD0_SetLow();
            IO_RD5_Toggle();
			ADC_Value = ADCC_GetConversionResult();
			Ds_Separar_Digito(&My_Paquete_Salida, ADC_Value);
			enviar = 1;	
		}
		
		if(enviar && EUSART1_is_tx_ready()){
			enviar = 0;
            
			EUSART1_Write(My_Paquete_Salida.Pack[0] + '0');
			EUSART1_Write(My_Paquete_Salida.Pack[1] + '0');
			EUSART1_Write(My_Paquete_Salida.Pack[2] + '0');
			EUSART1_Write(My_Paquete_Salida.Pack[3] + '0');
            
            
			EUSART1_Write(0x0D);
		}
		
	}
}