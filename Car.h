#ifndef UNTITLEDGL_CAR_H
#define UNTITLEDGL_CAR_H


class Car {
  double pos_x = 150.0, pos_y = 200.0;
  double angle_z = 150.0;

public:
  bool lights_up = true;

  Car() {}
  void render();
  void turn(double delta_angle);
  void move(double distance);

private:
  void render_body();
  void render_tires(int sign);
  void render_lights();
};


#endif //UNTITLEDGL_CAR_H
