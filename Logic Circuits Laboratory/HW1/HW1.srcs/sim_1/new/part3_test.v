`timescale 1ns / 1ps

module ALU_design_tb;

    // Inputs
    reg Clk;
    reg [7:0] A;
    reg [7:0] B;
    reg [3:0] FunSel;
    
    // Outputs
    wire [7:0] OutALU;
    
    // Instantiate the unit under test
    ALU_design uut (
        .Clk(Clk),
        .A(A),
        .B(B),
        .FunSel(FunSel),
        .OutALU(OutALU)
    );
    
    // Initialize clock
    initial begin
        Clk = 0;
        #5;
        forever #5 Clk = ~Clk;
    end
    
    // Test cases
    initial begin
        // Test case 1: A = 5, B = 10, FunSel = 4'b0100 (Add)
        A = 5;
        B = 10;
        FunSel = 4'b0100;
        #10;
        if (OutALU !== 15) $display("Test case 1 failed. Expected 15, but got %d.", OutALU);
        
        // Test case 2: A = 12, B = 4, FunSel = 4'b0110 (Subtract)
        A = 12;
        B = 4;
        FunSel = 4'b0110;
        #10;
        if (OutALU !== 8) $display("Test case 2 failed. Expected 8, but got %d.", OutALU);
        
        // Test case 3: A = 7, B = 3, FunSel = 4'b1010 (Left shift)
        A = 7;
        B = 3;
        FunSel = 4'b1010;
        #10;
        if (OutALU !== 14) $display("Test case 3 failed. Expected 14, but got %d.", OutALU);
        
        // Add more test cases as needed...
        
        $finish;
    end
    
endmodule
