#ifndef Block_h
#define Block_h

#include <gl/glut.h>
#include "Shape.h"

class Block : public Shape
{
private:
	int side;
public:
	Block(float xCenter, float yCenter, float zCenter,
		float xSize, float* diffColor, float* ambiColor, float* specColor) :
		Shape(xCenter, yCenter, zCenter, xSize, xSize, xSize,
			specColor, diffColor, ambiColor) {

		this->side = xSize;
	}
	float getSide() { return side; }
	void setSide(float side) { this->side = side; }
	void draw() override;
};

#endif