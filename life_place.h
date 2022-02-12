#ifndef LIFE_PLACE_H
#define LIFE_PLACE_H
#include <QVector>
#include <iostream>


using namespace std;

class life_place {
    int height, width;
    QVector<QVector<int>> place;
    public:
        life_place(int width, int height, QVector<QVector<int>> place);
        life_place(int width, int height);
        void setWidth(int width);
        void setHeight(int heiht);
        int getWidth();
        int getHeight();
        void setPoint(int x, int y, bool life);
        bool getPoint(int x, int y);
        int nextGen();
        void clear();
        QVector<QVector<int>> getPlace();
        void setPlace(QVector<QVector<int>> place);
        void resize(int width, int height);
        void setFromFile(QString fname);
};

#endif // LIFE_PLACE_H
