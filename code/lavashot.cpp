#include "lavashot.h"
#include "mainwindow.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <QtMath>
#include <cmath>
#include <ctime>
#include <cstdlib>

lavashot::lavashot()

    //Process variables

    //alpha-provides a random, more 'natural' look to our trajectory animation
   : alpha(QRandomGenerator::global()->generateDouble()*M_PI / 2 - M_PI / 4),
    //v_0 - defines the speed of the trajectory
    v_0(35),

    //dx - change in x that affect the change in motion
    //if dx is positive, trajectory towards right
    //if dx is negative, trajectory towards left
    dx(QRandomGenerator::global()->generateDouble()*3*pow(-1,rand()%2)),

    //newX - new 'x' co-ordinate
    newX(0),
    //newY - new 'y' co-ordinate
    newY(0),

    //color - sets the color of the lava shots
    color(Qt::red)
{
  //PROCESS - makes sures that the change in x or 'dx' doesn't define our
  //          trajectory. It should be defined by our trajectory equation
  if(abs(dx)<0.5)
  {
      if(dx>0)
          dx+=1;
      else
          dx-=1;
  }

  //PROCESS - We make sure tan(alpha) isn't too small to affect the trajectory
  if(abs(alpha) <= M_PI/9)
  {
      if(alpha > 0)
          alpha += M_PI/5;
      else
          alpha -= M_PI/5;
  }

  //PROCESS - To make sure tan(alpha) is not undefined. That would lead to
  //          undesired behaviour in the aniamtion
  if(abs(alpha) == M_PI/2)
  {
      if(alpha > 0)
          alpha -= M_PI/9;
      else
          alpha += M_PI/9;
  }

  //OUTPUT
  std::cout << "alpha: " << alpha*180/M_PI << "\tv_0: " << v_0
            <<"\tdx: " << dx << std::endl;

}
//******************
//OLD
/********************************
Mouse::Mouse() : color(QRandomGenerator::global()->bounded(256),
                     QRandomGenerator::global()->bounded(256),
                     QRandomGenerator::global()->bounded(256))
{
  setRotation(QRandomGenerator::global()->bounded(360 * 16));
}
********************************/
//! [0]

//! [1]

/*******************************************************************************
* FUNCTION : boundingRect (const)
*
*      This function sets bounds for the lavashot to allow the timer to connect
*      with the object on the scene
*
*      returns --> bounds for an object in animation
******************************************************************************
*/
QRectF lavashot::boundingRect() const
{
  return QRectF(-18, -22,
                36, 60);
}
//! [1]

//! [2]

//defines the shape of the lavashot
//QPainterPath Mouse::shape() const
//{
//    QPainterPath path;
//    path.addRect(-10, -20, 20, 40);
//    return path;
//}
//! [2]

//! [3]

/*******************************************************************************
* FUNCTION : paint()
*
*      This function displays the lavashots within the 'bounds' defined above
*
*      returns --> nothing
******************************************************************************
*/
void lavashot::paint(QPainter *painter,                //painter - QPainter object
                                                  //that allows graphics to be
                                                  //displayed
                const QStyleOptionGraphicsItem *, //QStyleOptionGraphicsItem-
                                                  //allows different styles
                                                  //(shape,color,design) on
                                                  //the 'painter'
                QWidget *)                        //widget - allows us to use
                                                  //QWidgets
{
  // Body
  painter->setBrush(color);
  painter->drawEllipse(-10, -20, 20, 20);
}

//! [3]

//! [4]

/*******************************************************************************
* FUNCTION : advance
*
*      This function connects the graphic to the timer, allowing desired
*      animation along a trajectory
*
*      returns --> nothing
******************************************************************************
*/
void lavashot::advance(int step)
{
  if (!step)
      return;
//! [4]
//    // Don't move too far away
//! [5]
  QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));

////! [5] //! [6]
//! [6]

//! [7]

  //PROCESS - duplicate lavashot made to check for collisions
  QList <QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                         << mapToScene(0, 0)
                         << mapToScene(-30, -50)
                         << mapToScene(30, -50));

  //PROCESS - make sure the animation continues despite collisions
  foreach (QGraphicsItem *item, dangerMice)
  {
      if (item == this)
          continue;

      QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
  }
//! [7] //! [8]
////! [8] //! [9]

//! [9]
//! [10]

//! [10]

//! [11]


  //PROCESS - position - of the lavashot object is tracked to update using a
  //          trajectory path
  QPointF position = pos();

  //more positive the 'h', lower the shot angle of the trajectory
  double h = 50;

  //PROCESS - position of the lavashot follows a trajectory path by a change
  //          in x - 'dx'

  //newX - position changes by 'dx'
  newX = position.rx() + dx;


  //Variables of the following equation described:
  //1. h - height - how far from the initial position(starting point)
  //2. alpha - angle - capable of increasing the speed of the trajectory
  //                   when value of tan(alpha) > cos(alpha)-should be closeer
  //                   to 0
  //3. v_0 - initial velocity - capable of controlling the range of the
  //         trajectory, not really the speed
  //
  //(80 helps provide a natural look to the trajectory as parabolic distance
  // from volcano mountain increases)

  //PROCESS - if change in x is counter-clockwise, change in y should also be
  //          counter-clockwise
  if(dx<0)
  {
      newY = h + -1*newX*qTan(alpha) - g*qPow(-1*newX-80,2)/((2*qPow(v_0, 2)
                                                     *qPow(qCos(alpha),2)));
  }

  //PROCESS - if change in x is clockwise, change in y should also be
  //          clockwise
  else
  {
      newY = h + newX*qTan(alpha) - g*qPow(newX-80,2)/((2*qPow(v_0, 2)
                                               *qPow(qCos(alpha),2)));
  }

  std::cout << "\nnewX: " << newX << "\t newY: " << newY;
  //PROCESS - new position of lavashot(based on 'newX' & 'newY') set using
  //setPos() function.
  setPos(newX, newY);

//    if (position.ry() > 400)
//    {
//          //emit removeShot();
//        emit shotToRemove();
//        //QObject::connect(sender, SIGNAL(shotToRemove())), receiver, SLOT(removethis));
//        //QObject::connect(&scene, SIGNAL(), &scene, &QGraphicsScene::advance);
//    }
}


//! [11]
