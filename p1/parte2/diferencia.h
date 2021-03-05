#include "systemc.h"
#include "fifo.h"

SC_MODULE (diferencia) {
public:
sc_port<read_if_T<sc_uint<8>>>  X, Y;
sc_port<write_if_T<bool>>  Z;

  void calcularDiferencia();

  SC_CTOR(diferencia) {
    cout<<"diferencia: "<<name()<<endl;

    SC_THREAD(calcularDiferencia);
  } 

}; 

