`timescale 1ns / 1ps

module negative_edge_d_flipflop_test();

    reg d,clk,e;
    wire q,q_neg;
    
    negative_edge_d_flipflop uut(d,clk,e,q,q_neg);
    
    initial begin
    
        d=0;     clk=0;       e=1;     #20;
        d=1;     clk=1;       e=1;     #20;
        d=0;     clk=0;       e=1;     #20;
        d=1;     clk=1;       e=1;     #20;
        d=0;     clk=0;       e=1;     #20;
    end
endmodule
