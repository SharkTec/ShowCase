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

class MainWindowPresenter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const MainWindowPresenter* presenter, QWidget *parent = nullptr);
    ~MainWindow();

    void adjustImageSizeToWindow();
    void setMainImage(const QImage* image);
    void setImagePathLabelText(const QString& text);

    QPixmap getCurrentImage() const;

private:
    void initializeGUI();
    void initializeConnects();

    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QPixmap m_image;
    QMutex m_mutex;
    const MainWindowPresenter* m_presenter;
};
