@echo off
set "type=%1"

set "name=\COG.dll"

set "end=%type%%name%"

set source=Engine\bin\%end%
set dest=Tester\bin\%end%

echo DLL Source: %source%

copy %source% %dest%

pause