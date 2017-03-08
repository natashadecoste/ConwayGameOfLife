#ifndef GAME_H
#define GAME_H
#include <ctime>

// The class of cells to populate the board.
// A Cell object contains the current status and the next generation 
// status of the cell which is dependent on the numbers of living neighbours 
// this cell has at the moment. A cell can be dead or alive which would have 
// an impact on its neighbours. 
class Cell{
	public:
		Cell(); // Constructor
		~Cell(); // Deconstructor
		bool isAlive();	// Checks status
		void changeStatus(); // Reverses the current status
		void kill(); // Changes the status to Dead
		void resurrect(); // Changes the status to Alive
		void updateState(); // Upades the board
		void advance();

		int livingNeighbours;
		bool nextState;

	private:
		bool alive;


};

// The class to hold the cells and game structure (back-end logic)
class ConwayGame{
	public:
		ConwayGame(); // Constructor
		~ConwayGame(); // Deconstructor
		void reverseBoard(); // Changes the life states of all cells to the OPPOSITE
		void showBoard(); // Prints the board. Puerly for testing purposes.
		void randomize(); // Randomizes the status of all the cells
		void clear();
		Cell board [30][30]; // Two-dimensional Cell array which holds all the back-end information of the board
		void checkNeighbours();

		void advanceState();
	private:
		int gameSize;
		clock_t t; 

};




#endif