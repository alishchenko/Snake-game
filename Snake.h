#include <gl/glut.h>
#include <vector>
#include <string>
#include "Shape.h"
#include "Block.h"
enum {RIGHT, LEFT, UP, DOWN};
class Snake
{
private:
	std::vector <Block*> snake;	
	int direction = RIGHT;
public:
	Snake();
	std::vector <Block*> getSnake() { return snake; }
	int getDirection() { return direction; }
	void draw();
	void move(int key, bool borders);
	void addBlock();
};