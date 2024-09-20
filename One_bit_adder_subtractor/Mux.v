module Mux(d0, d1, d2, d3, M0, M1, f);
  input d0, d1, d2, d3, M0, M1;
  output reg f;

  always @ (d0, d1, d2, d3, M0, M1) begin
    case ({M1, M0})
      2'b00: f = d0;
      2'b01: f = d1;
      2'b10: f = d2;
      2'b11: f = d3;
endcase
end
endmodule
