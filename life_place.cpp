#include "life_place.h"

#include <fstream>


life_place::life_place(int height, int width, QVector<QVector<int>> place)
{
    life_place::height = height;
    life_place::width = width;
    life_place::place = place;
}

life_place::life_place(int height, int width) {
    life_place::height = height;
    life_place::width = width;
    life_place::place.resize(height+2);
    for(int i = 0; i<height+2; i++) {
        life_place::place[i].resize(width+2);
        for(int j = 0; j<width+2; j++)
            life_place::place[i][j] = 0;
    }

}

void life_place::setWidth(int width) {
    life_place::width = width;
}

void life_place::setHeight(int height) {
    life_place::height = height;
}

int life_place::getHeight() {
    return life_place::height;
}

void life_place::setPoint(int x, int y, bool life)
{
    if(life) life_place::place[y+1][x+1] = 1;
    else life_place::place[x+1][y+1] = 0;
}

bool life_place::getPoint(int x, int y)
{
    return life_place::place[y+1][x+1] == 1;
}

int life_place::getWidth() {
    return life_place::width;
}

void life_place::setPlace(QVector<QVector<int>> place) {
    life_place::place = place;
}

void life_place::resize(int width, int height)
{
    life_place::height = height;
    life_place::width = width;
    life_place::place.resize(height+2);
    for(int i = 0; i<height+2; i++) {
        life_place::place[i].resize(width+2);
        for(int j = 0; j<width+2; j++)
            life_place::place[i][j] = 0;
    }
}

void life_place::setFromFile(QString fname)
{
    ifstream fin(fname.toStdString());
    int width, height;
    fin>>width>>height;
    life_place::resize(width, height);
    for(int i = 1; i<=height; i++)
        for(int j = 1; j<=width; j++)
            fin>>life_place::place[i][j];
    fin.close();
}

QVector<QVector<int>> life_place::getPlace() {
    return life_place::place;
}

int life_place::nextGen() {
    int k = -1;
    QVector<QVector<int>> newplace;
    newplace.resize(height+2);
    for(int i = 0; i<height+2; i++) {
        newplace[i].resize(width+2);
        for(int j = 0; j<width+2; j++)
            newplace[i][j] = 0;
    }
    for(int i = 1; i<=height; i++)
        for(int j = 1; j<=width; j++) {
            int nb = 0;
            if(life_place::place[i-1][j-1] > 0) nb++;
            if(life_place::place[i-1][j] > 0) nb++;
            if(life_place::place[i-1][j+1] > 0) nb++;
            if(life_place::place[i][j-1] > 0) nb++;
            if(life_place::place[i][j+1] > 0) nb++;
            if(life_place::place[i+1][j-1] > 0) nb++;
            if(life_place::place[i+1][j] > 0) nb++;
            if(life_place::place[i+1][j+1] > 0) nb++;

            if(life_place::place[i][j]==0) {
                if(nb == 3) {
                    newplace[i][j]= 1;
                    k++;
                }
            }
            else {
                if(nb<2 || nb>3) {
                    newplace[i][j] = 0;
                    k++;
                }
                else
                    newplace[i][j] = 1;
            }
        }
    life_place::place = newplace;
    return k;
}

void life_place::clear() {
    for(int i = 0; i<height+2; i++)
        for(int j = 0; j<width+2; j++)
            life_place::place[i][j] = 0;
}
