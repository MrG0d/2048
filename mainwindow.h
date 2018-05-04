#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QGridLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <grid.h>
#include <gridlogic.h>

class InputIntDialog : public QInputDialog{
    Q_OBJECT
public:
    InputIntDialog();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Grid *grid;
    GridLogic *logic;
    QLabel *lb_score;
    QGridLayout *gl;
    QPushButton *pb_newGame;
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    QPoint windowPos;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void newGame();
public slots:
    void changeSize(int size);
    void changeScore(int score);

};

#endif // MAINWINDOW_H
