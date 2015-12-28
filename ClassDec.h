#pragma once
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
	if (level[poz_x / rez - 1][poz_y / rez] == 'w')
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