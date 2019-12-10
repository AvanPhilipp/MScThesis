----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10/15/2019 02:42:52 PM
-- Design Name: 
-- Module Name: timing_state_machine_tb - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity timing_state_machine_tb is
--  Port ( );
end timing_state_machine_tb;

architecture Behavioral of timing_state_machine_tb is

component timing_State_Machine is
    Port (
    clk: in std_logic;
    rst: in std_logic;
    video_in: in std_logic_vector (7 downto 0);
    video_out: out  std_logic_vector (7 downto 0);
    h_blank: out std_logic;
    v_blank: out std_logic);
end component;

subtype word16 is std_logic_vector (7 downto 0);

signal clk_sig: std_logic:='0';
signal rst_sig: std_logic:='0';
signal data_in_sig: word16:=(others => '0');
signal data_out_sig: word16:=(others => '0');
signal h_out_sig: std_logic:='0';
signal v_out_sig: std_logic:='0';


begin

uut: timing_State_Machine port map (
clk => clk_sig,
rst => rst_sig,
video_in => data_in_sig,
video_out => data_out_sig,
h_blank => h_out_sig,
v_blank => v_out_sig
);

clock: process begin
    clk_sig <='0';
    wait for 5 ns;
    clk_sig <='1';
    wait for 5 ns;
end process;

data_process : process begin

    for j in 1 to 10 loop
        for i in 1 to 20 loop
            wait until falling_edge(clk_sig);
            data_in_sig <= x"00";
        end loop;
    
        wait until falling_edge(clk_sig);
        data_in_sig <=x"ff";
        wait until falling_edge(clk_sig);
        data_in_sig <=x"00";
        wait until falling_edge(clk_sig);
        data_in_sig <=x"00";
        wait until falling_edge(clk_sig);
        data_in_sig <=x"80";
        
        for i in 1 to 40 loop
            wait until falling_edge(clk_sig);
            data_in_sig <= std_logic_vector(to_unsigned(i, 8));
        end loop;
    
    
        wait until falling_edge(clk_sig);
        data_in_sig <=x"ff";
        wait until falling_edge(clk_sig);
        data_in_sig <=x"00";
        wait until falling_edge(clk_sig);
        data_in_sig <=x"00";
        wait until falling_edge(clk_sig);
        if(j/=10) then
            data_in_sig <=x"9d";
        else
            data_in_sig <=x"B6";
        end if;
    end loop;
    
    for j in 1 to 5 loop
        for i in 1 to 68 loop
            wait until falling_edge(clk_sig);
            data_in_sig <= x"00";
        end loop;
    end loop;
    
end process;

assert(data_out_sig = x"00" and (h_out_sig = '1' or v_out_sig = '1')) 
report("data out false active");


end Behavioral;
