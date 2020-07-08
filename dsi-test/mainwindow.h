#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimeOut();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

protected:
    void		mousePressEvent(QMouseEvent *e);
    void		mouseReleaseEvent(QMouseEvent *e);
    void		mouseMoveEvent(QMouseEvent *e);
    void		paintEvent(QPaintEvent *e);
private:
    QColor      m_backgroundColor;
    QPolygon    m_polygon;
    bool        m_bPressed;
    QPoint		m_prevPoint;
    QPoint		m_curPoint;
};

#endif // MAINWINDOW_H
