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
    timer(new QTimer(this))
    //game(new GameWidget(this))
{
    timer->setInterval(150);
    ui->setupUi(this);
    //ui->bx_x->setReadOnly(true);
    //ui->bx_y->setReadOnly(true);
    ui->bx_x->setValue(pos().x());
    ui->bx_y->setValue(pos().y());
    configureSpinBox(ui->bx_x, -INT_MAX, +INT_MAX);
    configureSpinBox(ui->bx_y, -INT_MAX, +INT_MAX);


    //connect(game,SIGNAL(mousePress(QMouseEvent *e)),SIGNAL(clickedGraph(QMouseEvent *e)));



    //connect(ui->addPointButton,SIGNAL(clicked()),game,SLOT(addPoint(bx_x.value(),bx_y.value())));
    //connect(game,SIGNAL(environmentChanged(bool)),SLOT(addPoint(bx_x.value(),bx_y.value())));
   // connect(game,SIGNAL(environmentChanged(bool)),ui->intervalSpinBox,SLOT(setDisabled(bool)));
    connect(ui->clearButton,SIGNAL(clicked()),SLOT(clearData()));

    //ui->gameLayout->addWidget(game);
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(int x, int y)             //adds the newly added points to the vector
{
    int index_counter = 0;
    int check = 0;
    for(int element : qv_x)         //checks if the city is already there
    {

        if(element == x)
        {
            if(qv_y[index_counter] == y)
            {
                check++;
            }
        }
        index_counter++;
    }
    if((x > 318 or x < 8) or (y > 408 or y < 8))      //checks if the coordinates are inside our playfield
        check ++;
    if(check == 0)      //if no checks are made -> add city
    {
        qv_x.append(x);
        qv_y.append(y);
        qDebug("Point added.");
        calculateRadius();
    }                     //calculates radius from the points

}

void MainWindow::calculateRadius()
{
    double sum_x = 0;
    double sum_y = 0;
    for (int x : qv_x)
        sum_x += x;
    rx_x.push_back(sum_x / qv_x.size());


    for (int x =0; x < qv_y.size(); x++)
        sum_y += qv_y[x];
    rx_y.push_back(sum_y / qv_y.size());

}

void MainWindow::clearData()        //removes all dots from the field
{
    qDebug("CLeared");
    qv_x.clear();           //clears the city Vector
    qv_y.clear();
    rx_x.clear();           //clears the radius
    rx_y.clear();
    update();

}

void MainWindow::paintEvent(QPaintEvent *e)         //paints the needed dots on the field
{
    QPainter cityPainter(this);
    //QPainter elasticNetPainter(this);
    QPen cities(QColor("green"));
    //QPen elasticNet(QColor("green"));
    cities.setWidth(5);
    //elasticNet.setWidth(5);
    cityPainter.setPen(cities);
    //elasticNetPainter.setPen(elasticNet);



    if(qv_x.size()!= 0 and qv_y.size()!=0)              //if not empty, draw new points
    {
        for (int i = 0; i< qv_x.size(); i++)
            cityPainter.drawPoint(qv_x[i],qv_y[i]);

    }

    QPen net(QColor("red"));
    net.setWidth(3);
    cityPainter.setPen(net);

    if (rx_x.size()!= 0 and rx_y.size()!=0)
    {
        cityPainter.drawPoint(rx_x.back(),rx_y.back());
    }


    for (int i = 0; i < qv_x.size(); i ++)      //calculate number of points on the net
            net_members += (i+1)*2;

    radius = 30 + 0.8*(2.5*qv_x.size());

    QPen ellipse(QColor("black"));              //use this pen for the circle
        ellipse.setWidth(0.1);
        cityPainter.setPen(ellipse);

    if (qv_x.size()!= 0 and qv_y.size()!= 0)        //draw the circle
            cityPainter.drawEllipse(QPointF(rx_x.back(),rx_y.back()),radius,radius);




    QRect gameLayout(3,3,320,410);
    cityPainter.drawRect(gameLayout);;

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    onMouseEvent("Press",e->pos());             // if the user clicks
    update();


}

/*void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
   onMouseEvent("Move",e->pos());

}*/

void MainWindow::onMouseEvent(const QString &eventName, const QPoint &pos)
{
    emit environmentChanged(true);
    ui->bx_x->setValue(pos.x());                //assign position on dot to the spinBox
    ui->bx_y->setValue(pos.y());
    addPoint(pos.x(),pos.y());

}

void MainWindow::configureSpinBox(QSpinBox *spinBox, int min, int max) const
{
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
}
