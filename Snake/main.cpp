# include <iostream>
# include <windows.h>
# include <conio.h> // библиотека для взаимодействия с консолью
# include <time.h>

using namespace std;

bool game_over;
const int width = 20;
const int height = 20;
int tail_x[100], tail_y[100];
int n_tail;
int x, y, fruit_x, fruit_y, score;
enum eDirection { STOP = 0, LEFT, RIGHT, DOWN, UP};
eDirection dir;



void Setup() 
{
	game_over = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;
}

void Draw() 
{
	system("cls"); // очистить экран на Windows
	// Верхняя граница
	for (int i = 0; i < width + 1; i++)
		cout << '#';
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1) cout << "#";
			if (i == y && j == x) cout << "0";
			else if (i == fruit_y && j == fruit_x) cout << "F";
			else 
			{
				bool print = false;
				for (int k = 0; k < n_tail; k++)
				{
					if (tail_x[k] == j && tail_y[k] == i)
					{	
						print = true;
						cout << 'o';
					}
				}
				if(!print) cout << " ";
			}
		}
		cout << endl;
	}
	// Верхняя граница
	// Нижняя граница
	for (int i = 0; i < width + 1; i++)
		cout << '#';
	cout << endl;
	// Нижняя граница
	cout << "Score: " << score << endl;

}

void Logic()
{
	int prev_x = tail_x[0]; // предыдушая позиция хвоста по x
	int prev_y = tail_y[0]; // предыдушая позиция хвоста по y
	int prev_2x, prev_2y;	// временные переменные позии хвоста
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < n_tail; i++) 
	{
		prev_2x = tail_x[i];
		prev_2y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;

	}


	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	case UP:
		y--;
		break;
	}

	if (x >= width - 1) x = 0;
	else if (x < 0) x = width - 2;

	if (y >= height - 1) y = 0;
	else if (y < 0) y = height - 2;

	for (int i = 0; i < n_tail; i++)
		if (tail_x[i] == x && tail_y[i] == y)
			game_over = true;
	if (x == fruit_x && y == fruit_y) 
		{
		score += 10;
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		n_tail++;
		}
}
void Input()
{
	if (_kbhit()) //_kbhit () функция отслеживает нажатие на кнопку
	{
		switch (_getch()) //_getch() показывает какая именно кнопка была нажата
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			game_over = true;
			break;
		}


	}
}

int main() 
{
	srand(time(NULL));
	Setup();
	while (!game_over)
	{
		//Sleep(100);
		Draw();
		Input();
		Logic();
	}
	return 0;
}