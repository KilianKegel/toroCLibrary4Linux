@echo off
call "C:\Program Files\Microsoft Visual Studio\18\Insiders\VC\Auxiliary\Build\vcvars64.bat"
set path=%~p0\tools;%path%
cmd /k title Development Environment
