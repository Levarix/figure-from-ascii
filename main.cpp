#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;
int Gwidth, Gheight; 

struct Punkt  
{
	int x, y, height, width;
};

Punkt Point, LatestPoint, SquarePoint;

int wyznaczSrodekX() 
{
	int x;
	if (Gwidth % 2) x = Gwidth / 2 + 1;
	else x = Gwidth / 2;
	return x;
}

int wyznaczSrodekY()
{
	int y;
	if (Gheight % 2) y = Gheight / 2 + 1;
	else y = Gheight / 2;
	return y;
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int wherex()
{

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}

void HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void ustawOkno()
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c2 = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
	SetConsoleScreenBufferSize(handle, c2);
	SMALL_RECT sr;
	sr.Left = 0;
	sr.Top = 0;
	sr.Right = c2.X - 1;
	sr.Bottom = c2.Y - 1;
	SetConsoleWindowInfo(handle, true, &sr);
	Gwidth = sr.Right;
	Gheight = sr.Bottom;
}

void RysujObiekt(char znak, int size, int x, int y)
{

	Point.x = x;
	Point.y = y;

	gotoxy(x, y);
	cout << znak;

	for (int i = 2, j = 1; j < size; i += 2, j++)
	{
		gotoxy(x - i, y + j);
		cout << znak;

		gotoxy(x + i, y + j);
		cout << znak;
		LatestPoint.x = wherex() - 1;
		LatestPoint.y = wherey() + 1;
		LatestPoint.height = j;
		LatestPoint.width = i * 2;
	}


	SquarePoint.x = LatestPoint.x - LatestPoint.width; 
	SquarePoint.y = LatestPoint.y;

	for (int i = 1, j; i < size * 2 + 1; i++)
	{
		if (i == 1) j = 0;
		else j = 1;
		if (i % 2 == 0)
		{
			SquarePoint.x += LatestPoint.width;
			gotoxy(SquarePoint.x, SquarePoint.y);
			LatestPoint.width *= -1;
		}
		else
		{
			SquarePoint.y += j;
			gotoxy(SquarePoint.x, SquarePoint.y);
		}
		cout << znak;
		LatestPoint.x = SquarePoint.x;
		LatestPoint.y = SquarePoint.y;
	}
	if (LatestPoint.width < 0) LatestPoint.width *= -1;

	for (int i = 0; i < LatestPoint.width; i++)
	{
		if (size % 2 == 0) gotoxy(LatestPoint.x + i, LatestPoint.y);
		else gotoxy(LatestPoint.x - i, LatestPoint.y); 
		cout << znak;
	}

}
void MoveUp(char znak, int &size)
{

	if (Point.y > 0)
	{
		system("cls"); 
		RysujObiekt(znak, size, Point.x, Point.y - 1);
	}
}
void MoveDown(char znak, int &size)
{

	if (Point.y + (size * 2) < Gheight)
	{
		system("cls");
		RysujObiekt(znak, size, Point.x, Point.y + 1);
	}
	
}

void MoveLeft(char znak, int &size)

	if (Point.x - LatestPoint.width / 2 > 0)
		system("cls");
		RysujObiekt(znak, size, Point.x - 1, Point.y);
	}
}

void MoveRight(char znak, int &size)
{

	if (Point.x + LatestPoint.width / 2 < Gwidth - 1)
	{
		system("cls");
		RysujObiekt(znak, size, Point.x + 1, Point.y);
	}
}

void ZoomUp(char znak, int &size)
{

	if (Point.x + LatestPoint.width / 2 < Gwidth - 2 && Point.x - LatestPoint.width / 2 > 1 && Point.y + (size * 2) < Gheight && Point.y > 1)
	{
		system("cls");
		size += 1;
		RysujObiekt(znak, size, Point.x, Point.y);
	}
}

void ZoomDown(char znak, int &size)
{

	if (size > 3)
	{
		system("cls");
		size -= 1;
		RysujObiekt(znak, size, Point.x, Point.y);
	}
}

void menu(int &size, char &znak)
{
	system("cls");
	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY());
	cout << "Welcome to the program!";
	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY() + 1);
	cout << "Control: ";
	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY() + 2);
	cout << "Moving figure - arrows";
	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY() + 3);
	cout << "Change figure size - +/-";
	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY() + 4);
	cout << "If you want exit program please type ESC";
	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY() + 5);
	cout << "If you want back to menu please type 'r'";
	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY() + 6);
	cout << "Ready? (Type any key)";
	_getch();
	system("cls");


	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY());
	cout << "Type ASCII char: "; cin >> znak;
	gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY());
	cout << "Type size of figure (1-10): "; cin >> size;

	while (size < 1 || size > 10)
	{
		system("cls");
		gotoxy(wyznaczSrodekX() - 30, wyznaczSrodekY());
		cout << "Make sure that your value is between (1-10): "; cin >> size;
	}
	size++;
	system("cls");
	RysujObiekt(znak, size, wyznaczSrodekX(), wyznaczSrodekY());
}
int sterowanie(char znak, int &size)
{
	while (1)
	{
		char prewybor = _getch();
		int wybor = (int)prewybor;
		switch (wybor)
		{
		case 72: //UP
			MoveUp(znak, size);
			break;

		case 80: //DOWN
			MoveDown(znak, size);
			break;

		case 75: //LEFT
			MoveLeft(znak, size);
			break;

		case 77: //RIGHT
			MoveRight(znak, size);
			break;

		case 43: //+
			ZoomUp(znak, size);
			break;

		case 45: //-
			ZoomDown(znak, size);
			break;

		case 114: //R
			menu(size, znak);
			break;

		case 27: //ESC
			return 0;
			break;
		}
	}
}

int main()
{
	int size;
	char znak = ' ';
	ustawOkno();
	HideCursor();
	menu(size, znak);
	sterowanie(znak, size);
	_getch();
	return 0;
}
