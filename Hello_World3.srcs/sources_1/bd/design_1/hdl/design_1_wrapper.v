//Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2017.3.1 (win64) Build 2035080 Fri Oct 20 14:20:01 MDT 2017
//Date        : Sat Jan 27 21:11:05 2018
//Host        : Thomas-labtop running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (e_tri_io,
    lcd_data_tri_io,
    push_buttons_4bits_tri_i,
    reset_0,
    rs_tri_io,
    rw_tri_io,
    sys_clock,
    usb_uart_rxd,
    usb_uart_txd);
  inout [0:0]e_tri_io;
  inout [7:0]lcd_data_tri_io;
  input [3:0]push_buttons_4bits_tri_i;
  input reset_0;
  inout [0:0]rs_tri_io;
  inout [0:0]rw_tri_io;
  input sys_clock;
  input usb_uart_rxd;
  output usb_uart_txd;

  wire [0:0]e_tri_i_0;
  wire [0:0]e_tri_io_0;
  wire [0:0]e_tri_o_0;
  wire [0:0]e_tri_t_0;
  wire [0:0]lcd_data_tri_i_0;
  wire [1:1]lcd_data_tri_i_1;
  wire [2:2]lcd_data_tri_i_2;
  wire [3:3]lcd_data_tri_i_3;
  wire [4:4]lcd_data_tri_i_4;
  wire [5:5]lcd_data_tri_i_5;
  wire [6:6]lcd_data_tri_i_6;
  wire [7:7]lcd_data_tri_i_7;
  wire [0:0]lcd_data_tri_io_0;
  wire [1:1]lcd_data_tri_io_1;
  wire [2:2]lcd_data_tri_io_2;
  wire [3:3]lcd_data_tri_io_3;
  wire [4:4]lcd_data_tri_io_4;
  wire [5:5]lcd_data_tri_io_5;
  wire [6:6]lcd_data_tri_io_6;
  wire [7:7]lcd_data_tri_io_7;
  wire [0:0]lcd_data_tri_o_0;
  wire [1:1]lcd_data_tri_o_1;
  wire [2:2]lcd_data_tri_o_2;
  wire [3:3]lcd_data_tri_o_3;
  wire [4:4]lcd_data_tri_o_4;
  wire [5:5]lcd_data_tri_o_5;
  wire [6:6]lcd_data_tri_o_6;
  wire [7:7]lcd_data_tri_o_7;
  wire [0:0]lcd_data_tri_t_0;
  wire [1:1]lcd_data_tri_t_1;
  wire [2:2]lcd_data_tri_t_2;
  wire [3:3]lcd_data_tri_t_3;
  wire [4:4]lcd_data_tri_t_4;
  wire [5:5]lcd_data_tri_t_5;
  wire [6:6]lcd_data_tri_t_6;
  wire [7:7]lcd_data_tri_t_7;
  wire [3:0]push_buttons_4bits_tri_i;
  wire reset_0;
  wire [0:0]rs_tri_i_0;
  wire [0:0]rs_tri_io_0;
  wire [0:0]rs_tri_o_0;
  wire [0:0]rs_tri_t_0;
  wire [0:0]rw_tri_i_0;
  wire [0:0]rw_tri_io_0;
  wire [0:0]rw_tri_o_0;
  wire [0:0]rw_tri_t_0;
  wire sys_clock;
  wire usb_uart_rxd;
  wire usb_uart_txd;

  design_1 design_1_i
       (.e_tri_i(e_tri_i_0),
        .e_tri_o(e_tri_o_0),
        .e_tri_t(e_tri_t_0),
        .lcd_data_tri_i({lcd_data_tri_i_7,lcd_data_tri_i_6,lcd_data_tri_i_5,lcd_data_tri_i_4,lcd_data_tri_i_3,lcd_data_tri_i_2,lcd_data_tri_i_1,lcd_data_tri_i_0}),
        .lcd_data_tri_o({lcd_data_tri_o_7,lcd_data_tri_o_6,lcd_data_tri_o_5,lcd_data_tri_o_4,lcd_data_tri_o_3,lcd_data_tri_o_2,lcd_data_tri_o_1,lcd_data_tri_o_0}),
        .lcd_data_tri_t({lcd_data_tri_t_7,lcd_data_tri_t_6,lcd_data_tri_t_5,lcd_data_tri_t_4,lcd_data_tri_t_3,lcd_data_tri_t_2,lcd_data_tri_t_1,lcd_data_tri_t_0}),
        .push_buttons_4bits_tri_i(push_buttons_4bits_tri_i),
        .reset_0(reset_0),
        .rs_tri_i(rs_tri_i_0),
        .rs_tri_o(rs_tri_o_0),
        .rs_tri_t(rs_tri_t_0),
        .rw_tri_i(rw_tri_i_0),
        .rw_tri_o(rw_tri_o_0),
        .rw_tri_t(rw_tri_t_0),
        .sys_clock(sys_clock),
        .usb_uart_rxd(usb_uart_rxd),
        .usb_uart_txd(usb_uart_txd));
  IOBUF e_tri_iobuf_0
       (.I(e_tri_o_0),
        .IO(e_tri_io[0]),
        .O(e_tri_i_0),
        .T(e_tri_t_0));
  IOBUF lcd_data_tri_iobuf_0
       (.I(lcd_data_tri_o_0),
        .IO(lcd_data_tri_io[0]),
        .O(lcd_data_tri_i_0),
        .T(lcd_data_tri_t_0));
  IOBUF lcd_data_tri_iobuf_1
       (.I(lcd_data_tri_o_1),
        .IO(lcd_data_tri_io[1]),
        .O(lcd_data_tri_i_1),
        .T(lcd_data_tri_t_1));
  IOBUF lcd_data_tri_iobuf_2
       (.I(lcd_data_tri_o_2),
        .IO(lcd_data_tri_io[2]),
        .O(lcd_data_tri_i_2),
        .T(lcd_data_tri_t_2));
  IOBUF lcd_data_tri_iobuf_3
       (.I(lcd_data_tri_o_3),
        .IO(lcd_data_tri_io[3]),
        .O(lcd_data_tri_i_3),
        .T(lcd_data_tri_t_3));
  IOBUF lcd_data_tri_iobuf_4
       (.I(lcd_data_tri_o_4),
        .IO(lcd_data_tri_io[4]),
        .O(lcd_data_tri_i_4),
        .T(lcd_data_tri_t_4));
  IOBUF lcd_data_tri_iobuf_5
       (.I(lcd_data_tri_o_5),
        .IO(lcd_data_tri_io[5]),
        .O(lcd_data_tri_i_5),
        .T(lcd_data_tri_t_5));
  IOBUF lcd_data_tri_iobuf_6
       (.I(lcd_data_tri_o_6),
        .IO(lcd_data_tri_io[6]),
        .O(lcd_data_tri_i_6),
        .T(lcd_data_tri_t_6));
  IOBUF lcd_data_tri_iobuf_7
       (.I(lcd_data_tri_o_7),
        .IO(lcd_data_tri_io[7]),
        .O(lcd_data_tri_i_7),
        .T(lcd_data_tri_t_7));
  IOBUF rs_tri_iobuf_0
       (.I(rs_tri_o_0),
        .IO(rs_tri_io[0]),
        .O(rs_tri_i_0),
        .T(rs_tri_t_0));
  IOBUF rw_tri_iobuf_0
       (.I(rw_tri_o_0),
        .IO(rw_tri_io[0]),
        .O(rw_tri_i_0),
        .T(rw_tri_t_0));
endmodule
