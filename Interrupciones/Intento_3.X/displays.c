#include "displays.h"
#include "mcc_generated_files/pin_manager.h"
#include <stdint.h>

void Ds_Iniciar_displays(Ds_Display *dsp, char d1, char d2, char d3, char tE, char tA){
    dsp->estados=D1E;
    dsp->D1=d1;
    dsp->D2=d2;
    dsp->D3=d3;
    dsp->tiempoEncendido=tE;
    dsp->tiempoApagado=tA;
    dsp->tempE=tE;
    dsp->tempA=tA;
}

void Ds_Encienda_Disp(char dispNum){
	switch (dispNum){
	case 0:
		IO_RB0_SetLow();
		IO_RB3_SetLow();
		IO_RB5_SetLow();
	break;
	
	case 1:
		IO_RB0_SetHigh();
		IO_RB3_SetLow();
		IO_RB5_SetLow();
	break;
	
	case 2:
		IO_RB0_SetLow();
		IO_RB3_SetHigh();
		IO_RB5_SetLow();
	break;
	
	case 3:
		IO_RB0_SetLow();
		IO_RB3_SetLow();
		IO_RB5_SetHigh();
	break;
		
	}


}


void Ds_BCD(char digito){
	switch (digito){
	
	case 0:
		IO_RA0_SetHigh();
		IO_RA1_SetHigh();
		IO_RA2_SetHigh();
		IO_RA3_SetHigh();
		IO_RA4_SetHigh();
		IO_RA6_SetHigh();
		IO_RA7_SetLow();
		
	break;
	
	case 1:
		IO_RA0_SetLow();
		IO_RA1_SetHigh();
		IO_RA2_SetHigh();
		IO_RA3_SetLow();
		IO_RA4_SetLow();
		IO_RA6_SetLow();
		IO_RA7_SetLow();
		
	break;
	
	case 2:
		IO_RA0_SetHigh();
		IO_RA1_SetHigh();
		IO_RA2_SetLow();
		IO_RA3_SetHigh();
		IO_RA4_SetHigh();
		IO_RA6_SetLow();
		IO_RA7_SetHigh();
		
	break;
	
	case 3:
		IO_RA0_SetHigh();
		IO_RA1_SetHigh();
		IO_RA2_SetHigh();
		IO_RA3_SetHigh();
		IO_RA4_SetLow();
		IO_RA6_SetLow();
		IO_RA7_SetHigh();
		
	break;
	
	case 4:
		IO_RA0_SetLow();
		IO_RA1_SetHigh();
		IO_RA2_SetHigh();
		IO_RA3_SetLow();
		IO_RA4_SetLow();
		IO_RA6_SetHigh();
		IO_RA7_SetHigh();
		
	break;
	
	case 5:
		IO_RA0_SetHigh();
		IO_RA1_SetLow();
		IO_RA2_SetHigh();
		IO_RA3_SetHigh();
		IO_RA4_SetLow();
		IO_RA6_SetHigh();
		IO_RA7_SetHigh();
		
	break;
	
	case 6:
		IO_RA0_SetHigh();
		IO_RA1_SetLow();
		IO_RA2_SetHigh();
		IO_RA3_SetHigh();
		IO_RA4_SetHigh();
		IO_RA6_SetHigh();
		IO_RA7_SetHigh();
		
	break;
	
	case 7:
		IO_RA0_SetHigh();
		IO_RA1_SetHigh();
		IO_RA2_SetHigh();
		IO_RA3_SetLow();
		IO_RA4_SetLow();
		IO_RA6_SetHigh();
		IO_RA7_SetLow();
		
	break;
	
	case 8:
		IO_RA0_SetHigh();
		IO_RA1_SetHigh();
		IO_RA2_SetHigh();
		IO_RA3_SetHigh();
		IO_RA4_SetHigh();
		IO_RA6_SetHigh();
		IO_RA7_SetHigh();
		
	break;
	
	case 9:
		IO_RA0_SetHigh();
		IO_RA1_SetHigh();
		IO_RA2_SetHigh();
		IO_RA3_SetLow();
		IO_RA4_SetLow();
		IO_RA6_SetHigh();
		IO_RA7_SetHigh();
		
	break;
	
	case 10:
		IO_RA0_SetHigh();
		IO_RA1_SetHigh();
		IO_RA2_SetHigh();
		IO_RA3_SetHigh();
		IO_RA4_SetHigh();
		IO_RA6_SetHigh();
		IO_RA7_SetHigh();
		
	break;
	}
}

void Ds_Separar_Digito (Ds_Display *dsp, uint16_t Recibido){
	dsp->D3 = Recibido % 10;
	Recibido = Recibido/10;
	dsp->D2 = Recibido % 10;
	Recibido = Recibido/10;
	dsp->D1 = Recibido % 10;
}

uint16_t Ds_Regla_de_3 (uint16_t Leido){ // retora el valor leido de 0-10           
    float salidaa=0.97654;
    uint16_t salida = (uint16_t)(((float)Leido)*salidaa);
	return(salida);
}


void Ds_Procese_displays (Ds_Display *dsp){

    switch ( dsp->estados){
	
    case D1E:
        --(dsp->tempE);
        if(!(dsp->tempE)){
            dsp->estados =D1A;
            dsp->tempA=dsp->tiempoApagado;
        }
        Ds_Encienda_Disp(1);
        Ds_BCD(dsp->D1);

        break;
    case D1A:
        --(dsp->tempA);
        if(!(dsp->tempA)){
            dsp->estados =D2E;
            dsp->tempE=dsp->tiempoEncendido;
        }
        Ds_Encienda_Disp(0);
    break;
    case D2E:
        --(dsp->tempE);
        if(!(dsp->tempE)){
            dsp->estados =D2A;
            dsp->tempA=dsp->tiempoApagado;
        }

        Ds_Encienda_Disp(2);//transistor
        Ds_BCD(dsp->D2);// enciende el 7 segmentos dependiendo del numero
    break;
    case D2A:
        --(dsp->tempA);
        if(!(dsp->tempA)){
            dsp->estados =D3E;
            dsp->tempE=dsp->tiempoEncendido;
        }
        Ds_Encienda_Disp(0);
    break;
    case D3E:
        --(dsp->tempE);
        if(!(dsp->tempE)){
            dsp->estados =D3A;
            dsp->tempA=dsp->tiempoApagado;
        }
        Ds_Encienda_Disp(3);
        Ds_BCD(dsp->D3);
    break;
    case D3A:
        --(dsp->tempA);
        if(!(dsp->tempA)){
            dsp->estados =D1E;
            dsp->tempE=dsp->tiempoEncendido;
        }
        Ds_Encienda_Disp(0);
    break;
    default:
        // a este no deberia llegar nunca
        while(1){
			Ds_BCD(10);
			Ds_Encienda_Disp(2);
        }
}
}