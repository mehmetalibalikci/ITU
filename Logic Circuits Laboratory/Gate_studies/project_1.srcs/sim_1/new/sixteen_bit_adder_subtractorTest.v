`timescale 1ns / 1ps

module sixteen_bit_adder_subtractorTest();
    
    reg [15:0] x;
    reg [15:0] y;
    reg cin;
    
    wire [15:0] sum;
    wire cout;
    
   sixteen_bit_adder_subtractor uut(x,y,cin,sum,cout);
   
   initial begin
   x = 16'b0000000000010111; y = 16'b0000000000000011; cin=1'b0; #20;
   x = 16'b0000000000010101; y = 16'b0000000001001011; cin=1'b0; #20;
   x = 16'b0100000110100000; y = 16'b0100001000000100; cin=1'b0; #20;
   x = 16'b0001101101000111; y = 16'b0001100111111010; cin=1'b0; #20;
   /*x=16'b; y=16'b; cin=1'b1; #20;
   x=16'b; y=16'b; cin=1'b1; #20;
   x=16'b; y=16'b; cin=1'b1; #20;
   x=16'b; y=16'b; cin=1'b1; #20;*/
    end
endmodule
