#include "MainWindowPresenter.h"
//#include "MainWindowPresenterModel.h"
#include "MainWindow.h"

#include "src/Business/Logger.h"

#include "src/Business/ImageUtilityProvider.h"

#include <QFileDialog>

MainWindowPresenter::MainWindowPresenter()
    : m_mainWindow(nullptr)
    , m_imageUtilsProvider(std::make_unique<ImageUtilityProvider>())
    /*, m_model(new MainWindowPresenterModel(this))*/
{}

void MainWindowPresenter::setMainWindow(MainWindow* mainWindow)
{
    m_mainWindow = mainWindow;
    Logger::getInstance()->logMessage("Setting main window.");
    Logger::getInstance()->logMessage("Launching up.");
}

void MainWindowPresenter::loadImage()
{
    const QImage& image = m_imageUtilsProvider->loadImage(m_imageFilepath);

    m_mainWindow->setMainImage(image);
    m_mainWindow->adjustImageSizeToWindow();
}

void MainWindowPresenter::showFileDialog()
{
    const QString& homeDir = "D:\\"; //example path, should be configurable
    m_imageFilepath = QFileDialog::getOpenFileName(m_mainWindow, tr("Open image file"), homeDir, tr("Image files (*.png *.tif *.jpg)"));
    m_mainWindow->setPathLabelText(m_imageFilepath);
}

void MainWindowPresenter::filterImage()
{
    QImage currentImage = m_mainWindow->getMainImage();

    m_imageUtilsProvider->filterImage(currentImage);

    m_mainWindow->setMainImage(currentImage);
    m_mainWindow->adjustImageSizeToWindow();
}
