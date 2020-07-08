#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_prevPoint(QPoint(0, 0)), m_curPoint(QPoint(0, 0))
{
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 1001);
    m_backgroundColor = "#ffffff";
    //连接定时器信号与槽
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    //设置定时器时间并启动
    timer->start(1000);
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeOut()
{
    qDebug() << "1秒时间到!";
    m_backgroundColor = qRgb(rand()%256,rand()%256,rand()%256);
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    m_polygon.append(e->pos());
    QWidget::mousePressEvent(e);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    //do nothing
    m_bPressed = false;
    m_polygon.clear();
    this->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        m_polygon.append(e->pos());
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    QRect rect(2, 2, this->width() - 4, this->height() - 4);
    painter.fillRect(rect, m_backgroundColor);

    // 绘制曲线
    if (!m_polygon.isEmpty()) {
        painter.setClipRect(rect);
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(2);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawPolyline(m_polygon);
    }
}




