#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *w = new QWidget;
    gl = new QGridLayout;
    w->setLayout(gl);
    this->setCentralWidget(w);
    this->setStyleSheet("QMainWindow{background:#1C1F20; margin:0; padding:0; color:#FFF;}QPushButton{padding:5px 10px}");

    this->setWindowFlags(Qt::FramelessWindowHint);


    QHBoxLayout *hb_header = new QHBoxLayout;
    QPushButton *pb_close = new QPushButton(QIcon(":close.png"),"");
    connect(pb_close,SIGNAL(clicked(bool)),this,SLOT(close()));
    pb_close->setIconSize(QSize(32,32));
    pb_close->setFlat(true);
    pb_close->setFocusPolicy(Qt::NoFocus);

    pb_newGame = new QPushButton;
    pb_newGame->setFocusPolicy(Qt::NoFocus);
    pb_newGame->setFlat(true);
    pb_newGame->setIcon(QIcon(":restart.png"));
    pb_newGame->setIconSize(QSize(32,32));
    connect(pb_newGame,SIGNAL(clicked(bool)),this,SLOT(newGame()));
    hb_header->addWidget(pb_newGame);

    hb_header->addStretch();
    lb_score=new QLabel("0");
    lb_score->setStyleSheet("color:#09F; font-size:20px; text-align:center; padding:2px 10px;");
    hb_header->addWidget(lb_score);

    hb_header->addStretch();
    hb_header->addWidget(pb_close);

    gl->addLayout(hb_header,0,0);
    grid = new Grid;
    logic = new GridLogic;
    connect(grid,SIGNAL(move(int)),logic,SLOT(move(int)));
    connect(logic,SIGNAL(changeGrid(QVector<QVector<int> >)),grid,SLOT(changeData(QVector<QVector<int> >)));
    connect(grid,SIGNAL(changeSize(int)),this,SLOT(changeSize(int)));
    connect(logic,SIGNAL(changeStatus(int)),grid,SLOT(changeStatus(int)));
    connect(logic,SIGNAL(changeScore(int)),this,SLOT(changeScore(int)));

    QHBoxLayout *hb = new QHBoxLayout;
    hb->addWidget(grid);
    gl->addLayout(hb,2,0);
    gl->setRowStretch(2,5);
    logic->setSize(4);
    grid->setFocus();
}

void MainWindow::newGame(){
    bool ok=false;
    int size = InputIntDialog::getInt(this,"Новая игра","Размер поля",logic->getSize(),2,10,1,&ok);
    if(ok){
        logic->setSize(size);
    }
}
void MainWindow::changeScore(int score){
    lb_score->setText(QString::number(score));
}
void MainWindow::changeSize(int size){
    this->resize(size,size+55);
}

MainWindow::~MainWindow()
{

}
void MainWindow::mousePressEvent(QMouseEvent* e)
{
    windowPos=e->pos();
}
void MainWindow::mouseMoveEvent(QMouseEvent* e)
{
    if (windowPos.rx() >= 0 && e->buttons() && Qt::LeftButton)
    {
        QPoint diff = e->pos() - windowPos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
