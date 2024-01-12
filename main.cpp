#include "MainWindow.h"
#include "MainWindowPresenter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::unique_ptr<MainWindowPresenter> mainPresenter = std::make_unique<MainWindowPresenter>();

    std::unique_ptr<MainWindow> mainWindow = std::make_unique<MainWindow>();

    mainWindow->show();

    return a.exec();
}
