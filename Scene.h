#pragma once
#include "Shape.h"
#include "Snake.h"
#include "Block.h"
#include <vector>
const int N = 24, M = 24;

class Scene
{
    std::vector<Shape*> shapes; // "�������" ����� ��������� �� �������� ���
    int button;           // ������ ���� (-1 - �� ���������, 0 - ���, 2 - �����)
    float angleX, angleY; // �������� ��� �������� ����� 
    float mouseX, mouseY; // ������ ����������
    float width, height;  // ������ ����
    float distZ;          // ������� �� �� Z �� �����
    bool finish;          // ������ ����, �� ��� ���������
    bool pause = true;
    bool stop = true;
    Snake* snake;
    int speed = 4;
    bool borders = true;
    bool switchText = true;
    int score = 0;
    int bestscore = 0;
public:
    Scene(float side);
    ~Scene();
    void on_paint();
    void on_size(int width, int height);
    void on_mouse(int button, int state, int x, int y); 
    void on_motion(int x, int y);
    void on_special(int key, int x, int y);
    void on_keyboard(int key, int x, int y);
    void on_timer(int value);
private:
    void initialize();
    void eat();
    bool checkFinish();
    void checkFood();
    void bestScore();    
};

