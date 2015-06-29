#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

class Messager
{
public:
	Messager();
	~Messager();
	static void Error(string message)
	{
		DisplayMessage(message, 4);
	}
	static void Succes(string message)
	{
		DisplayMessage(message, 2);
	}
	static void Message(string message)
	{
		DisplayMessage(message, 7);
	}
private:
	//0 = Black	8 = Gray
	//1 = Blue	9 = Light Blue
	//2 = Green a = Light Green
	//3 = Aqua	b = Light Aqua
	//4 = Red	c = Light Red
	//5 = Purple	d = Light Purple
	//6 = Yellow	e = Light Yellow
	//7 = White	f = Bright White
	static void DisplayMessage(string message, int value)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, value);
		cout << message << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
};