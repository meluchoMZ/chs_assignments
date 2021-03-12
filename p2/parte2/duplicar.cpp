#include"duplicar.h" 

void duplicar::registros() {

	if (reset.read()) {
		a = 0; b = 0; c = 0;
		valido = false;
	}
	else {
		if (valX.read()) {
			c = b;
			b = a;
			a = X.read();
		}
		valido = valX.read();
	}
	FIRE.write(!FIRE.read());
}

void duplicar::replicar(){

	Y.write(a);
	Z.write(c);
	valY.write(valido);
	valZ.write(valido);

}
