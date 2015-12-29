#pragma warning
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include <map>
#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class TextMenu : public sf::Text //used in Menu
{
public:
	using Text::Text;
	TextMenu *pre;
	TextMenu *urm;
};

TextMenu Play, Score, Exit, Continue;
TextMenu *current = &Play;
sf::Text ScoreM;

enum GameState {
	Uninitialized, Paused,
	ShowingMenu, Playing, Exiting, Died
};

static GameState _gameState = ShowingMenu;

struct scoruri
{
	int valoare;
	string nume;
};

scoruri scoruri_array[100];
scoruri aux;

class RectangleShapeLocal : public sf::RectangleShape
{
public:
	using RectangleShape::RectangleShape;
	using RectangleShape::move;
	bool canMoveRight();
	bool canMoveLeft();
	bool canMoveUp();
	bool canMoveDown();
	bool isMoving();
	bool isColliding(RectangleShapeLocal aux);
	char moving;
	void passive_move();
	void aggressive_move();
	void run_move();
	void Respawn();
	int oldpoz_x = 0;
	int oldpoz_y = 0;
};

int rez = 25;

RectangleShapeLocal pacman(sf::Vector2f(rez, rez));
RectangleShapeLocal blueP(sf::Vector2f(rez, rez));
RectangleShapeLocal redP(sf::Vector2f(rez, rez));
RectangleShapeLocal greenP(sf::Vector2f(rez, rez));
RectangleShapeLocal medP(sf::Vector2f(rez, rez));

/////////////////////////////////////////////////////
/////  GLOBAL VARIABLES //\\ GLOBAL VARIABLES  //////
/////////////////////////////////////////////////////

char level[100][100];
int pacmanStartPoz_x = 1, pacmanStartPoz_y = 1;
int x = pacmanStartPoz_x*rez, y = pacmanStartPoz_y*rez;
int x_old = x, y_old = y;
int score;
int v[100][100] = { 10000 };
bool first = true;
int lives,k;
sf::Vector2f limit;
sf::RenderWindow window;
sf::RectangleShape wall(sf::Vector2f(rez - 1, rez - 1));
sf::RectangleShape gate(sf::Vector2f(rez, rez));
sf::RectangleShape score_point(sf::Vector2f(rez / 3, rez / 3));
sf::RectangleShape x_point(sf::Vector2f(rez / 2.5, rez / 2.5));
sf::RectangleShape Background(sf::Vector2f(700, 750));
sf::RectangleShape Background2(sf::Vector2f(700, 750));
sf::Text PauseText, Naem, Nume_Scor;
sf::Font Arial;
sf::Texture HeartTexture;
sf::Texture Background_Texture;
sf::Texture Background_Texture2;
sf::Sprite Heart;
string inputName;
string outputScor;
sf::Clock xclock,tclock;