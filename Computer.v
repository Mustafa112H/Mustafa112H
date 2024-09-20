module COMP(clock, PC, IR, MBR, MAR, RegisterOutput, MemoryOutput);
//Heba Mustafa 1221916
input clock;
output PC, IR, MBR, MAR, MemoryOutput[15:0], RegisterOutput[15:0];
reg [15:0] IR, MBR, R[0:7]; 
reg [6:0] MAR, PC;
reg [15:0] Memory [0:127];
reg [2:0] state; 
reg[15:0] MemoryOutput, RegisterOutput;

//opcode
parameter load= 3'b000, store=3'b001, add=3'b010, sub=3'b011, mul=3'b100, div=3'b101;
//addressing modes
parameter directMemory=2'b00, register=2'b01, registerIndirect=2'b10, constant=2'b11;

initial begin 
//program 
Memory[10]=16'h001A;
Memory[11]=16'h801B;
Memory[12]=16'h0419;
Memory[13]=16'h6500;
Memory[14]=16'h4705;
Memory[15]=16'h001C;
Memory[16]=16'h401D;
Memory[17]=16'h6302;
Memory[18]=16'hA500;
Memory[19]=16'h241E;

//data at byte address
Memory[25]=16'd18;
Memory[26]=16'd3;
Memory[27]=16'd4;
Memory[28]=16'd8;
Memory[29]=-3;
Memory[30]=16'd5;
//Set the Program Counter to the start of the Instructions
PC=10; state=0;
end 

always @(posedge clock) 
begin 
case (state)
0: begin
MAR <= PC;
PC <=PC+1; 
state=1; 
end 

1:begin //Fetch instructions from Memory 
MBR=Memory[MAR];//this is one clock cycle 
IR = MBR;       //next clock 
state=2; //next state
end 

2: begin //Instruction Decode
if(IR[9:8]==constant||IR[9:8]==register)
state=4; //Immediate doesnt need anything from memory
else if(IR[9:8]==directMemory)
MAR<=IR[6:0];
else if(IR[9:8]==registerIndirect)
MAR<=R[IR[7:0]];
state =3;
end 

3: begin //operand fetch
state=4;
case (IR[15:13])
load: MBR<=Memory[MAR];
store: MBR<=R[IR[12:10]];
add: MBR<=Memory[MAR];
sub: MBR<=Memory[MAR];
mul: MBR<=Memory[MAR];
div: MBR<=Memory[MAR];
endcase
end 

4: begin //execute
case(IR[15:13])

load:begin
if(IR[9:8]==directMemory||IR[9:8]==registerIndirect)
R[IR[12:10]]<=MBR;
else if (IR[9:8]==register)
R[IR[12:10]]<=R[IR[7:0]];
else 
R[IR[12:10]]<=IR[7:0];
end

store:begin
Memory[MAR]=MBR;
MemoryOutput= Memory[MAR];
end

add:begin 
if(IR[9:8]==directMemory||IR[9:8]==registerIndirect)
R[IR[12:10]]<=R[IR[12:10]]+MBR;
else if (IR[9:8]==register)
R[IR[12:10]]<=R[IR[12:10]]+R[IR[7:0]];
else 
R[IR[12:10]]<=R[IR[12:10]]+IR[7:0];
end

sub:begin 
if(IR[9:8]==directMemory||IR[9:8]==registerIndirect)
R[IR[12:10]]<=R[IR[12:10]]-MBR;
else if (IR[9:8]==register)
R[IR[12:10]]<=R[IR[12:10]]-R[IR[7:0]];
else 
R[IR[12:10]]<=R[IR[12:10]]-IR[7:0];
end

mul:begin 
if(IR[9:8]==directMemory||IR[9:8]==registerIndirect)
R[IR[12:10]]<=R[IR[12:10]]*MBR;
else if (IR[9:8]==register)
R[IR[12:10]]<=R[IR[12:10]]*R[IR[7:0]];
else 
R[IR[12:10]]<=R[IR[12:10]]*IR[7:0];
end

div:begin 
if(IR[9:8]==directMemory||IR[9:8]==registerIndirect)
R[IR[12:10]]<=R[IR[12:10]]/MBR;
else if (IR[9:8]==register)
R[IR[12:10]]<=R[IR[12:10]]/R[IR[7:0]];
else 
R[IR[12:10]]<=IR[IR[12:10]]/IR[7:0];
end
endcase
state=0;
end 
endcase
RegisterOutput=R[IR[12:10]];
end
endmodule
