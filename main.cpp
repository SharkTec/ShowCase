
#include "src/UI/MainWindow.h"
#include "src/UI/MainWindowPresenter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::unique_ptr<MainWindowPresenter> mainPresenter = std::make_unique<MainWindowPresenter>();

    std::unique_ptr<MainWindow> mainWindow = std::make_unique<MainWindow>(mainPresenter.get());
    mainPresenter->setMainWindow(mainWindow.get());

    mainWindow->show();

    return a.exec();
}
