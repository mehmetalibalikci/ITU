`timescale 1ns / 1ps
module and_gate_four_test();

    reg A,B,C,D;
    
    wire o;
    
    and_gate_four uut(.i_1(A), .i_2(B), .i_3(C), .i_4(D), .o(o) );
    
    initial begin
    
        A=0; B=0; C=0; D=0; #100;
        A=0; B=0; C=0; D=1; #100; 
        A=0; B=0; C=1; D=0; #100;
        A=0; B=0; C=1; D=1; #100; 
        A=0; B=1; C=0; D=0; #100; 
        A=1; B=1; C=0; D=1; #100; 
        A=1; B=1; C=1; D=0; #100; 
        A=1; B=1; C=1; D=1; #100;
    end

endmodule
