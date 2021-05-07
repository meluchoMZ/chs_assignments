// Versión "simplificada" de código original del Independent JPEG Group


void prepararBloqueY(unsigned char *Y, short *bloque){

	int i, j, p=0, q=0;
			
	for(i=0; i<8; ++i){
		for(j=0; j<8; ++j)
			bloque[p++] = ((unsigned short)Y[q++])-128;
		q+=8; // para pasar a la fila de abajo
	}

}

void prepararBloqueC2(short temp[][8], short *bloque){

	int i, j, p=0, q=0;
			
	for(i=0; i<16; i+=2){
		for(j=0; j<8; ++j){
			bloque[p++] = ((temp[i][j] + temp[i+1][j]) >> 2) - 128;
		}
	}
}

void prepararBloqueC(unsigned char *C, short *bloque){

	int i, j,q=0;
	short temp[16][8];
			
	for(i=0; i<16; ++i){
		for(j=0; j<8; ++j){
			temp[i][j] = C[q] + C[q+1];
			q+=2;
		}
	}

	prepararBloqueC2(temp, bloque);
}


#define FIX_0_382683433  ((short)   98)		/* FIX(0.382683433) */
#define FIX_0_541196100  ((short)  139)		/* FIX(0.541196100) */
#define FIX_0_707106781  ((short)  181)		/* FIX(0.707106781) */
#define FIX_1_306562965  ((short)  334)		/* FIX(1.306562965) */

#define MULTIPLY(var,const)  ((short) ((((var) * (const)) + 128) >> 8))



void transponerBloque(short *original, short *traspuesto){

	short *o, *t;
	int i, j;

	o = original;	t = traspuesto;

	for(i=0; i<8; ++i){
		for(j=0; j<8; ++j){
			*t = *o;
			t++;
			o += 8;
		}
		o -= 63; // volvemos al principio de la siguiente columna
	}
}


void dct_1D (short *data, short *res){

  short tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  short tmp10, tmp11, tmp12, tmp13;
  short z1, z2, z3, z4, z5, z11, z13;
  short *dataptr, *dataOut;
  short ctr;

  dataptr = data;
  dataOut = res;
  for (ctr = 7; ctr >= 0; ctr--) {
    tmp0 = dataptr[0] + dataptr[7];
    tmp7 = dataptr[0] - dataptr[7];
    tmp1 = dataptr[1] + dataptr[6];
    tmp6 = dataptr[1] - dataptr[6];
    tmp2 = dataptr[2] + dataptr[5];
    tmp5 = dataptr[2] - dataptr[5];
    tmp3 = dataptr[3] + dataptr[4];
    tmp4 = dataptr[3] - dataptr[4];
    
    tmp10 = tmp0 + tmp3;	
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;
    
    dataOut[0] = tmp10 + tmp11; 
    dataOut[4] = tmp10 - tmp11;
    
    z1 = MULTIPLY(tmp12 + tmp13, FIX_0_707106781); 
    dataOut[2] = tmp13 + z1;
    dataOut[6] = tmp13 - z1;
    
    tmp10 = tmp4 + tmp5;	
    tmp11 = tmp5 + tmp6;
    tmp12 = tmp6 + tmp7;
  
    z5 = MULTIPLY(tmp10 - tmp12, FIX_0_382683433); 
    z2 = MULTIPLY(tmp10, FIX_0_541196100) + z5; 
    z4 = MULTIPLY(tmp12, FIX_1_306562965) + z5;
    z3 = MULTIPLY(tmp11, FIX_0_707106781);

    z11 = tmp7 + z3;		
    z13 = tmp7 - z3;

    dataOut[5] = z13 + z2;	
    dataOut[3] = z13 - z2;
    dataOut[1] = z11 + z4;
    dataOut[7] = z11 - z4;

    dataptr += 8;		// avanza a la siguiente fila de datos
	dataOut += 8;
  }
}

