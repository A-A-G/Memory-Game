#include "memory.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Hello World!");
    Memory w;
    w.show();
    return app.exec();
}

