#include "Gaim.h"
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
	int oldpoz_x=0;
	int oldpoz_y=0;
};
RectangleShapeLocal pacman(sf::Vector2f(rez, rez));
RectangleShapeLocal blueP(sf::Vector2f(rez, rez));
RectangleShapeLocal redP(sf::Vector2f(rez, rez));
RectangleShapeLocal greenP(sf::Vector2f(rez, rez));
RectangleShapeLocal medP(sf::Vector2f(rez, rez));
int Distanta(sf::Vector2f v1, sf::Vector2f v2) {
	int x1 = v1.x;
	int x2 = v2.x;
	int y1 = v1.y;
	int y2 = v2.y;
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
void CreareVectorDist()
{
	ofstream fout("date.out");
	int i, j;
	sf::Vector2f p = pacman.getPosition();
	sf::Vector2f l;
	for (j = 0; j <= limit.y; j++)
	{
		for (i = 0; i <= limit.x; i++)
		{
			if (level[i][j] == 't' || level[i][j] == 'a' || level[i][j] == 'g')
			{
				v[i][j] = 10000;
			}
			else
			{
				if (level[i][j] != 'w')
				{
					l.x = j * 25;
					l.y = i * 25;
					v[i][j] = Distanta(l, p);
				}
				else v[i][j] = 10000;
			}
		}
	}
}
bool RectangleShapeLocal::canMoveRight()
{
	int poz_x, poz_y;
	poz_x = this->getPosition().y;
	poz_y = this->getPosition().x;
	if (level[poz_x / rez][poz_y / rez + 1] == 'w')
		return false;
	else
		return true;
}
bool RectangleShapeLocal::canMoveLeft()
{
	int poz_x, poz_y;
	poz_x = this->getPosition().y;
	poz_y = this->getPosition().x;
	if (level[poz_x / rez][poz_y / rez - 1] == 'w')
		return false;
	else
		return true;
}
bool RectangleShapeLocal::canMoveUp()
{
	int poz_x, poz_y;
	poz_x = this->getPosition().y;
	poz_y = this->getPosition().x;
	if (level[poz_x / rez -1][poz_y / rez] == 'w')
		return false;
	else
		return true;
}
bool RectangleShapeLocal::canMoveDown()
{
	int poz_x, poz_y;
	poz_x = this->getPosition().y;
	poz_y = this->getPosition().x;
	if (level[poz_x / rez + 1][poz_y / rez] == 'w')
		return false;
	else
		return true;
}
bool RectangleShapeLocal::isMoving()
{
	int poz_x, poz_y;
	poz_x = this->getPosition().y;
	poz_y = this->getPosition().x;
	if (poz_y%rez == 0 && poz_x%rez == 0)
		return false;
	else return true;
}
bool RectangleShapeLocal::isColliding(RectangleShapeLocal aux)
{
	sf::Vector2f a, b;
	a = this->getPosition();
	b = aux.getPosition();
	if ((a.x < b.x + 10 && a.x>b.x - 10) && (a.y < b.y + 10 && a.y>b.y - 10))
		return true;
	return false;
}
char moving;
char rmoving;
void RectangleShapeLocal::passive_move()
{
	if (!this->isColliding(pacman))
	{
		if (this->isMoving())
		{
			switch (this->moving)
			{
			case 'l': {

				this->move(-1, 0); break;
			}
			case 'r': {

				this->move(1, 0); break;
			}
			case 'u': {

				this->move(0, -1); break;
			}
			case 'd': {

				this->move(0, 1); break;
			}
			}
			return;
		}
		else
		{
			CreareVectorDist();
			int poz_x, poz_y;
			poz_x = (this->getPosition().y) / 25;
			poz_y = (this->getPosition().x) / 25;

			v[this->oldpoz_x][this->oldpoz_y] = 999;
			if (v[poz_x][poz_y - 1] < 999) v[poz_x][poz_y - 1] = rand() % 100;
			if (v[poz_x][poz_y + 1] < 999) v[poz_x][poz_y + 1] = rand() % 100;
			if (v[poz_x - 1][poz_y] < 999) v[poz_x - 1][poz_y] = rand() % 100;
			if (v[poz_x + 1][poz_y] < 999) v[poz_x + 1][poz_y] = rand() % 100;

			int min = minT(v[poz_x][poz_y - 1], v[poz_x][poz_y + 1], v[poz_x - 1][poz_y], v[poz_x + 1][poz_y]);

			switch (min)
			{
			case 1:
			{
				this->move(-1, 0);
				this->moving = 'l';
				this->oldpoz_x = poz_x;
				this->oldpoz_y = poz_y;
				break;
			}
			case 2:
			{
				this->move(1, 0);
				this->moving = 'r';
				this->oldpoz_x = poz_x;
				this->oldpoz_y = poz_y;
				break;
			}
			case 3:
			{
				this->move(0, -1);
				this->moving = 'u';
				this->oldpoz_x = poz_x;
				this->oldpoz_y = poz_y;
				break;
			}
			case 4:
			{
				this->move(0, 1);
				this->moving = 'd';
				this->oldpoz_x = poz_x;
				this->oldpoz_y = poz_y;
				break;
			}

			}
		}
	}
	else _gameState = Died;
}
void RectangleShapeLocal::aggressive_move()
{
	if (!this->isColliding(pacman))
		if (this->isMoving())
		{
			switch (this->moving)
			{
			case 'l': {
				this->move(-1, 0); break;
			}
			case 'r': {
				this->move(1, 0); break;
			}
			case 'u': {
				this->move(0, -1); break;
			} 
			case 'd': {
				this->move(0, 1); break;
			}
			}
			return;
		}
		else
		{
			CreareVectorDist();

			int poz_x, poz_y;
			poz_x = (this->getPosition().y) / 25;
			poz_y = (this->getPosition().x) / 25;
			if (v[this->oldpoz_x][this->oldpoz_y] < 1000) v[this->oldpoz_x][this->oldpoz_y] = 999;
			int min = minT(v[poz_x][poz_y - 1], v[poz_x][poz_y + 1], v[poz_x - 1][poz_y], v[poz_x + 1][poz_y]);
			//cout << "Stanga " << v[poz_x][poz_y - 1] << endl;
			//cout << "Dreapta " << v[poz_x][poz_y + 1] << endl;
			//cout << "Sus " << v[poz_x - 1][poz_y] <<endl;
			//cout << "Jos " << v[poz_x + 1][poz_y]<<endl;
			switch (min)
			{
			case 1:
			{
				this->move(-1, 0);
				this->moving = 'l';
				this->oldpoz_x = poz_x;
				this->oldpoz_y = poz_y;
				break;
			}
			case 2:
			{
				this->move(1, 0);
				moving = 'r';
				this->oldpoz_x = poz_x;
				this->oldpoz_y = poz_y;
				break;
			}
			case 3:
			{
				this->move(0, -1);
				this->moving = 'u';
				this->oldpoz_x = poz_x;
				this->oldpoz_y = poz_y;
				break;
			}
			case 4:
			{
				this->move(0, 1);
				this->moving = 'd';
				this->oldpoz_x = poz_x;
				this->oldpoz_y = poz_y;
				break;
			}
			}
		}
	else _gameState = Died;
}

void WriteConsole()
{
	sf::Vector2f a = blueP.getPosition();
	bool r,l,u,d;
	system("cls");
	cout << "Score = " << score << " ";
	cout << "PacmanPoz<" << x/rez << "," << y/rez << ">" << endl;
	r = pacman.canMoveRight();
	if (r) cout << "Pacman poate mere dreapta"<<endl;
	else cout << "Pacman nu poate mere dreapta"<<endl;
	l = pacman.canMoveLeft();
	if (l) cout << "Pacman poate mere stanga"<<endl;
	else cout << "Pacman nu poate mere stanga"<<endl;
	u = pacman.canMoveUp();
	if (u) cout << "Pacman poate mere sus" << endl;
	else cout << "Pacman nu poate mere sus" << endl;
	d = pacman.canMoveDown();
	if (d) cout << "Pacman poate mere jos" << endl;
	else cout << "Pacman nu poate mere jos" << endl;
	cout << v[(int)(a.y / rez)][(int)(a.x / rez)]<<endl;
	cout << "BluePoz<" << a.y /rez << "," << a.x /rez << ">" << endl;
	cout << "<" << limit.x - 1 << "> <" << limit.y + 2 << "> limita <x><y>";
}

void ReadLevel()
{
	ifstream fin("date.in");
	ofstream fout("date.out");
	int i, j;
	i = 0, j = 0;
	char code;
	while (fin)
	{
		fin >> noskipws >> code;
		if (code == '\n')
		{
			j = 0; i++;
		}
		else if (code != ' ')
		{
			level[i][j] = code;
			j++;
			
		}
		code = ' ';
	}
	limit.x = i;
	limit.y = j;
}

void DrawLevel()
{
	int l, c;
	for (l = 0; l <= limit.x; l++)
	{
		for (c = 0; c < limit.y; c++)
		{
			if (level[l][c] == 'w')
			{
				window.draw(wall);
				wall.setPosition(c * rez, l * rez);
			}
			if (level[l][c] == 's')
			{
				window.draw(score_point);
				score_point.setPosition(c * rez +rez/3, l * rez+rez/3);
			}
			if (level[l][c] == 'g')
			{
				gate.setFillColor(sf::Color::Red);
				window.draw(gate);
				gate.setPosition(c * rez, l * rez);
			}
			if (level[l][c] == 'c')
			{
				gate.setFillColor(sf::Color::White);
				window.draw(gate);
				gate.setPosition(c * rez, l * rez);
			}
		}
	}
}

void CreateWindow()
{
	window.create(sf::VideoMode(rez*(limit.x - 1), rez*(limit.y + 2)), "Shitty Pacman");
}

void CreatePacman()
{
	pacman.setFillColor(sf::Color::Yellow);
	pacman.setPosition(pacmanStartPoz_x * rez, pacmanStartPoz_y * rez);
	pacmanStartPoz_x = 1;
	pacmanStartPoz_y = 1;
	x = pacmanStartPoz_x*rez;
	y = pacmanStartPoz_y*rez;
}

void CreateWall()
{
	wall.setFillColor(sf::Color(150, 50, 250));
	wall.setOutlineThickness(1);
	wall.setOutlineColor(sf::Color(100, 50, 200));
}

void CreateScorePoints()
{
	score_point.setFillColor(sf::Color(200, 20, 20));
}

void checkEvent()
{
	if (x / rez == 13 && y / rez == 0)
	{
		pacman.setPosition(26 * rez, 13 * rez);
		x = 13 * rez;
		y = 26 * rez;
	}
	if (x / rez == 13 && y / rez == 27)
	{
		pacman.setPosition(1 * rez, 13 * rez);
		x = 13 * rez;
		y = 1 * rez;
	}
	if (level[x / rez][y / rez] == 's')
	{
		score++;
		WriteConsole();
		level[x / rez][y / rez] = 'e';
	}
	if (level[x / rez][(y + 1) / rez] == 's')
	{
		score++;
		WriteConsole();
		level[x / rez][(y + 1) / rez] = 'e';
	}

}

void pacMove()
{
	checkEvent();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (x % rez == 0 && (level[x / rez][y / rez + 1] == 'w' || level[x / rez][y / rez + 1] == 'g' || level[x / rez][y / rez + 1] == 'c'))
		{
			//cout << "Col:" << "x = " << x / rez << " y = " << (y / rez) + 1 << endl;;
		}
		else
			if (x%rez == 0)
			{
				pacman.move(1, 0);
				y++;
			}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (y%rez == 0 && (level[x / rez][y / rez - 1] == 'w' || level[x / rez][y / rez - 1] == 'g' || level[x / rez][y / rez - 1] == 'c'))
		{
			//cout << "Col:" << "x = " << x / rez << " y = " << (y / rez) - 1 << endl;
		}
		else if (x % rez == 0)
		{
			pacman.move(-1, 0);
			y--;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (x % rez == 0 && (level[x / rez + 1][y / rez] == 'w' || level[x / rez +1][y / rez] == 'g' || level[x / rez + 1][y / rez] == 'c'))
		{
			//cout << "Col:" << "x = " << (x / rez) + 1 << " y = " << y / rez << endl;
		}
		else if (y % rez == 0)
		{
			pacman.move(0, 1);
			x++;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (x%rez == 0 && (level[x / rez - 1][y / rez] == 'w' || level[x / rez - 1][y / rez] == 'g' || level[x / rez - 1][y / rez] == 'c'))
		{
			//cout << "Col:" << "x = " << (x / rez) - 1 << " y = " << y / rez << endl;
		}
		else if (y % rez == 0)
		{
			pacman.move(0, -1);
			x--;
		}
	}
}

void showPacmanPoz()
{
	if (x%rez==0 && y%rez==0 && (x_old!=x || y_old!=y))
	{
		WriteConsole();
		x_old = x;
		y_old = y;
	}
}

void CreateblueP()
{
	blueP.setFillColor(sf::Color::Blue);
	blueP.setPosition(16 * rez, 13 * rez);
}
void CreateredP()
{
	redP.setFillColor(sf::Color::Red);
	redP.setPosition(11 * rez, 13 * rez);
}
void CreategreenP()
{
	greenP.setFillColor(sf::Color::Green);
	greenP.setPosition(16 * rez, 15 * rez);
}
void CreatemedP()
{
	medP.setFillColor(sf::Color::Magenta);
	medP.setPosition(11 * rez, 15 * rez);
}

void CreateGate()
{
	gate.setFillColor(sf::Color(100, 100, 200));
}

void CreatePauseText()
{

	PauseText.setFont(Arial);
	PauseText.setString("You PUSED THE GAIM");
	PauseText.setCharacterSize(80);
	PauseText.setPosition(limit.x / 2, limit.y / 2*10 );
	PauseText.setColor(sf::Color::Red);

	Naem.setFont(Arial);
	Naem.setCharacterSize(80);
	Naem.setPosition(limit.x / 2, limit.y / 2 * 25);
	Naem.setColor(sf::Color::Red);
}

void CreateAll()
{
	CreatePacman();
	CreateblueP();
	CreateredP();
	CreategreenP();
	CreatemedP();
	CreateWall();
	CreateGate();
	CreatePauseText();
}
void DrawAll()
{
	window.draw(pacman);
	window.draw(redP);
	window.draw(blueP);
	window.draw(greenP);
	window.draw(medP);
}
void DrawHearts()
{
	int i=0;
	Heart.setPosition(1, 10*26);
	int poz = 0;
	while (i != lives)
	{
		window.draw(Heart);
		poz = poz + 40;
		Heart.setPosition(poz, 10 * 26);
		i++;
	}
}
void DrawScore()
{
	int i = 0;
	string l;
	l = "Score: /n";
	l = to_string(score);
	ScoreM.setFont(Arial);
	ScoreM.setCharacterSize(60);
	ScoreM.setPosition(1, 16*23.5);
	ScoreM.setColor(sf::Color::Blue);
	ScoreM.setString(l);
	window.draw(ScoreM);
}

void RunGame()
{
	
	Arial.loadFromFile("orange.ttf");
	HeartTexture.loadFromFile("food.png");
	Background_Texture.loadFromFile("ShittyBackground.png");
	Background_Texture2.loadFromFile("ShittyBackground2.png");
	Heart.setTexture(HeartTexture);

	Background.setTexture(&Background_Texture);
	Background2.setTexture(&Background_Texture2);
	ReadLevel();
	CreateMenuText();
	CreateWindow();
	CreateScorePoints();
	CreateAll();
	int i;
	bool citire = false;

	sf::Clock clock;
	while (window.isOpen())
	{

		sf::Event Event;

		switch (_gameState)
		{
		case Uninitialized:
		{
			PauseText.setString("no more lifes");
			ReadLevel();
			_gameState = Playing;
			CreateScorePoints();
			CreateAll();
			break;
		}
		case Paused:
		{
			CreateAll();
			_gameState = Playing;
			break;
		}
		case Playing:
		{
			sf::Time elapsed1 = clock.getElapsedTime();
			if (((int)elapsed1.asSeconds()) %5 == 0)
			{
				int i, j;
				for (j = 0; j <= limit.y; j++)
					for (i = 0; i <= limit.x; i++)
						if (level[i][j] == 'g') level[i][j] = 'c';
			}
			if (((int)elapsed1.asSeconds()) %10 == 0)
			{
				int i, j;
				for (j = 0; j <= limit.y; j++)
					for (i = 0; i <= limit.x; i++)
						if (level[i][j] == 'c') level[i][j] = 'g';
			}
			window.setFramerateLimit(200);
			window.display();
			window.clear(sf::Color::Black);
			window.draw(Background2);
			DrawLevel();
			if (rand() % 2 == 0)
				blueP.aggressive_move();
			else
				blueP.passive_move();
			if (rand() % 2 == 0)
				redP.aggressive_move();
			else
				redP.passive_move();
			if (((int)elapsed1.asSeconds()) >13)
			if (rand() % 2 == 0)
				greenP.aggressive_move();
			else
				greenP.passive_move();
			if (((int)elapsed1.asSeconds()) >8)
			if (rand() % 2 == 0)
				medP.aggressive_move();
			else
				medP.passive_move();
			DrawAll();
			DrawHearts();
			DrawScore();
			showPacmanPoz();
			pacMove();
			if(score == 244) _gameState = Died;
			while (window.pollEvent(Event))
			{
				if (Event.type == sf::Event::KeyPressed)
					if (Event.key.code == sf::Keyboard::Escape)
					{
						_gameState = ShowingMenu;
						first = false;
					}
			}
			break;
		}
		case Died:
		{
			window.clear(sf::Color::Black);
			window.draw(Background);
			switch (lives)
			{
			case 3:
			{
				PauseText.setString("2 lifes left \n/*press enter to \ncontinue */");
				break;
			}
			case 2:
			{
				PauseText.setString("1 life left  \n/*press enter to \ncontinue */");
				break;
			}
			}
			//PauseText.setString("You DED");
			window.draw(PauseText);
			window.draw(Naem);
			window.display();
			if (lives != 1 && score!=244)
			{
				while (window.pollEvent(Event))
				{
					if (Event.type == sf::Event::KeyPressed)
						if (Event.key.code == sf::Keyboard::Return)
						{
							_gameState = Paused; lives--; 
							clock.restart();
							break;
						}
				}
				break;
			}
			else
			{
				PauseText.setString("Scor: " + to_string(score) + "\n *INPUT NAME*");
				while (window.pollEvent(Event))
				{
					if (Event.type == sf::Event::KeyPressed)
					{
						if (Event.key.code == sf::Keyboard::Return) 
						{ 
							ofstream fout("Scor.txt", std::ios_base::app | std::ios_base::out);
							_gameState = ShowingMenu;
							if(inputName!="")fout << inputName << " " << score << endl;
							inputName = "";
							Naem.setString("");
							fout.close();
						}
						if (Event.key.code == sf::Keyboard::BackSpace && inputName.size()>0 && inputName.size()<8)
							inputName.pop_back();
					}

					if (Event.type == sf::Event::TextEntered)
							if (Event.text.unicode >= 32 && Event.text.unicode <= 126)
								inputName += (char)Event.text.unicode;
							Naem.setString(inputName);
				}
				break;
			}
		}
		case ShowingMenu:
		{
			window.clear(sf::Color::Yellow);
			window.draw(Background);
			//Tabela Scor
			if (!citire)
			{
				i = 0;
				ifstream fin("Scor.txt");
				while (fin)
				{
					fin >> scoruri_array[i].nume;
					fin >> scoruri_array[i].valoare;
					for (int j = 0; j <= i; j++)
					{
						if (scoruri_array[j].valoare < scoruri_array[i].valoare)
						{
							aux = scoruri_array[j];
							scoruri_array[j] = scoruri_array[i];
							scoruri_array[i] = aux;
						}
					}
					i++;
				}
				citire = true;
				fin.close();
			}
			int y = 20;
			for (int j = 0; j < 3; j++)
			{
				Nume_Scor.setFont(Arial);
				Nume_Scor.setPosition(limit.x / 2, limit.y / 2 * y+5);
				Nume_Scor.setString(scoruri_array[j].nume + " :: " + to_string(scoruri_array[j].valoare));
				window.draw(Nume_Scor);
				y = y + 5;
			}
			window.draw(Continue);
			window.draw(Play);
			window.draw(Score);
			window.draw(Exit);
			window.display();
			while (window.pollEvent(Event))
			{
				if (Event.type == sf::Event::KeyPressed)
					switch (Event.key.code)
					{

					case sf::Keyboard::Down:
					{
						current->setColor(sf::Color::Red);
						current->urm->setColor(sf::Color::Black);
						current = current->urm;
						break;
					}
					case sf::Keyboard::Up:
					{
						current->setColor(sf::Color::Red);
						current->pre->setColor(sf::Color::Black);
						current = current->pre;
						break;
					}
					case sf::Keyboard::Return:
					{
						if (current == &Continue)
						{
							if (lives > 1)
							{
								_gameState = Playing;
								break;
							}
							else
							{
								clock.restart();
								lives = 3;
								score = 0;
								_gameState = Uninitialized;
							}
						}
						if (current == &Play)
						{
							if (first = true)
							{
								clock.restart();
								lives = 3;
								score = 0;
								_gameState = Uninitialized;
							}
							else
							{
								clock.restart();
								lives = 3;
								score = 0;
								_gameState = Uninitialized;
								first = true;
							}
							break;
						}
						if (current == &Exit)
						{
							window.close(); break;
						}
						if (current == &Score)
						{
							window.close();
							_gameState = Playing;
							break;
						}
						citire = false;
					}
					}
			}
		}
		}
	}

}

int main()
{
	RunGame();
}