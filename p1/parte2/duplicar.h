#include "systemc.h"
#include "fifo.h"

SC_MODULE (duplicar) {
public:
sc_port<read_if_T<sc_uint<8>>>  X;
sc_port<write_if_T<sc_uint<8>>>  Y, Z;

  void replicar();

  SC_CTOR(duplicar) {
    cout<<"duplicar: "<<name()<<endl;

    SC_THREAD(replicar);
  } 

}; 

