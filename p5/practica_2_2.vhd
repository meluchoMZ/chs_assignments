library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;


entity practica_2_2 is
  Port ( 
    clk, reset : in std_logic;
    X : in unsigned(7 downto 0);
    valX : in std_logic;    
    res, vRes : out std_logic
    );
end practica_2_2;


architecture rtl of practica_2_2 is
 
    signal qY, qZ : unsigned(7 downto 0);
    signal vY, vZ : std_logic;
    
    component duplicar
        Port ( 
        clk, reset : in std_logic;
        X : in unsigned(7 downto 0);
        valX : in std_logic;    
        Y, Z : out unsigned(7 downto 0);
        valY, valZ : out std_logic
        ); 
    end component;        
        
    component diferencia
        Port ( 
        clk, reset : in std_logic;
        Y, Z : in unsigned(7 downto 0);
        valY, valZ : in std_logic;    
        res, vRes : out std_logic
        );            
    end component;            
        
begin
   
   instDup:duplicar port map(  clk => clk, reset => reset, X => X, valX => valX, Y => qY, Z => qZ, valY => vY, valZ => vZ);
   
   instDif:diferencia port map(  clk => clk, reset => reset, Z => qZ, valZ => vZ, Y => qY, valY => vY, res => res, vRes => vRes);
   
   
   
end rtl;