`timescale 1ns / 1ps
module eight_one_mux(input i_0,i_1,i_2,i_3,i_4,i_5,i_6,i_7,sel_1,sel_2,sel_3, output o);
    
    wire t_1,t_2,t_3,t_4,t_5,t_6,t_7,t_8,t_9,t_10,t_11;
    
    not_gate u1(sel_1,t_1);
    not_gate u2(sel_2,t_2);
    not_gate u3(sel_3,t_3);
    
    and_gate_four u4(i_0,t_1,t_2,t_3,t_4);       
    and_gate_four u5(i_1,t_1,t_2,sel_3,t_5);
    and_gate_four u6(i_2,t_1,sel_2,t_3,t_6);
    and_gate_four u7(i_3,t_1,sel_2,sel_3,t_7);
    and_gate_four u8(i_4,sel_1,t_2,t_3,t_8);       
    and_gate_four u9(i_5,sel_1,t_2,sel_3,t_9);
    and_gate_four u10(i_6,sel_1,sel_2,t_3,t_10);
    and_gate_four u11(i_7,sel_1,sel_2,sel_3,t_11);
    
    or_gate_eight u12(t_4,t_5,t_6,t_7,t_8,t_9,t_10,t_11,o);

endmodule
