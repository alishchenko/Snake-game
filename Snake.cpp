#include "Snake.h"
#include <gl/glut.h>
#include "utils.h"
using namespace GraphUtils;
	Snake::Snake() {
		snake.push_back(new Block(0.0, 0.0, 0.0, 1, diffBlue, ambiBlue, specBlue));
		snake.push_back(new Block(0.0 - snake.size(), 0.0, 0.0, 1, diffLightBlue, ambiLightBlue, specLightBlue));
		snake.push_back(new Block(0.0 - snake.size(), 0.0, 0.0, 1, diffLightBlue, ambiLightBlue, specLightBlue));
		snake[0]->setColors(diffBlue, ambiBlue, specBlue);
		snake[1]->setColors(diffLightBlue, ambiLightBlue, specLightBlue);
		snake[2]->setColors(diffLightBlue, ambiLightBlue, specLightBlue);
	}
	void Snake::draw() {
		for (int i = 0; i < snake.size(); i++)
			snake[i]->draw();
	}
	void Snake::move(int key, bool borders) {
		switch (key)
		{case GLUT_KEY_RIGHT:
			if (snake[0]->getXCenter() + 1 >= 12 && !borders)
				snake[snake.size() - 1]->setXCenter(-11);
			else
				snake[snake.size() - 1]->setXCenter(snake[0]->getXCenter() + 1);
			snake[snake.size() - 1]->setZCenter(snake[0]->getZCenter());
			direction = RIGHT;
			break;
		case GLUT_KEY_LEFT:
			if (snake[0]->getXCenter() - 1 <= -12 && !borders)
				snake[snake.size() - 1]->setXCenter(11);
			else
				snake[snake.size() - 1]->setXCenter(snake[0]->getXCenter() - 1);
			snake[snake.size() - 1]->setZCenter(snake[0]->getZCenter());
			direction = LEFT;
			break;
		case GLUT_KEY_UP:
			if (snake[0]->getZCenter() - 1 <= -12 && !borders)
				snake[snake.size() - 1]->setZCenter(11);
			else
				snake[snake.size() - 1]->setZCenter(snake[0]->getZCenter() - 1);
			snake[snake.size() - 1]->setXCenter(snake[0]->getXCenter());
			direction = UP;
			break; 
		case GLUT_KEY_DOWN:
			if (snake[0]->getZCenter() + 1 >= 12 && !borders)
				snake[snake.size() - 1]->setZCenter(-11);
			else
				snake[snake.size() - 1]->setZCenter(snake[0]->getZCenter() + 1);
			snake[snake.size() - 1]->setXCenter(snake[0]->getXCenter());
			direction = DOWN;
			break;
		default:
			break;
		}
		snake.insert(snake.begin(), snake[snake.size() - 1]);
		snake.pop_back();
		snake[0]->setColors(diffBlue, ambiBlue, specBlue);
		snake[1]->setColors(diffLightBlue, ambiLightBlue, specLightBlue);		
	}
	void Snake::addBlock() {
		snake.push_back(new Block(snake[snake.size() - 1]->getXCenter(), snake[snake.size() - 1]->getYCenter(), snake[snake.size() - 1]->getZCenter(), 1, diffLightBlue, ambiLightBlue, specLightBlue));
	}