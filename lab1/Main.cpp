#include "schoolplanner.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SchoolPlanner schoolPlanner;
    schoolPlanner.show();
    return a.exec();
}
