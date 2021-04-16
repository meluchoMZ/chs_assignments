-- ALU simplificada --
-- Author: Miguel Blanco Godón --

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity alu is 
	port
	(
	 	A, B : in unsigned(15 downto 0);
		Y : out unsigned(15 downto 0);
		aluOp : in unsigned(1 downto 0)
	);
end entity alu;

architecture alu_behav of alu is
begin
	Y <= A + B when aluOp = "00" else
		A - B when aluOp = "01" else
		A and B when aluOp = "10" else A or B;
end architecture alu_behav;
