############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
############################################################
open_project 2d_convolution_unit
set_top doImgproc
add_files 2d_convolution_unit/core.cpp
add_files 2d_convolution_unit/core.h
add_files -tb 2d_convolution_unit/test_bench.cpp
open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./2d_convolution_unit/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
