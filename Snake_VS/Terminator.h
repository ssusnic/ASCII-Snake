/**############################################################################
#
# @Program      TERMINATOR GAME FRAMEWORK v0.003
# @File         Terminator.h (header file)
# @Date         24.03.2022
#
# @Description  Header file of the simple game framework for making
#               terminal/text based games in Windows 10 using C++.
#
# @Usage        1. include it in the source code of your game:
#                  #include "Terminator.h"
#
#               2. compile your game using MinGW g++ compiler: 
#                  - dynamically with Terminator.dll
#                  - statically  with Terminator.lib
#
# @Author       Srdjan Susnic
# @Website      https://www.askforgametask.com
# @Github       https://www.github.com/ssusnic
# @Youtube      https://www.youtube.com/ssusnic
#
# Copyright (C) 2022 Ask For Game Task
# 
# This program is protected by GNU General Public License version 3.
# If you use it, you must attribute me.
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You can view this license here:
# https://opensource.org/licenses/GPL-3.0
#
#############################################################################*/

//=============================================================================
// Preprocessor directives - use the following switches when compiling:
//    a) -DSTATIC_LIB to export and import "Terminator.lib" static library
//    b) -DEXPORT_DLL to export "Terminator.dll" dynamic library
//    c) without switch to import "Terminator.dll" dynamic library
//=============================================================================

#ifdef STATIC_LIB
	#define API
#elif EXPORT_DLL
	#define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif

//=============================================================================
// Included header files
//=============================================================================

#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <mmsystem.h>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

//=============================================================================
// ANSI escape code definitions
//=============================================================================

// foreground colors
#define BLACK           "\033[30m"
#define DARK_RED        "\033[31m"
#define DARK_GREEN      "\033[32m"
#define DARK_YELLOW     "\033[33m"
#define DARK_BLUE       "\033[34m"
#define DARK_MAGENTA    "\033[35m"
#define DARK_CYAN       "\033[36m"
#define GREY            "\033[37m"
#define DARK_GREY       "\033[90m"
#define RED             "\033[91m"
#define GREEN           "\033[92m"
#define YELLOW          "\033[93m"
#define BLUE            "\033[94m"
#define MAGENTA         "\033[95m"
#define CYAN            "\033[96m"
#define WHITE           "\033[97m"

// background colors
#define BG_BLACK        "\033[40m"
#define BG_DARK_RED     "\033[41m"
#define BG_DARK_GREEN   "\033[42m"
#define BG_DARK_YELLOW  "\033[43m"
#define BG_DARK_BLUE    "\033[44m"
#define BG_DARK_MAGENTA "\033[45m"
#define BG_DARK_CYAN    "\033[46m"
#define BG_GREY         "\033[47m"
#define BG_DARK_GREY    "\033[100m"
#define BG_RED          "\033[101m"
#define BG_GREEN        "\033[102m"
#define BG_YELLOW       "\033[103m"
#define BG_BLUE         "\033[104m"
#define BG_MAGENTA      "\033[105m"
#define BG_CYAN         "\033[106m"
#define BG_WHITE        "\033[107m"

// default color
#define DEFAULT         "\033[39;49m"

//=============================================================================
// Globals with external linkage
//=============================================================================

// screen size
extern API int screenCols;
extern API int screenRows;

// exit flag
extern API bool quit;

//=============================================================================
// Control handler routine.
//=============================================================================
API BOOL CtrlHandler(DWORD signal);

//=============================================================================
// Creates a new Console screen.
//=============================================================================
API void CreateConsole(
	wstring title,
	int cols = 60, 
	int rows = 30, 
	wstring fontName = L"Consolas",
	short fontWidth = 14, 
	short fontHeight = 16, 
	int fps = 30
);

//=============================================================================
// Destroys the current Console screen and restores the original one.
//=============================================================================
API void DestroyConsole();

//=============================================================================
// Starts timer.
//=============================================================================
API void StartTimer();

//=============================================================================
// Waits to elapse the desired time between two frames.
//=============================================================================
API void WaitTimer();

//=============================================================================
// Draws a char (note: use Grave Accent "`" as a transparent glyph)
//=============================================================================
API void DrawChar(int character, int x, int y, string fg_color, string bg_color="");

//=============================================================================
// Draws left-aligned text.
//=============================================================================
API void DrawText(string text, int x, int y, string fg_color, string bg_color="");

//=============================================================================
// Draws center-aligned text.
//=============================================================================
API void DrawTextC(string text, int x, int y, string fg_color, string bg_color="");

//=============================================================================
// Draws right-aligned text.
//=============================================================================
API void DrawTextR(string text, int x, int y, string fg_color, string bg_color="");

//=============================================================================
// Draws rectangle.
//=============================================================================
API void DrawRect(int x, int y, int width, int height, string bg_color);

//=============================================================================
// Clears the Console screen with the given background color.
//=============================================================================
API void ClearScreen(string bg_color);

//=============================================================================
// Redraws the entire Console screen using data stored in buffers.
//=============================================================================
API void RedrawScreen();

//=============================================================================
// Plays a waveform audio file.
//=============================================================================
API void PlayAudio(LPCWSTR filename, float duration, bool isHighPriority = false);

//=============================================================================
// Plays a waveform audio file in a loop.
//=============================================================================
API void PlayAudioLoop(LPCWSTR filename);
