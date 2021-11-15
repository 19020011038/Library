#include "mainwindow.h"

#include <QApplication>
#include <partition.h>
#include "book_ditails.h"

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    {
        QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling );
        QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    }
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
