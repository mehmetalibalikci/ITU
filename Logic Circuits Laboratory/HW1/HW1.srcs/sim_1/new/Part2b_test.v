`timescale 1ns / 1ps

module eight_registers_test();
    reg [7:0] indata;
    reg [2:0] o1Sel;
    reg [2:0] o2Sel;
    reg [1:0] funsel;
    reg [3:0] regsel;
    reg [3:0] tsel;
    reg clk;
    wire [7:0] O_1;
    wire [7:0] O_2;

    always #5 clk = ~clk ;
    
    eight_registers uut( 
    .data_in(indata), 
    .O1_sel(o1Sel), 
    .O2_sel(o2Sel), 
    .FunSel(funsel), 
    .Reg_sel( regsel), 
    .T_sel(tsel), .Clk( clk), 
    .Q1(O_1), 
    .Q2(O_2)
);
    
    initial begin
        clk = 0;
        indata = 8'd32;
        funsel =2'b01;
        regsel =4'b0001;  // R4 is enabled
        tsel = 4'b1000;   // T1 is enabled
        o1Sel = 3'b000;   // O_1 = T1
        o2Sel = 3'b111;   // O_2 = R4
        #10;
        funsel = 2'b10;   // O_1 - 1 AND O_2 - 1
        #10;
        funsel = 2'b11;   // O_1 + 1 AND O_2 + 1   
        #10;
        //funsel = 2'b00;   // O_1 = 0 AND O_2 = 0
        #10;
        regsel =4'b0000; // NO REGISTER IS ENABLED
        tsel = 4'b0000; // NO REGISTER IS ENABLED
        #10;
        funsel = 2'b00; // O_1 = 0 AND O_2 = 0
        $finish;
    end
    
endmodule