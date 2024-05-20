`timescale 1ns / 1ps

module D_latches_enable(
    
    input d,e,
    output Q, Q_neg      
);
    wire o1,o2,o3,o4;
    
    nand_gate u1(d,e,o1);
    nand_gate u2(d,d,o2);
    nand_gate u3(o2,e,o3);
    nand_gate u4(o1,Q_neg,Q);
    nand_gate u5(o3,Q,Q_neg);

endmodule
