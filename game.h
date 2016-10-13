#ifndef GAME_H
#define GAME_H

#include <ctime>


//the class of cells to populate the board
class Cell{
	public:
		Cell();	//constructor
		~Cell();	//deconstructor
		bool isAlive();	//check status
		void changeStatus();
		void kill();
		void resurrect();
		void updateState();
		void advance();

		int livingNeighbours;
		bool nextState;

	private:
		bool alive;


};



//the class to hold the cells and game structure (backend logic)
class ConwayGame{
	public:
		ConwayGame();		//constructor
		~ConwayGame();		//deconstructor
		void reverseBoard();	//changes the life states of all cells to the OPPOSITE
		void showBoard(); // for testing
		void randomize(); //randomizing the status of all the cells
		void clear();
		Cell board [30][30];
		void checkNeighbours();

		void advanceState();
	private:
		int gameSize;
		clock_t t; 

};




#endif