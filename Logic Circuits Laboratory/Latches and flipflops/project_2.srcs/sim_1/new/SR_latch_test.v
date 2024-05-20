`timescale 1ns / 1ps

module SR_latch_test();

    reg s,r;
    wire q,q_neg;
    
    SR_latch uut(s,r,q,q_neg);
    
    initial begin
        s=0; r=0; #20;
        s=0; r=1; #20;
        s=1; r=0; #20;
        //s=1; r=1; #20;
    end
endmodule
