#include <String>

using namespace std;

class Figure
{
public:

	int cordX;
	int cordY;
	int rotatePos=0;
	string nameFigure;

	Figure(int x, int y, string name) {
		cordX = x;
		cordY = y;
		nameFigure = name;
	}

	void onePlus() {
		if (rotatePos > 3) {
			this->rotatePos = 0;
		}
		else {
			this->rotatePos++;
		}
	}

};

//Figure::Figure()
//{
//}
//
//Figure::~Figure()
//{
//}