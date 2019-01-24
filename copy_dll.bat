@echo off
set "type=%1"

set "name=\COG.dll"

set "end=%type%%name%"

set source=..\Engine\bin\%end%
set dest=..\Tester\bin\%end%

dir ..\
echo DLL Source: %source%
echo DLL Dest: %dest%

copy "%source%" "%dest%"

pause