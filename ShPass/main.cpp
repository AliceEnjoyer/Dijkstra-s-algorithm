#include "winodw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    winodw w;
    w.show();
    return a.exec();
}
