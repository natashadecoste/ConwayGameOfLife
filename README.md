CONWAY'S GAME OF LIFE


=======


# Simple simulation using openGL with the GLUT LIBRARY

THIS IS THE README FILE FOR ASSIGNMENT 1 PART 2 (GRAPHICS USING OPENGL)

The purpose of this was to learn and use openGL and the GLUT library and simulate conway's game of life. 



********************************

Living cells are green, dead cells are black. 

Specifications of cell life:

Any live cell with fewer than two live neighbors dies, as if by under population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by overpopulation.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

(https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)




**********************************

Files

There is an game.cpp and game.h file that contain the logic of the game (see the above specifications of cell life)

There is also a conway.cpp file that runs openGL and GLUT.

There is a makefile that compiles the cpp files together to make the executable and then runs it automatically.


**********************************

To Run

via Terminal (ON LINUX):


$ make



***********************************

More information about Conway's Game of Life:

https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life


***********************************

Natasha DeCoste
