`timescale 1ns / 1ps

module n_bitRegister #(parameter N = 8) (
    input clock, E, [1:0] FunSel, [N-1:0] I,
    output reg [N-1:0] Q
);
    always @(posedge clock) begin
        if (E) begin
            case (FunSel)
                2'b00: Q <= 0;
                2'b01: Q <= I;
                2'b10: Q <= Q-1;
                2'b11: Q <= Q+1;
                default: begin
                    Q <= Q;
                end
            endcase
        end
        else begin
            Q <= Q;
        end
    end
endmodule

module eight_registers(
    input [7:0] data_in,
    input [2:0] O1_sel,
    input [2:0] O2_sel,
    input [1:0] FunSel,
    input [3:0] Reg_sel,
    input [3:0] T_sel,
    input Clk,
    output reg [7:0] Q1,
    output reg [7:0] Q2
 );
 
     wire [7:0] r1_data_out;
     wire [7:0] r2_data_out;
     wire [7:0] r3_data_out;
     wire [7:0] r4_data_out;
     wire [7:0] t1_data_out;
     wire [7:0] t2_data_out;
     wire [7:0] t3_data_out;
     wire [7:0] t4_data_out;
 
n_bitRegister #(.N(8)) R1(.I(data_in), .FunSel(FunSel), .E(Reg_sel[3]), .clock(Clk), .Q(r1_data_out) );
n_bitRegister #(.N(8)) R2(.I(data_in), .FunSel(FunSel), .E(Reg_sel[2]), .clock(Clk), .Q(r2_data_out) );
n_bitRegister #(.N(8)) R3(.I(data_in), .FunSel(FunSel), .E(Reg_sel[1]), .clock(Clk), .Q(r3_data_out) );
n_bitRegister #(.N(8)) R4(.I(data_in), .FunSel(FunSel), .E(Reg_sel[0]), .clock(Clk), .Q(r4_data_out) );
n_bitRegister #(.N(8)) T1(.I(data_in), .FunSel(FunSel), .E(T_sel[3]),   .clock(Clk), .Q(t1_data_out) );
n_bitRegister #(.N(8)) T2(.I(data_in), .FunSel(FunSel), .E(T_sel[2]),   .clock(Clk), .Q(t2_data_out) );
n_bitRegister #(.N(8)) T3(.I(data_in), .FunSel(FunSel), .E(T_sel[1]),   .clock(Clk), .Q(t3_data_out) );
n_bitRegister #(.N(8)) T4(.I(data_in), .FunSel(FunSel), .E(T_sel[0]),   .clock(Clk), .Q(t4_data_out) );

    always@ (*) begin
        case(O1_sel)
            3'b000:   Q1 <= t1_data_out;
            3'b001:   Q1 <= t2_data_out;
            3'b010:   Q1 <= t3_data_out;
            3'b011:   Q1 <= t4_data_out;
            3'b100:   Q1 <= r1_data_out;
            3'b101:   Q1 <= r2_data_out; 
            3'b110:   Q1 <= r3_data_out;
            3'b111:   Q1 <= r4_data_out;
            default:  
            begin
                Q1 <= Q1;
            end
        endcase  
        
        case(O2_sel)
            3'b000:  Q2 <= t1_data_out;
            3'b001:  Q2 <= t2_data_out;
            3'b010:  Q2 <= t3_data_out;
            3'b011:  Q2 <= t4_data_out;
            3'b100:  Q2 <= r1_data_out;
            3'b101:  Q2 <= r2_data_out;
            3'b110:  Q2 <= r3_data_out;
            3'b111:  Q2 <= r4_data_out;
            default:  
            begin
                 Q2 <= Q2;
            end
        endcase 
     end
endmodule
