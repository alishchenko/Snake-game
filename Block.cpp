#include "Block.h"
#include <gl/glut.h>

#include "utils.h"

void Block::draw() {
    // Визначення властивостей матеріалу :
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, getAmbiColor());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, getDiffColor());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, getSpecColor());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
    // Запис поточної матриці в стек
    // (збереження вмісту поточної матриці для подальшого використання):
    glPushMatrix();
    glTranslatef(getXCenter(), getYCenter() + getYSize() / 2, getZCenter());
    // Циліндр повинен бути розташований у вертикальному напрямку:
    glRotatef(90, 1, 0, 0);
    glutSolidCube(side);
    // Диск повинен бути намальований зовнішньою гранню догори:
    glRotatef(180, 1, 0, 0);
    // Малюємо диск зверху:
    glTranslatef(0, 0, -getYSize());
    // Відновлення поточної матриці зі стека:
    glPopMatrix();
}