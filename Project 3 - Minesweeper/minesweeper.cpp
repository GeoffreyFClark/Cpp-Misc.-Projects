#include "minesweeper.h"

// Constructs cell. Initializes textures, position, and boolean states.
Cell::Cell(map<string, Texture>& textures, int xpos, int ypos) {
	background.setPosition(xpos, ypos);
	foreground.setPosition(xpos, ypos);
	flagicon.setPosition(xpos, ypos);
	icon.setPosition(xpos, ypos);

	background.setTexture(textures["revealed"]);
	foreground.setTexture(textures["hidden"]);
	flagicon.setTexture(textures["flag"]);

	flagicon.setColor(Color(255, 255, 255, 0));
	bombBool = false;
	isrevealed = false;
	isflagged = false;
	debugOn = false;
}

//sets cell as bomb or not
void Cell::loadBomb(bool isBombCell) {
	bombBool = isBombCell;
}

// Toggles debug mode, which can reveal bombs.
void Cell::toggleDebug() {
	if (bombBool && !isrevealed) {
		if (debugOn) {
			debugOn = false;
			icon.setColor(Color(255, 255, 255, 0));
		}
		else {
			debugOn = true;
			icon.setColor(Color(255, 255, 255, 255));
		}
	}
}

// Toggles cell's flag 
bool Cell::toggleFlag() {
	if (!isrevealed) {
		if (isflagged) {
			isflagged = false;
			flagicon.setColor(Color(255, 255, 255, 0));
		}
		else {
			isflagged = true;
			flagicon.setColor(Color(255, 255, 255, 255));
		}
	}
	return isflagged;
}

// Reveal all bombs on the board, can be used when game is over.
void Cell::GameOverRevealAll() {
	if (bombBool && !isrevealed) {
		icon.setColor(Color(255, 255, 255, 255));
	}
}

// Uncovers cell, revealing its content. Returns whether it contains a bomb.
bool Cell::reveal(int& counter) {
	if (!isrevealed && !isflagged) {
		isrevealed = true;
		counter++;
		foreground.setColor(Color(255, 255, 255, 0));
		icon.setColor(Color(255, 255, 255, 255));
		if (surroundingBombHolder == 0 && !bombBool) {
			for (int i = 0; i < 8; i++) {
				if (adjacents[i] != nullptr && !(adjacents[i]->bombBool)) {
					adjacents[i]->reveal(counter);
				}
			}
		}
	}
	return bombBool;
}

// Resets cell to initial state and sets appropriate icon based on bomb/surrounding bombs.
void Cell::updateIcon(map<string, Texture>& textures) {
	surroundingBombHolder = 0;
	for (int i = 0; i < 8; i++) {
		if (adjacents[i] != nullptr && adjacents[i]->bombBool) {
			surroundingBombHolder++;
		}
	}
	if (bombBool)
		icon.setTexture(textures["bomb"]);
	else {
		switch (surroundingBombHolder) {
		case 1: icon.setTexture(textures["one"]); break;
		case 2: icon.setTexture(textures["two"]); break;
		case 3: icon.setTexture(textures["three"]); break;
		case 4: icon.setTexture(textures["four"]); break;
		case 5: icon.setTexture(textures["five"]); break;
		case 6: icon.setTexture(textures["six"]); break;
		case 7: icon.setTexture(textures["seven"]); break;
		case 8: icon.setTexture(textures["eight"]); break;
		default: icon.setTexture(textures["revealed"]); break;
		}
	}
	icon.setColor(Color(255, 255, 255, 0));
	flagicon.setColor(Color(255, 255, 255, 0));
	foreground.setColor(Color(255, 255, 255, 255));
	isrevealed = false;
	isflagged = false;
	debugOn = false;
}

// Renders cell's layers to the window.
void Cell::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(foreground);
	window.draw(flagicon);
	window.draw(icon);
}




// .cfg file and testboards dimensions must match, else unusual results e.g. 20col 32row
void GameHandler::ReadConfigFile() {
	string filename = "boards/config.cfg";
	ifstream file(filename);
	if (file.is_open()) {
		string line;
		getline(file, line);
		columns = stoi(line);
		getline(file, line);
		rows = stoi(line);
		getline(file, line);
		num_bombs = stoi(line);

		file.close();
	}
	else {
		cout << "boards/config.cfg file missing!" << endl;
	}

	window_width = columns * 32;
	centerX_width = window_width / 2;
	window_height = (rows * 32) + 100;
}

void GameHandler::run() {
	RenderWindow window(VideoMode((columns * 32), ((rows * 32) + 100)), "Minesweeper by Geoff F. Clark");

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.clear(Color(255, 255, 255, 255));
		Update(window);
		window.display();
	}
}

GameHandler::GameHandler() {
	ReadConfigFile();
	bombs_remaining = num_bombs;
	srand(time(NULL)); // seed random using current time
	fstream file;
	string currentLine;

	file.open("boards/testboard1.brd");
	//file.open("boards/lots_o_mines.brd");
	//file.open("boards/recursion_test.brd");
	if (file.is_open()) {
		int tempRows = 0;
		while (getline(file, currentLine)) {
			auto currentCharacter = currentLine.begin();
			while (currentCharacter != currentLine.end()) {
				int convertedChar = (*currentCharacter) - 48;
				testBoard_1.push_back(convertedChar);
				currentCharacter++;
			}
		}
		file.close();
	}
	file.open("boards/testboard2.brd");
	if (file.is_open()) {
		int tempRows = 0;
		while (getline(file, currentLine)) {
			auto currentCharacter = currentLine.begin();
			while (currentCharacter != currentLine.end()) {
				int convertedChar = (*currentCharacter) - 48;
				testBoard_2.push_back(convertedChar);
				currentCharacter++;
			}
		}
		file.close();
	}
	file.open("boards/testboard3.brd");
	if (file.is_open()) {
		int tempRows = 0;
		while (getline(file, currentLine)) {
			auto currentCharacter = currentLine.begin();
			while (currentCharacter != currentLine.end()) {
				int convertedChar = (*currentCharacter) - 48;
				testBoard_3.push_back(convertedChar);
				currentCharacter++;
			}
		}
		file.close();
	}

	Texture container;
	container.loadFromFile("images/number_1.png");
	icontextures.emplace("one", container);
	container.loadFromFile("images/number_2.png");
	icontextures.emplace("two", container);
	container.loadFromFile("images/number_3.png");
	icontextures.emplace("three", container);
	container.loadFromFile("images/number_4.png");
	icontextures.emplace("four", container);
	container.loadFromFile("images/number_5.png");
	icontextures.emplace("five", container);
	container.loadFromFile("images/number_6.png");
	icontextures.emplace("six", container);
	container.loadFromFile("images/number_7.png");
	icontextures.emplace("seven", container);
	container.loadFromFile("images/number_8.png");
	icontextures.emplace("eight", container);
	container.loadFromFile("images/mine.png");
	icontextures.emplace("bomb", container);
	container.loadFromFile("images/flag.png");
	icontextures.emplace("flag", container);
	container.loadFromFile("images/tile_revealed.png");
	icontextures.emplace("revealed", container);
	container.loadFromFile("images/tile_hidden.png");
	icontextures.emplace("hidden", container);

	container.loadFromFile("images/digits.png");
	icontextures.emplace("digits", container);
	container.loadFromFile("images/face_happy.png");
	icontextures.emplace("happy", container);
	container.loadFromFile("images/face_win.png");
	icontextures.emplace("win", container);
	container.loadFromFile("images/face_lose.png");
	icontextures.emplace("lose", container);
	container.loadFromFile("images/debug.png");
	icontextures.emplace("debug", container);
	container.loadFromFile("images/test_1.png");
	icontextures.emplace("testone", container);
	container.loadFromFile("images/test_2.png");
	icontextures.emplace("testtwo", container);
	container.loadFromFile("images/test_3.png");
	icontextures.emplace("testthree", container);

	hundreds.setTexture(icontextures["digits"]);
	hundreds.setTextureRect(Rect<int>(0, 0, 21, 32));
	hundreds.setPosition(0, window_height - 100);
	tens.setTexture(icontextures["digits"]);
	tens.setTextureRect(Rect<int>(21 * 5, 0, 21, 32));
	tens.setPosition(21, window_height - 100);
	ones.setTexture(icontextures["digits"]);
	ones.setTextureRect(Rect<int>(0, 0, 21, 32));
	ones.setPosition(42, window_height - 100);
	smileyFace.setTexture(icontextures["happy"]);
	smileyFace.setPosition(centerX_width - 32, window_height - 100);
	debugButton.setTexture(icontextures["debug"]);
	debugButton.setPosition(centerX_width + 96, window_height - 100);
	test1Button.setTexture(icontextures["testone"]);
	test1Button.setPosition(centerX_width + 160, window_height - 100);
	test2Button.setTexture(icontextures["testtwo"]);
	test2Button.setPosition(centerX_width + 224, window_height - 100);
	test3Button.setTexture(icontextures["testthree"]);
	test3Button.setPosition(centerX_width + 288, window_height - 100);

	InstantiateEmptyCells();
	RandomizeBombLocations();
}

// creates vector of unique, randomized bomb locations baed on config file
void GameHandler::RandomizeBombLocations() {
	CellBoolean.clear();
	ReadConfigFile();
	vector<int> bits;
	int randyNum;

	bool can_add = false;
	for (int i = 0; i < num_bombs; i++) {
		while (!can_add) {
			randyNum = rand() % (columns * rows);
			if (find(bits.begin(), bits.end(), randyNum) == bits.end()) {
				bits.push_back(randyNum);
				can_add = true;
			}
		}
		can_add = false;
	}
	CellBoolean.resize(columns * rows, false); // Initialize all cells to false (no bomb)
	for (int i : bits) {
		CellBoolean[i] = true; // Set cells with bombs to true
	}

	bombs_remaining = num_bombs;
	cells_revealed = 0;
	gameLost = false;
	gameEnded = false;

	LoadBombs();
	LoadCellNumIcons();
	RefreshBombsRemaining();
}

// Uses bits to store boolean for each cell (TODO: skip boolean conversions, just use 0/1 directly to denote bomb)
void GameHandler::CellBitsToBools(vector<int>& bits) {
	CellBoolean.clear();
	num_bombs = 0;
	for (int i = 0; i < bits.size(); i++) {
		if (bits[i] == 0) {
			CellBoolean.push_back(false);
		}
		else if (bits[i] == 1) {
			CellBoolean.push_back(true);
			num_bombs++;
		}
	}

	bombs_remaining = num_bombs;
	cells_revealed = 0;
	gameLost = false;
	gameEnded = false;

	LoadBombs();
	LoadCellNumIcons();
	RefreshBombsRemaining();
}

//instantiates 2D array of empty cells
void GameHandler::InstantiateEmptyCells() {
	int x = 0;
	int y = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Cell cell = Cell(icontextures, x, y);
			cells.push_back(cell);
			x += 32;
		}
		x = 0;
		y += 32;
	}
}

void GameHandler::LoadBombs() {
	for (int i = 0; i < (rows * columns); i++) {
		cells[i].loadBomb(CellBoolean[i]);
	}
}

void GameHandler::RefreshSmileyFace() {
	if (gameEnded) {
		if (gameLost)
			smileyFace.setTexture(icontextures["lose"]);
		else
			smileyFace.setTexture(icontextures["win"]);
	}
	else smileyFace.setTexture(icontextures["happy"]);
}

//calls toggleDebug on each cell
void GameHandler::Debug() {
	for (int i = 0; i < (columns * rows); i++) {
		cells[i].toggleDebug();
	}
}

void GameHandler::Visualize(RenderWindow& window) {
	for (int i = 0; i < (columns * rows); i++) {
		cells[i].draw(window);
	}
	window.draw(hundreds);
	window.draw(tens);
	window.draw(ones);
	window.draw(smileyFace);
	window.draw(debugButton);
	window.draw(test1Button);
	window.draw(test2Button);
	window.draw(test3Button);
}

//assigns icon baed on number of adjacent bombs
void GameHandler::LoadCellNumIcons()
{
	for (int i = 0; i < (rows * columns); i++) {
		cells[i].adjacents.clear();
		for (int j = 0; j < 8; j++) {
			cells[i].adjacents.push_back(nullptr);
		}
		if (i == 0) //top left cell
		{
			cells[i].adjacents[4] = &(cells[i + 1]);
			cells[i].adjacents[6] = &(cells[i + columns]);
			cells[i].adjacents[7] = &(cells[i + columns + 1]);
		}
		else if (i == columns - 1) // top right cell
		{
			cells[i].adjacents[3] = &(cells[i - 1]);
			cells[i].adjacents[5] = &(cells[i + columns - 1]);
			cells[i].adjacents[6] = &(cells[i + columns]);
		}
		else if (i == (rows - 1) * columns) // bottom left cell
		{
			cells[i].adjacents[4] = &(cells[i + 1]);
			cells[i].adjacents[1] = &(cells[i - columns]);
			cells[i].adjacents[2] = &(cells[i - columns + 1]);
		}
		else if (i == rows * columns - 1) // bottom right cell
		{
			cells[i].adjacents[3] = &(cells[i - 1]);
			cells[i].adjacents[1] = &(cells[i - columns]);
			cells[i].adjacents[0] = &(cells[i - columns - 1]);
		}
		else if (i < columns) // top row cell
		{
			cells[i].adjacents[3] = &(cells[i - 1]);
			cells[i].adjacents[4] = &(cells[i + 1]);
			cells[i].adjacents[5] = &(cells[i + columns - 1]);
			cells[i].adjacents[6] = &(cells[i + columns]);
			cells[i].adjacents[7] = &(cells[i + columns + 1]);
		}
		else if (i >= (rows - 1) * columns) // bottom row cell
		{
			cells[i].adjacents[3] = &(cells[i - 1]);
			cells[i].adjacents[4] = &(cells[i + 1]);
			cells[i].adjacents[2] = &(cells[i - columns + 1]);
			cells[i].adjacents[1] = &(cells[i - columns]);
			cells[i].adjacents[0] = &(cells[i - columns - 1]);
		}
		else if ((i % columns) == 0) // left column cell
		{
			cells[i].adjacents[4] = &(cells[i + 1]);
			cells[i].adjacents[6] = &(cells[i + columns]);
			cells[i].adjacents[7] = &(cells[i + columns + 1]);
			cells[i].adjacents[1] = &(cells[i - columns]);
			cells[i].adjacents[2] = &(cells[i - columns + 1]);
		}
		else if (((i + 1) % columns) == 0) // right column cell
		{
			cells[i].adjacents[3] = &(cells[i - 1]);
			cells[i].adjacents[0] = &(cells[i - columns - 1]);
			cells[i].adjacents[1] = &(cells[i - columns]);
			cells[i].adjacents[5] = &(cells[i + columns - 1]);
			cells[i].adjacents[6] = &(cells[i + columns]);
		}
		else // middle cell
		{
			cells[i].adjacents[3] = &(cells[i - 1]);
			cells[i].adjacents[4] = &(cells[i + 1]);
			cells[i].adjacents[5] = &(cells[i + columns - 1]);
			cells[i].adjacents[6] = &(cells[i + columns]);
			cells[i].adjacents[7] = &(cells[i + columns + 1]);
			cells[i].adjacents[2] = &(cells[i - columns + 1]);
			cells[i].adjacents[1] = &(cells[i - columns]);
			cells[i].adjacents[0] = &(cells[i - columns - 1]);
		}
		cells[i].updateIcon(icontextures);
	}
}

void GameHandler::RefreshBombsRemaining() {
	int hundredsplace = 0;
	int tensplace = 0;
	int onesplace = 0;
	int temp = bombs_remaining;

	if (temp < 0) {
		hundreds.setTextureRect(Rect<int>(21 * 10, 0, 21, 32));
		temp *= -1;
	}
	else if (100 > temp && temp >= 0) {
		hundreds.setTextureRect(Rect<int>(0, 0, 21, 32));
	}
	else if (temp >= 100) {
		hundredsplace = temp / 100;
		temp %= 100;
		hundreds.setTextureRect(Rect<int>(21 * hundredsplace, 0, 21, 32));
	}

	if (temp >= 10) {
		tensplace = temp / 10;
		temp %= 10;
	}
	onesplace = temp;

	tens.setTextureRect(Rect<int>(21 * tensplace, 0, 21, 32));
	ones.setTextureRect(Rect<int>(21 * onesplace, 0, 21, 32));
}

//left and right click event logic
void GameHandler::Update(RenderWindow& window) {
	if (clickCooldown.getElapsedTime().asMilliseconds() >= 175) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i position = Mouse::getPosition(window);
			if (position.y >= 0 && position.y < (window_height - 100) && !gameEnded) {
				if (position.x >= 0 && position.x <= window_width) {
					int x = (position.x / 32);
					int y = (position.y / 32);
					int pos = (y * columns) + x;
					int count = 0;
					if (!cells[pos].isflagged) {
						if (cells[pos].reveal(count)) {
							gameEnded = true;
							gameLost = true;
							for (int i = 0; i < (columns * rows); i++) {
								cells[i].GameOverRevealAll();
							}
						}
						else cells_revealed += count;
					}
				}
			}
			else if (position.y >= (window_height - 100) && position.y < (window_height - 36)) {
				if (position.x >= (centerX_width - 32) && position.x < (centerX_width + 32)) {
					RandomizeBombLocations();
				}
				if (position.x >= (centerX_width + 96) && position.x < (centerX_width + 160) && !gameEnded) {
					Debug();
				}
				if (position.x >= (centerX_width + 160) && position.x < (centerX_width + 224)) {
					CellBitsToBools(testBoard_1);
				}
				if (position.x >= (centerX_width + 224) && position.x < (centerX_width + 288)) {
					CellBitsToBools(testBoard_2);
				}
				if (position.x >= (centerX_width + 288) && position.x < (centerX_width + 352)) {
					CellBitsToBools(testBoard_3);
				}
			}
			clickCooldown.restart();
		}

		if (Mouse::isButtonPressed(Mouse::Right) && !gameEnded) {
			Vector2i position = Mouse::getPosition(window);
			if (position.x >= 0 && position.x <= window_width) {
				if (position.y >= 0 && position.y <= (window_height - 100)) {
					int x = (position.x / 32);
					int y = (position.y / 32);

					int pos = (y * columns) + x;
					if (!cells[pos].isflagged && !cells[pos].isrevealed) {
						cells[pos].toggleFlag();
						bombs_remaining--;
					}
					else if (!cells[pos].isrevealed && cells[pos].isflagged) {
						cells[pos].toggleFlag();
						bombs_remaining++;
					}
					RefreshBombsRemaining();
				}
			}
			clickCooldown.restart();
		}
	}
	if (cells_revealed == ((columns * rows) - num_bombs) && !gameLost) {
		gameEnded = true;
		for (int i = 0; i < (columns * rows); i++) {
			if (cells[i].bombBool && !cells[i].isflagged) {
				cells[i].toggleFlag();
			}
		}
		bombs_remaining = 0;
		RefreshBombsRemaining();
	}
	RefreshSmileyFace();
	Visualize(window);
}