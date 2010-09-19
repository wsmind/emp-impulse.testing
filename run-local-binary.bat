@echo off
rem Run a binary using local libraries (the ones in the lib/ directory).
rem Without this script, the system cannot find these dynamic libraries.
set PATH=lib;lib\thirdparty;%PATH%
%1 %2 %3 %4 %5 %6 %7 %8 %9
