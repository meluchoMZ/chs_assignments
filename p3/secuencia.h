#include "systemc.h"

SC_MODULE (secuencia) {
public:

sc_in <bool> clk, reset;
sc_in < sc_uint <8>> input;
sc_in <bool> valInput;
sc_out<bool> bingo;
sc_out<sc_uint<8>> res;

  void evaluarFSM();
  void registros();

  SC_CTOR(secuencia) {
    cout<<"secuencia: "<<name()<<endl;

    SC_METHOD(evaluarFSM);
    sensitive << in << bit_de_cambio; 
    SC_METHOD(registros);
    sensitive << clk.pos(); 

  } 

private: 
	sc_signal<sc_uint<3>> estado;
	sc_uint<3> estado_seguinte, estado_anterior;
	sc_signal<sc_uint<8>> in;
	sc_signal<bool> valI;
	sc_signal<sc_uint<1>> bit_de_cambio;
	sc_uint<8> reg_entra, reg_anterior, reg_sae;
	sc_uint<10> reg_suma;
}; 

