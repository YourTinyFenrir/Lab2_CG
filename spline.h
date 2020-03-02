#ifndef SPLINE_H
#define SPLINE_H

#include "QGraphicsScene"

class Spline {
private:
    QVector<QVector4D> nodes;
public:
    Spline(int);
    Spline(QVector<QVector4D>);
    void drawBrokenLine(QGraphicsScene*);
    void drawSpline(QGraphicsScene*, float);
    QVector<QVector4D> multiplyMatrix(QVector<QVector4D>);
    Spline rotateOX(float);
    Spline rotateOY(float);
};

#endif // SPLINE_H
