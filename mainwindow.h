#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QWidget>
#include <QPaintEvent>
#include <Gamewidget.h>

namespace Ui {
class MainWindow;
}

class QSpinBox;
class MainWindow : public QMainWindow
{
    Q_OBJECT     // macro

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addPoint(int x, int y);
    void calculateRadius();



    ~MainWindow();

signals:
    void environmentChanged(bool ok);

public slots:
    void clearData();

private:
    Ui::MainWindow *ui;
    //GameWidget *game;
    QVector <int> qv_x,qv_y,x_net,y_net;
    QVector <double> rx_x, rx_y; // vectors for coordinates
    QTimer *timer;
    int *net_members;

    double radius;
    double circumference = 2*radius*3.14;
    //double net_distance = circumference/(qv_x.size()*2);        //distance between the points on the elastic net

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    //void mouseMoveEvent(QMouseEvent *e);
    void onMouseEvent(const QString &eventName, const QPoint &pos);
    void configureSpinBox(QSpinBox *spinBox, int min, int max ) const;
};

#endif // MAINWINDOW_H
