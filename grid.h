#ifndef GRID_H
#define GRID_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QVector>
#include <QMap>
struct Color{
    QString font;
    QString background;
};
class Grid : public QWidget
{
    Q_OBJECT
    int size;
    QVector<QVector<int> > data;
    QMap<int,Color> color;
    void keyPressEvent(QKeyEvent *keyEvent);
    void paintEvent(QPaintEvent *);
    void change(QPainter *p);
    int status;
    int width,margin;
public:
    int getWidth();
    Grid();
signals:
    void move(int side); //1 - вверх, 2 - вправо, 3 - вниз, 4 - влево
    void changeSize(int size); //новая ширина игрового поля
public slots:
    void changeData(QVector<QVector<int> > data);
    void changeStatus(int i);
};

#endif // GRID_H
