#pragma once

#include "MainWindowPresenter.h"

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindowPresenter;
class QGraphicsScene;
class QPixmap;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const MainWindowPresenter* presenter, QWidget* parent = nullptr);
    virtual ~MainWindow();

    void setMainImage(const QImage& image);
    QImage getMainImage() const;

    void setImagePathLabelText(const QString& text);

    void adjustImageSizeToWindow();

    void setPathLabelText(const QString& text);

private:
    void initializeGUI();
    void initializeConnects();

    Ui::MainWindow* ui;
    QGraphicsScene* m_scene;
    QPixmap m_image;
    const MainWindowPresenter* m_presenter;
};
