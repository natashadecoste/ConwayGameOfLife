#ifndef GAME_H
#define GAME_H
#include <ctime>

// The class of cells to populate the board.
// A Cell object contains the current status and the next generation 
// status of each cell. The status of a cell is dependent on the numbers 
// of its living neighbours. A cell can be either dead or alive. A boolean
// variable "alive" is used to implement this.

class Cell{
	public:
		Cell(); // Constructor
		~Cell(); // Deconstructor
		bool isAlive();	// Checks status
		void changeStatus(); // Reverses the current status
		void kill(); // Changes the status to Dead
		void resurrect(); // Changes the status to Alive
		void updateState(); // Checks the number of living neigbhours 
		void advance(); // and updats the status of a Cell

		int livingNeighbours;
		bool nextState;

	private:
		bool alive;


};

// The class to hold the cells and the game structure (back-end logic)
// To present the grid, two-dimensional array is used as the data structure
// And randomize() will be called in the beginning of the program to create a
// board filled will cells have random status.
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