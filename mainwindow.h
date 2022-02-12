#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();

    void on_clear_clicked();

    void drawplace(bool first);

    void on_resize_clicked();

    void on_save_clicked();

    void on_load_preset_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void resizeEvent(QResizeEvent *event);

public slots:
    void timerTick();
};
#endif // MAINWINDOW_H
