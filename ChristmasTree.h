#ifndef UNTITLEDGL_CHRISTMASTREE_H
#define UNTITLEDGL_CHRISTMASTREE_H

class ChristmasTree {
  double pos_x, pos_y;
  double angle_z;

public:
  void render();

private:
  void render_stump(double radius, double height);
  void render_tree_decorations(double radius, double ballRadius, int ballCount);
  void render_ball(double radius, double offset, bool tex = true);
};


#endif //UNTITLEDGL_CHRISTMASTREE_H
