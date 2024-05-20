`timescale 1ns / 1ps

module xor_gate_test();

    reg A;
    reg B;
    
    wire o;
    
    xor_gate uut(.i_1(A), .i_2(B), .o(o) );
    
    initial begin
        A=0; B=0; #250;
        A=1; B=0; #250;
        A=0; B=1; #250;
        A=1; B=1; #250;
    end
endmodule
