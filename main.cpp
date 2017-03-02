#include "closest_points.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    closest_points w;
    w.show();

    return a.exec();
}
