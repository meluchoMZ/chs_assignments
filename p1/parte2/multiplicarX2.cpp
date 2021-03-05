#include "multiplicarX2.h"

void multiplicarX2::multiply(void)
{
	sc_uint<8> val;
	while (true)
	{
		input->read(val);
		val = val * 2;
		output->write(val);
	}
}
