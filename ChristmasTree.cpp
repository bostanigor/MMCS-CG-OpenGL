#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <cmath>

#include "ChristmasTree.h"

void ChristmasTree::render() {
  glPushMatrix();
  glRotatef(angle_z, 0.0, 0.0, 1.0);

  render_stump(10, 25);

  float ambient[] = {0.0, 0.0, 0.0, 1.0};
  float diffuse[] = {0.0, 1.0, 0.0, 1.0};
  float specular[] = {0.5, 0.5, 0.5, 1.0};
  float shininess = 0.2 * 128;

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  glTranslatef(0, 0, 25);
  glutSolidCone(70, 100, 100, 1);
  render_tree_decorations(70, 8, 5);

  glTranslatef(0, 0, 50);
  glutSolidCone(60, 80, 100, 1);
  render_tree_decorations(60, 10, 7);

  glTranslatef(0, 0, 50);
  glutSolidCone(50, 60, 100, 1);
  render_tree_decorations(50, 5, 4);

  glTranslatef(0, 0, 45);


  glPopMatrix();
}

void ChristmasTree::render_tree_decorations(double radius, double ballRadius, int ballCount) {
  glPushMatrix();

  double angle = 360.0 / ballCount;
  for (int i = 0; i < ballCount; i++) {
    render_ball(ballRadius, radius);
    glRotatef(angle, 0.0, 0.0, 1.0);
  }

  glPopMatrix();
}

void ChristmasTree::render_stump(double radius, double height) {
  float ambient[] = {0.5, 0.5, 0.5};
  float diffuse[] = {0.5, 0.5, 0.5};
  float specular[] = {1, 1, 1};
  float shininess = 1 * 128;

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  glutSolidCylinder(radius, height, 20, 1);
}

void ChristmasTree::render_ball(double radius, double offset, bool tex) {
  if (tex) {
    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glEnable(GL_TEXTURE_2D);

    glTranslatef(offset, offset, 0);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, radius, 12, 12);
    gluDeleteQuadric(quadObj);
    glTranslatef(-offset, -offset, 0);

    glDisable(GL_TEXTURE_2D);
  } else {
    glTranslatef(offset, offset, 0);
    glutSolidSphere(radius, 12, 12);
    glTranslatef(-offset, -offset, 0);
  }
}
