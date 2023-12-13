#include <QApplication>
#include "view/Mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/ioPrenoto.png"));
    MainWindow mainWindow;
    mainWindow.resize(MainWindow::mainWindowWidth, MainWindow::mainWindowHeigth);
    mainWindow.show();
    return app.exec();
}
