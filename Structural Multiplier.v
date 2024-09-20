//One Bit Adder
module OneBitFullAdd(input A,B,C,output out,Cout); 
	wire w1,w2,w3;
 	xor#(10ns)g1(w1,A,B);
	xor#(10ns)g2(out,w1,C);
	and#(5ns)g3(w2,A,B);
	and#(5ns)g4(w3,C,w1);
 	or#(5ns)g5(Cout,w3,w2);
endmodule	  

 /////////////////////////////////////////////////////////////////////////////////////////////////////
//Four Bit Adder
module RippleAdder(input cin, input [3:0] in1, in2, output Cout, output [3:0] out);
    wire [3:0] w; 

    OneBitFullAdd g1(in1[0], in2[0], cin, out[0], w[0]);  
    OneBitFullAdd g2(in1[1], in2[1], w[0], out[1], w[1]);
    OneBitFullAdd g3(in1[2], in2[2], w[1], out[2], w[2]);
    OneBitFullAdd g4(in1[3], in2[3], w[2], out[3], Cout);
endmodule 
/////////////////////////////////////////////////////////////////////////////////////////// 

module DFF#(parameter N = 4)(input clk,rst,input[N-1:0] D,output reg [N-1:0] Q);
	always@(posedge clk,negedge rst) begin
		if(!rst)
			Q=0;
		else 
			Q=D;
		end 
		endmodule
////////////////////////////////////////////////////////////////////////////////////////////////


module FourByNMultiplier1 #(parameter N = 4) ( input clk,rst, input [3:0] x,input [N-1:0] y,output  [N+3:0] res);
wire [3:0] x1;
wire[N-1:0] y1; //to clock inputs
wire [N+3:0] restemp[N:0];	//for the addition of each bit of y with x
reg [3:0] temp [N-1:0];    //for the anding between one bit in y and x
assign restemp[0]=0;  
wire [N+3:0]sum;  //to gather the final sums of the products
 //send the inputs into a register
 DFF d1(clk,rst,x,x1);
 DFF #(N) d2(clk,rst,y,y1);

genvar i, j;
generate
    for (i = 0; i < N; i++) begin
        for (j = 0; j < 4; j++) begin	//each y bit ands with the 4 x
            
			and #(5ns) g(temp[i][j], x1[j], y1[i]); //i row j column	 
           end
										//this will give us the product of each y bit with all 4 x so we can then add
			 if (i != N-1) begin
		assign restemp[i+1][N+3:i+5]=0;	//make the unused bits zero
		end
		 if (i != 0) begin // Check if i is not zero
         
            assign restemp[i+1][i-1:0] = 0;
        end 
         RippleAdder adder(1'b0, (i == 0) ? 4'b0 : restemp[i][i+3:i], temp[i], restemp[i+1][i+4],restemp[i+1][i+3:i]);  
		//CarryAheadAdder adder(1'b0, (i == 0) ? 4'b0 : restemp[i][i+3:i], temp[i], restemp[i+1][i+4],restemp[i+1][i+3:i]); 
		assign sum[i]=restemp[i+1][i];				  //take the last bit from each iteration
		assign sum[N+3:N]=restemp[N][N+3:N];									  //take the final bits
    end
endgenerate
DFF #(N+4) d3(clk,rst,sum,res);

endmodule



////////////////////////////////////////////////////////////////////////////////////////////////////




module TESTFourByNMultiplier;
    parameter N = 8;  
	parameter K=4;
    reg [3:0] x;
    reg [N-1:0] y;	
	 reg [K-1:0] y1;
    wire [N+3:0] ans;
	wire [K+3:0] ans1;
	reg rst;
    reg clk = 0;   
	wire [2*N:0] re=N*N;  
	wire [2*K:0] re2=K*K; 

    FourByNMultiplier1 #(N) tst(clk,rst, x, y, ans);   
	FourByNMultiplier1 #(K) tst1(clk,rst, x, y1, ans1); 
	assign answer=x*y;
    initial begin
        forever #(1ns) clk = ~clk;
    end
initial begin
	rst=0;
        #(10ns); 
        rst=1; 	   
		x=0;
		y=0;
 
		repeat(15)begin	
			x=x+1;
			repeat(re) begin
			y=y+1;			  
			#(230ns);	// ripple adder
			//#(190ns)   //Carry LookAhead
			$monitor("time:%0d         %d x %d = %d",$time, x,y, ans); 
			if(ans!=x*y) begin
				$display("TEST FAILED!!!!!");
				$finish;
			end	
		
			end	 
		end	 	 
		x=0;
		y1=0;
		repeat(15)begin
			x=x+1;
			repeat(re2) begin
			y1=y1+1;
			#(130ns);	 //for ripple adder n=4   
			//	#(110ns)//carry Look Ahead
			 $display("time:%0d         %d x %d = %d",$time, x,y1, ans1); 
			if(ans1!=x*y1) begin	  
				$display("TEST FAILED!!!!!");
				$finish;
			end
			
			end 
		end	  
		$display("TEST PASSED!"); 
		#(200ns); 
		$finish;
        
end	  				

endmodule			
//138 for evaluation 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Carry a Look Ahead
module CarryAheadAdder(input Cin,input [3:0] A,B, output Cout, output [3:0] out);

wire [3:0] G, P; 
//Generate
and#(5ns)G1(G[0],A[0],B[0]);	  
and#(5ns)G2(G[1],A[1],B[1]);	
and#(5ns)G3(G[2],A[2],B[2]);
and#(5ns)G4(G[3],A[3],B[3]);
//Propogate
or#(5ns)P1(P[0],A[0],B[0]);	  
or#(5ns)P2(P[1],A[1],B[1]);	
or#(5ns)P3(P[2],A[2],B[2]);	 
or#(5ns)P4(P[3],A[3],B[3]);

//Creating the Carry Ci+1=Gi+PiCi
wire [2:0] C;
wire [3:0] W;
//PiCi
 and#(5ns)W1(W[0],Cin,P[0]);
 and#(5ns)W2(W[1],C[0],P[1]);
 and#(5ns)W3(W[2],C[1],P[2]);
 and#(5ns)W4(W[3],C[2],P[3]);	
 
or#(5ns)C1(C[0],G[0],W[0]);
or#(5ns)C2(C[1],G[1],W[1]);
or#(5ns)C3(C[2],G[2],W[2]);
or#(5ns)C4(Cout,G[3],W[3]);	 

//Getting the sum													   
xor#(10ns) g1(out[0], A[0], B[0], Cin);
xor#(10ns) g2(out[1], A[1], B[1], C[0]);
xor#(10ns) g3(out[2], A[2], B[2], C[1]);
xor#(10ns) g4(out[3], A[3], B[3], C[2]);

endmodule		

