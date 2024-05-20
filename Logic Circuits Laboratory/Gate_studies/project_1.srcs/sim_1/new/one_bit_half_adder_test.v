`timescale 1ns / 1ps
module one_bit_half_adder_test();

    reg a,b;
    wire sum,carry;
    
    one_bit_half_adder uut(.i_1(a), .i_2(b), .s(sum), .c(carry) );
    
    initial begin
        a=0; b=0; #50;
        a=0; b=1; #50;
        a=1; b=0; #50;
        a=1; b=1; #50;
    end

endmodule
