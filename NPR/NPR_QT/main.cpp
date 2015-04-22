#include <QApplication>

#include "edgefinder.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EdgeFinder edgefinder;
    edgefinder.show();
    return app.exec();
}
