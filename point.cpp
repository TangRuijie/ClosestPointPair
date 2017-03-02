#include "point.h"

Point::Point(QWidget *parent): m_x(0), m_y(0), QWidget(parent)
{
    m_picture = new QLabel(this);
    m_picture->setPixmap(QPixmap("black_circle.png"));
    m_picture->setGeometry(QRect(m_x, m_y, 9, 9));
} // The defintion of default constructor finished

Point::Point(int x, int y, QWidget *parent): m_x(x - 4), m_y(y - 4), QWidget(parent)
{
    m_picture = new QLabel(parent);
    m_picture->setPixmap(QPixmap(":/picture/Resource/black_circle.png"));
    m_picture->setGeometry(QRect(m_x, m_y, 9, 9));
    m_picture->show();
    show();
} // The definition of parametered constructor finished

Point::~Point()
{
    delete m_picture;
} // The definition of destructor finished

int Point::x()
{
    return m_x;
} // The definition of x() finished

int Point::y()
{
    return m_y;
} // The definition of y() finished
