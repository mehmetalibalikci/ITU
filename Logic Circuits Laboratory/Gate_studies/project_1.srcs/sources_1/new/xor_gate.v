`timescale 1ns / 1ps

module xor_gate(i_1, i_2, o);
    
    input wire i_1;
    input wire i_2;
    
    output wire o;
    
    assign o = i_1 ^ i_2;
endmodule
