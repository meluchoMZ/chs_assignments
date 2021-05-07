#include<stdio.h>
#include"jpeg.h"

const int zig_zag_inv[64] = {
0, 8, 1, 2, 9, 16, 24, 17, 
10, 3, 4, 11, 18, 25, 32, 40, 
33, 26, 19, 12, 5, 6, 13, 20, 
27, 34, 41, 48, 56, 49, 42, 35, 
28, 21, 14, 7, 15, 22, 29, 36, 
43, 50, 57, 58, 51, 44, 37, 30, 
23, 31, 38, 45, 52, 59, 60, 53, 
46, 39, 47, 54, 61, 62, 55, 63
};


extern int last_dc_val[3];

void zigzag(short *block, short *ordenado){

	int i; 

	for(i=0; i<64; ++i)
		ordenado[i] =  block[zig_zag_inv[i]];
}


void generadorCodigos(short *block, int tipoBlock){

	int k;
	short temp, r;

	// primero el coeficiente DC

	temp = block[0] - last_dc_val[tipoBlock];
	last_dc_val[tipoBlock] = block[0];

	procesadorValores(esDC, (tipoBlock != 0), 0, temp);	// procesar coeficiente DC; de tipo Y ó no; sin run-length; valor = temp

	// ahora el bucle de los AC

	r = 0;			// r = run-length de ceros
   
	for (k = 1; k < 64; k++) {
		if (block[k] == 0) {
			++r;
		}else{
			while(r>15){
				procesadorValores(esAC, (tipoBlock != 0), 15, 0);	// procesar coeficiente AC; de tipo Y ó no; run-length = 15; sin valor				
				r -= 16;
			}
			procesadorValores(esAC, (tipoBlock != 0), r, block[k]);	// procesar coeficiente AC; de tipo Y ó no; con run-length = r; valor = temp
			r = 0;
		}
	}
	if(r)
		procesadorValores(esAC, (tipoBlock != 0), 0, 0);	// procesar coeficiente AC; de tipo Y ó no; run-length = 0; sin valor

}

