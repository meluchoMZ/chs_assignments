all:
	ghdl -s practica_2_2.vhd duplicar.vhd diferencia.vhd
	ghdl -s --ieee=synopsys TB_practica_2_2.vhd
	ghdl -a practica_2_2.vhd duplicar.vhd diferencia.vhd
	ghdl -a --ieee=synopsys TB_practica_2_2.vhd
	ghdl -e --ieee=synopsys TB_practica_2_2
	ghdl -r --ieee=synopsys TB_practica_2_2 --vcd=resultados.vcd
