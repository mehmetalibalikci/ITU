`timescale 1ns / 1ps

module three_to_eight_decoder(input i_1,i_2,i_3,output D0,D1,D2,D3,D4,D5,D6,D7);
    
    wire t_1,t_2,t_3;
    
    not_gate u1(i_1,t_1);
    not_gate u2(i_2,t_2);
    not_gate u3(i_3,t_3);
    
    and_gate_three u4(t_1,t_2,t_3,D0); //000
    and_gate_three u5(t_1,t_2,i_3,D1); //001
    and_gate_three u6(t_1,i_2,t_3,D2); //010
    and_gate_three u7(t_1,i_2,i_3,D3); //011
    and_gate_three u8(i_1,t_2,t_3,D4); //100
    and_gate_three u9(i_1,t_2,i_3,D5); //101
    and_gate_three u10(i_1,i_2,t_3,D6);//110
    and_gate_three u11(i_1,i_2,i_3,D7);//111
    
endmodule
