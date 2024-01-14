#pragma once

#include <QObject>

#include "src/Business/ImageUtilityProvider.h"

class MainWindow;
class MainWindowPresenterModel;
class ImageUtilityProvider;

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
    std::unique_ptr<ImageUtilityProvider> m_imageUtilsProvider;

    // see header of MainWindowPresenterModel for why this is commented

    //MainWindowPresenterModel* m_model;
};
