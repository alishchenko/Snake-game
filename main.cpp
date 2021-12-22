#include <gl/glut.h>
#include <ctime>
#include "Scene.h"
//#include <JesusHelp>
Scene* scene;

void on_paint()
{
    // Викликаємо відповідну функцію класу Scene:
    scene->on_paint();
}

void on_size(int width, int height)
{
    // Викликаємо відповідну функцію класу Scene:
    scene->on_size(width, height);
}

void on_mouse(int button, int state, int x, int y)
{
    // Викликаємо відповідну функцію класу Scene:
    scene->on_mouse(button, state, x, y);
}

void on_motion(int x, int y)
{
    // Викликаємо відповідну функцію класу Scene:
    scene->on_motion(x, y);
}

void on_special(int key, int x, int y)
{
    // Викликаємо відповідну функцію класу Scene:
    scene->on_special(key, x, y);
}

void on_keyboard(unsigned char key, int x, int y)
{
    // Обробка подій від клавіатури:
    scene->on_keyboard(key, x, y);
    if (key == 27)
        exit(0);
}

void on_timer(int value)
{
    // Обробка події від таймера
    scene->on_timer(0);
    glutTimerFunc(25, on_timer, 0); // зa 25 мс викличеться ця функція
}
int main(int argc, char* argv[]) {
    srand(time(NULL));
    glutInit(&argc, argv);         // ініціалізуємо GLUT
    scene = new Scene(1);   // створюємо об'єкт "сцена"
    glutInitWindowSize(800, 600);  // встановлюємо розміри вікна
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);// ініціалізуємо режими відображення
    glutCreateWindow("SnakeGame");     // створюємо вікно
    glutDisplayFunc(on_paint);     // реєструємо функцію відображення
    glutReshapeFunc(on_size);      // реєструємо функцію обробки зміни розмірів вікна
    glutMotionFunc(on_motion);     // реєструємо функцію, яка відповідає за переміщення миші з натиснутою кнопкою
    glutMouseFunc(on_mouse);       // реєструємо функцію, яка відповідає за натискання на кнопку миші
    glutKeyboardFunc(on_keyboard); // реєструємо функцію, яка відповідає за натискання клавіш
    glutSpecialFunc(on_special);   // реєструємо функцію, яка відповідає за натискання спеціальних клавіш
    glutTimerFunc(25, on_timer, 0);// кожні 25 мс викликається ця функція
    glutMainLoop();                // стартуємо основний цикл обробки подій
    delete scene;                  // видаляємо об'єкт "сцена"
	return 0;
}