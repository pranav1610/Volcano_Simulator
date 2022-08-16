#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "lavashot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//public slots:
//    void removeItem(int index);

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;

    QTimer *timer;
    QGraphicsScene *scene;

    lavashot* shot;

//signals:
//    //void removeShot();
//    void shotToRemove();


//public slots:
//    void removeItem();

};
#endif // MAINWINDOW_H


//*******


