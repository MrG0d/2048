#ifndef GRIDLOGIC_H
#define GRIDLOGIC_H

#include <QVector>
#include <QObject>
#include <QDebug>
#include <QTextStream>
struct pos{
    int x;
    int y;
};

class GridLogic: public QObject
{
    Q_OBJECT
private:
    int flagMove; //флаг перемещения, 1 - если перемещение произошло, 0 - нет
    QVector<QVector<int> > grid;
    int status;// 0 - Игра окончена, 1 - Активна
    int size;
    void rotate90();
    static void cyclicRoll(int &a, int &b, int &c, int &d);
public:
    bool moveUp(bool pseudo = false);
    bool moveRight(bool pseudo = false);
    bool moveDown(bool pseudo = false);
    bool moveLeft(bool pseudo = false);
    void printGrid(); //отобразить массив grid в терминале
    void newRandomItem(); //добавить новый элемент
    QVector <pos> getFreeCell();
    void set_status(int status);
    int doubling(int n);
    int getScore();
public:
    GridLogic();
    void setSize(int size);
    int getSize();
public slots:
    void move(int side);  //1 - вверх, 2 - вправо, 3 - вниз, 4 - влево
signals:
    void changeScore(int);//Изменение кол-ва очков
    void changeGrid(QVector<QVector<int> > grid);//Изменение поля
    void changeStatus(int i);//0 - Игра окончена, 1 - Активная игра, 2 - 2048
};
#endif // GRIDLOGIC_H
