`timescale 1ns / 1ps
module sixteen_bit_adder_subtractor(

    input [15:0] A,
    input [15:0] B,
    input x,  // carry in
    output [15:0] S,
    output cout  // carry out
    );
    
    wire c1 , cin;
    wire [15:0] b;
    
    assign cin = x;
    
    xor_gate m0( B[0], x, b[0] );
    xor_gate m1( B[1], x, b[1] );
    xor_gate m2( B[2], x, b[2] );
    xor_gate m3( B[3], x, b[3] );
    xor_gate m4( B[4], x, b[4] );
    xor_gate m5( B[5], x, b[5] );
    xor_gate m6( B[6], x, b[6] );
    xor_gate m7( B[7], x, b[7] );
    xor_gate m8( B[8], x, b[8] );
    xor_gate m9( B[9], x, b[9] );
    xor_gate m10( B[10], x, b[10] );
    xor_gate m11( B[11], x, b[11] );
    xor_gate m12( B[12], x, b[12] );
    xor_gate m13( B[13], x, b[13] );
    xor_gate m14( B[14], x, b[14] );
    xor_gate m15( B[15], x, b[15] );
   
    eigth_bit_full_adder u1(A[7:0], b[7:0], cin, S[7:0], c1);
    eigth_bit_full_adder u2(A[15:8],b[15:8],c1, S[15:8], cout);
    
    
endmodule
