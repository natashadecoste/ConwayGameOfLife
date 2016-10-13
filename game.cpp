#include "Game.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;




/*

The ConwayGame class.
Uses a 30 x 30 grid of cells.

*/


//creates the gameboard object
ConwayGame::ConwayGame(){
	cout << "Game Started"<<endl;
	gameSize = 30;


}


//desconstructor for the game 
ConwayGame::~ConwayGame(){
	cout<< "Game Over"<<endl;

}


//for testing to show the status of all the cells
void ConwayGame::showBoard(){
	for(int i= 0; i< gameSize; i++){
		for (int j =0; j< gameSize; j++){
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

// changes the life status of all the cells to their opposite
void ConwayGame::reverseBoard(){
	for(int i= 0; i< gameSize; i++){
		for (int j =0; j< gameSize; j++){
			board[i][j].changeStatus();
		}
		
	}

}


//randomizes the board
void ConwayGame::randomize(){
		t = clock();
		srand(t);
		int temp;
		//cout<<"vhut up mannnn"<<endl;
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



void ConwayGame::clear(){
	for(int i=0; i< gameSize; i++){
		for(int j=0; j<gameSize; j++){
			board[i][j].kill();
		}
	}
}

void ConwayGame::checkNeighbours(){
	for(int i =0;i<gameSize;i++){
		for(int j = 0; j<gameSize;j++){

			//check the neighbours


				//topleft
				if(i>0){
					if(j>0){
						if(board[i-1][j-1].isAlive()){
							board[i][j].livingNeighbours++;
						}
					}
					//top
					if(board[i-1][j].isAlive()){
						board[i][j].livingNeighbours++;
					}
					//top right
					if(j<gameSize-1){
						if(board[i-1][j+1].isAlive()){
							board[i][j].livingNeighbours++;
						}
					}
				}
				
				//left
				if(j>0){
					if(board[i][j-1].isAlive()){
						board[i][j].livingNeighbours++;
					}
				}

				//right
				if(j<gameSize-1){
					if(board[i][j+1].isAlive()){
						board[i][j].livingNeighbours++;
					}
				}	

				if(i<gameSize-1){

					//bottom left
					if(j>0){
						if(board[i+1][j-1].isAlive()){
							board[i][j].livingNeighbours++;
						}
					}
					//bottom middle
					if(board[i+1][j].isAlive()){
						board[i][j].livingNeighbours++;
					}

					//bottom right
					if(j<gameSize-1){
						if(board[i+1][j+1].isAlive()){
							board[i][j].livingNeighbours++;
						}
					}
				}








		}
	}
	

}

void ConwayGame::advanceState(){
	for(int i=0; i< gameSize; i++){
		for(int j=0; j<gameSize; j++){
			board[i][j].updateState();
		}
	}

	for(int i=0; i< gameSize; i++){
		for(int j=0; j<gameSize; j++){
			board[i][j].advance();
		}
	}

}



/*

The class for Cell

*/

//constructing the cell
Cell::Cell(){
	alive = false;
	nextState = NULL;
	livingNeighbours = 0;
}


Cell::~Cell(){
	//deconstructor
}

//checking the status of the cell
bool Cell::isAlive(){
	return alive;
}

//simply reverses the status of the cell
void Cell::changeStatus(){
	alive = !alive;
}

//to make the cell dead
void Cell::kill(){
	alive = false;
}

//to make the cell alive
void Cell::resurrect(){
	alive = true;
}





void Cell::updateState(){
	if(alive){	//if the cell is alive
		if(livingNeighbours < 2){
			nextState = false;
		}
		else if( livingNeighbours > 3){
			nextState = false;
		}
		else{
			nextState = true;
		}
	}
	else {//if its dead	
		if(livingNeighbours == 3){
			nextState = true;
		}
	}

}

void Cell::advance(){
	alive = nextState;
	livingNeighbours =0;
}

/*

int main(){
	ConwayGame c;
/*	c.showBoard();
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