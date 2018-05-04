#include "grid.h"

Grid::Grid()
{
    this->setStyleSheet("border:none");
    this->width=50;
    this->margin=2;
    Color tmp;
    tmp.background="#ECF0F1";
    tmp.font="#37BFBD";
    color[2]=tmp;
    color[4]=tmp;
    tmp.background="#95A5A5";
    tmp.font="#FFF";
    color[8]=tmp;
    color[16]=tmp;
    tmp.background="#19BC9D";
    tmp.font="#FFF";
    color[32]=tmp;
    color[64]=tmp;
    tmp.background="#2C97DF";
    tmp.font="#FFF";
    color[128]=tmp;
    color[256]=tmp;
    tmp.background="#F1C50E";
    tmp.font="#FFF";
    color[512]=tmp;
    color[1024]=tmp;
    tmp.background="#E84C3D";
    tmp.font="#FFF";
    color[2048]=tmp;
}

void Grid::keyPressEvent(QKeyEvent *keyEvent){
    if(this->status!=0)
    switch(keyEvent->key()){
        case 16777235:
            emit move(1);//↑
            break;
        case 16777236:
            emit move(2);//→
            break;
        case 16777237:
            emit move(3);//↓
            break;
        case 16777234:
            emit move(4);//←
            break;
    }
}
void Grid::paintEvent(QPaintEvent *){
    QPainter *p = new QPainter(this);
    p->setRenderHint(QPainter::TextAntialiasing);
    this->change(p);

    switch(this->status){
        case 0:
            p->setBrush(QBrush(QColor(0,0,0,75)));
            p->setPen(QPen(QColor(0,0,0,75)));
            p->drawRect(0,0,this->geometry().height()+100,this->geometry().width());
            p->setBrush(QBrush(QColor("#e95247")));
            p->setPen(QPen(QColor("#e95247")));

            p->setFont(QFont("Sans", 15));
            p->drawRect(0,this->geometry().height()/2-25,this->geometry().width(),50);
            p->setPen(QPen(QColor("#FFF")));
            p->drawText(0,this->geometry().height()/2-25,this->geometry().width(),50,Qt::AlignCenter,"Игра окончена!");
            break;
        case 2:
            p->setBrush(QBrush(QColor(0,0,0,75)));
            p->setPen(QPen(QColor(0,0,0,75)));
            p->drawRect(0,0,this->geometry().height(),this->geometry().width());
            p->setBrush(QBrush(QColor("#37BFBD")));
            p->setPen(QPen(QColor("#37BFBD")));

            p->setFont(QFont("Sans", 15));
            p->drawRect(0,this->geometry().height()/2-25,this->geometry().width(),50);
            p->setPen(QPen(QColor("#FFF")));
            p->drawText(0,this->geometry().height()/2-25,this->geometry().width(),50,Qt::AlignCenter,"Вы выиграли!");
            break;
    }
}
void Grid::change(QPainter *p){
    QString blue="#37BFBD";

    this->size=this->data.count();
    emit changeSize(this->getWidth());
    for(int y=0;y<this->size;y++)
        for(int x=0;x<this->size;x++){
            if(this->data[y][x]!=0){
                QString font_color=color[this->data[y][x]].font;
                QString background_color=color[this->data[y][x]].background;
                p->setBrush(QBrush(QColor(background_color)));
                p->setPen(QPen(QColor(background_color)));
                p->drawRect(x*width,y*width,width-margin,width-margin);
                QString text=QString::number(this->data[y][x]);
                p->setFont(QFont("Sans",(text.length()<4)? 20 :16));
                p->setPen(QPen(QColor(font_color)));
                p->drawText(x*width,y*width,width-margin,width-margin,Qt::AlignCenter,text);
            }else{
                p->setBrush(QBrush(Qt::transparent));
                p->setPen(QPen(Qt::transparent));
                p->drawRect(x*width,y*width,width-margin,width-margin);
            }
        }
}
int Grid::getWidth(){
    int size=(width+margin*3)*this->size;
    return size;
}

void Grid::changeData(QVector<QVector<int> > data){
    this->data=data;
    repaint();
}
void Grid::changeStatus(int i){
    this->status=i;
    repaint();
}
