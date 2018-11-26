#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this)),
    game(new GameWidget(this))
{
    timer->setInterval(150);
    ui->setupUi(this);
    ui->bx_x->setReadOnly(true);
    ui->bx_y->setReadOnly(true);
    ui->bx_x->setValue(pos().x());
    ui->bx_y->setValue(pos().y());
    configureSpinBox(ui->bx_x, -INT_MAX, +INT_MAX);
    configureSpinBox(ui->bx_y, -INT_MAX, +INT_MAX);


    //connect(game,SIGNAL(mousePress(QMouseEvent *e)),SIGNAL(clickedGraph(QMouseEvent *e)));



    connect(ui->addPointButton,SIGNAL(clicked()),game,SLOT(addPoint(bx_x.value(),bx_y.value())));
    connect(game,SIGNAL(environmentChanged(bool)),SLOT(addPoint(bx_x.value(),bx_y.value())));
    connect(game,SIGNAL(environmentChanged(bool)),ui->intervalSpinBox,SLOT(setDisabled(bool)));
    connect(ui->clearButton,SIGNAL(clicked()),SLOT(clearData()));

    ui->gameLayout->addWidget(game);
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(int x, int y)
{

    qv_x.append(x);
    qv_y.append(y);
    qDebug("Point added.");



}

void MainWindow::clearData()
{
    qDebug("CLeared");
    qv_x.clear();
    qv_y.clear();
    update();

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter cityPainter(this);
    //QPainter elasticNetPainter(this);
    QPen cities(QColor("blue"));
    //QPen elasticNet(QColor("green"));
    cities.setWidth(5);
    //elasticNet.setWidth(5);
    cityPainter.setPen(cities);
    //elasticNetPainter.setPen(elasticNet);



    if(qv_x.size()!= 0 and qv_y.size()!=0)
    {
        for (int i = 0; i< qv_x.size(); i++)
            cityPainter.drawPoint(qv_x[i],qv_y[i]);

    }







    //QRect gameLayout(6,6,320,400);
    //painter.drawRect(gameLayout);;

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    onMouseEvent("Press",e->pos());
    update();


}

/*void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
   onMouseEvent("Move",e->pos());

}*/

void MainWindow::onMouseEvent(const QString &eventName, const QPoint &pos)
{
    emit environmentChanged(true);
    qDebug("Clicked");
    ui->bx_x->setValue(pos.x());
    ui->bx_y->setValue(pos.y());
    addPoint(pos.x(),pos.y());

}

void MainWindow::configureSpinBox(QSpinBox *spinBox, int min, int max) const
{
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
}
