// MatthewsGameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

/*
@Author Matthew Pecko
A 'linked' 2d vector of nodes. All functions are void for now because I only want to print out the values to make sure
my data structure is linked properly. The end goal of this project is to make a faster implementaion of Conways Game of Life.
and then add a "Personality" structure to each cell, which will be passed on to new cells based on the neighbors personalities.
*/
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

struct cell {
	int value = 0;
	std::string name = "*";
};

struct node {
	cell* data = new cell();

	int state = 0;
	std::string name = "*";

	node* n = NULL;
	node* ne = NULL;
	node* e = NULL;
	node* se = NULL;
	node* s = NULL;
	node* sw = NULL;
	node* w = NULL;
	node* nw = NULL;
};

int main()
{
	int ROWS;
	int COLS;

	//Create a manual sized glider
	
	node alive;
	alive.state = 1;
	node dead;
	dead.state = 0;
	std::vector< std::vector<node> > world {
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, alive, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, alive, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, alive, alive, alive, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
		{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead}
	};
	ROWS = world.size();
	COLS = world[0].size();
	


	//Create randomozied alive/dead grid
	/*
	ROWS = 70;
	COLS = 230;
	std::vector< std::vector<node> > world(ROWS, std::vector<node>(COLS));
	srand(time(0));
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			world[i][j].state = rand() % 2;
		}
	}
	*/

	//Set all the pointers of the matrix
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			int counter = 0;
			for (int k = -1; k < 2; k++) {
				for (int m = -1; m < 2; m++) {
					if (!(k == 0 && m == 0)) {
						counter++;
						int col = (j + k + COLS) % COLS;
						int row = (i + m + ROWS) % ROWS;
						switch (counter) {
						case 1:
							world[i][j].nw = &world[row][col];
							break;
						case 2:
							world[i][j].w = &world[row][col];
							break;
						case 3:
							world[i][j].sw = &world[row][col];
							break;
						case 4:
							world[i][j].n = &world[row][col];
							break;
						case 5:
							world[i][j].s = &world[row][col];
							break;
						case 6:
							world[i][j].ne = &world[row][col];
							break;
						case 7:
							world[i][j].e = &world[row][col];
							break;
						case 8:
							world[i][j].se = &world[row][col];
							break;
						}

					}
				}
			}
		}
	}


	//Update loop
	while (true) {
		//create the next generation and pass all the same pointers from last generation
		std::vector<std::vector<node>> nextGen = world;

		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				int lives = 0;
				if (world[i][j].n->state == 1) {
					lives++;
				}
				if (world[i][j].ne->state == 1) {
					lives++;
				}
				if (world[i][j].e->state == 1) {
					lives++;
				}
				if (world[i][j].se->state == 1) {
					lives++;
				}
				if (world[i][j].s->state == 1) {
					lives++;
				}
				if (world[i][j].sw->state == 1) {
					lives++;
				}
				if (world[i][j].w->state == 1) {
					lives++;
				}
				if (world[i][j].nw->state == 1) {
					lives++;
				}

				if ((world[i][j].state == 1) && (lives < 2)) {
					nextGen[i][j].state = 0;
				}
				else if ((world[i][j].state == 1) && (lives > 3)) {
					nextGen[i][j].state = 0;
				}
				else if ((world[i][j].state == 0) && (lives == 3)) {
					nextGen[i][j].state = 1;
				}
				else {
					nextGen[i][j].state = world[i][j].state;
				}
			}
		}
		world = nextGen;

		//Print the world
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (world[i][j].state == 0) {
					std::cout << ' ';
				}
				else {
					std::cout << '*';
				}
			}
			std::cout << "\n";
		}

		//Clear the screen
		system("CLS");
	}

	//debugging
	int x;
	std::cin >> x;
}
