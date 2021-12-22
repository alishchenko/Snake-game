#include "Shape.h"

class Food : public Shape
{
private:
	float side;
public:
	Food(float xCenter, float yCenter, float zCenter,
		float xSize, float* diffColor, float* ambiColor, float* specColor) :
		Shape(xCenter, yCenter, zCenter, xSize, xSize, xSize,
			specColor, diffColor, ambiColor) {

		this->side = xSize;
	}
	float getSide() { return side; }
	void setSide(float side) { this->side = side; }
	void draw() override;
};

