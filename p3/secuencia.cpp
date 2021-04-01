#include "secuencia.h"

void secuencia::registros() {

	if (reset.read()) {
		estado.write(0);
		reg_entra = 0; reg_anterior = 0; reg_sae = 0; reg_suma = 0;
	}
	else {
		valI.write(valInput.read());
		in.write(input->read());
		estado.write(estado_seguinte);
		if (!valI.read()) {
			return;
		}
		reg_sae = reg_anterior;
		reg_anterior = reg_entra;
		reg_entra = in.read();
		reg_suma += reg_entra;	
		bit_de_cambio.write(bit_de_cambio.read() + 1);
	}

}



void secuencia::evaluarFSM() {
	switch (estado.read()) { // fsm	
		case 0: 
			estado_seguinte = valI.read() ? 1 : 0;
			estado_anterior = 0;
			bingo->write(false);
			break;
		case 1:
			estado_anterior = 1;
			estado_seguinte = valI.read() ? ((in.read()>reg_entra) ? 2 : 1) : 4;
			bingo->write(false);
			break;
		case 2:
			estado_anterior = 2;
			estado_seguinte = valI.read() ? ((in.read()>reg_entra) ? 3 : 1) : 4;
			bingo->write(false);
			break;
		case 3: 
			estado_anterior = 3;
			estado_seguinte = valI.read() ? ((in.read()>reg_entra) ? 3 : 1) : 4;
			bingo->write(true);
			break;
		case 4:
			if (!valI.read()) {
				estado_seguinte = 4;
				bingo->write(false);
				break;
			}
			switch (estado_anterior)
			{
				case 1:
					estado_seguinte = (in.read()>reg_entra) ? 2 : 1;
					break;
				case 2: 
					estado_seguinte = (in.read()>reg_entra) ? 3 : 1;
					break;
				case 3:
					estado_seguinte = (in.read()>reg_entra) ? 3 : 1;
					break;
				default:
					break;
			}
			bingo->write(false);
		default:
			break;
	};
	res->write(reg_suma/3);
	if (!valI.read()) {
		return;
	}
	reg_suma -= reg_sae;
}
