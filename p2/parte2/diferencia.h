#include "systemc.h"

SC_MODULE (diferencia) {
public:

sc_in <bool> clk, reset;
sc_in<sc_uint<8>> X, Y;
sc_in<bool> valX, valY;

sc_out<bool> Z, valZ;

  void calcularDiferencia();
  void registros();

  SC_CTOR(diferencia) {
    cout<<"diferencia: "<<name()<<endl;
	FIRE = false;
    SC_METHOD(calcularDiferencia);
    sensitive << FIRE; 
    SC_METHOD(registros);
    sensitive << clk.pos(); // reset asíncrono

  } 

private: 
    sc_uint<8> x, y;
    bool valido;
    sc_signal <bool> FIRE;
}; 

