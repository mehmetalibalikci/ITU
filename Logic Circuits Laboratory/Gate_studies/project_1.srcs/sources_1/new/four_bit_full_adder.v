`timescale 1ns / 1ps
module four_bit_full_adder(input a3,a2,a1,a0,b3,b2,b1,b0,cin, output s3,s2,s1,s0, c2,c1,c0,cout);

    one_bit_full_adder u1(cin,a0,b0,s0,c0);
    one_bit_full_adder u2(c0,a1,b1,s1,c1);
    one_bit_full_adder u3(c1,a2,b2,s2,c2);
    one_bit_full_adder u4(c2,a3,b3,s3,cout);

endmodule
