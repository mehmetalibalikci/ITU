`timescale 1ns / 1ps

module eight_bit_full_adder(
    input [7:0] i_1,
    input [7:0] i_2,
    output [7:0] o,
    output cout
);
    wire c0,c1,c2,c3,c4,c5,c6,c7;
    wire cin = 0;
        one_bit_full_adder u1(cin,i_1[0],i_2[0],o[0],c0);
        one_bit_full_adder u2(c0,i_1[1],i_2[1],o[1],c1);
        one_bit_full_adder u3(c1,i_1[2],i_2[2],o[2],c2);
        one_bit_full_adder u4(c2,i_1[3],i_2[3],o[3],c3);
        one_bit_full_adder u5(c3,i_1[4],i_2[4],o[4],c4);
        one_bit_full_adder u6(c4,i_1[5],i_2[5],o[5],c5);
        one_bit_full_adder u7(c5,i_1[6],i_2[6],o[6],c6);
        one_bit_full_adder u8(c6,i_1[7],i_2[7],o[7],cout);
endmodule
