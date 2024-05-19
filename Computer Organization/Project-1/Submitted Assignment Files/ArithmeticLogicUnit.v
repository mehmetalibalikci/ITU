`timescale 1ns / 1ps
module ArithmeticLogicUnit(
    input wire [15:0] A,
    input wire [15:0] B,
    input wire [4:0] FunSel,
    input Clock,
    input WF,
    output reg [15:0] ALUOut,
    output reg [3:0] FlagsOut
);
    reg temp;
    reg [8:0] temp_2;
    reg [7:0] A_s, B_s;
    reg [15:0] temp3;
always @(posedge Clock) begin
    A_s = $signed(A[7:0]);
    B_s = $signed(B[7:0]);

//######### 8 BIT OPERATIONS ########
//----------------------------------

      case (FunSel)
        5'b00000: begin
                      ALUOut <= A_s;
                      FlagsOut[3] = (A_s == 0); // Zero flag
                      FlagsOut[1] = A_s[7]; // Negative flag
                  end
        5'b00001: begin
                      ALUOut <= B_s;
                      FlagsOut[3] = (B_s == 0); // Zero flag
                      FlagsOut[1] = B_s[7]; // Negative flag
                  end
        
        5'b00010: begin
                      ALUOut <= ~A_s;
                      FlagsOut[3] = ((~A_s) == 0); // Zero flag
                      FlagsOut[1] = ~A_s[7]; // Negative flag
                  end
        5'b00011: begin
                      ALUOut <= ~B_s;
                      FlagsOut[3] = ((~B_s) == 0); // Zero flag
                      FlagsOut[1] = ~B_s[7]; // Negative flag
                  end    
        5'b00100: begin
                     ALUOut <= A_s + B_s;  
                     FlagsOut[0] = (A_s[7] & B_s[7] & ~ALUOut[7]) | (~A_s[7] & ~B_s[7] & ALUOut[7]); // Overflow flag
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                     FlagsOut[2] = (ALUOut > 127); // Carry flag
                  end
        5'b00101: begin
                     ALUOut <= A_s + B_s + FlagsOut[2]; // Add A, B, and Carry
                     FlagsOut[0] = ((A_s[7] & B_s[7]) | (B_s[7] & FlagsOut[2]) | (A_s[7] & FlagsOut[2])); // Overflow flag
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                     FlagsOut[2] = (ALUOut > 127); // Carry flag  
                  end
        5'b00110: begin
                     ALUOut <= A_s - B_s; // Subtract B from A
                     FlagsOut[0] = (A_s[7] & ~B_s[7] & ALUOut[7]) | (~A_s[7] & B_s[7] & ~ALUOut[7]); // Overflow flag
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                     FlagsOut[2] = (ALUOut < 0); // Carry flag
                  end
       
        5'b00111: begin
                     ALUOut <= A_s & B_s; // Perform bitwise AND operation
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag    
                  end
        5'b01000: begin
                     ALUOut <= A_s | B_s; // Perform bitwise OR operation
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                  end
        5'b01001: begin
                     ALUOut <= A_s ^ B_s; // Perform bitwise XOR operation
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                  end
        5'b01010: begin
                     ALUOut <= ~(A_s & B_s); // Perform bitwise NAND operation
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                  end
        5'b01011: begin 
                     ALUOut <= A_s << 1; // Perform logical shift left by 1
                     FlagsOut[0] = A_s[7]; // Carry flag (bit shifted out)
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                 end    
        5'b01100: begin 
                     ALUOut <= A_s >>> 1; // Perform logical shift right by 1
                     FlagsOut[0] = A_s[0]; // Carry flag (bit shifted out)
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = 0; // Negative flag (always 0 after logical shift right)
                  end 
        5'b01101: begin
                     ALUOut <= A_s >> 1; // Perform arithmetic shift right by 1
                     FlagsOut[0] = A_s[0]; // Carry flag (bit shifted out)
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                 end 
        5'b01110: begin
                     ALUOut <= {A_s[6:0], A_s[7]}; // Perform circular shift left by 1
                     FlagsOut[0] = A_s[0]; // Carry flag (bit shifted out)
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                 end 
        5'b01111: begin
                     ALUOut <= {A_s[0], A_s[7:1]}; // Perform circular shift right by 1
                     FlagsOut[0] = A_s[0]; // Carry flag (bit shifted out)
                     FlagsOut[3] = (ALUOut == 0); // Zero flag
                     FlagsOut[1] = ALUOut[7]; // Negative flag
                 end
                 
//  ###################### 16 BIT OPERATION ####################
// --------------------------------------------------------------

    5'b10000: begin
                 ALUOut <= A;
                 FlagsOut[3] = (A == 0); // Zero flag
                 FlagsOut[1] = A[7]; // Negative flag
             end
    5'b10001: begin
                 ALUOut <= B;
                 FlagsOut[3] = (B == 0); // Zero flag
                 FlagsOut[1] = B[7]; // Negative flag
             end
    5'b10010: begin
                 ALUOut <= ~A;
                 FlagsOut[3] = ((~A) == 0); // Zero flag
                 FlagsOut[1] = ~A[7]; // Negative flag
             end
    5'b10011: begin
                 ALUOut <= ~B;
                 FlagsOut[3] = ((~B) == 0); // Zero flag
                 FlagsOut[1] = ~B[7]; // Negative flag
             end
    5'b10100: begin
                 ALUOut <= A + B;  
                 FlagsOut[0] = (A[15] & B[15] & ~ALUOut[15]) | (~A[15] & ~B[15] & ALUOut[15]); // Overflow flag
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
                 FlagsOut[2] = (ALUOut > 32767); // Carry flag
             end
    5'b10101: begin
                 ALUOut <= A + B + FlagsOut[2]; // Add A, B, and Carry
                 FlagsOut[0] = ((A[15] & B[15]) | (B[15] & FlagsOut[2]) | (A[15] & FlagsOut[2])); // Overflow flag
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
                 FlagsOut[2] = (ALUOut > 32767); // Carry flag 
             end
    5'b10110: begin
                 ALUOut <= A - B; // Subtract B from A
                 FlagsOut[0] = (A[15] & ~B[15] & ALUOut[15]) | (~A[15] & B[15] & ~ALUOut[15]); // Overflow flag
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
                 FlagsOut[2] = (ALUOut < 0); // Carry flag
             end
    5'b10111: begin
                 ALUOut <= A & B; // Perform bitwise AND operation
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag   
             end
    5'b11000: begin
                 ALUOut <= A | B; // Perform bitwise OR operation
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
             end
    5'b11001: begin
                 ALUOut <= A ^ B; // Perform bitwise XOR operation
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
             end
    5'b11010: begin
                 ALUOut <= ~(A & B); // Perform bitwise NAND operation
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
             end
    5'b11011: begin
                 ALUOut <= A << 1; // Perform logical shift left by 1
                 FlagsOut[0] = A[15]; // Carry flag (bit shifted out)
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
             end
    5'b11100: begin
                 ALUOut <= A >>> 1; // Perform logical shift right by 1
                 FlagsOut[0] = A[0]; // Carry flag (bit shifted out)
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = 0; // Negative flag (always 0 after logical shift right)
             end
    5'b11101: begin
                 ALUOut <= A >> 1; // Perform arithmetic shift right by 1
                 FlagsOut[0] = A[0]; // Carry flag (bit shifted out)
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag 
             end
    5'b11110: begin
                 ALUOut <= {A[14:0], A[15]}; // Perform circular shift left by 1
                 FlagsOut[0] = A[0]; // Carry flag (bit shifted out)
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
             end
    5'b11111: begin
                 ALUOut <= {A[0], A[15:1]}; // Perform circular shift right by 1
                 FlagsOut[0] = A[0]; // Carry flag (bit shifted out)
                 FlagsOut[3] = (ALUOut == 0); // Zero flag
                 FlagsOut[1] = ALUOut[15]; // Negative flag
             end
  endcase
end
endmodule