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
    h_blank: in std_logic;
    v_blank: in std_logic);
end component;

subtype word16 is std_logic_vector (7 downto 0);

signal clk_sig: std_logic:='0';
signal rst_sig: std_logic:='0';
signal data_in_sig: word16:=(others => '0');
signal data_out_sig: word16:=(others => '0');
signal h_b_sig: std_logic:='0';
signal v_b_sig: std_logic:='0';

constant width:integer := 20;
constant height:integer := 10;
constant h_width:integer := 10;
constant v_width:integer := 5;

begin

uut: timing_State_Machine port map (
clk => clk_sig,
rst => rst_sig,
video_in => data_in_sig,
video_out => data_out_sig,
h_blank => h_b_sig,
v_blank => v_b_sig
);



clock: process begin
    clk_sig <='0';
    wait for 5 ns;
    clk_sig <='1';
    wait for 5 ns;
end process;

data: process begin
    
    for i in 1 to h_width loop
        wait until falling_edge(clk_sig);
        data_in_sig <= x"00";
        h_b_sig <= '1';
        v_b_sig <= '1';
    end loop;
    
    for j in 1 to height loop
        for i in 1 to width loop
            wait until falling_edge(clk_sig);
            data_in_sig <= std_logic_vector(to_unsigned(i,8));
            h_b_sig <= '0';
            v_b_sig <= '0';
        end loop;
        for i in 1 to h_width loop
            wait until falling_edge(clk_sig);
            data_in_sig <= x"00";
            h_b_sig <= '1';
            v_b_sig <= '0';
        end loop;
    end loop; 
    
    for i in 1 to v_width*(height + h_width) loop
        wait until falling_edge(clk_sig);
        data_in_sig <= x"00";
        h_b_sig <= '0';
        v_b_sig <= '1';
    end loop;
end process;


end Behavioral;
