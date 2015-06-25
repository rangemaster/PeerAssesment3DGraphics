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
	static void Message(string message)
	{
		DisplayMessage(message, 2);
	}
private:
	static void DisplayMessage(string message, int value)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, value);
		cout << message << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
};