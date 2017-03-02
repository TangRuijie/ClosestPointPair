#ifndef POINT_H
#define POINT_H
#include <QWidget>
#include <QLabel>
#include <QDebug>

class Point: QWidget
{
    Q_OBJECT
public:
    Point(QWidget *parent = 0);
    Point(int x, int y, QWidget *parent = 0);
    ~Point();
public:
    int x();
    int y();
private:
    int m_x;
    int m_y;
public:
    QLabel *m_picture;
};

#endif // POINT_H
