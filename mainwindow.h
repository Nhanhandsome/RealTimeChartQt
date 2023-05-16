#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QQueue>
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *fps_timer;
    QLineSeries *serial;
    QChart *chart;
    QChartView *chart_view;
    uint32_t x;
    QList<float> data;
    QQueue<QList<float>> data_buff;
    float fps;
    uint16_t T;
public slots:
    void update();
    void update_fps();
};
#endif // MAINWINDOW_H
