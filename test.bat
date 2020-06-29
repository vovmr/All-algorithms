@echo off
gen > in
stupid < in > o
F < in > o1

fc o o1
if errorlevel 1 goto f
echo OK
test
:f
