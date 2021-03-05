#include <systemc.h>
#include <fifo.h>

SC_MODULE (multiplicarX2)
{
	public:
		sc_port<read_if_T<sc_uint<8>>> input;
		sc_port<write_if_T<sc_uint<8>>> output;

		void multiply(void);

		SC_CTOR (multiplicarX2)
		{
			cout << "multiplicarX2" << name() << endl;
			SC_THREAD (multiply);
		}
};
