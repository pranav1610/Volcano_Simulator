#ifndef LAVASHOT_H
#define LAVASHOT_H

#include <QGraphicsItem>
#include <QtMath>
#include <iostream>
#include <QObject>

//PROCESS - gravity defined
const qreal g = -9.8;


class lavashot : public QGraphicsItem
{
    //Q_OBJECT
public:
    lavashot();

    /***************************************************************************
     * FUNCTION : boundingRect (const)
     *
     *      This function sets bounds for the lavashot to allow the timer to
     *      connect with the object on the scene. We override this function
     *      to update its behavior with respect to the boundingRect() within the
     *      Qt Class.
     *
     *      returns --> bounds for an object in animation
     ***************************************************************************
     */
    QRectF boundingRect() const override;

    //QPainterPath shape() const override;

    /***************************************************************************
     * FUNCTION : paint()
     *
     *      This function displays the lavashots within the 'bounds' defined
     *      above. We override this function to update its behavior with respect
     *      to the boundingRect() within the Qt Class.
     *
     *      returns --> nothing
     ***************************************************************************
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


protected:

    /***************************************************************************
     * FUNCTION : advance
     *
     *      This function connects the graphic to the timer, allowing desired
     *      animation along a trajectory
     *
     *      returns --> nothing
     ***************************************************************************
     */
    void advance(int step) override;

private:

    qreal alpha;        //PROCESS - angle of trajectory
    qreal v_0;          //PROCESS - initial velocity of the
                        //          object following trajectory

    qreal dx;           //PROCESS - change in x-position over time
    QColor color;       //PROCESS + OUTPUT - color of object

    qreal newX;         //PROCESS - newX position along the trajectory
    qreal newY;         //PROCESS - newY position along the trajectory


};

#endif // LAVASHOT_H


//Must emit signal from lavashot.cpp as it stores the item location.
//Thus the signal and slot must also be defined in lavashot.h / lavashot.cpp
//However,  the slot serves to removeItem which is only possible after an
//instance of the shot is made in mainwindow.cpp. Thus slot should exist in
//mainwindow.cpp

//******************************************************************************

