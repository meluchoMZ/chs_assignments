#include "systemc.h"

SC_MODULE (duplicar) {
public:

sc_in <bool> clk, reset;

sc_in < sc_uint <8>> X;
sc_in <bool> valX;
sc_out < sc_uint <8>> Y, Z;
sc_out <bool> valY, valZ;

  void registros(); 
  void replicar();

  SC_CTOR(duplicar) {
    cout<<"duplicar: "<<name()<<endl;
	FIRE = false;
    SC_METHOD(replicar);
    sensitive << FIRE;
    SC_METHOD(registros);
    sensitive << clk.pos();  // reset asíncrono
  } 
private:
    sc_uint <8> a, b, c; 
    bool valido;
    sc_signal <bool> FIRE;
}; 

