#include "closest_points.h"
#include "ui_closest_points.h"
#include <cmath>

closest_points::closest_points(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::closest_points)
{
    ui->setupUi(this);
}

closest_points::~closest_points()
{
    delete ui;
}

void closest_points::mousePressEvent(QMouseEvent *event)
{
    Point *p = new Point(event->x(), event->y(), this);
    point_set.push_back(p);
    int num_of_point = point_set.size();
    if (num_of_point >= 2) {
        quicksort_x(point_set, 0, num_of_point);
        point_pair result = find_closest_point_pair(0, num_of_point);
        for (auto &i: point_set) {
            i->m_picture->setPixmap(QPixmap(":/picture/Resource/black_circle.png"));
        }
        result.a->m_picture->setPixmap(QPixmap(":/picture/Resource/red_circle.png"));
        result.b->m_picture->setPixmap(QPixmap(":/picture/Resource/red_circle.png"));
    }
}

void element_swap(Point *&a, Point *&b)
{
    Point *temp = a;
    a = b;
    b = temp;
} // The definition of element_swap method finished

double distance(Point *x, Point *y)
{
    return sqrt((x->x() - y->x()) * (x->x() - y->x())
                + (x->y() - y->y()) * (x->y() - y->y()));
}

int partition_x(QVector<Point*> &arr, int l, int r)
{
    Point *x = arr[r - 1];
    int j = l;
    for (int i = l; i < r - 1; ++i) {
        if (arr[i]->x() <= x->x()) {
            element_swap(arr[i], arr[j++]);
        }
    }
    element_swap(arr[j], arr[r - 1]);
    return j;
} // The definition of partition finished

void quicksort_x(QVector<Point*> &arr, int l, int r)
{
    if (l < r) {
        int q = partition_x(arr, l, r);
        quicksort_x(arr, l, q);
        quicksort_x(arr, q + 1, r);
    }
} // The definition of quicksort finished

int partition_y(QVector<Point*> &arr, int l, int r)
{
    Point *y = arr[r - 1];
    int j = l;
    for (int i = l; i < r - 1; ++i) {
        if (arr[i]->y() <= y->y()) {
            element_swap(arr[i], arr[j++]);
        }
    }
    element_swap(arr[j], arr[r - 1]);
    return j;
} // The definition of partition finished

void quicksort_y(QVector<Point*> &arr, int l, int r)
{
    if (l < r) {
        int q = partition_y(arr, l, r);
        quicksort_y(arr, l, q);
        quicksort_y(arr, q + 1, r);
    }
} // The definition of quicksort finished

point_pair closest_points::strip_closest(QVector<Point*> &strip, int num, point_pair d)
{
    point_pair min = d;
    quicksort_y(strip, 0, num);
    for (int i = 0; i < num; ++i) {
        for (int j = i + 1; j < num && (strip[j]->y() - strip[i]->y()) < min.distance; ++j) {
            if (distance(strip[i],strip[j]) < min.distance) {
                min.a = strip[i];
                min.b = strip[j];
                min.distance = distance(strip[i],strip[j]);
            }
        }
    }

    return min;
}

point_pair closest_points::find_closest_point_pair(int l, int r)
{
    if (r - l <= 3) {
        point_pair min;
        min.distance = 10000;
        for (int i = l; i < r; ++i) {
            for (int j = i + 1; j < r; ++j) {
                if (distance(point_set[i], point_set[j]) < min.distance) {;
                    min.a = point_set[i];
                    min.b = point_set[j];
                    min.distance = distance(point_set[i], point_set[j]);
                }
            }
        }
        return min;
    }
    int mid = (l + r)/2;
    Point *mid_point = point_set[mid];
    point_pair dl = find_closest_point_pair(l, mid);
    point_pair dr = find_closest_point_pair(mid, r);
    point_pair d = dl.distance < dr.distance ? dl : dr;

    QVector<Point*> strip(r - l);
    int j = 0;
    for (int i = 0; i < r - l; ++i) {
        if (abs(point_set[i]->x() - mid_point->x()) < d.distance) {
            strip[j++] = point_set[i];
        }
    }

    point_pair between = strip_closest(strip, j, d);
    if (d.distance < between.distance) {
        return d;
    }
    else {
        return between;
    }
}
