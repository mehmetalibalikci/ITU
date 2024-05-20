`timescale 1ns / 1ps


module negative_edge_d_flipflop(D, CLK, EN, Q, Qneg);
  
  input D, CLK, EN;
  output Q, Qneg;
  wire not_clk, not_en;
  wire Qbar;

  assign not_clk = ~CLK;
  assign not_en = ~EN;

  D_latches_enable DL1 (D, not_clk, Q, Qbar);
  D_latches_enable DL2 (Qbar, not_en, Qneg, Q);

endmodule