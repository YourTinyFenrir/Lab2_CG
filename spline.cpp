#include "spline.h"
#include "QVector4D"
#include "QtMath"

Spline::Spline(int size) {

    QVector4D temp(0 ,0, 0, 0);

    for (int i = 0; i < size; ++i) {
        nodes.push_back(temp);
    }

}

Spline::Spline(QVector<QVector4D> pts) {

    nodes = pts;

}

void Spline::drawBrokenLine(QGraphicsScene* scene) {

    // 5 цветов, возможна ошибка при увеличении числа точек
    QVector<QPen> pens;
    QPen temp(Qt::red);
    pens.push_back(temp);
    temp.setColor(Qt::yellow);
    pens.push_back(temp);
    temp.setColor(Qt::green);
    pens.push_back(temp);
    temp.setColor(Qt::blue);
    pens.push_back(temp);
    temp.setColor(Qt::black);
    pens.push_back(temp);

    for (int i = 0; i < nodes.size() - 1; ++i)
        scene->addLine(nodes[i].x(), nodes[i].y(), nodes[i+1].x(), nodes[i+1].y(), pens[i]);

}

QVector<QVector4D> createSpline(QVector<QVector4D> tempPts, float t) {

    QVector<QVector4D> newTempPts;
    QVector<QVector4D> finalRes;

    for (int i = 0; i < tempPts.size() - 1; ++i) {

        float newX = t * (tempPts[i+1].x() - tempPts[i].x()) + tempPts[i].x();
        float newY = t * (tempPts[i+1].y() - tempPts[i].y()) + tempPts[i].y();
        float newZ = t * (tempPts[i+1].z() - tempPts[i].z()) + tempPts[i].z();

        newTempPts.push_back(QVector4D(newX, newY, newZ, 1));

    }

    if (tempPts.size() > 3)

        finalRes = createSpline(newTempPts, t);

    else {

       float X = t * (newTempPts[1].x() - newTempPts[0].x()) + newTempPts[0].x();
       float Y = t * (newTempPts[1].y() - newTempPts[0].y()) + newTempPts[0].y();
       float Z = t * (newTempPts[1].z() - newTempPts[0].z()) + newTempPts[0].z();

       QVector4D finalPoint(X, Y, Z, 1);

       finalRes.push_back(finalPoint);

       return finalRes;

    }

}

void Spline::drawSpline(QGraphicsScene* scene, float step) {

    QVector<QVector4D> extraPts;

    for (float t = 0; t <= 1; t += step) {

            /*float newX1 = t * (nodes[i].x() - nodes[i-1].x()) + nodes[i-1].x();
            float newY1 = t * (nodes[i].y() - nodes[i-1].y()) + nodes[i-1].y();
            float newZ1 = t * (nodes[i].z() - nodes[i-1].z()) + nodes[i-1].z();

            float newX2 = t * (nodes[i+1].x() - nodes[i].x()) + nodes[i].x();
            float newY2 = t * (nodes[i+1].y() - nodes[i].y()) + nodes[i].y();
            float newZ2 = t * (nodes[i+1].z() - nodes[i].z()) + nodes[i].z();

            float newX = t * (newX2 - newX1) + newX1;
            float newY = t * (newY2 - newY1) + newY1;
            float newZ = t * (newZ2 - newY1) + newZ1;

            extraPts.push_back(QVector4D(newX, newY, newZ, 1));*/

        QVector<QVector4D> newPoint = createSpline(nodes, t);

        extraPts.push_back(newPoint.first());

    }

    for (int i = 0; i < extraPts.size() - 1; ++i)
        scene->addLine(extraPts[i].x(), extraPts[i].y(), extraPts[i+1].x(), extraPts[i+1].y());

}

QVector<QVector4D> Spline::multiplyMatrix(QVector<QVector4D> mR) {

    QVector<QVector4D> res;

    QVector4D temp(0, 0, 0, 0);

    for(int i = 0; i < nodes.size(); ++i)
        res.push_back(temp);

    for(int i = 0; i < nodes.size(); ++i) {

        res[i].setX(nodes[i].x() * mR[0].x() + nodes[i].y() * mR[1].x() + nodes[i].z() * mR[2].x() + nodes[i].w() * mR[3].x());
        res[i].setY(nodes[i].x() * mR[0].y() + nodes[i].y() * mR[1].y() + nodes[i].z() * mR[2].y() + nodes[i].w() * mR[3].y());
        res[i].setZ(nodes[i].x() * mR[0].z() + nodes[i].y() * mR[1].z() + nodes[i].z() * mR[2].z() + nodes[i].w() * mR[3].z());
        res[i].setW(nodes[i].x() * mR[0].w() + nodes[i].y() * mR[1].w() + nodes[i].z() * mR[2].w() + nodes[i].w() * mR[3].w());

    }

    return res;

}

Spline Spline::rotateOX(float angle) {

    QVector<QVector4D> tempMatrix;
    QVector<QVector4D> matrixRotation;

    float radAngle = qDegreesToRadians(angle);

    matrixRotation.push_back(QVector4D(1, 0, 0, 0));
    matrixRotation.push_back(QVector4D(0, cos(radAngle), sin(radAngle), 0));
    matrixRotation.push_back(QVector4D(0, -sin(radAngle), cos(radAngle), 0));
    matrixRotation.push_back(QVector4D(0, 0, 0, 1));

    tempMatrix = multiplyMatrix(matrixRotation);
    Spline res(tempMatrix);

    return res;

}

Spline Spline::rotateOY(float angle) {

    QVector<QVector4D> tempMatrix;
    QVector<QVector4D> matrixRotation;

    float radAngle = qDegreesToRadians(angle);

    matrixRotation.push_back(QVector4D(cos(radAngle), 0, -sin(radAngle), 0));
    matrixRotation.push_back(QVector4D(0, 1, 0, 0));
    matrixRotation.push_back(QVector4D(sin(radAngle), 0, cos(radAngle), 0));
    matrixRotation.push_back(QVector4D(0, 0, 0, 1));

    tempMatrix = multiplyMatrix(matrixRotation);
    Spline res(tempMatrix);

    return res;

}
