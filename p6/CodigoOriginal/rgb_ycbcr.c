void RGB_YCbCr(	unsigned char *RGB, 
						unsigned char *Y, unsigned char *Cb, unsigned char *Cr)
{

	*Y = (RGB[0] * 19595 + RGB[1] * 38470 + RGB[2] * 7471 + 32768) >> 16;
	*Cb = (RGB[0] * (-11059) + RGB[1] * (-21709) + RGB[2] * 32768 + 8388608 + 32767) >> 16;
	*Cr = (RGB[0] * 32768 - RGB[1] * 27439 - RGB[2] * 5329 + 8388608 + 32767) >> 16;

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
