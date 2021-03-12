#include"duplicar.h" 

void duplicar::registros() {

	if (reset.read()) {
		a.write(0);
		b.write(0);
		c.write(0);
		valido.write(false);
	}
	else {
		if (valX.read()) {
			c.write(b.read());
			b.write(a.read());
			a.write(X.read());
		}
		valido.write( valX.read() );
	}
}

void duplicar::replicar(){

	Y.write(a.read());
	Z.write(c.read());
	valY.write(valido.read());
	valZ.write(valido.read());

}
