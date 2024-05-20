`timescale 1ns / 1ps
module four_bit_full_adder_test();
    
    reg x3,x2,x1,x0;
    reg y3,y2,y1,y0;
    reg cin;
    
    wire sum3,sum2,sum1,sum0;
    wire car2,car1,car0,carout;
    
    four_bit_full_adder uut(.a3(x3),.a2(x2),.a1(x1),.a0(x0),.b3(y3),.b2(y2),.b1(y1),.b0(y0),.cin(cin),
    .s3(sum3),.s2(sum2),.s1(sum1),.s0(sum0),.c2(car2),.c1(car1),.c0(car0),.cout(carout) );
    
    initial begin
    
        x3=1 ; x2=0 ; x1=0 ; x0=0 ; y3=0 ; y2=0 ; y1=0 ; y0=1; cin=0 ; #50;
        x3=0 ; x2=0 ; x1=1 ; x0=0 ; y3=0 ; y2=1 ; y1=1 ; y0=1 ;#50;
        x3=0 ; x2=1 ; x1=0 ; x0=0 ; y3=0 ; y2=1 ; y1=0 ; y0=1 ;#50;
        x3=1 ; x2=0 ; x1=1 ; x0=1 ; y3=1 ; y2=0 ; y1=1 ; y0=0 ;#50;
        x3=1 ; x2=1 ; x1=1 ; x0=0 ; y3=0 ; y2=1 ; y1=0 ; y0=1 ;#50;
        x3=1 ; x2=1 ; x1=1 ; x0=1 ; y3=1 ; y2=0 ; y1=0 ; y0=1 ;#50;
        x3=0 ; x2=1 ; x1=1 ; x0=0 ; y3=0 ; y2=0 ; y1=1 ; y0=1 ;#50;
        x3=1 ; x2=0 ; x1=0 ; x0=0 ; y3=1 ; y2=1 ; y1=0 ; y0=0 ;#50;

    end
endmodule
