`timescale 1ns / 1ps

module three_to_eight_decoder_test();

    reg A,B,C;
    
    wire d0,d1,d2,d3,d4,d5,d6,d7;
    
    three_to_eight_decoder uut(.i_1(A), .i_2(B), .i_3(C), .D0(d0),.D1(d1),.D2(d2),.D3(d3),.D4(d4),.D5(d5),.D6(d6),.D7(d7));
    
    initial begin
        A=0; B=0; C=0; #100;
        A=0; B=0; C=1; #100;
        A=0; B=1; C=0; #100;
        A=0; B=1; C=1; #100;
        A=1; B=0; C=0; #100;
        A=1; B=0; C=1; #100;
        A=1; B=1; C=0; #100;
        A=1; B=1; C=1; #100;
    end
endmodule
