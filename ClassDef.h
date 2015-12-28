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

enum GameState {
	Uninitialized, Paused,
	ShowingMenu, Playing, Exiting, Died
};

struct scoruri
{
	int valoare;
	string nume;
};

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
	int oldpoz_x = 0;
	int oldpoz_y = 0;
};

int rez = 25;

RectangleShapeLocal pacman(sf::Vector2f(rez, rez));
RectangleShapeLocal blueP(sf::Vector2f(rez, rez));
RectangleShapeLocal redP(sf::Vector2f(rez, rez));
RectangleShapeLocal greenP(sf::Vector2f(rez, rez));
RectangleShapeLocal medP(sf::Vector2f(rez, rez));













scoruri scoruri_array[100];
scoruri aux;










char level[100][100];

int pacmanStartPoz_x = 1, pacmanStartPoz_y = 1;
int x = pacmanStartPoz_x*rez, y = pacmanStartPoz_y*rez;
int x_old = x, y_old = y;
int score;
int v[100][100] = { 10000 };
int viz1 = 0, viz2 = 0;
int vz1 = 0, vz2 = 0;

sf::Vector2f limit;
sf::RenderWindow window;
sf::RectangleShape wall(sf::Vector2f(rez-1, rez-1));
sf::RectangleShape gate(sf::Vector2f(rez, rez));
sf::RectangleShape score_point(sf::Vector2f(rez / 3, rez / 3));
sf::RectangleShape Background(sf::Vector2f(700 ,750));
sf::RectangleShape Background2(sf::Vector2f(700, 750));
sf::Text PauseText,Naem,Nume_Scor;
sf::Font Arial;
sf::Texture HeartTexture;
sf::Texture Background_Texture;
sf::Texture Background_Texture2;
sf::Sprite Heart;
string inputName;
string outputScor;




int minT(int i1, int i2, int i3, int i4)
{
	if (i1 <= i2 && i1 <= i3 && i1 <= i4) return 1;
	if (i2 <= i1 && i2 <= i3 && i2 <= i4) return 2;
	if (i3 <= i1 && i3 <= i2 && i3 <= i4) return 3;
	if (i4 <= i1 && i4 <= i2 && i4 <= i3) return 4;
	return 0;
}
bool first = true;
bool second = true;
static GameState _gameState=ShowingMenu;
int lives;


TextMenu Play, Score, Exit, Continue;
TextMenu *current = &Play;
sf::Text ScoreM;



void CreateMenuText()
{
	Play.setString("New Game");
	Exit.setString("Exit");
	Continue.setString("Continue");
	Naem.setString("");

	Continue.setFont(Arial);
	Continue.setCharacterSize(60);
	Continue.setPosition(limit.x / 2 * 30, limit.y / 2 * 20);
	Continue.setColor(sf::Color::Black);

	Play.setFont(Arial);
	Play.setCharacterSize(60);
	Play.setPosition(limit.x / 2 * 30, limit.y / 2 * 25);
	Play.setColor(sf::Color::Red);

	Exit.setFont(Arial);
	Exit.setCharacterSize(60);
	Exit.setPosition(limit.x / 2 * 30, limit.y / 2 * 30);
	Exit.setColor(sf::Color::Red);

	Nume_Scor.setFont(Arial);
	Nume_Scor.setCharacterSize(60);
	Nume_Scor.setPosition(limit.x / 2, limit.y / 2 * 20);
	Nume_Scor.setColor(sf::Color::Red);

	current = &Continue;
	Continue.urm = &Play;
	Continue.pre = &Exit;
	Play.urm = &Exit;
	Play.pre = &Continue;
	Exit.urm = &Continue;
	Exit.pre = &Play;
}