@echo off
if exist result.txt del result.txt
For %%i in (1,2,3,4,5,6,7,8,9,10,11) do call test.bat %%i %1
