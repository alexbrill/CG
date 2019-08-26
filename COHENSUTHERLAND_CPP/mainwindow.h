#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <calculations.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawRect(double, double, double, double);
    void drawLines(Lines, bool);

private slots:
    void on_generatebtn_clicked();

    void on_makeRectBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
