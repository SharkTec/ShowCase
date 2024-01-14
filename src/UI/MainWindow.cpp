#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsScene>
#include <QPixmap>

MainWindow::MainWindow(const MainWindowPresenter* presenter, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_scene(nullptr),
    m_image(QPixmap()),
    m_presenter(presenter)
{
    ui->setupUi(this);

    initializeGUI();
    initializeConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeGUI()
{
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(m_image.rect());
    ui->imageView->setScene(m_scene);
    ui->loadButton->setText(tr("Load image file"));
    ui->browseButton->setText(tr("Browse images"));
    ui->pathLabelText->setText(tr("Path:"));
    ui->pathLabel->setText("No path selected yet.");
    this->setWindowTitle("<< Super useful edge detector >>");
}

void MainWindow::initializeConnects()
{
    connect(ui->loadButton, &QPushButton::clicked,
            m_presenter, &MainWindowPresenter::loadImage);

    connect(ui->browseButton, &QPushButton::clicked,
            m_presenter, &MainWindowPresenter::showFileDialog);

    connect(ui->filterButton, &QPushButton::clicked,
            m_presenter, &MainWindowPresenter::filterImage);

    connect(ui->scaleButton, &QPushButton::clicked,
            this, &MainWindow::adjustImageSizeToWindow);
}

void MainWindow::adjustImageSizeToWindow()
{
    m_scene->clear();
    m_scene->setSceneRect(m_image.rect());
    m_scene->addPixmap(m_image);
    ui->imageView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::setPathLabelText(const QString &text)
{
    ui->pathLabel->setText(text);
}

void MainWindow::setMainImage(const QImage& image)
{
    m_image = QPixmap::fromImage(image);
}

void MainWindow::setImagePathLabelText(const QString& text)
{
    ui->pathLabel->setText(text);
}

QImage MainWindow::getMainImage() const
{
    return m_image.toImage();
}
