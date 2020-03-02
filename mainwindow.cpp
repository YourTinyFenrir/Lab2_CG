#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsLineItem"

#include "QVector4D"
#include "spline.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Spline MainWindow::createSpline() {

    QVector<QVector4D> pts;

    ui->graphicsView->items().clear();
    ui->graphicsView->scene()->clear();

    QVector4D temp1(ui->SB1->value(), -ui->SB2->value(), ui->SB3->value(), 1);
    QVector4D temp2(ui->SB4->value(), -ui->SB5->value(), ui->SB6->value(), 1);
    QVector4D temp3(ui->SB7->value(), -ui->SB8->value(), ui->SB9->value(), 1);
    QVector4D temp4(ui->SB10->value(), -ui->SB11->value(), ui->SB12->value(), 1);
    QVector4D temp5(ui->SB13->value(), -ui->SB14->value(), ui->SB15->value(), 1);

    pts.push_back(temp1);
    pts.push_back(temp2);
    pts.push_back(temp3);
    pts.push_back(temp4);
    pts.push_back(temp5);

    Spline spl(pts);

    // Нанесение осей координат
    ui->graphicsView->scene()->addLine(-300, 0, 300, 0, QPen(Qt::red));
    ui->graphicsView->scene()->addLine(0, -300, 0, 300, QPen(Qt::red));

    return spl;

}

void MainWindow::on_CreateBrokenLine_clicked() {

    Spline spl = createSpline();

    spl.drawBrokenLine(ui->graphicsView->scene());
    spl.drawSpline(ui->graphicsView->scene(), ui->SB16->value());

}

void MainWindow::on_RotateOX_clicked() {

    Spline spl = createSpline();

    Spline rotateSpl = spl.rotateOX(ui->SB17->value());

    rotateSpl.drawBrokenLine(ui->graphicsView->scene());
    rotateSpl.drawSpline(ui->graphicsView->scene(), ui->SB16->value());

}

void MainWindow::on_RotateOY_clicked() {

    Spline spl = createSpline();

    Spline rotateSpl = spl.rotateOY(ui->SB17->value());

    rotateSpl.drawBrokenLine(ui->graphicsView->scene());
    rotateSpl.drawSpline(ui->graphicsView->scene(), ui->SB16->value());

}
