`timescale 1ns / 1ps

module testbench;

    // Inputs
    reg [7:0] data_in;
    reg [2:0] O1_sel;
    reg [2:0] O2_sel;
    reg [1:0] FunSel;
    reg [3:0] Reg_sel;
    reg [3:0] T_sel;
    reg Clk;
    
    // Outputs
    wire [7:0] Q1;
    wire [7:0] Q2;
    
    // Instantiate the unit under test (UUT)
    eight_registers uut (
        .data_in(data_in), 
        .O1_sel(O1_sel), 
        .O2_sel(O2_sel), 
        .FunSel(FunSel), 
        .Reg_sel(Reg_sel), 
        .T_sel(T_sel), 
        .Clk(Clk), 
        .Q1(Q1), 
        .Q2(Q2)
    );
    
    initial begin
        // Initialize inputs
        data_in = 8'hFF;
        O1_sel = 3'b000;
        O2_sel = 3'b000;
        FunSel = 2'b00;
        Reg_sel = 4'b0000;
        T_sel = 4'b0000;
        Clk = 0;
        
        // Wait for a few clock cycles to ensure everything is stable
        #10;
        
        // Set input values
        data_in = 8'hA5;
        O1_sel = 3'b100;
        O2_sel = 3'b101;
        FunSel = 2'b11;
        Reg_sel = 4'b1010;
        T_sel = 4'b1100;
        
        // Toggle clock
        #5 Clk = 1;
        #5 Clk = 0;
        #5 Clk = 1;
        #5 Clk = 0;
        
        // Check output values
        if (Q1 !== 8'hA5) $error("Test failed: Q1 = %h", Q1);
        if (Q2 !== 8'h00) $error("Test failed: Q2 = %h", Q2);
        
        $display("Test passed.");
        
        // End simulation
        #10 $finish;
    end
    
endmodule
