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

    SC_METHOD(calcularDiferencia);
    sensitive << x << y << valido ; 
    SC_METHOD(registros);
    sensitive << clk.pos(); // reset asíncrono

  } 

private: 
    sc_signal<sc_uint<8>> x, y;
    sc_signal <bool> valido;
}; 

