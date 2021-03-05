#include"duplicar.h"

void duplicar::replicar(){

	sc_uint<8> a, b, c;

	b = c = 0; 
	while(true){

		X->read(a);
		Y->write(a);
		Z->write(c);
		c = b; 
		b = a; 
	}

}
