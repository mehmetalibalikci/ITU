`timescale 1ns / 1ps

module SR_latch(
    
    input S,
    input R,
    output Q,
    output Q_neg
    );
    
    
    nand_gate u1(S,Q,Q_neg);
    nand_gate u2(R,Q_neg,Q);
  
     
endmodule
