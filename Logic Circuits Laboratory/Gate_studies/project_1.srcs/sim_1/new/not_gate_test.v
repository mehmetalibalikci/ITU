`timescale 1ns / 1ps

module not_gate_test();
    
    reg A;
    
    wire o;
    
    not_gate uut(.i_1(A), .o(o) );
    
    initial begin 
    
        A=0; #250;
        A=1; #250;     
    end
endmodule
