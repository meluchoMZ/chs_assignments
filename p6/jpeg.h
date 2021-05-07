#ifndef _MIS_FUNCIONES__H
#define _MIS_FUNCIONES__H

#define SIZE (256*256*3)
#define esDC 0
#define esAC 1

void codificaJPEG(FILE *input_file, FILE *output_file);
int cargaImagen(FILE *fin, unsigned char *IMAGEN);
void ponerCabecera(FILE *outp);
void RGB_YCbCr(	unsigned char *RGB, unsigned char *Y, unsigned char *Cb, unsigned char *Cr);
void prepararBloqueY(unsigned char *Y, short *bloque);
void prepararBloqueC(unsigned char *Y, short *bloque);
void jpeg_fdct_ifast (short * data);
void dct_1D (short *data, short *res);
void transponerBloque(short *original, short *traspuesto);
void quantizarCoeficientes(short *datos, short *cuantizados, int tipoBlock);
void zigzag(short *block, short *ordenado);
void generadorCodigos(short *block, int tipoBlock);
void procesadorValores(int dcAC, int tipoBlock, int RL, short valor);
void emiteBits(unsigned short code, int size);

void terminarHuffman();

#endif

