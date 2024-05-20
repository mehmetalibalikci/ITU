`timescale 1ns / 1ps

module SR_latch_enable_test();

    reg s;
    reg r;
    reg e;
    wire q,q_neg;
     
    SR_latch_enable uut(s,r,e,q,q_neg);
    
    initial begin
        s=0; r=0; e=0; #20;
        s=0; r=1; e=0; #20;
        s=0; r=0; e=1; #20;
        s=0; r=1; e=1; #20;
        s=1; r=0; e=1; #20;
        //s=1; r=1; #20;
    end

   
endmodule
