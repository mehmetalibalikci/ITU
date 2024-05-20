`timescale 1ns / 1ps

module one_bit_half_adder(input i_1,i_2, output s,c);
    
    xor_gate u1(i_1,i_2,s);
    and_gate u2(i_1,i_2,c);

endmodule
