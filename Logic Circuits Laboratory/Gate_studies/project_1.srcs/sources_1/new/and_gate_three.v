`timescale 1ns / 1ps

module and_gate_three( i_1,i_2,i_3,o);
    input wire i_1,i_2,i_3;
    
    output wire o;
    
    assign o = i_1 & i_2 & i_3 ;
    
endmodule
