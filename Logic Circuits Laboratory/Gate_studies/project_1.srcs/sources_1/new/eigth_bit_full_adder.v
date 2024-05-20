`timescale 1ns / 1ps

module eigth_bit_full_adder(
    input [7:0] A, // 8-bit input A
    input [7:0] B, // 8-bit input B
    input cin, // carry in
    output [7:0] S, // 8-bit sum
    output cout // carry out
);

wire [7:1] c;

one_bit_full_adder u0(cin,A[0],B[0],S[0],c[1]);
one_bit_full_adder u1(c[1],A[1],B[1],S[1],c[2]);
one_bit_full_adder u2(c[2],A[2],B[2],S[2],c[3]);
one_bit_full_adder u3(c[3],A[3],B[3],S[3],c[4]);
one_bit_full_adder u4(c[4],A[4],B[4],S[4],c[5]);
one_bit_full_adder u5(c[5],A[5],B[5],S[5],c[6]);
one_bit_full_adder u6(c[6],A[6],B[6],S[6],c[7]);
one_bit_full_adder u7(c[7],A[7],B[7],S[7],cout);

endmodule
