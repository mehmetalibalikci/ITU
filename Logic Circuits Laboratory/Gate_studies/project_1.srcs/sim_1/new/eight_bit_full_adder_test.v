`timescale 1ns / 1ps

module eight_bit_full_adder_test();

    reg [7:0] a;
    reg [7:0] b;
    reg cin;
    
    wire [7:0] sum;
    wire carout;
    
    eigth_bit_full_adder uut(a,b,cin,sum,carout);
    
    initial begin
    
        a = 8'b00011101; b=8'b00000101; cin=1'b0;   #10;
        a = 8'b00110011; b=8'b01011100; cin=1'b0;   #10;
        a = 8'b00010001; b=8'b00011100; cin=1'b0;   #10;
        a = 8'b10111111; b=8'b00000010; cin=1'b0;   #10;
        a = 8'b11001000; b=8'b01011111; cin=1'b0;   #10;
        a = 8'b00110001; b=8'b00011001; cin=1'b0;   #10;
        a = 8'b01001110; b=8'b11111111; cin=1'b0;   #10;
        a = 8'b00101011; b=8'b00111011; cin=1'b0;   #10;
    
    end
    
endmodule
