#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsScene>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QMatrix3x3>


#include "ImageReader.h"
#include "ImageFilter.h"

MainWindow::MainWindow(const MainWindowPresenter* presenter, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_scene(nullptr),
    m_image(QPixmap()),
    m_imageFilepath(QString()),
    m_imageReader(nullptr),
    m_presenter(presenter)
{
    ui->setupUi(this);

    m_imageReader = std::make_unique<ImageReader>();
    m_imageFilter = std::make_unique<ImageFilter>();

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
}

void MainWindow::initializeConnects()
{
    connect(ui->loadButton, &QPushButton::clicked,
            this, &MainWindow::loadImage);

    connect(ui->browseButton, &QPushButton::clicked,
            this, &MainWindow::showFileDialog);

    connect(ui->scaleButton, &QPushButton::clicked,
            this, &MainWindow::adjustImageSizeToWindow);

    connect(ui->filterButton, &QPushButton::clicked,
            this, &MainWindow::filterImage);
}

void MainWindow::adjustImageSizeToWindow()
{
    m_scene->clear();
    m_scene->setSceneRect(m_image.rect());
    m_scene->addPixmap(m_image);
    ui->imageView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::setMainImage(QImage image)
{
    QMutexLocker locker(&m_mutex);
    m_image = QPixmap::fromImage(image);
}

void MainWindow::loadImage()
{
    if(m_imageFilepath.isEmpty()){
        qDebug() << tr("Image filepath is empty.");
        return;
    }

    const QFuture<QImage> future = QtConcurrent::run(&ImageReader::readImage, m_imageReader.get(), m_imageFilepath);

    QFutureWatcher<QImage>* watcher = new QFutureWatcher<QImage>(this);
    connect(watcher, &QFutureWatcher<QImage>::finished, [this, future]{

        const auto result = future.result();
        if(!result.isNull()){
            setMainImage(result);
            adjustImageSizeToWindow();
        }
    });
    watcher->setFuture(future);
}

void MainWindow::showFileDialog()
{
    const QString homeDir = "D:\\";
    m_imageFilepath = QFileDialog::getOpenFileName(this, tr("Open image file"), homeDir,
                                         tr("Image files (*.png *.tif *.jpg)"));

    ui->pathLabel->setText(m_imageFilepath);
}

void MainWindow::filterImage()
{
    const auto image = m_image.toImage();
    if(image.isNull()){
        qDebug() << tr("Image is empty. Filtering is not possible.");
        return;
    }

    const QFuture<QImage> future = QtConcurrent::run(&ImageFilter::filterImage, m_imageFilter.get(), image);

    QFutureWatcher<QImage>* watcher = new QFutureWatcher<QImage>(this);

    connect(watcher, &QFutureWatcher<QImage>::finished, [this, future]{

        const auto result = future.result();
        if(!result.isNull()){
            setMainImage(result);
            adjustImageSizeToWindow();
        }
    });
    watcher->setFuture(future);
}
