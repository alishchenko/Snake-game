#define _CRT_SECURE_NO_WARNINGS
#include <gl/glut.h>
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Scene.h"
#include "Block.h"
#include "utils.h"
#include "Board.h"
#include "Food.h"
using namespace GraphUtils;
using namespace std;

Scene::Scene(float side)
{
    // Додаємо дошку сірого кольору. 
    // Розміри визначаємо так, щоб поміщалися всі стрижні:
    shapes.push_back(new Board(0.0, 0.0, 0.0, N, 0.1, M, diffGreen, ambiGreen, specGreen));
    shapes.push_back(new Board(M / 2 + 0.1, 0.0, 0.0, 1, 3, M - 0.86, diffRed, ambiRed, specRed));
    shapes.push_back(new Board(-M / 2 - 0.1, 0.0, 0.0, 1, 3, M - 0.86, diffRed, ambiRed, specRed));
    shapes.push_back(new Board(0.0, 0.0, -M / 2, N + 1.2, 3, 1, diffRed, ambiRed, specRed));
    shapes.push_back(new Board(0.0, 0.0, M / 2 , N + 1.2, 3, 1, diffRed, ambiRed, specRed));
    int foodX = 11 - rand() % 21, foodZ = 11 - rand() % 21;
    shapes.push_back(new Food(foodX, 0.0, foodZ, 0.8, diffRed, ambiRed, specRed));
    // Здійснюємо ініціалізацію параметрів перед першою грою:
    initialize();
   
}

Scene::~Scene()
{
    // Видаляємо всі фігури:
    for (int i = 0; i < shapes.size(); i++)
    {
        delete shapes[i];
    }
}

void Scene::initialize()
{
    snake = new Snake();
    distZ = -25;
    angleX = 0;
    angleY = 80;
    score = 0;
}

bool Scene::checkFinish() {
    if (fabs(snake->getSnake()[0]->getXCenter()) >= 12 || fabs(snake->getSnake()[0]->getZCenter()) >= 12) {
        return true;
    }
    for (int i = 1; i < snake->getSnake().size(); i++) {
        if (snake->getSnake()[0]->getXCenter() == snake->getSnake()[i]->getXCenter() &&
            snake->getSnake()[0]->getZCenter() == snake->getSnake()[i]->getZCenter()) {
            return true;
        }
    }
    return false;
}

void Scene::checkFood() {
    for (int i = 0; i < snake->getSnake().size(); i++) {
        if (shapes[shapes.size() - 1]->getXCenter() == snake->getSnake()[i]->getXCenter() &&
            shapes[shapes.size() - 1]->getZCenter() == snake->getSnake()[i]->getZCenter()) {
            int foodX = 11 - rand() % 21, foodZ = 11 - rand() % 21;
            shapes[shapes.size() - 1]->setXCenter(foodX);
            shapes[shapes.size() - 1]->setZCenter(foodZ);
            checkFood();
        }
    }
}

void Scene::eat() {
    if (shapes[shapes.size() - 1]->getXCenter() == snake->getSnake()[0]->getXCenter() && 
        shapes[shapes.size() - 1]->getZCenter() == snake->getSnake()[0]->getZCenter()) {
        snake->addBlock();
        score++;
        int foodX = 11 - rand() % 21, foodZ = 11 - rand() % 21;        
        shapes[shapes.size() - 1]->setXCenter(foodX);
        shapes[shapes.size() - 1]->setZCenter(foodZ);
    }

}

void Scene::bestScore() {
    fstream file;
    file.open("bestScore.txt", fstream::in);
    int bs;
    file >> bs;
    if (bs < score) bs = score;
    file.close();
    file.open("bestScore.txt", fstream::out);
    file << bs;
    bestscore = bs;
    file.close();
}
int value = -1;

// Оброблювач події, пов'язаної з перемалюванням вікна
bool needScore = true;
void Scene::on_paint()
{
        finish = checkFinish();
        eat();
        checkFood();
        char text[128], menu1[128], menu2[128], menu3[128], menu4[128], menu5[128], menu6[128], menu7[128]; // Масив символів, 
        // Заповнення масиву символів відповідно до стану гри:

        if (finish && !pause)
        {
            if (needScore) {
                bestScore();
                needScore = false;
            }
            sprintf(text, "Game over. Score: %d points. Best Score: %d points. F1 - Restart game", score, bestscore);
        }
        else if (!pause && !stop)
        {
            sprintf(text, "F1 - Restart game   Esc - Exit   Space - pause   Score: %d points", score);
        }
        else if (!pause && stop)
        {
            sprintf(text, "F1 - Menu   Esc - Exit   Space - continue   Score: %d points", score);
        }

        if (pause) {
            sprintf(menu1, "MENU");
            if (borders)
                sprintf(menu2, "Borders: on");
            else
                sprintf(menu2, "Borders: off");
            switch (speed) {
            case 0:
                sprintf(menu3, "Speed: 3 level");
                break;
            case 2:
                sprintf(menu3, "Speed: 2 level"); 
                break;
            case 4:
                sprintf(menu3, "Speed: 1 level");
                break;
            }

        }
        sprintf(menu5, "Press SPACE for change");
        sprintf(menu6, "Press F1 to start");
        // Встановлюємо область перегляду таку, щоб вона вміщувала все вікно:
        glViewport(0, 0, width, height);

        // Ініціалізуємо параметри матеріалів і джерела світла:
        float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // колір фонового освітлення 
        float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // колір дифузного освітлення 
        float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// колір дзеркального відображення
        float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };// розташування джерела світла

        // Встановлюємо параметри джерела світла:
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // Визначаємо блакитний колір для очищення:
        if (finish)
        {
            glClearColor(0, 0.7, 0.7, 0);
        }
        else
        {
            glClearColor(0, 0.5, 0.5, 0);
        }

        // Очищуємо буфери:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Для відображення тексту, краще використовувати ортографічну проекцію:
        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1, 1, 0); // жовтий текст
        if (!pause) {
            drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
        }
        if (pause) {
            drawString(GLUT_BITMAP_TIMES_ROMAN_24, menu1, 0.45, 0.6);
            if (switchText) {
                glColor3f(0, 1, 0); // зелений текст
                drawString(GLUT_BITMAP_TIMES_ROMAN_24, menu2, 0.35, 0.5);
                glColor3f(1, 1, 0); // жовтий текст
                drawString(GLUT_BITMAP_TIMES_ROMAN_24, menu3, 0.35, 0.45);
            }
            else {
                drawString(GLUT_BITMAP_TIMES_ROMAN_24, menu2, 0.35, 0.5);
                glColor3f(0, 1, 0); // зелений текст
                drawString(GLUT_BITMAP_TIMES_ROMAN_24, menu3, 0.35, 0.45);
            }
            glColor3f(1, 1, 0); // жовтий текст
            drawString(GLUT_BITMAP_TIMES_ROMAN_24, menu5, 0.33, 0.3);
            drawString(GLUT_BITMAP_TIMES_ROMAN_24, menu6, 0.39, 0.25);
        }
        glPopMatrix();

        // Включаємо режим роботи з матрицею проекцій:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Задаємо усічений конус видимості в лівосторонній системі координат, 
        // 60 - кут видимості в градусах по осі у,
        // width/height - кут видимості уздовж осі x,
        // 1 и 100 - відстань від спостерігача до площин відсікання по глибині:
        gluPerspective(60, width / height, 1, 100);

        // Включаємо режим роботи з видовою матрицею:
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, distZ);	// камера з початку координат зсувається на distZ, 

        glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // потім обертається по осі Oy
        glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // потім обертається по осі Ox
        glEnable(GL_DEPTH_TEST);	// включаємо буфер глибини (для відсікання невидимих частин зображення)

                                    // Включаємо режим для установки освітлення:
        glEnable(GL_LIGHTING);

        // Додаємо джерело світла № 0 (їх може бути до 8), зараз воно світить з "очей":
        glEnable(GL_LIGHT0);

        // Малюємо усі фігури:
        if (!pause) {
            for (int i = 0; i < shapes.size(); i++)
            {
                shapes[i]->draw();
            }

            for (int i = 0; i < snake->getSnake().size(); i++)
            {
                snake->draw();
            }
            if (value == 0 && !stop) {
                if (!finish) {
                    if (snake->getDirection() == RIGHT)
                        snake->move(GLUT_KEY_RIGHT, borders);
                    else if (snake->getDirection() == LEFT)
                        snake->move(GLUT_KEY_LEFT, borders);
                    else if (snake->getDirection() == UP)
                        snake->move(GLUT_KEY_UP, borders);
                    else if (snake->getDirection() == DOWN)
                        snake->move(GLUT_KEY_DOWN, borders);

                }
            }
            value--;
        }
        // Вимикаємо все, що включили:
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glFlush();
        // показуємо вікно:
        glutSwapBuffers(); // перемикання буферів
}

// Оброблювач події, пов'язаної зі зміною розмірів вікна 
void Scene::on_size(int width, int height)
{
    this->width = width;
    if (height == 0)
        height = 1;
    this->height = height;
}
// Оброблювач подій, пов'язаних з натисканням кнопок миші
void Scene::on_mouse(int button, int state, int x, int y)
{
    // Зберігаємо поточні координати миші:
    mouseX = x;
    mouseY = y;
    if ((state == GLUT_UP)) // кнопка віджата
    {
        int i = 0;
        // Перевірка закінчення гри:
        if ( i == 0)
        {
            finish = true;
        }
        this->button = -1;  // ніяка кнопка не натиснута
        return;
    }
    this->button = button;  // зберігаємо інформацію про кнопки
    if (finish)
    {
        return;
    }
 
}
// Оброблювач подій, пов'язаних з пересуванням миші з натисненою кнопкою
void Scene::on_motion(int x, int y)
{
    switch (button)
    {
    case 2: // права кнопка - обертання сцени
        angleX += x - mouseX;
        angleY += y - mouseY;
        mouseX = x;
        mouseY = y;
        break;
    }
}
// Оброблювач подій, пов'язаних з натисненням функціональних клавіш і стрілок 
void Scene::on_keyboard(int key, int x, int y) {
    if (pause) {
        switch (key) {
        case ' ':
            if (switchText)
                borders ? borders = false : borders = true;
            else {
                speed -= 2;
                if (speed == -2) speed = 4;
                on_timer(speed);
            }
            break;
        }
    }
    else {
        switch (key) {
        case ' ':
               stop ? stop = false : stop = true;         
        }
    }

}
void Scene::on_special(int key, int x, int y)
{
    int foodX = 11 - rand() % 21, foodZ = 11 - rand() % 21;
    if (pause) {
        switch (key) {
        case GLUT_KEY_UP:
            switchText = true;
            break;
        case GLUT_KEY_DOWN:
            switchText = false;
            break;
        case GLUT_KEY_F1: // пауза
            pause = false;
            break;
        }
    }
    else {
        switch (key) {
        case GLUT_KEY_RIGHT:
            if (!finish && !stop && snake->getDirection() != LEFT && snake->getDirection() != RIGHT)
                snake->move(key, borders);
            break;
        case GLUT_KEY_LEFT:
            if (!finish && !stop && snake->getDirection() != LEFT && snake->getDirection() != RIGHT)
                snake->move(key, borders);
            break;
        case GLUT_KEY_UP:
            if (!finish && !stop && snake->getDirection() != UP && snake->getDirection() != DOWN)
                snake->move(key, borders);
            break;
        case GLUT_KEY_DOWN:
            if (!finish && !stop && snake->getDirection() != UP && snake->getDirection() != DOWN)
                snake->move(key, borders);
            break;
        case GLUT_KEY_F3: // віддалення
            distZ -= 0.1;
            break;
        case GLUT_KEY_F4:   // наближення
            if (distZ > -1.7)
            {
                break;
            }
            distZ += 0.1;
            break;
        case GLUT_KEY_F1:   // нова гра
            if (finish || stop) {
                pause = true;
                shapes[shapes.size() - 1]->setXCenter(foodX);
                shapes[shapes.size() - 1]->setZCenter(foodZ);
                needScore = true;
                initialize();
            }
            break;
        }
    }
}
// Оброблювач події від таймера
void Scene::on_timer(int x)
{
    
    if (value == -1)
        value = speed;
    on_paint();     // здійснюємо перемалювання вікна
}