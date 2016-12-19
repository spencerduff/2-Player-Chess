#include <iostream>
#include <fstream>

class Representation{
public:
	Representation(char s, int f, int b);

	void setColor(int foreground, int background);

	//Only background is allowed to change.
	void changeBackground(int b);

	int getBackground();

	void printSymbol();

	friend void operator<<(std::ostream& os, Representation& s);

private:

	char symbol;
	int colorForeground, colorBackground;

};