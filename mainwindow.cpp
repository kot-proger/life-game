#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QLabel>
#include <QtGui/QMouseEvent>
#include "life_place.h"
#include <QTimer>
#include <QtTest>
#include <fstream>
#include <QMessageBox>
#include <string.h>
#include <iostream>

bool start = false;
life_place place(25,50);
QTimer *life_timer;
int saves;
int lw = 1200;
int lh = 600;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    life_timer = new QTimer(this);
    connect(life_timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    ifstream fin("saves.txt");
    fin>>saves;
    fin.close();
    for(int i = 0; i<saves; i++){
        ui->set_save->addItem(QString().number(i+1), QVariant(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawplace(bool first)
{
    int n = place.getHeight(), m = place.getWidth(), nh = lh/n, mh = lw/m;
    lh = nh*n;
    lw = mh*m;
    QVector<QVector<int>> nowplace = place.getPlace();
    QPainter pen;
    QPixmap lplace;
    if(first) lplace = QPixmap(lw, lh);
    else lplace = QPixmap(ui->life_place->pixmap());
    pen.begin(&lplace);
    pen.eraseRect(0,0,lw,lh);
    pen.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    for(int i = 0; i<lw; i+=mh)
        pen.drawLine(i,0,i,lh);
    for(int i = 0; i<lh; i+=nh)
        pen.drawLine(0,i,lw,i);
    pen.setBrush(QBrush(Qt::green));
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=m; j++)
            if(nowplace[i][j] == 1)
                pen.drawRect(QRect((j-1)*mh, (i-1)*nh, mh, nh));
                //pen.drawEllipse(QPoint((i-1)*nh+nh/2, (j-1)*mh+mh/2), nh/2, mh/2);
    pen.end();
    ui->life_place->setPixmap(lplace);
}

void MainWindow::on_start_clicked()
{
    if(start) {
        ui->start->setText("Старт");
        life_timer->stop();
        ui->timertick->setEnabled(true);
    }
    else {
        ui->start->setText("Стоп");
        life_timer->start(ui->timertick->value());
        ui->timertick->setEnabled(false);
    }
    start = !start;
    MainWindow::drawplace(true);
}

void MainWindow::timerTick()
{
    if(place.nextGen() < 0){
        MainWindow::on_start_clicked();
    }
    else {
        MainWindow::drawplace(true);
    }
}

void QLabel::mousePressEvent(QMouseEvent *ev) {

    if(ev->button() == Qt::LeftButton && !life_timer->isActive())
    {
        int n = place.getHeight(), m = place.getWidth(), nh = lh/n, mh = lw/m;
        QVector<QVector<int>> nowplace = place.getPlace();
        QPixmap lplace(QLabel::pixmap());
        QPainter pen;
        pen.begin(&lplace);
        pen.setPen(QPen(Qt::black,1,Qt::SolidLine));
        pen.setBrush(QBrush(Qt::white));
        if(nowplace[ev->y()/nh+1][ev->x()/mh+1] == 1) {
            nowplace[ev->y()/nh+1][ev->x()/mh+1] = 0;
            pen.drawRect(QRect((ev->x()/mh)*mh, (ev->y()/nh)*nh, mh, nh));
        }
        else{
            nowplace[ev->y()/nh+1][ev->x()/mh+1] = 1;
            pen.setBrush(QBrush(Qt::green));
            pen.drawRect(QRect((ev->x()/mh)*mh, (ev->y()/nh)*nh, mh, nh));
        }
        pen.end();
        QLabel::setPixmap(lplace);
        place.setPlace(nowplace);
    }

}

void MainWindow::on_clear_clicked()
{
    place.clear();
    MainWindow::drawplace(false);
}

void MainWindow::on_resize_clicked()
{
    if(!life_timer->isActive()){
        int width = ui->width->displayText().toInt();
        int height = ui->height->displayText().toUInt();
        if(width <= lw/5 && height <= lh/5) {
            place.resize(width, height);
            MainWindow::drawplace(true);
        }
        else {
            QMessageBox::about(this, "Ошибка", "Введите размеры меньше");
        }
    }
}

void MainWindow::on_save_clicked()
{
    saves++;
    QVector<QVector<int>> saveplace = place.getPlace();
    char fpath[55];
    sprintf(fpath,"saves/save_%d.txt",saves);
    ofstream fout(fpath, ios_base::trunc);
    fout<<place.getWidth()<<' '<<place.getHeight()<<endl;
    for(int i = 1; i<=place.getHeight(); i++){
        for(int j = 1; j<=place.getWidth(); j++)
            fout<<saveplace[i][j]<<' ';
        fout<<endl;
    }
    ui->set_save->addItem(QString().number(saves),QVariant(saves));
    QMessageBox::about(this, "Сохранение", "Состояние поля сохранено в папку Saves в файл save_"+ QString::number(saves)+".txt");
    ofstream fsaves("saves.txt", std::fstream::out);
    fsaves<<saves;
    fsaves.close();
}

void MainWindow::on_load_preset_clicked()
{
    if(ui->presets->currentIndex() == 0)
        place.setFromFile("presets/gosper_gun.txt");
    if(ui->presets->currentIndex() == 1)
        place.setFromFile("presets/planer.txt");
    if(ui->presets->currentIndex() == 2)
        place.setFromFile("presets/S_engine.txt");
    MainWindow::drawplace(true);
    ui->width->setText(QString().number(place.getWidth()));
    ui->height->setText(QString().number(place.getHeight()));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QTest::qWait(100);
    lw = ui->centralwidget->width()-ui->start->width();
    lh = ui->centralwidget->height();
    drawplace(true);
    QWidget::resizeEvent(event);
}

void MainWindow::on_pushButton_clicked()
{
    char fpath[55];
    sprintf(fpath,"saves/save_%d.txt",ui->set_save->currentIndex()+1);
    place.setFromFile(fpath);
    drawplace(true);
}
