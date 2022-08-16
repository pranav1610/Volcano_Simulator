#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>
#include <QtWidgets>
#include "lavashot.h"
#include <math.h>
#include <cmath>
#include <QObject>

//GLOBAL CONSTANT - number of lava shots
static const int shotCount = 7;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    //setRenderHint - what type of rendering implement on the graphics presented
    //Antialiasing - smooth graphics set-up
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //Defines the boundaries of movement on the graphic scene
    //QGraphicsScene scene;

    //boudaries of the scene set to a rectangle 300x600
    scene->setSceneRect(-300, -300, 600, 600);
//! [1] //! [2]

    //The item index function is used to speed up item discovery.
    //NoIndex implies that item location is of linear complexity,as all items on
    //the scene are searched.
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//! [2]

//! [3]
    //when angle of sin() is > 0, (0<x<Pi), the shots are closer to the right side of the scene
    //when angle of sin < 0, the shots are spread out

    //PROCESS - lava shots added at a time to the scene
    for(int i=0;i<shotCount;i++)
    {
        lavashot *shot = new lavashot;
        shot->setPos(-10, 180);

        scene->addItem(shot);
    }

    //QObject::connect(&mouse1, SIGNAL(removeShot(mouse1)), &mouse2, SLOT(addShot(mouse2)));

//! [3]

//! [4]
    //To be able to view the scene, we must also create a QGraphicsView widget.
    //The QGraphicsView class visualizes the contents of a scene in a
    //scrollable viewport.
    //QGraphicsView view(&scene);

    //Indicates that the engine should antialias edges of primitives if possible
    //view.setRenderHint(QPainter::Antialiasing);

    //PROCESS + OUTPUT - background set to volcano.jpg
    ui->graphicsView->setBackgroundBrush(QPixmap(":/images/volcano.jpg"));

//! [4] //! [5]
    //The CacheMode property holds which parts of the view are cached, and the
    //CacheBackground flag enables caching of the view's background.
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    //QGraphicsView caches pre-rendered content in a pixmap, which is then
    //drawn onto the viewport.
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //By setting the dragMode property, we define what should happen when the
    //user clicks on the scene background and drags the mouse.The ScrollHandDrag
    //flag makes the cursor change into a pointing hand, and dragging the mouse
    //around will scroll the scrollbars.
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
//! [5] //! [6]

    //PROCESS - Set the application window's title
    ui->graphicsView->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Volcano"));

    //PROCESS - Set the application window's size
    ui->graphicsView->resize(1400, 900);

    //OUTPUT - display the application window
    ui->graphicsView->show();


    //PROCESS - connects QTimer's timeout() signal to the advance() slot of the
    //scene. Every time the timer fires, the scene will advance one frame
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene,SLOT(advance()));
    timer->start(1000 / 33);

    //adds volcano to scene
    QPolygonF poly;
    //poly << QPointF(-100, 50) << QPointF(0, 50) << QPointF(-50, -40 );
    poly << QPointF(-140, 290) << QPointF(120, 290) << QPointF(-10, 80 );

    //Brush color set to black
    QBrush brush(Qt::black);

    //Pen to draw polygon on scene
    QPen pen(Qt::black);

    //'pen[s]' polygon to scene with color black set by brush
    scene->addPolygon(poly, pen, brush);

}


//void MainWindow::removeItem(int index)
//void MainWindow::removeItem()
//{
//   scene->removeItem(shot);
//}

MainWindow::~MainWindow()
{
    delete ui;
}

