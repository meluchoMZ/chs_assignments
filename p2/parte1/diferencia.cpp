#include "diferencia.h"

void diferencia::registros() {

	if (reset.read()) {
		x.write(0);
		y.write(0);
		valido.write(false);
	}
	else {
		if (valX.read() && valY.read() ) {
			x.write(X.read());
			y.write(Y.read());
			valido.write(true);
		}
		else {
			valido.write(false);
		}
	}
}



void diferencia::calcularDiferencia(){
	sc_int<9> dif;
	dif = X.read() - Y.read();
	if (dif < 0) {
		dif = 0 - dif;
	}
	if (dif < 6) {
		Z.write(true);
	} else {
		Z.write(false);
	}
	valZ.write(valido.read());
}

