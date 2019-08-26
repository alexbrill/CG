#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->drawArea->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QGraphicsScene *scene = new QGraphicsScene();
    ui->drawArea->setScene(scene);
    ui->drawArea->setSceneRect(0, 0, ui->drawArea->viewport()->width(),
                               ui->drawArea->viewport()->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawRect(double x, double y, double w, double h)
{
    ui->drawArea->scene()->clear();
    ui->drawArea->scene()->addRect(QRect(x, y, w, h));
}

void MainWindow::drawLines(Lines lines, bool isIn)
{
    for (Line line : lines)
        ui->drawArea->scene()->addLine(QLineF(line.first.first,
                                              line.first. second,
                                              line.second.first,
                                              line.second.second),
                                       QPen(isIn?Qt::green:Qt::black));
}

void MainWindow::on_generatebtn_clicked()
{
    LINES.clear();
    LINES = getRandomLines(N,
                           ui->drawArea->viewport()->width(),
                           ui->drawArea->viewport()->height());

    drawRect(X, Y, W, H);

    drawLines(LINES, false);

    LINES_CLIPPED.clear();
    LINES_CLIPPED = getClippedLines(LINES);

    drawLines(LINES_CLIPPED, true);
}

void MainWindow::on_makeRectBtn_clicked()
{
    if (ui->x->text().isEmpty() || ui->y->text().isEmpty()
            || ui->w->text().isEmpty() || ui->h->text().isEmpty())
        return;

    X = ui->x->text().toDouble();
    Y = ui->y->text().toDouble();
    W = ui->w->text().toDouble();
    H = ui->h->text().toDouble();

    drawRect(X, Y, W, H);

    drawLines(LINES, false);

    LINES_CLIPPED.clear();
    LINES_CLIPPED = getClippedLines(LINES);

    drawLines(LINES_CLIPPED, true);
}
