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



    ~MainWindow();

signals:
    void environmentChanged(bool ok);

public slots:
    void clearData();

private:
    Ui::MainWindow *ui;
    //GameWidget *game;
    QVector <int> qv_x,qv_y,x_net,y_net,rx;
    QTimer *timer;

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    //void mouseMoveEvent(QMouseEvent *e);
    void onMouseEvent(const QString &eventName, const QPoint &pos);
    void configureSpinBox(QSpinBox *spinBox, int min, int max ) const;
};

#endif // MAINWINDOW_H
