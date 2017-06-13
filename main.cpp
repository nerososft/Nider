#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

//#include <QtCore>
//#include <QtGui>
//#include <QApplication>
//#include <QMainWindow>

//#include "lib/qtermwidget.h"

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    QMainWindow *mainWindow = new QMainWindow();

//    QTermWidget *console = new QTermWidget();

//    QFont font = QApplication::font();
//    font.setFamily("Terminus");
//    font.setPointSize(12);

//    console->setTerminalFont(font);

//    //console->setColorScheme(COLOR_SCHEME_BLACK_ON_LIGHT_YELLOW);
//    console->setScrollBarPosition(QTermWidget::ScrollBarRight);

//    mainWindow->setCentralWidget(console);
//    mainWindow->resize(802, 610);

//    QObject::connect(console, SIGNAL(finished()), mainWindow, SLOT(close()));

//    mainWindow->show();
//    return app.exec();
//}


