`timescale 1ns / 1ps
module D_latches_enable_test();

    reg d,e;
    wire q,q_neg;
    
    D_latches_enable uut(d,e,q,q_neg);
    
    initial begin
    
        d=0;  e=0;    #30;
        d=1;  e=0;    #30;
        d=0;  e=1;    #30;
        d=1;  e=1;    #30;
    
    end

endmodule
