#pragma once

#include <QMainWindow>
#include <QMutex>

#include "MainWindowPresenter.h"

namespace Ui
{
class MainWindow;
}

class QGraphicsScene;
class QPixmap;
class ImageReader;
class ImageFilter;

class MainWindowPresenter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const MainWindowPresenter* presenter, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadImage();
    void showFileDialog();
    void filterImage();

private:
    void initializeGUI();
    void initializeConnects();

    void adjustImageSizeToWindow();
    void setMainImage(QImage image);

    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QPixmap m_image;
    QString m_imageFilepath;
    std::unique_ptr<ImageReader> m_imageReader;
    std::unique_ptr<ImageFilter> m_imageFilter;
    QMutex m_mutex;

    const MainWindowPresenter* m_presenter;
};
