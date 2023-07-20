#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSize size(640, 400);
    image = QPixmap(size).toImage();
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(QRect(QPoint(0, 0), size));
    ui->graphicsView->setFixedSize(size);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::refresh);
    timer->setInterval(refreshDelay);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh() {
    QFile file("/tmp/doom_image");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Unable to open file.";
        return void();
    }
    int counter = 0;
    quint8 r;
    quint8 g;
    quint8 b;
    qint64 fileSize = file.size();
    char* buffer = new char[fileSize];
    qint64 bytesRead = file.read(buffer, fileSize);

    if (bytesRead != fileSize) {
        qDebug() << "Error: Failed to read all bytes from the file.";
        delete[] buffer;
        file.close();
        // exit(-1);
        return void();
    }
    file.remove();

    for(int y = 0; y < 400; y++) {
        for(int x = 0; x < 640; x++) {
            r = static_cast<quint8>(buffer[counter]);
            g = static_cast<quint8>(buffer[counter + 1]);
            b = static_cast<quint8>(buffer[counter + 2]);
            QColor color(r, g, b);
            //qDebug() << "RGB:" << r << g << b;
            image.setPixel(x, y, color.rgb());
            counter = counter + 4;
        }
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);

    delete[] buffer;
}

void MainWindow::button(QString content) {
    QString filename = "/tmp/doom_control";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << content << endl;
        file.close();
    }
}

void MainWindow::stopButton(QString content) {
    QString filename = "/tmp/doom_control_stop";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << content << endl;
        file.close();
    }
}

void MainWindow::on_Enter_clicked()
{
    button("enter");
}


void MainWindow::on_escButton_clicked()
{
    button("esc");
}


void MainWindow::on_strafeButton_clicked()
{
    button("straf");
}


void MainWindow::on_fireButton_clicked()
{
    button("fire");
    QTimer::singleShot(buttonStopDelay, this, [this] () {
        stopButton("fire_stop");
    });
}


void MainWindow::on_useButton_clicked()
{
    button("use");
    QTimer::singleShot(buttonStopDelay, this, [this] () {
        stopButton("use_stop");
    });
}


void MainWindow::on_leftButton_clicked()
{
    button("left");
    QTimer::singleShot(buttonStopDelay, this, [this] () {
        stopButton("left_stop");
    });
}


void MainWindow::on_upButton_clicked()
{
    button("up");
    QTimer::singleShot(buttonStopDelay, this, [this] () {
        stopButton("up_stop");
    });
}


void MainWindow::on_rightButton_clicked()
{
    button("right");
    QTimer::singleShot(buttonStopDelay, this, [this] () {
        stopButton("right_stop");
    });
}


void MainWindow::on_downButton_clicked()
{
    button("down");
    QTimer::singleShot(buttonStopDelay, this, [this] () {
        stopButton("down_stop");
    });
}

