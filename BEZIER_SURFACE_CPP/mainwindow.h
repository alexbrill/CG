#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double*** getDataFromTable();
    void drawLines(double***, int, int);
    void drawDots(double***, int, int);
    void drawSurface();
    void drawAxis();

private slots:
    void on_addRowBtn_clicked();

    void on_deleteRowBtn_clicked();

    void on_calcBtn_clicked();

    void on_addColBtn_clicked();

    void on_deleteColBtn_clicked();

    void on_makeRotationBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
