`timescale 1ns / 1ps
module not_gate(i_1, o);
    input wire i_1;
    
    output wire o;
    
    assign o = ~i_1;
endmodule
