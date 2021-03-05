#include "diferencia.h"


void diferencia::calcularDiferencia(){

	sc_uint<8> x, y;
	sc_int<9> dif;

	while(true){
		X->read(x);
		Y->read(y);
		dif = x - y;
		if (dif<0) {
			dif = 0-dif;
		}
		if(dif<6) {
			dif = true;
		} else {
			dif = false;
		}
		Z->write(dif);
	}
}

