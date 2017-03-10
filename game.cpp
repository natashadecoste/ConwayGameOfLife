#include "Game.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

/*
The ConwayGame class.
Uses a two-dimensional Cell array and the size of the array
is defined by gameSize.
*/

// Assigns the value of gameSize which determines the size 
// of the two-dimensional Cell array used to store all the
// information for each Cell.
ConwayGame::ConwayGame(){
	cout << "Game Started"<<endl;
	gameSize = 30;
}

// Desconstructor for the game which prints a message on 
// the console.
ConwayGame::~ConwayGame(){
	cout<< "Game Over"<<endl;

}

// Shows the status (either Alive/T or Dead/F) of all the
// cells. This is purely used for testing and debugging.
void ConwayGame::showBoard(){
	for(int i= 0; i< gameSize; i++){
		for (int j =0; j< gameSize; j++){
			// Go through each Cell element in the array
			// and prints out its status.
			if(board[i][j].isAlive()){
				printf("T ");
			}
			else{
				printf("F ");
			}
		}
		printf("\n");
	}
}

// Changes the life status of all the cells to their opposite.
void ConwayGame::reverseBoard(){
	for(int i= 0; i< gameSize; i++){
		for (int j =0; j< gameSize; j++){
			board[i][j].changeStatus();
		}
	}
}

// Randomizes the board.
void ConwayGame::randomize(){
	// Take the processor time consumed by the program as the
	// seed of the random function.
	t = clock(); 
	srand(t);
	int temp;
	// Randomly decides the status of a Cell.
	for(int i=0;i<gameSize;i++){
		for(int j=0;j<gameSize;j++){
			temp = rand () % 2;
			if(temp < 1){
				board[i][j].resurrect();
			}
			else{
				board[i][j].kill();
			}
		}
	}
}

// Returns a clean board by marking all the Cells 'Dead'.
void ConwayGame::clear(){
	for(int i=0; i< gameSize; i++){
		for(int j=0; j<gameSize; j++){
			board[i][j].kill();
		}
	}
}

// Counts the number of living neighbours of a Cell by going
// through its nearby 8 cells. gameSize is the size of the Cell
// array board where all the Cell information is stored.
void ConwayGame::checkNeighbours(){
	for(int i =0;i<gameSize;i++){
		for(int j = 0; j<gameSize;j++){
				// Case analysis on position of the neighbours
				if(i>0){
					if(j>0){
						// Top Left Neighbour
						// Cells in the first column don't have left neighbours
						// while Cells in the first row don't have top neighbours
						if(board[i-1][j-1].isAlive()){
							board[i][j].livingNeighbours++;
						}
					}
					// Top Neighbour
					if(board[i-1][j].isAlive()){
						board[i][j].livingNeighbours++;
					}
					// Top Right Neighbour
					if(j<gameSize-1){
						if(board[i-1][j+1].isAlive()){
							board[i][j].livingNeighbours++;
						}
					}
				}
				// Left Neighbour
				if(j>0){
					if(board[i][j-1].isAlive()){
						board[i][j].livingNeighbours++;
					}
				}
				// Right Neighbour
				// Cells in the last column do not have right neighbours
				if(j<gameSize-1){
					if(board[i][j+1].isAlive()){
						board[i][j].livingNeighbours++;
					}
				}	
				// Bottom Neighbour
				// Cells in the last row do not have bottom neighbours 
				if(i<gameSize-1){
					
					if(j>0){
						if(board[i+1][j-1].isAlive()){
							board[i][j].livingNeighbours++;
						}
					}
					// Bottom Middle Neighbour
					if(board[i+1][j].isAlive()){
						board[i][j].livingNeighbours++;
					}

					// Bottom Right Neighbour
					if(j<gameSize-1){
						if(board[i+1][j+1].isAlive()){
							board[i][j].livingNeighbours++;
						}
					}
				}
			}
		}
	}

// Updates the board to the next generation.
void ConwayGame::advanceState(){
	for(int i=0; i< gameSize; i++){
		for(int j=0; j<gameSize; j++){
			board[i][j].updateState();
			// updateState checks the number of the living neighbours
			// and update the nextState value.
		}
	}

	for(int i=0; i< gameSize; i++){
		for(int j=0; j<gameSize; j++){
			board[i][j].advance();
			// Assign the status to the Cell
		}
	}

}



/*
The class for Cell. For each Cell object, it includes the current status
and the next generation status which is dependent on the numbers of living
neighbours this cell has at this moment. 
*/

// Constructor of the cell
Cell::Cell(){
	alive = false;
	nextState = NULL;
	livingNeighbours = 0;
}


Cell::~Cell(){
	// Deconstructor
}

// Return True when the Cell is Alive
bool Cell::isAlive(){
	return alive;
}

// Simply reverses the status of the cell
void Cell::changeStatus(){
	alive = !alive;
}

// To make the cell dead
void Cell::kill(){
	alive = false;
}

// To make the cell alive
void Cell::resurrect(){
	alive = true;
}

// Generates the next generation of the board
void Cell::updateState(){
	// Case analysis on number of neighbours
	// When the Cell is currently Alive
	if(alive){
		// Cell dies due to underpopulation
		// when it has less than 2 neighbours.
		if(livingNeighbours < 2){
			nextState = false;
		}
		// Cell dies due to overpopulation
		// when it has more than 3 neighbours.
		else if( livingNeighbours > 3){
			nextState = false;
		}
		// Cell remains alive if it has exact
		// two or three neighbours.
		else{
			nextState = true;
		}
	}
	else {
	// When the cell is currently dead
		if(livingNeighbours == 3){
			// It becomes alive when it has exact 3 neighbours.
			nextState = true;
		}
	}

}

// Cell updates for the next generation.
void Cell::advance(){
	alive = nextState;
	livingNeighbours =0;
}

// Testing Code
/*
int main(){
	ConwayGame c;
	c.showBoard();
	cout<<endl;
	c.reverseBoard();
	c.showBoard();
	cout<<endl;
	cout<<"the first state"<<endl;
	c.randomize();
	c.showBoard();
	cout<<endl;
	c.clear();
	c.showBoard();
	cout<<endl;
	cout<<"the next state"<<endl;
	c.checkNeighbours();
	c.advanceState();
	c.showBoard();
}*/