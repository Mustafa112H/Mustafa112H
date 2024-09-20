module one_bit_adder_subtractor_1(a,b, m, sum ,cout);
input a, b, m;
output sum, cout;
assign sum=a^b^m;
assign cout=(a&b)|(m&(a^b));
endmodule 