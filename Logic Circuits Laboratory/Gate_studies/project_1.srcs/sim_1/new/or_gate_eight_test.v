`timescale 1ns / 1ps
module or_gate_eight_test();

    reg a,b,c,d,e,f,g,h;
    reg s_1,s_2,s_3;
    wire o;
    
    or_gate_eight uut(.i_0(a), .i_1(b), .i_2(c), .i_3(d), .i_4(e), .i_5(f), .i_6(g), .i_7(h), .sel_1(s_1), .sel_2(s_2), .sel_3(s_3), .o(o) );
    
    initial begin
    
        a=0; b=0; c=0; d=0; e=0; f=0; g=0; h=0; s_1=0; s_2=0; s_3=0; #100;
        a=1; b=0; c=0; d=0; e=0; f=0; g=0; h=0; s_1=0; s_2=0; s_3=0; #100;
        a=1; b=0; c=0; d=0; e=0; f=0; g=0; h=0; s_1=0; s_2=0; s_3=0; #100;
        a=1; b=0; c=0; d=0; e=0; f=0; g=0; h=0; s_1=1; s_2=0; s_3=1; #100;
    end
endmodule
