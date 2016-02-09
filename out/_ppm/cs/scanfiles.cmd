@echo off
setlocal EnableDelayedExpansion

@if exist _objs del /f _objs

echo OBJSX = \> _objs

for /f "delims=" %%A in ('forfiles /s /p src /m *.cs /c "cmd /c echo @relpath"') do (
	set "file=%%~A"
	setlocal enableDelayedExpansion
	set file=!file:~2!
	set "tps=	$(SOURCE_DIR)\"
	set tps=!tps!!file! \
	
	echo !tps!>> _objs
	endlocal
)
echo. >> _objs


