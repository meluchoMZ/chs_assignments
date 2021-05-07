#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jpeg.h"

// SOLO FUNCIONA CON IMÁGENES DE 256 x 256 

volatile unsigned int *COPput, *COPget;

int Hput_buffer;
int Hput_bits;
FILE *Hfile_out;
int last_dc_val[3];
unsigned char *IMAGEN;


int main(int nargs, char *vargs[]){

	FILE *input_file, *output_file;


	input_file = fopen("hdr_256_256.ppm", "rb");
	Hfile_out = output_file = fopen("hdrPrueba.jpg", "wb");

	IMAGEN = (unsigned char*)malloc(SIZE); //width * height * 3);
	if(!IMAGEN){
		printf("Error reservando memoria para cargar la imagen original\n");
		return -1;
	}


	last_dc_val[0]=last_dc_val[1]=last_dc_val[2]=0;

	if(cargaImagen(input_file, IMAGEN)){
		printf("Problemas cargando la imagen\n");
		fclose(input_file);
		fclose(output_file);
		exit(-1);
	}

	ponerCabecera(output_file);

	codificaJPEG(input_file, output_file);

}

void codificaJPEG(FILE *input_file, FILE *output_file){

	int width=256, height=256; 

	int i, j, k, m, p;
	unsigned char R[256], G[256], B[256];
	unsigned char Y[256], Cb[256], Cr[256];
	
	unsigned char *pY, *pCb, *pCr, *RGB;

	short bloqueDCT[64], dctPas1[64], traspuesto[64], dctPas2[64], cuantizados[64], bloqueOrdenado[64];

	unsigned int res;

	COPput = (unsigned int *)0x80000000;
	COPget = (unsigned int *)0x80000004;

/////////////////////////////////////////////////////////////////////////////////////////

//  PARA UTILIZAR EL COPROCESADOR CON emiteBits(), DEBES INICIALIZARLO ANTES: 

//  PARA ELLO, DESCOMENTA LA SIGUIENTE LÍNEA

/////////////////////////////////////////////////////////////////////////////////////////

//	*COPput = 128 << 24; // INICIALIZACIÓN  ( SOLO SEGUNDA PARTE DE LA PRÁCTICA ) 

	for(i=0; i<height; i+=16){
		for(j=0; j<width; j+=16){
			p = 0;
			RGB = &(IMAGEN[(i*width+j)*3]);
			pY = Y; pCb = Cb; pCr = Cr;
			for(k=0; k<16; ++k){
				for(m=0; m<16; ++m){

// SOLO PARA RGB_YCbCr  ( TERCERA PARTE DE LA PRÁCTICA )
// PARA LA TERCERA PARTE DE LA PRÁCTICA, COMENTAR LA SIGUIENTE LÍNEA (  RGB_YCbCr(RGB, pY, pCb, pCr);  )
					RGB_YCbCr(RGB, pY, pCb, pCr);

// PARA LA TERCERA PARTE DE LA PRÁCTICA, ESCRIBE EL CÓDIGO QUE REALIZA LAS SIGUIENTES OPERACIONES

// PRIMERO: PÁSALE AL COPROCESADOR LOS VALORES RGB, DISPONIBLES EN:      *((unsigned int*) RGB)

// SEGUNDO, RECOGE EL RESULTADO DEL COPROCESADOR Y PONLO EN LA VARIABLE "res"

// TERCERO, GUARDA LOS RESULTADOS EN LOS ARRAYS pY, pCb y pCr
// Para ello descomenta las siguientes líneas y complétalas teniendo en cuenta que 
//      el valor para pY está en los bits  [23 a 16]
//      el valor para pCb está en los bits [15 a  8]
//      el valor para pCr está en los bits [ 7 a  0]

//					*pY =  
//					*pCb = 
//					*pCr =   

					RGB += 3;	++pY; 	++pCb;	++pCr;
					
				}
				RGB += (width-16)*3;

			}

			//procesa Y
			prepararBloqueY(Y+0, bloqueDCT); 
			dct_1D(bloqueDCT, dctPas1);
			transponerBloque(dctPas1, traspuesto);
			dct_1D(traspuesto, dctPas2);
			quantizarCoeficientes(dctPas2, cuantizados, 0);
			zigzag(cuantizados, bloqueOrdenado);
			generadorCodigos(bloqueOrdenado, 0); 

			prepararBloqueY(Y+8, bloqueDCT); 
			dct_1D(bloqueDCT, dctPas1);
			transponerBloque(dctPas1, traspuesto);
			dct_1D(traspuesto, dctPas2);
			quantizarCoeficientes(dctPas2, cuantizados, 0);
			zigzag(cuantizados, bloqueOrdenado);
			generadorCodigos(bloqueOrdenado, 0); 

			prepararBloqueY(Y+128, bloqueDCT); 
			dct_1D(bloqueDCT, dctPas1);
			transponerBloque(dctPas1, traspuesto);
			dct_1D(traspuesto, dctPas2);
			quantizarCoeficientes(dctPas2, cuantizados, 0);
			zigzag(cuantizados, bloqueOrdenado);
			generadorCodigos(bloqueOrdenado, 0); 

			prepararBloqueY(Y+136, bloqueDCT); 
			dct_1D(bloqueDCT, dctPas1);
			transponerBloque(dctPas1, traspuesto);
			dct_1D(traspuesto, dctPas2);
			quantizarCoeficientes(dctPas2, cuantizados, 0);
			zigzag(cuantizados, bloqueOrdenado);
			generadorCodigos(bloqueOrdenado, 0); 

			prepararBloqueC(Cb, bloqueDCT); 
			dct_1D(bloqueDCT, dctPas1);
			transponerBloque(dctPas1, traspuesto);
			dct_1D(traspuesto, dctPas2);
			quantizarCoeficientes(dctPas2, cuantizados, 1);
			zigzag(cuantizados, bloqueOrdenado);
			generadorCodigos(bloqueOrdenado, 1); 

			prepararBloqueC(Cr, bloqueDCT); 
			dct_1D(bloqueDCT, dctPas1);
			transponerBloque(dctPas1, traspuesto);
			dct_1D(traspuesto, dctPas2);
			quantizarCoeficientes(dctPas2, cuantizados, 1);
			zigzag(cuantizados, bloqueOrdenado);
			generadorCodigos(bloqueOrdenado, 2); 

		}
	}
		
	terminarHuffman();
	free(IMAGEN);
	fclose(input_file);
	fclose(output_file);

}



