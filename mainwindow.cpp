#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QRandomGenerator>
#include <stdio.h>
#include <math.h>
#include <QDebug>

QTimer *timer_plot;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->x = 0;
    this->fps = 0;
    this->T = 0;
    this->serial = new QLineSeries();
    this->serial->setName("data");

    this->chart = new QChart();

    //this->serial->setMarkerSize(100);

    this->chart->addSeries(this->serial);
    this->chart->setTitle("Chart");
    this->chart->legend()->setMarkerShape(QLegend::MarkerShapeCircle);
    this->chart->createDefaultAxes();
    this->chart_view = new QChartView(this->chart);

    this->ui->gridLayout->addWidget(this->chart_view);

    timer_plot = new QTimer(NULL);
    this->fps_timer = new QTimer(NULL);
    connect(timer_plot,SIGNAL(timeout()),this,SLOT(update()));
    connect(this->fps_timer,SIGNAL(timeout()),this,SLOT(update_fps()));
    timer_plot->start(10);
    this->fps_timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#define MAX_POINT 360*100

void MainWindow::update()
{

    static uint32_t range = 0;
    //this->serial->append(this->x,y_point);
    if(!this->data_buff.isEmpty()){
        QList<float> p_data = this->data_buff.dequeue();
        this->T++;
        range += MAX_POINT;
        float min = *std::min_element(p_data.begin(),p_data.end());
        float max = *std::max_element(p_data.begin(),p_data.end());
       // this->serial->clear();
        QList<QPointF> source;
        for(uint32_t i = 0;i<MAX_POINT;i++){
            QPointF value(i+range-MAX_POINT,p_data.at(i));
            source.append(value);
           // this->serial->append();
        }
        this->serial->replace(source);
        this->chart->axisX()->setRange(range-MAX_POINT,range);
        this->chart->axisY()->setRange(min,max);
    }
}

void MainWindow::update_fps()
{
    for(uint32_t i = 0;i<MAX_POINT;i++){
        float y_point = 10*std::sin(x*3.14/180);
        this->x++;
        this->data.append(y_point);
    }
    this->x = 0;
    this->data_buff.enqueue(this->data);
    this->data.clear();
}
