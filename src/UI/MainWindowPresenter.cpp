#include "MainWindowPresenter.h"
#include "MainWindow.h"

#include "src/Business/Logger.h"

#include "src/Business/ImageReader.h"
#include "src/Business/ImageFilter.h"

#include <QDebug>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QFileDialog>

void MainWindowPresenter::setMainWindow(MainWindow* mainWindow)
{
    m_mainWindow = mainWindow;
    Logger::getInstance()->logMessage("Setting main window.");
    Logger::getInstance()->logMessage("Launching up.");
}

void MainWindowPresenter::loadImage()
{
    if(m_imageFilepath.isEmpty())
    {
        Logger::getInstance()->logMessage("Image filepath is empty.");
        return;
    }

    const QFuture<QImage> future = QtConcurrent::run(&ImageReader::readImage, m_imageReader.get(), m_imageFilepath);

    QFutureWatcher<QImage>* watcher = new QFutureWatcher<QImage>(this);
    connect(watcher, &QFutureWatcher<QImage>::finished, [this, future, watcher]
    {
        const auto result = future.result();
        if(!result.isNull()){
            m_mainWindow->setMainImage(&result);
            m_mainWindow->adjustImageSizeToWindow();
            delete watcher;
        }
    });
    watcher->setFuture(future);
}

void MainWindowPresenter::showFileDialog()
{
    const QString homeDir = "D:\\";
    m_imageFilepath = QFileDialog::getOpenFileName(m_mainWindow, tr("Open image file"), homeDir, tr("Image files (*.png *.tif *.jpg)"));
}

void MainWindowPresenter::filterImage()
{
    const QImage& image = m_mainWindow->getCurrentImage().toImage();
    if(image.isNull())
    {
        qDebug() << tr("Image is empty. Filtering is not possible.");
        return;
    }

    const QFuture<QImage> future = QtConcurrent::run(&ImageFilter::filterImage, m_imageFilter.get(), image);

    QFutureWatcher<QImage>* watcher = new QFutureWatcher<QImage>(this);

    connect(watcher, &QFutureWatcher<QImage>::finished, [this, future, watcher]
    {
        const auto result = future.result();
        if(!result.isNull()){
            m_mainWindow->setMainImage(&result);
            m_mainWindow->adjustImageSizeToWindow();
            delete watcher;
        }
    });
    watcher->setFuture(future);
}
