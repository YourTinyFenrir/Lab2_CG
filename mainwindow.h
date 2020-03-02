#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Spline createSpline();

private slots:

    void on_CreateBrokenLine_clicked();

    void on_RotateOX_clicked();

    void on_RotateOY_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
