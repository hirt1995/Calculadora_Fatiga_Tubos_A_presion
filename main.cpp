#include "calfatiga.h"
#include <QApplication>
#include <qmath.h>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalFatiga w;
    w.show();

    return a.exec();
}
