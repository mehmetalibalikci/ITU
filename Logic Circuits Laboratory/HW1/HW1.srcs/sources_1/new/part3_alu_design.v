`timescale 1ns / 1ps

module DesignOfALU(
    input Clk,
    input [7:0] A,
    input [7:0] B,
    input [3:0] FunSel,
    output reg [3:0] FlagReg,
    output [7:0] OutALU
);
wire cin;
reg [7:0] result;
reg  OFlowCheck = 0;

assign cin = FlagReg[2];
assign OutALU = result;


    always @(*) begin 
    case (FunSel)
        4'b0000: begin
            result <= A;
        end
        4'b0001: begin
            result <= B;
        end
        4'b0010: begin
            result <= ~A;
        end
        4'b0011: begin
            result <= ~B;
        end
        4'b0100: begin
            result <= A + B;
            OFlowCheck <=1;      
        end
        4'b0101: begin
            result <= A + B + cin;
            OFlowCheck <=1;
        end
        4'b0110: begin
            result <= A - B;
            OFlowCheck <=1;
        end
        4'b0111: begin
            result <= A & B;
            
        end
        4'b1000: begin
            result <= A | B;
        end
        4'b1001: begin
            result <= A ^ B;
        end
        4'b1010: begin
            FlagReg[2] <= A[7];
            result <= A << 1;
        end
        4'b1011: begin
            FlagReg[2] <= A[0];
            result <= A >> 1;
        end
        4'b1100: begin
            result <= A <<< 1;
            OFlowCheck <=1;
        end
        4'b1101: begin
            result <= A >>> 1;
        end
        4'b1110: begin
            FlagReg[2] <= A[7];
            result[0] <= FlagReg[2];
            result[1] <= A[0];
            result[2] <= A[1];
            result[3] <= A[2];
            result[4] <= A[3];
            result[5] <= A[4];
            result[6] <= A[5];
            result[7] <= A[6];
            OFlowCheck <=1;
        end
        4'b1111: begin
            FlagReg[2]<= A[0];
            result[0] <= A[1];
            result[1] <= A[2];
            result[2] <= A[3];
            result[3] <= A[4];
            result[4] <= A[5];
            result[5] <= A[6];
            result[6] <= A[7];
            result[7] <= FlagReg[2];
            OFlowCheck <=1;
        end
    endcase
    end
always @(negedge Clk) begin
        if(result == 0) begin
            FlagReg[3] = 1;
        end else begin
            FlagReg[3] = 0;
        end

        if(result[7] == 1) begin
            FlagReg[1] = 1;
        end else begin
            FlagReg[1] = 0;
        end
        
        if((A[7] == ~result[7]) && (OFlowCheck))
            FlagReg[0] = 1;

   end

endmodule
