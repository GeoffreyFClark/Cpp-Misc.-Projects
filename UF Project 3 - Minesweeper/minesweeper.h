#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;


struct Cell {
	Cell(map<string, Texture>& textures, int xpos, int ypos);
	vector<Cell*> adjacents;
	void updateIcon(map<string, Texture>& textures);
	void loadBomb(bool bombstate);
	bool reveal(int& counter);
	bool toggleFlag();
	void toggleDebug();
	void GameOverRevealAll();
	void draw(RenderWindow& w);
	int surroundingBombHolder;
	bool bombBool;
	bool isflagged;
	bool isrevealed;
	Sprite background;
	Sprite foreground;
	Sprite flagicon;
	Sprite icon;
	bool debugOn;
};


struct GameHandler {
	GameHandler();
	void ReadConfigFile();
	void run();
	void CellBitsToBools(vector<int>& bits);
	void RandomizeBombLocations();
	void InstantiateEmptyCells();
	void LoadBombs();
	void Debug();
	void RefreshSmileyFace();
	void Visualize(RenderWindow& window);
	void LoadCellNumIcons();
	void RefreshBombsRemaining();
	void Update(RenderWindow& window);
	int columns;
	int rows;
	int num_bombs;
	int window_width;
	int centerX_width;
	int window_height;
	int bombs_remaining;
	int cells_revealed;
	bool gameLost;
	bool gameEnded;
	Clock clickCooldown;
	Sprite hundreds;
	Sprite tens;
	Sprite ones;
	Sprite smileyFace;
	Sprite debugButton;
	Sprite test1Button;
	Sprite test2Button;
	Sprite test3Button;
	map<string, Texture> icontextures;
	vector<Cell> cells;
	vector<bool> CellBoolean;
	vector<int> testBoard_1;
	vector<int> testBoard_2;
	vector<int> testBoard_3;
};