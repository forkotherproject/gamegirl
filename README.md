# GameGirl
`GameGirl` is a Nintendo Gameboy emulator written in C++.

 It was written as a project in the course "Object Oriented Programming (C++) " in 2019. 


 ## Build
Building the emulator requires [`SDL2`](https://www.libsdl.org/) and `cmake` on `Windows`. 
For test, it has been tested  on Windows 10  and Arch Linux.
To complie the project on Windows (need `MinGW` environment):
````
MINGW64 $ cmake .
````
To complie the project on Linux:
````
$ g++ ./Catridges/* ./*.cpp ./*.h -o a.out -O3 --std=c++17 -march=corei7-avx -lSDL2 -lSDL2main
````
(Note:It uses the avx--Advanced Vector Extensions)

## Test 
 The emulators is using the roms from [`Blargg's test ROMs`](http://blargg.parodius.com/gb-tests/) and [`bgbTest.gb`](http://bgb.bircd.org/) to test the hardware accurency.

Here are some screenshot of the test.
![image](https://github.com/NorthernLights-1/ImageRepositry/tree/master/gamegirl/cpu_instrs.png)

![image](https://github.com/NorthernLights-1/ImageRepositry/tree/master/gamegirl/bgb_test.png)
## Input
 The key bindings are: 
 Direction:  <kbd>&uarr;</kbd>, <kbd>&darr;</kbd>, <kbd>&larr;</kbd>, <kbd>&rarr;</kbd>
 Selection:  <kbd>X</kbd> for B, <kbd>Z</kbd> for A, <kbd>Enter</kbd> for START , <kbd>Backspace</kbd> for SELECT.

## Game Screenshot
###1. Mario Land
![Mairo](https://github.com/NorthernLights-1/ImageRepositry/tree/master/gamegirl/Mario.png)
![Mario](https://github.com/NorthernLights-1/ImageRepositry/tree/master/gamegirl/MairoTitle.png)

###2. Tetris
![Tetris](https://github.com/NorthernLights-1/ImageRepositry/blob/master/gamegirl/Tetirs.png)
![Tetris](https://github.com/NorthernLights-1/ImageRepositry/tree/master/gamegirl/TetrisTitle.png)


###3. Zelda
![Zelda](https://github.com/NorthernLights-1/ImageRepositry/blob/master/gamegirl/Zelda_title.png)

