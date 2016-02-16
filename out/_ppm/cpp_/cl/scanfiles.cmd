@echo off
setlocal EnableDelayedExpansion

@if exist _objs del /f _objs

echo OBJSX = \> _objs

for /f "delims=" %%A in ('forfiles /s /p src /m *.cpp /c "cmd /c echo @relpath"') do (
setlocal enableDelayedExpansion
	set "source=%%~A"
	set source=!source:~2!
	
	set "end= \"

	set "firstLine=	$(SOURCE_DIR)\"
	
	echo !firstLine!!source!!end!>> _objs
endlocal
)
echo. >> _objs

