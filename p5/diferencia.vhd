library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;


entity diferencia is
  Port ( 
    clk, reset : in std_logic;
    Y, Z : in unsigned(7 downto 0);
    valY, valZ : in std_logic;    
    res, vRes : out std_logic
    );
end diferencia;

architecture rtl of diferencia is
 
    signal regY, regZ : unsigned(7 downto 0);
    signal regValido : std_logic;
    
signal dif, abso : signed(8 downto 0);
signal uY, uZ : unsigned(8 downto 0);
-- nota: dif, abso, uY y uZ podrían ser variables en el proceso "calculos"
--       pero entonces no serían visibles durante la simulación
--       y sería más complicado depurar los posibles errores

    
begin


vRes <= regValido; 	-- se puede poner fuera del proceso

calculos:process(regY, regZ, regValido, uZ, uY, regY, regZ, dif, abso)	-- lista de sensibilidad exhaustiva
begin
   
    
    uY <= "0" & regY;					-- extensión a 9 bits
    uZ <= "0" & regZ;
    
    dif <= signed(uY) - signed(uZ);		-- resta con signo
    
	-- (1) calcular aquí "abso" a partir de "dif"
	if dif < 0 then
    		abso <= 0-dif;
	else
		abso <= dif;
	end if;
	
    -- (2) res = 1 si abso < 6, y cero en caso contrario
	if abso < 6 then
		res <= '1';
	else 
		res <= '0';
	end if;
	vRes <= '1';

end process;

    
sync:process(clk, reset, Y, Z, valZ, valY)
begin

  if rising_edge( clk ) then
    if reset = '1' then
      regZ <= x"00";
      regY <= x"00";
      regValido <= '0';
    else
	
      -- (3) registra aquí las entradas del circuito
	  
      regZ <= Z;
      regY <= Y;
      regValido <= valY and valZ;
    end if;
  end if;

end process;    


end rtl;
