library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.numeric_std.ALL;
use IEEE.std_logic_textio.all;
use std.textio.all;



entity TB_practica_2_2 is

end TB_practica_2_2;

architecture Behavioral of TB_practica_2_2 is

	component practica_2_2 port (
    clk, reset : in std_logic;
    X : in unsigned(7 downto 0);
    valX : in std_logic;    
    res, vRes : out std_logic);
	end component;

signal X : unsigned(7 downto 0);            -- señales para conectar   
signal valX, res, vRes : std_logic;
signal dummy1, dummy2, dummy3, check : std_logic_vector(0 downto 0);
signal clk : std_logic := '0';
signal reset : std_logic := '1';

begin

	instancia: practica_2_2 port map(       -- instancia aquí la ALU, conectando todos sus puertos
	    clk, reset, X, valX, res, vRes
		);

	reloj: process
		variable i : integer;
	begin
		for i in 1 to 7020 loop
			clk <= not clk;
			wait for 0.5 ns;
		end loop;
		wait;
	end process;

	-- creando el reset
	ini: process
	begin
		reset<='1';
		wait until clk'event and clk='1';
		reset<='0' after 2 ns;
		wait;
	end process;	
	


	simulacion: process	
	file stimul_io : text is in "./practica_2_2_IN.txt";
	variable aline, oline: line;	
	variable i_X, i_valX  : integer; 
	variable o_res, o_vRes : integer;
	variable C_res, C_vRes : integer;  
	variable dummyA, dummyB, dummyC : std_logic_vector(0 downto 0);
	
	begin
	
		wait until reset'event and reset = '0';
	
		loop
		
			wait until clk'event and clk = '1';
		    wait for 0 ns;
			
			if (not(endfile(stimul_io))) then
				readline(stimul_io, aline);
				read(aline, i_X);
				read(aline, i_valX);
				read(aline, o_res);       
                read(aline, o_vRes);  

			else
				assert false
					report "Se ha llegado al final del fichero de entrada. Comprobar si hay errores anteriores a este mensaje."
					severity failure;
					file_close(stimul_io);
			end if;



			X <= to_unsigned(i_X, 8);
			dummyA := std_logic_vector(to_unsigned(i_valX, 1));						
			valX <= dummyA(0);
			dummyB := std_logic_vector(to_unsigned(o_res, 1));						
			dummyC := std_logic_vector(to_unsigned(o_vRes, 1));	
			
			check <= dummyB;
			
            wait for 500 ps;
            
            dummy2(0) <= res;
            dummy3(0) <= vRes;  
			C_res := to_integer(unsigned(dummy2));
			C_vRes := to_integer(unsigned(dummy3));

			
			assert (C_res = o_res)  -- debe coincidir con el valor leido del fichero
				report "No coincide el valor de res " & integer'image(C_res) & "  " & integer'image(o_res)				
				severity error;						

			assert (C_vRes = o_vRes)  -- debe coincidir con el valor leido del fichero
				report "No coincide el valor de validez "  & integer'image(C_vRes) & "  " & integer'image(o_vRes)				
				severity error;		

		end loop;
	end process;



end Behavioral;
