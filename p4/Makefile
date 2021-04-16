all:
	ghdl -s alu.vhd
	ghdl -s --ieee=synopsys TB_alu.vhd
	ghdl -a alu.vhd
	ghdl -a --ieee=synopsys TB_alu.vhd
	ghdl -e --ieee=synopsys TB_alu
	ghdl -r --ieee=synopsys TB_alu --vcd=resultados.vcd
