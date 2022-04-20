@echo off
Set "appName=Snake%2"

echo.
prompt $g$s

if "%1"=="-d" goto compile_dynamic_lib
if "%1"=="-s" goto compile_static_lib
goto compile_dynamic_lib

:compile_dynamic_lib
	echo Compiling with the Terminator dynamic library...
	@echo on
	g++ %appName%.cpp Terminator.dll -o %appName%.exe -DUNICODE -O3 -lwinmm
	@echo off
	goto end

:compile_static_lib
	echo Compiling with the Terminator static library...
	@echo on
	g++ %appName%.cpp Terminator.lib -o %appName%.exe -DUNICODE -O3 -lwinmm -DSTATIC_LIB -static
	@echo off
	goto end

:end
	if %errorlevel% == 0 (
		echo.
		echo Successfully Compiled.
		echo Running %appName%.exe...
		%appName%.exe
	)

prompt
