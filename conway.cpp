#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string>




#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Game.h"


/* The Global Variables
*/
float camPos[] = {0, 0, 3.42f};
int gameSize =30;	//the size of the grid
ConwayGame game;
bool play = false;
bool slow = true;


//drawng the square (using the global variable for the square location)
void colourCell(int x, int y){
	float startX = (-1.0 + (x*(2/(float)gameSize))); //draw from this starting x
	float endX = startX + (2/(float)gameSize); //draw to this ending x
	float startY =(1.0 - (y * (2/(float)gameSize)));	//draw from this starting y
	float endY = startY - (2/(float)gameSize);		//draw to this ending y
	for(float j = startY; j >=endY; j-=0.001){
		for(float i= startX; i <= endX; i +=0.001){
				glBegin(GL_POINTS);
				glColor3f(0,1,0);	//body is green
				glVertex2f(i, j);
				glEnd();
		}

	}

}




void drawgrid(){	//to draw the grid for the GUI
	float c = 0.0;
	float m = (float) gameSize; //grid square numbers
	float end = 2.0/m;
	float i, j;

	for(j = (1.0+end); c<=m; c++){
		j -= end;
		for(i = -1.0; i<=1.0; i += 0.001){
			glBegin(GL_POINTS);
			glColor3f(1,1,1);
			glVertex2f(i, j);
			glEnd();
		}
		
	}
    c = 0.0;
	for(i = (-1.0 - end); c<= m; c++){
		i+= end;
		for(j = 1.0; j>=-1; j-=0.001){
			glBegin(GL_POINTS);
			glColor3f(1,1,1);
			glVertex2f(i, j);
			glEnd();
		}
		
	}


}



void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,1,100);



	drawgrid(); //draw the grid


	//flush out to single buffer
	//glFlush();
	glutSwapBuffers();
}


void redrawBoard(){
	//glFlush();
	for(int i=0;i<gameSize;i++){
		for(int j=0; j<gameSize;j++){
			if(game.board[i][j].isAlive()){
				colourCell(i,j);
			}
		}
	}

	glutSwapBuffers();

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
	glColor3f(1,1,1);
	glPointSize(1.0f);




	drawgrid(); //draw the grid GUI
	redrawBoard();



	glutSwapBuffers();
}

void reshape(int w, int h)
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45, (float)((w+0.0f)/h), 1, 100);


glMatrixMode(GL_MODELVIEW);
glViewport(0, 0, w, h);
}


void mouse(int btn, int state, int x,int y){
	float mouseX = (float)x;
	float mouseY = (float)y;
	float length = (float)400/gameSize;
	int incrmentX = 0;
	int incrmentY = 0;


	if (btn == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
			//printf("Pressed at coords: %i %i\n", x,y);
			while(mouseX > 150 + length){
				mouseX -= length;
				incrmentX ++;
				
			}

			while(mouseY > 85 + length){
				mouseY -= length;
				incrmentY ++;
			}
			//printf("square: %i,%i\n", incrmentX, incrmentY);
			
			game.board[incrmentX][incrmentY].changeStatus();

			glutPostRedisplay();
			glutSwapBuffers();


		}

	}

}


void FPS(int val){
	//glutPostRedisplay();

	if(play){
		game.checkNeighbours();
		game.advanceState();
		//redrawBoard();
		glutPostRedisplay();
		glutTimerFunc(17,FPS,0); //1 sec
	}


	
}



void keyboard(unsigned char key, int xIn, int yIn){
	switch (key)
	{
		case 'q':
		case 27:	//27 is the esc key
			exit(0);
			break;
		case 'r':
			printf("RESETTING!\n");
			game.clear();
			play = false;
			glutPostRedisplay();
			break;
		case 't':
			game.randomize();
			play = false;
			redrawBoard();
			printf("RANDOMIZING!!\n");
			break;
		case 'p':
			play = !play;
			if(play){
				printf("PLAY\n");
			}
			else{
				printf("PAUSE\n");
			}
			if(slow){
				glutTimerFunc(10,FPS,0); //1 sec
			}
			else {
				glutTimerFunc(17,FPS,0); //1 sec
			}
			
			break;
		case GLUT_KEY_UP:
			slow = false;
			printf("High Speed\n");
			glutTimerFunc(17,FPS,0); //1 sec
			break;
		case GLUT_KEY_DOWN:
			slow = true;
			printf("Low Speed");
			glutTimerFunc(9,FPS,0); //1 sec
			break;

	}

}


void callBackInit(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutTimerFunc(0 , FPS, 0);

}




int main(int argc, char** argv)
{	
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);


	


	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Natasha's Conway Game");	//creates the window

	printf("Welcome to the simulation. The keys to control are...\n");
	printf("t: will create a random board of cells.\n");
	printf("p: will alternate between play and pause functionality.\n");
	printf("r: will clear/reset the board.\n");
	printf("up arrow: go to high speed.\n");
	printf("down arrow: go to low speed.\n");
	printf("\n");

	printf("the game will pause after a randomization, or clearing of the board.\n");
	printf("throughout the simulation, the console will inform you of the state of the program.\n");

	printf("\n");

	callBackInit();
	init();

	glutMainLoop();				//starts the event glutMainLoop

	return(0);	
}