#ifndef CLOSEST_POINTS_H
#define CLOSEST_POINTS_H

#include <QMainWindow>
#include <QVector>
#include <QMouseEvent>
#include <QDebug>
#include "point.h"

namespace Ui {
class closest_points;
}

struct point_pair
{
    Point *a = nullptr;
    Point *b = nullptr;
    double distance;
};

class closest_points : public QMainWindow
{
    Q_OBJECT

public:
    explicit closest_points(QWidget *parent = 0);
    ~closest_points();
public:
    friend int partition(QVector<Point*> &arr, int l, int r);
    friend void quicksort_x(QVector<Point*> &arr, int l, int r);
    point_pair find_closest_point_pair(int l, int r);
    point_pair strip_closest(QVector<Point*> &strip, int num, point_pair d);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::closest_points *ui;
    QVector<Point*> point_set;
};

#endif // CLOSEST_POINTS_H
