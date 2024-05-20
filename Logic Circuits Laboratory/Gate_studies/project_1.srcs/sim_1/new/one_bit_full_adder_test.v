`timescale 1ns / 1ps
module one_bit_full_adder_test();

    reg a,b,c;
    wire sum,carry;
    
    one_bit_full_adder uut(.i_1(a), .i_2(b), .cin(c), .s(sum), .cout(carry) );
    
    initial begin
    
        a=0; b=0; c=0; #50;
        a=0; b=0; c=1; #50;
        a=0; b=1; c=0; #50;
        a=0; b=1; c=1; #50;
        a=1; b=0; c=0; #50;
        a=1; b=0; c=1; #50;
        a=1; b=1; c=0; #50;
        a=1; b=1; c=1; #50;
    
    end
endmodule
