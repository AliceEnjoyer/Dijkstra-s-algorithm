#include "winodw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window w;
    w.setMinimumSize(895, 700);
    w.show();
    return a.exec();
}
