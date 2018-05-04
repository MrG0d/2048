#include "gridlogic.h"

GridLogic::GridLogic()
{

}

/**
 * @brief GridLogic::setSize - Меняем размер поля
 * @param size
 */
void GridLogic::setSize(int size){
    this->size = size;
    QVector<int> tmp;
    tmp.fill(0,size);
    this->grid.clear();
    this->grid.fill(tmp,size);

    this->newRandomItem();
    this->newRandomItem();
    this->set_status(1);
    emit changeGrid(this->grid);
    this->printGrid();
}
int GridLogic::getSize(){
    return this->size;
}
/**
 * @brief GridLogic::rotate90 - Вращение доски по часовой стрелки
 * @param grid
 */
void GridLogic::rotate90(){
    int n = grid.length();
    for(int i=0; i<n/2; i++){
       for(int j=0; j<(n+1)/2; j++){
           GridLogic::cyclicRoll(grid[i][j], grid[n-1-j][i], grid[n-1-i][n-1-j], grid[j][n-1-i]);
       }
    }
}
/**
 * @brief GridLogic::cyclicRoll - Циклический перенос значений
 * @param a
 * @param b
 * @param c
 * @param d
 */
void GridLogic::cyclicRoll(int &a, int &b, int &c, int &d)
{
   int temp = a;
   a = b;
   b = c;
   c = d;
   d = temp;
}

/**
 * @brief GridLogic::move - Перемещение элементов в одну из сторон
 * @param side - Сторону ( 1 - вверх, 2 - вправо, 3 - вниз, 4 - влево)
 * @param size
 */
void GridLogic::move(int side){
    if(this->status!=1)return;
    switch(side){
//        case 1: this->moveUp(); break;
        case 1: // UP
            this->moveUp();
            break;
        case 2: // Right
            this->moveRight();
            break;
        case 3: //Down
            this->moveDown();
            break;
        case 4:  //Left
            this->moveLeft();
        break;
    }
    //qDebug()<<this->moveUp(true)<<this->moveRight(true)<<this->moveDown(true)<<this->moveLeft(true);

    if(this->flagMove){
        this->flagMove=0;
        this->newRandomItem();
        this->printGrid();
        emit changeGrid(this->grid);
        emit changeScore(this->getScore());
    }
    if(!this->moveUp(true) && !this->moveRight(true) && !this->moveDown(true) && !this->moveLeft(true)){
        this->set_status(0);
    }
}
void GridLogic::newRandomItem(){
    QVector <pos> free = this->getFreeCell();

    if(free.count()>0){
        int i = qrand()%free.count();
        pos newItem = free[i];
        QVector<int> vector = QVector<int>()<<4<<2<<2<<2;
        int rand=qrand()%vector.count();
        this->grid[newItem.y][newItem.x]=vector[rand];
    }
}
/**
 * @brief GridLogic::moveUp
 * @param pseudo - Если указать pseudo = false, то перемещений и слияний не будет, функция возвратит true, если перемещение или слияние возможно
 * @return
 */
bool GridLogic::moveUp(bool pseudo){
    this->rotate90();
    this->rotate90();
    bool res = this->moveDown(pseudo);
    this->rotate90();
    this->rotate90();
    return res;
}

bool GridLogic::moveRight(bool pseudo){
    this->rotate90();
    bool res = this->moveDown(pseudo);
    this->rotate90();
    this->rotate90();
    this->rotate90();
    return res;
}

bool GridLogic::moveLeft(bool pseudo){
    this->rotate90();
    this->rotate90();
    this->rotate90();
    bool res = this->moveDown(pseudo);
    this->rotate90();
    return res;
}

bool GridLogic::moveDown(bool pseudo){
    for(int y=this->size-1, m=y+1; y >= 0; y--,m=y+1){ //m - клетка ниже текущей
        for(int x=0; x < this->size; x++){
            int tmpY=y;
            if(this->grid[y][x]==0) continue; //нулевые клетки нет смысла перемещать
            for(int i=m; i<this->size; i++){
                if(this->grid[i][x]==0){ //если ниже клетка пуста, то текущую клетку перемещаем вниз
                    if(pseudo) return true;
                    this->grid[i][x]=this->grid[tmpY][x];
                    this->grid[tmpY][x]=0;
                    this->flagMove=1;
                    tmpY++; // если мы переместили текущую клетку, то меняем её отслеживаемую координату
                    continue;
                }
                if(this->grid[tmpY][x]==this->grid[i][x]){
                    if(pseudo) return true;
                    this->grid[i][x]=doubling(this->grid[i][x]); //если текущая клетка и клетка ниже одинаковой разрядности, то объединяем их и переходим к обработке следующей клетки
                    this->grid[tmpY][x]=0;
                    this->flagMove=1;
                    break;
                }else if(this->grid[tmpY][x]!=this->grid[i][x] && this->grid[i][x]!=0){
                    break; // если текущая клетка и клетка ниже разной разрядности, то переходим к обработке следующей клетки
                }
            }
        }
    }
    return false;
}

QVector <pos> GridLogic::getFreeCell(){
    QVector <pos> free;
    if(free.count()==0){
        /*Теперь пытаемся разместить новую клетку на краю, если на углах мест нету*/
        for(int i=0;i<this->size;i++)//верх
            if(this->grid[0][i]==0){
                pos tmp;
                tmp.x=i;
                tmp.y=0;
                free<<tmp;
            }
        for(int i=1;i<this->size;i++)//лево
            if(this->grid[i][0]==0){
                pos tmp;
                tmp.x=0;
                tmp.y=i;
                free<<tmp;
            }
        for(int i=1,e=this->size-1;i<=e;i++)//право
            if(this->grid[e][i]==0){
                pos tmp;
                tmp.x=i;
                tmp.y=e;
                free<<tmp;
            }
        for(int i=1,e=this->size-1;i<e;i++)//низ
            if(this->grid[i][e]==0){
                pos tmp;
                tmp.x=e;
                tmp.y=i;
                free<<tmp;
            }
        if(free.count()==0){ //Пытаемся хотя бы где-то разместить клетку
            for(int y=0;y<this->size;y++)
                for(int x=0;x<this->size;x++)
                    if(this->grid[y][x]==0){
                        pos tmp;
                        tmp.x=x;
                        tmp.y=y;
                        free<<tmp;
                    }
        }
//        for(int i=0;i<free.count();i++)
//            qDebug()<<free[i].y<<free[i].x;
    }
    return free;
}

int GridLogic::doubling(int n){
    int res = n*2;
    if(res==2048) this->set_status(2);
    return res;
}

void GridLogic::set_status(int status){
    this->status=status;
    emit changeStatus(status);
}
int GridLogic::getScore(){
    int sum=0;
    for(int i=0; i<this->size; i++)
        for(int j=0; j<this->size; j++)
            if(this->grid[i][j]>2)sum+=this->grid[i][j];
    return sum;
}

void GridLogic::printGrid(){
    QTextStream cout(stdout);
    cout<<"-------------------------"<<endl;
    cout.setFieldWidth(5);
    for(int i=0; i<this->size; i++){
        for(int j=0; j<this->size; j++){
            cout<<this->grid[i][j]<<flush;
        }
        cout<<endl;
    }
}
