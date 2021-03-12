#include "diferencia.h"

void diferencia::registros() {

	if (reset.read()) {
		x = 0;
		y = 0;
		valido = false;
	}
	else {
		if (valX.read() && valY.read() ) {
			x = X.read();
			y = Y.read();
			valido = true;
		}
		else {
			valido = false;
		}
	}
	FIRE.write(!FIRE.read());
}



void diferencia::calcularDiferencia(){
	sc_int<9> dif;
	dif = x - y;
	if (dif < 0) {
		dif = 0 - dif;
	}
	if (dif < 6) {
		Z.write(true);
	} else {
		Z.write(false);
	}
	valZ.write(valido);
}

