#include "Representation.h"
#include <Windows.h>

Representation::Representation(char s, int f, int b){
	symbol = s;
	colorForeground = f;
	colorBackground = b;
}

Representation::Representation(Representation &other){
	this->symbol = other.symbol;
	this->colorForeground = other.colorForeground;
	this->colorBackground = other.colorBackground;
}

void Representation::setColor(int foreground, int background){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground | background);
}

void Representation::changeBackground(int b){
	colorBackground = b;
}

void operator<<(std::ostream& os, Representation& s)
{
	s.setColor(s.colorForeground, s.colorBackground);
	std::cout << s.symbol;
	s.setColor(7, 0); //sets it back to original console colors
	return;
}

int Representation::getBackground(){
	return colorBackground;
}