`timescale 1ns / 1ps
module and_gate_four(i_1,i_2,i_3,i_4,o);
    
    input wire i_1,i_2,i_3,i_4;
    
    output wire o;
    
    assign o = i_1 & i_2 & i_3 & i_4;

endmodule
