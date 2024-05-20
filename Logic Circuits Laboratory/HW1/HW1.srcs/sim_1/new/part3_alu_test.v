module ALU_test();
    
    reg clk;
    reg[7:0] A;
    reg[7:0] B;
    reg[3:0] FunSel;

    wire[7:0] OutALU;
    wire[3:0] RegFlag;
        
    DesignOfALU test(
    .Clk(clk),
    .FunSel(FunSel),
    .A(A),
    .B(B),
    .FlagReg(RegFlag), 
    .OutALU(OutALU)
);
    always #5 clk = ~clk;
    initial begin
        A = 5;
        B = 10;
        FunSel = 4'b0100;
        #10;
        
        A = 7;
        B = 3;
        FunSel = 4'b1010;
        #10;

        
        #10;
        A = 8'b11111111;
        B = 8'b11111111;
        
        #10;
        FunSel = 4'b0001;
        #10;
        FunSel = 4'b0011;
        #10;
        FunSel = 4'b0101;
        #10;
        FunSel = 4'b1001;
        #10;
        FunSel = 4'b1111;
        #10;
    end
         
    
endmodule    