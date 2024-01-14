#include "ImageUtilityProvider.h"

#include "src/Business/ImageReader.h"
#include "src/Business/ImageFilter.h"

#include "src/Business/Logger.h"

//#include <QFutureWatcher>
//#include <QtConcurrent/QtConcurrent>
#include <QImage>

#include <future>

QImage ImageUtilityProvider::loadImage(const QString& imagePath)
{
    if(imagePath.isEmpty())
    {
        Logger::getInstance()->logMessage("Image filepath is empty.");
        return QImage();
    }

    std::future<QImage> imageLoadFuture = std::async(std::launch::async, [this, imagePath]()
    {
        return m_imageReader->readImage(imagePath);
    });

    return imageLoadFuture.get();
}

void ImageUtilityProvider::filterImage(QImage& image)
{
    if(image.isNull())
    {
        Logger::getInstance()->logMessage("Image is empty. Filtering not possible.");
        return;
    }

    std::future<QImage> imageFilterFuture = std::async(std::launch::async, [this, &image]()
    {
        return m_imageFilter->filterImage(image);
    });

    image = imageFilterFuture.get();

    Logger::getInstance()->logMessage("Image filtered.");

    // here the way of implementation if I'd do asynchronous computation using Qt classes

    /*
     * const QFuture<QImage> future = QtConcurrent::run(&ImageFilter::filterImage, m_imageFilter.get(), image);

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
    watcher->setFuture(future); */
}
