library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;


entity duplicar is
  Port ( 
    clk, reset : in std_logic;
    X : in unsigned(7 downto 0);
    valX : in std_logic;    
    Y, Z : out unsigned(7 downto 0);
    valY, valZ : out std_logic
    );
end duplicar;

architecture rtl of duplicar is
 
    signal a, b, c : unsigned(7 downto 0);
    signal valido : std_logic;
begin

replicar:process(a, c, valido)
begin

    Y <= a; 
    Z <= c;
    valY <= valido;
    valZ <= valido;
    
end process;
    
    
sync:process(clk, reset, X, valX, a, b, c, valido)
begin

  if rising_edge( clk ) then
    if reset = '1' then
      a <= x"00";
      b <= x"00";
      c <= x"00";
      valido <= '0';
    else
      c <= b;
      b <= a;
      a <= X;
      valido <= valX;
    end if;
  end if;

end process;    


end rtl;