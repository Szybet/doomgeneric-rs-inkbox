#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qgraphicsscene.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refresh();
    QImage image;
    QGraphicsScene* scene;
    QTimer* timer;
    void button(QString content);
    void stopButton(QString content);
    int refreshDelay = 100;
    int buttonStopDelay = 100;

private slots:
    void on_Enter_clicked();

    void on_escButton_clicked();

    void on_strafeButton_clicked();

    void on_fireButton_clicked();

    void on_useButton_clicked();

    void on_leftButton_clicked();

    void on_upButton_clicked();

    void on_rightButton_clicked();

    void on_downButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
