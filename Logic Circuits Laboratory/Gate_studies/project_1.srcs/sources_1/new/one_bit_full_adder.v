`timescale 1ns / 1ps
module one_bit_full_adder(input cin,i_1,i_2, output s,cout);
    
    wire k1,l2,l3,l4,m1;
    
    xor_gate u1(i_1,i_2,k1);
    xor_gate u2(k1,cin,s);
    
    and_gate u3(i_1,cin,l2);
    and_gate u4(i_2,cin,l3);
    and_gate u5(i_1,i_2,l4);
    
    or_gate u6 (l2,l3,m1);
    or_gate u7 (m1,l4,cout);
endmodule
