`timescale 1ns / 1ps
module nand_gate(
    input i_1,i_2,
    output o
    );
    
    assign o = ~(i_1 & i_2);
    
    
endmodule
