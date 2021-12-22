#include "Block.h"
#include <gl/glut.h>

#include "utils.h"

void Block::draw() {
    // ���������� ������������ �������� :
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, getAmbiColor());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, getDiffColor());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, getSpecColor());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
    // ����� ������� ������� � ����
    // (���������� ����� ������� ������� ��� ���������� ������������):
    glPushMatrix();
    glTranslatef(getXCenter(), getYCenter() + getYSize() / 2, getZCenter());
    // ������ ������� ���� ������������ � ������������� ��������:
    glRotatef(90, 1, 0, 0);
    glutSolidCube(side);
    // ���� ������� ���� ������������ ��������� ������ ������:
    glRotatef(180, 1, 0, 0);
    // ������� ���� ������:
    glTranslatef(0, 0, -getYSize());
    // ³��������� ������� ������� � �����:
    glPopMatrix();
}