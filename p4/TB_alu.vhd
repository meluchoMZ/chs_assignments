library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.ALL;
use IEEE.std_logic_textio.all;
use std.textio.all;



entity TB_alu is
end TB_alu;

architecture test of TB_alu is

	component ALU port (
        A, B : in unsigned(15 downto 0);
        Y : out unsigned(15 downto 0);
        aluOp : in unsigned(1 downto 0));
	end component;

signal A, B, Y : unsigned(15 downto 0);     -- señales para conectar la ALU
signal aluOp : unsigned(1 downto 0);        -- señal para conectar la ALU
signal checkY : unsigned(15 downto 0);  -- señal utilizada solo para visualizar durante la simulación

begin

	instancia: ALU port map(A => A, B => B, aluOp => aluOp, Y => Y);

	simulacion: process	
	file stimul_io : text is in "./alu_IN.txt";
	variable aline : line;	
	variable vA, vB, vY, vOp : integer; 
	variable v_res : unsigned (15 downto 0);
	
	begin
	
		loop
			
			if (not(endfile(stimul_io))) then
				readline(stimul_io, aline);
				read(aline, vA);
				read(aline, vB);
				read(aline, vOp);       -- lee las 3 entradas
                read(aline, vY);        -- lee el resultado también

			else
				assert false
					report "Se ha llegado al final del fichero de entrada. Comprobar si hay errores anteriores a este mensaje."
					severity failure;
			end if;


			A <= to_unsigned(vA, 16);
			B <= to_unsigned(vB, 16);
			aluOp <= to_unsigned(vOp, 2);
			
            wait for 500 ps;
            
			v_res := Y;	 -- valor calculado de Y			
            checkY <= to_unsigned(vY, 16);
     		
     		wait for 500 ps;       			
			
			assert (v_res = vY)  -- debe coincidir con el valor leido del fichero
				report "No coincide el valor de Y " & integer'image(to_integer(v_res)) & "  " & integer'image(vY)				
				severity error;						

		end loop;
	end process;
	 


end test;
