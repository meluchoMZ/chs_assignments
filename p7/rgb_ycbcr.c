#define OP3x1_1(D1, S1, S2, S3) \
	asm volatile ("mlanv %0, %1, %2, %3" : \
			"=&r"(D1) : "r"(S1), \
			"r"(S2), "r"(S3));

void RGB_YCbCr(	unsigned char *RGB, 
						unsigned char *Y, unsigned char *Cb, unsigned char *Cr)
{

	// avísase ao compilador que imos utilizar estas variables extensivamente para que as meta en rexistros
	register int acc1, acc2, acc3;

	//*Y = (RGB[0] * 19595 + RGB[1] * 38470 + RGB[2] * 7471 + 32768) >> 16;
	//*Cb = (RGB[0] * (-11059) + RGB[1] * (-21709) + RGB[2] * 32768 + 8388608 + 32767) >> 16;
	//*Cr = (RGB[0] * 32768 - RGB[1] * 27439 - RGB[2] * 5329 + 8388608 + 32767) >> 16;
	
	// intercálanse as instruccións para minimizar dependencias de datos
	OP3x1_1(acc1, RGB[0], 19595, 32768); //Y
	OP3x1_1(acc2, RGB[0], -11059, 8421375); // CB
	OP3x1_1(acc3, RGB[1], -27439, 8421375); // CR
	OP3x1_1(acc1, RGB[1], 38470, acc1); // Y
	OP3x1_1(acc2, RGB[1], -21709, acc2); // CB
	OP3x1_1(acc3, RGB[2], -5329, acc3); // CR
	OP3x1_1(acc1, RGB[2], 7471, acc1); //  Y
	// como 32768 = 2^15 podemos evitar a multiplicación
	acc2 += RGB[2] << 15; // CB
	acc3 += RGB[0] << 15; // CR
	*Y = acc1 >> 16;
	*Cb = acc2 >> 16;
	*Cr = acc3 >> 16;
}

/*
void RGB_YCbCr(	unsigned char *R, unsigned char *G, unsigned char *B, 
						unsigned char *Y, unsigned char *Cb, unsigned char *Cr)
{
	int k;

	for(k=0; k<256; ++k){
		Y[k] = (R[k] * 19595 + G[k] * 38470 + B[k] * 7471 + 32768) >> 16;
		Cb[k] = (R[k] * (-11059) + G[k] * (-21709) + B[k] * 32768 + 8388608 + 32767) >> 16;
		Cr[k] = (R[k] * 32768 - G[k] * 27439 - B[k] * 5329 + 8388608 + 32767) >> 16;
	}

}*/
