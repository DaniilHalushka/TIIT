@echo off
if exist game.in del game.in >nul
if exist game.out del game.out >nul
copy %1.in game.in >nul
Game.exe
@echo TEST NUMBER %1 >> result.txt
@echo TEST NUMBER %1
@Echo off
timer.exe %2 3000 65536 >> result.txt
fc game.out %1.out >> result.txt
