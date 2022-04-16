# ASCII Snake for Windows Console

This repository contains my terminal based **Snake** game written in **C++** for the **Windows Command Line**. 

Your task is to move the snake with the cursor keys, and eat as much food as possible before you die of insatiable greed. The snake earns points with each item eaten, but it also gets longer as a result of enormous gluttony. The game is over when the snake runs into itself, or hits the border walls.  

To make this game, I used my own game framework called **Terminator**. In this way, the final source code is simpler and easier to understand, as the framework already provides a set of specific functions, needed to develop terminal based games in the Windows console.

The game and the Terminator library are built with the **g++ compiler** using the **MinGW** development tools, so you should do the same if you want to make an executable file.

But if you rather prefer Visual Studio than MinGW to compile your C++ projects, then lucky you! 

The release section of this repo contains a Snake.zip file, which includes both the MinGW project and Visual Studio solution of the Snake game.

In addition, this zip file also contains an already generated executable file of the Visual Studio solution, so you can instantly start playing the game without building it.


## Building the game

1. install MinGW development tools (https://www.mingw-w64.org/) 
2. download the source code from this repo 
3. build the game:  
    a) dynamically by running this command:
      ```shell
      g++ Snake.cpp Terminator.dll -o Snake.exe -DUNICODE -O3 -lwinmm
      ```
    b) statically by running this command:  
    ```shell
    g++ Snake.cpp Terminator.lib -o Snake.exe -DUNICODE -O3 -lwinmm -DSTATIC_LIB -static  
    ```
	  c) by using the make.bat script and running the following commands:  
    ```make -d``` to build dynamically  
    ```make -s``` to build statically  
	
To build the game with the Visual Studio, check the release section and download the Snake.zip file!


## License notice
Copyright (C) 2022 Ask For Game Task

All programs in this repository are protected by GNU General Public License version 3.  
If you use them, you must attribute me.

Each program in this repository is free software: 
you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

Each program in this repository is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

See the LICENSE file for more details on the GNU General Public License.
