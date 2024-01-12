#pragma once

#include <QObject>
#include <QMutex>
#include <QPixmap>

class MainWindow;

class ImageReader;
class ImageFilter;
class QPixmap;

class MainWindowPresenter : public QObject
{
public:
    MainWindowPresenter();

    void setMainWindow(MainWindow* mainWindow);

public slots:
    void loadImage();
    void showFileDialog();
    void filterImage();

private:
    MainWindow* m_mainWindow;
    QString m_imageFilepath;
    std::unique_ptr<ImageReader> m_imageReader;
    std::unique_ptr<ImageFilter> m_imageFilter;
    QMutex m_mutex;
    QPixmap m_image;
};
