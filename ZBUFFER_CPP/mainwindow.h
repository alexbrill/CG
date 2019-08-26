#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

typedef std::vector<int> vect;
typedef std::vector<vect> vectArray;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    vectArray getCoordinates();
    void drawTriangle(vect, vect, vect, vect&, vect);


private slots:
    void on_draw_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
