#if !defined(DISPLAYS_H)
#define DISPLAYS_H
#ifdef __cplusplus
extern "C" {
#endif

#define D1E 1
#define D1A 2
#define D2E 3
#define D2A 4
#define D3E 5
#define D3A 6

typedef struct Ds_Display Ds_Display;
struct Ds_Display
{
	char estados;
    char D1;
    char D2;
    char D3;
    char tiempoEncendido;
    char tiempoApagado;
    char tempE;
    char tempA;
};
// funcion para inicializar estructura de display
void Ds_Iniciar_displays(Ds_Display *dsp, char d1, char d2, char d3, char tE, char tA);

//funciones para  procesar display
void Ds_Procese_displays (Ds_Display *dsp);

// funciones para traducir el numero a BCD
/*Faltan....*/


/* 
    La funcion Ds_Encienda_Disp
    enciende el display de acuerdo al numero que le ingrese

    si le entra [1-3] enciende el respectivo display
    si le entra otro numero apaga todos
*/
void Ds_Encienda_Disp(char dispNum);


/*
    La funcion BCD
    convierte el decimal a BCD y lo traduce a la configuración del hardware actual
*/
void Ds_BCD(char );


/*
     La función Ds_Mostrar_en_display le entran los 3 digitos que quiero mostrar en el display

*/
void Ds_Mostrar_en_display(Ds_Display *dsp, char d1, char d2, char d3);
/*
     convertir en decimal unidades
*/
char Ds_Convertir_en_uni_deci_centi(Ds_Display *dsp,int num);





#ifdef __cplusplus
} // extern "C"
#endif
#endif

