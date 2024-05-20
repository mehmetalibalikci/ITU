`timescale 1ns / 1ps

module SR_latch_enable(
    input S,
    input R,
    input enable,
    output Q,
    output Q_neg
    );
    
    wire o1,o2;

    nand_gate u1(S,enable,o1);
    nand_gate u2(R,enable,o2);
    nand_gate u3(o1,Q_neg,Q);
    nand_gate u4(o2,Q,Q_neg);


endmodule
