#include "systemc.h"

#include "secuencia.h"

// DESCOMENTA LA LÍNEA QUE SE CORRESPONDE CON LA PRÁCTICA QUE SE TE HA ASIGNADO

//   char NOMBRE_FICHERO_RESULTADOS[] = "..\\resultadosSecuencia_AscenMax.dat";
//   char NOMBRE_FICHERO_RESULTADOS[] = "..\\resultadosSecuencia_DescMax.dat";
//   char NOMBRE_FICHERO_RESULTADOS[] = "..\\resultadosSecuencia_AscenMin.dat";
//   char NOMBRE_FICHERO_RESULTADOS[] = "..\\resultadosSecuencia_DescMin.dat";
//   char NOMBRE_FICHERO_RESULTADOS[] = "..\\resultadosSecuencia_AscenMedio.dat";
//   char NOMBRE_FICHERO_RESULTADOS[] = "..\\resultadosSecuencia_DescMedio.dat";
	char NOMBRE_FICHERO_RESULTADOS[] = "./resultadosSecuencia_AscenPromedio.dat";



SC_MODULE(productor)
{
public:
	sc_in <bool> clk, reset;
	sc_out < sc_uint <8>> out;
	sc_out < bool> valido; 

SC_CTOR(productor) 
{
	fichero = fopen("./datosSecuencia.dat", "rt");
	if (!fichero) {
		cerr << "No se encuentra datosSecuencia.dat" << endl; 
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
		if (contador < 2000) {
			fscanf(fichero, "%d ", &dato);
			out->write(dato);
			valido.write( dato < 256); // habrá datos inválidos en mitad de la secuencia
			++contador;
			if (contador == 2000)
				fclose(fichero);
		}		
		
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
	sc_in <bool> bingo;
	sc_in <sc_uint<8>> res;

SC_CTOR(consumidor) 
{
	fichero = fopen(NOMBRE_FICHERO_RESULTADOS, "rt");
	if (!fichero) {
		cerr << "No se encuentra " << NOMBRE_FICHERO_RESULTADOS <<endl;
		exit(-1);
	}
	contador = 0;
	SC_METHOD(consumir); 
	sensitive << clk.pos();
}

void consumir() 
{
	sc_uint<8> resultado;
	unsigned int check;

	if (reset.read()) return;
	
	if (bingo.read()) {
		resultado = res.read();
		fscanf(fichero, "%d ", &check);
		if (check != resultado.to_int())
			printf("ERROR %d != %d @ %d\n", resultado.to_int(), check, contador);
		++contador;
		if (contador == 300) {
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

	sc_signal<sc_uint<8>> dato, res;
	sc_signal<bool> vDato, bingo;

productor *instProductor;
consumidor *instConsumidor;
secuencia* instSecuencia;

SC_CTOR(top) 
{


	instProductor = new productor("productor");
	instConsumidor = new consumidor("consumidor");
	instSecuencia = new secuencia("secuencia");

	// instanciar y conectar el módulo secuencia

	instProductor->clk(clk);
	instProductor->reset(reset);
	instProductor->out(dato);
	instProductor->valido(vDato);

	instSecuencia->clk(clk);
	instSecuencia->reset(reset);
	instSecuencia->input(dato);
	instSecuencia->valInput(vDato);
	instSecuencia->res(res);
	instSecuencia->bingo(bingo);

	instConsumidor->clk(clk);
	instConsumidor->reset(reset);
	instConsumidor->res(res);
	instConsumidor->bingo(bingo);


}
};





int sc_main(int nargs, char* vargs[]){

	sc_clock clk("clk", 1); // ciclo de 1 ns
	sc_signal <bool> reset;

	top moduloPrincipal("top");

	moduloPrincipal.clk(clk);
	moduloPrincipal.reset(reset);

	reset.write(true); sc_start(2, SC_NS);
	reset.write(false); sc_start(10, SC_SEC);
	return 0;
	   
}


