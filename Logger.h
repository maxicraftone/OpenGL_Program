#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>

tm getTimeStruct();

std::string getTimeStamp(tm timeStruct);

template<typename T>
void writeToConsole(T message, bool lineBreak = true) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	if (lineBreak)
		std::cout << getTimeStamp(getTimeStruct()) << " " << message << std::endl;
	else
		std::cout << getTimeStamp(getTimeStruct()) << " " << message;
	SetConsoleTextAttribute(hConsole, 7);
}

template<typename T>
void writeError(T message, bool lineBreak = true) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);

	if (lineBreak)
		std::cout << getTimeStamp(getTimeStruct()) << " <ERROR> " << message << std::endl;
	else
		std::cout << getTimeStamp(getTimeStruct()) << " <ERROR> " << message;
	SetConsoleTextAttribute(hConsole, 7);
}

template<typename T>
void writeInfo(T message, bool lineBreak = true) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);

	if (lineBreak)
		std::cout << getTimeStamp(getTimeStruct()) << " <INFO> " << message << std::endl;
	else
		std::cout << getTimeStamp(getTimeStruct()) << " <INFO> " << message;
	SetConsoleTextAttribute(hConsole, 7);
}

template<typename T>
void write(T message) {
	std::cout << message;
}

void resetColor(int color = 7, bool lineBreak = true);
#endif