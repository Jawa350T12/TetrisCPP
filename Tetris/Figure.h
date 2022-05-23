#include <String>

using namespace std;

class Figure
{
public:

	int cordX;
	int cordY;
	static int rotatePos;
	string nameFigure;

	Figure(int x, int y, string name) {
		cordX = x;
		cordY = y;
		nameFigure = name;
	}

	void onePlus() {
		if (rotatePos >= 4) {
			rotatePos = 0;
		}
		else {
			rotatePos++;
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