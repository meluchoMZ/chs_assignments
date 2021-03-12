#include "systemc.h"

#include "duplicar.h"
#include "diferencia.h"


SC_MODULE(productor)
{
public:
	sc_in <bool> clk, reset;
	sc_out < sc_uint <8>> out;
	sc_out < bool> valido; 

SC_CTOR(productor) 
{
	fichero = fopen("./datosImagen.dat", "rt");
	if (!fichero) {
		cerr << "No se encuentra datosImagen.dat" << endl; 
		exit(-1);
	}
	contador = 0; 

	SC_METHOD(producir);
	sensitive << clk.pos();
}
void producir() 
{
	int dato;

	if (reset.read()) {
		out.write(0);
		valido.write(false);
	}
	else {
		if (contador < 2768) {
			fscanf(fichero, "%d ", &dato);
			out->write(dato);
			++contador;
			if (contador == 2768)
				fclose(fichero);
		}		
		valido.write(true);
	}
}
private:
	FILE* fichero;
	int contador; 
};

SC_MODULE(consumidor)
{
public:
	sc_in <bool> clk, reset;
	sc_in <bool> in, valido;


SC_CTOR(consumidor) 
{
	fichero = fopen("./resultadosImagen.dat", "rt");
	if (!fichero) {
		cerr << "No se encuentra resultadosImagen.dat" << endl;
		exit(-1);
	}
	contador = 0;
	SC_METHOD(consumir); 
	sensitive << clk.pos();
}

void consumir() 
{
	bool res;
	unsigned int check;

	if (reset.read()) return;
	
	if (valido.read()) {
		res = in.read();
		fscanf(fichero, "%d ", &check);
		if (check !=res)
			printf("ERROR %d != %d @ %d\n", res, check, contador);
		++contador;
		if (contador == 2768) {
			fclose(fichero);
			printf("FINAL\n");
			sc_stop();
		}
	}
}
private:
	FILE* fichero;
	int contador;
};



class top : public sc_module
{
public:

	sc_in<bool> clk, reset; 

// crear las señales que sean necesarias
sc_signal<bool> prod_out_x_dup_val, dup_y_x_dif_val, dup_z_y_dif_val, dif_z_in_cons_val, dif_cons;
sc_signal<sc_uint<8>> prod_dup, dup_yx_dif, dup_zy_dif;



productor *instProductor;
consumidor *instConsumidor;

duplicar* instDuplicador;
diferencia* instDiferencia;

SC_CTOR(top) 
{

// no es necesario instanciar las señales

	instProductor = new productor("productor");
	instConsumidor = new consumidor("consumidor");

	instDuplicador = new duplicar("Duplicar");
	instDiferencia = new diferencia("Diferencia");

// conectar todas las colas

	instProductor->clk(clk);
	instProductor->reset(reset);
	instProductor->out(prod_dup);
	instProductor->valido(prod_out_x_dup_val);

	instDuplicador->clk(clk);	
	instDuplicador->reset(reset);
	instDuplicador->X(prod_dup);
	instDuplicador->valX(prod_out_x_dup_val);
	instDuplicador->Y(dup_yx_dif);
	instDuplicador->valY(dup_y_x_dif_val);
	instDuplicador->Z(dup_zy_dif);
	instDuplicador->valZ(dup_z_y_dif_val);

	instDiferencia->clk(clk);
	instDiferencia->reset(reset);
	instDiferencia->X(dup_yx_dif);
	instDiferencia->valX(dup_y_x_dif_val);
	instDiferencia->Y(dup_zy_dif);
	instDiferencia->valY(dup_z_y_dif_val);
	instDiferencia->Z(dif_cons);
	instDiferencia->valZ(dif_z_in_cons_val);

	instConsumidor->clk(clk);
	instConsumidor->reset(reset);
	instConsumidor->in(dif_cons);
	instConsumidor->valido(dif_z_in_cons_val);


}
};





int sc_main(int nargs, char* vargs[]){

	sc_clock clk("clk", 1); // ciclo de 1 ns
	sc_signal <bool> reset;

	top moduloPrincipal("top");

	moduloPrincipal.clk(clk);		// conexión del reloj y el reset
	moduloPrincipal.reset(reset);

	reset.write(true); sc_start(2, SC_NS);		// 2 NS reseteando
	reset.write(false); sc_start(10, SC_SEC);	// libre para procesar
	return 0;
	   
}


