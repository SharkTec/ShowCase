#include "MainWindowPresenterModel.h"

MainWindowPresenterModel::MainWindowPresenterModel(QObject* parent)
    : QObject(parent)
{}

void MainWindowPresenterModel::setModelData(const QImage& image)
{
    m_image = image;
}

QImage MainWindowPresenterModel::getModelData() const
{
    return m_image;
}
