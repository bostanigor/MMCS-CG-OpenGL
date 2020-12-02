#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <cmath>

#include "Car.h"

void Car::render() {
  glPushMatrix();

  float car_color[3]{25 / 255.0, 85 / 255.0, 250 / 255.0};
  float tire_color[3]{30 / 255.0, 30 / 255.0, 30 / 255.0};
  float ambient[] = {0.5, 0.5, 0.5};
  float specular[] = {0.5, 0.5, 0.5};
  float emission[] = {0, 0, 0};
  float shininess = 0.1 * 128;

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, car_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  glTranslatef(pos_x, pos_y, 50);
  glRotatef(angle_z, 0, 0, 1);
  render_body();

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, car_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tire_color);

  render_tires(1);
  render_tires(-1);

  render_lights();

  float new_mat_emmis[] = {0, 0, 0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new_mat_emmis);

  glPopMatrix();
}

void Car::render_body() {
  glPushMatrix();
  glTranslatef(35, 0, 0);
  glutSolidCube(70);
  glTranslatef(-70, 0, 0);
  glutSolidCube(70);
  glPopMatrix();
}

void Car::render_tires(int sign) {
  glPushMatrix();
  glTranslatef(60, sign * 35, -35);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(8, 10, 5, 10);
  glRotatef(-90, 1, 0, 0);
  glTranslatef(-120, 0, 0);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(8, 10, 5, 10);
  glPopMatrix();
}

void Car::render_lights() {
  glTranslatef(65, 15, -10);
  render_light(GL_LIGHT1);
  glTranslatef(0, -30, 0);
  render_light(GL_LIGHT2);
}

void Car::turn(double d_angle) {
  angle_z += d_angle;
}

void Car::move(double d) {
  pos_x += cos(angle_z * M_PI / 180) * d;
  pos_y += sin(angle_z * M_PI / 180) * d;
}

void Car::render_light(GLenum light) {
  float light_color[3]{250 / 255.0, 190 / 255.0, 60 / 255.0};

  if (lights_up) {
    float new_mat_emmis[] = {250 / 255.0, 190 / 255.0, 60 / 255.0};
    const GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    const GLfloat position[] = { 0.0, 0.0, 0.0, 1.0};
    const GLfloat direction[] = { 1.0, 0.0, 0.0 };
    const GLfloat cutoff = 60.0;

    glLightfv(light, GL_DIFFUSE, light_diffuse);
    glLightfv(light, GL_SPECULAR, light_specular);
    glLightfv(light, GL_POSITION, position);
    glLightfv(light, GL_SPOT_DIRECTION, direction);
    glLightf(light, GL_SPOT_CUTOFF, cutoff);
    glLightf(light, GL_SPOT_EXPONENT, 5.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new_mat_emmis);
  }

  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_color);

  glutSolidSphere(10, 12, 50);
  glPopMatrix();
}

void Car::turn_lights() {
  if (lights_up) {
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
  }
  else {
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
  }
  lights_up = !lights_up;
}

Car::Car() {
}
