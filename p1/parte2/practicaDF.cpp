#include "systemc.h"
#include "fifo.h"
// añadir las cabeceras necesarias
//#include ".h"
#include "multiplicarX2.h"
#include "duplicar.h"
#include "diferencia.h"


SC_MODULE(productor)
{
public:
sc_port<write_if_T<sc_uint<8>>> out; // producer output port

SC_CTOR(productor) 
{
	fichero = fopen("./datosImagen.dat", "rt");
	if (!fichero) {
		cerr << "No se encuentra datosImagen.dat" << endl; 
		exit(-1);
	}
	SC_THREAD(producir); 
}
void producir() 
{
	int i, dato;

	for(i=0; i<2768; ++i){
		fscanf(fichero, "%d ", &dato);
		out->write(dato); 
	}
	fclose(fichero);
	while (true) {
		wait(SC_ZERO_TIME);
	} 
}
private:
	FILE* fichero;
};

SC_MODULE(consumidor)
{
public:
sc_port<read_if_T< bool >> in; 

SC_CTOR(consumidor) 
{
	fichero = fopen("./resultadosImagen.dat", "rt");
	if (!fichero) {
		cerr << "No se encuentra resultadosImagen.dat" << endl;
		exit(-1);
	}
	SC_THREAD(consumir); 
}

void consumir() 
{
	bool val;
	unsigned int check, i;
	
	for(i=0; i<2768; ++i){	
		in->read(val); // valor calculado leído de la FIFO
		fscanf(fichero, "%d ", &check);
		if(check != val)
			printf("ERROR %d != %d @ %d\n", val, check, i);
	}
	fclose(fichero);
	printf("FINAL\n");
	sc_stop();
}
private:
	FILE* fichero;
};



class top : public sc_module
{
public:
// crear las colas que sean necesarias
fifo_T<sc_uint<8>> *Qprod_mul, *Qmul_dup, *QdupYdif, *QdupZdif;
fifo_T<bool> *Qdif_consumer;


productor *instProductor;
consumidor *instConsumidor;
// añadir los módulos que sean necesarion
duplicar *duplicador;
diferencia *diferenciador;

SC_CTOR(top) 
{

// instanciar la colas que se hayan creado

	Qprod_mul = new fifo_T<sc_uint<8>>("Q_productor_multiplicador", 1);
	Qmul_dup = new fifo_T<sc_uint<8>>("Q_multiplicador_duplicador", 1);
	QdupYdif = new fifo_T<sc_uint<8>>("Q_duplicador_Y_diferencia", 1);
	QdupZdif = new fifo_T<sc_uint<8>>("Q_duplicador_Z_diferencia", 1);
	Qdif_consumer = new fifo_T<bool>("Q_diferencia_consumidor", 1);

	instProductor = new productor("productor");
	instConsumidor = new consumidor("consumidor");
// instanciar los módulos necesarios
	multiplicarX2 *multiplicador = new multiplicarX2("multiplicador");
	duplicar *duplicador = new duplicar("duplicador");
	diferencia *diferenciador = new diferencia("diferenciador");

// conectar todas las colas
	instProductor->out(*Qprod_mul );
	multiplicador->input(*Qprod_mul);
	multiplicador->output(*Qmul_dup);
	duplicador->X(*Qmul_dup);
	duplicador->Y(*QdupYdif);
	duplicador->Z(*QdupZdif);
	diferenciador->X(*QdupYdif);
	diferenciador->Y(*QdupZdif);
	diferenciador->Z(*Qdif_consumer);
	instConsumidor->in(*Qdif_consumer);

}
};





int sc_main(int nargs, char* vargs[]){

	top principal("top");
	sc_start();
	return 0;

}


