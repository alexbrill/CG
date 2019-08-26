#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculations.h"

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
    memFree(surface, DESIRED_N, DESIRED_M);
    memFree(surfacePersp, DESIRED_N, DESIRED_M);
    delete ui;
}

void MainWindow::on_addRowBtn_clicked()
{
    ui->table->insertRow(ui->table->rowCount());
}

void MainWindow::on_deleteRowBtn_clicked()
{
    if (ui->table->rowCount() > 3)
        ui->table->removeRow(ui->table->rowCount() - 1);
}

double*** MainWindow::getDataFromTable()
{
    int nCols = ui->table->columnCount();
    int nRows = ui->table->rowCount();

    for (int i = 0, j; i < nRows; ++i)
        for (j = 0; j < nCols; ++j)
            if (ui->table->item(i, j) == nullptr || ui->table->item(i, j)->text().isEmpty())
                return nullptr;

    for (int i = 0, j; i < nRows; ++i)
        for (j = 0; j < nCols; ++j)
        {
            QStringList numbers = ui->table->item(i, j)->text().split(", ");

            if (numbers.size() != 3)
                return nullptr;
        }


    double ***data = new double**[nRows];

    for (int i = 0, j; i < nRows; ++i)
    {
        data[i] = new double*[nCols];

        for (j = 0; j < nCols; ++j)
        {
            data[i][j] = new double[3];
            QStringList numbers = ui->table->item(i, j)->text().split(", ");
            data[i][j][0] = numbers.at(0).toDouble();
            data[i][j][1] = numbers.at(1).toDouble();
            data[i][j][2] = numbers.at(2).toDouble();
        }
    }

    return data;
}

void MainWindow::drawLines(double ***data, int n, int m)
{
    for (int i = 0, j; i < n; ++i)
        for (j = 0; j < m; ++j)
        {
            if (i + 1 < n)
            {
                QLineF line = QLineF(data[i][j][0], data[i][j][1],
                        data[i+1][j][0], data[i+1][j][1]);
                ui->drawArea->scene()->addLine(line);
            }

            if (j + 1 < m)
            {
                QLineF line = QLineF(data[i][j][0], data[i][j][1],
                        data[i][j+1][0], data[i][j+1][1]);
                ui->drawArea->scene()->addLine(line);
            }

        }
}

void MainWindow::drawDots(double ***data, int n, int m)
{
    for (int i = 0, j; i < n; ++i)
        for (j = 0; j < m; ++j)
        {
            QRectF rect = QRectF(data[i][j][0] - 5, data[i][j][1] - 5, 10, 10);
            ui->drawArea->scene()->addEllipse(rect);
        }
}

void MainWindow::on_calcBtn_clicked()
{
    double ***dots = getDataFromTable();

    if (dots)
    {
        const int N = ui->table->rowCount(),
                  M = ui->table->columnCount();

        if (surface) memFree(surface, DESIRED_N, DESIRED_M);
        surface = getSurfaceBezier(dots, N, M, DESIRED_N, DESIRED_M);

        drawAxis();
        drawSurface();

        memFree(dots, N, M);
    }
}

void MainWindow::drawSurface()
{
    const int W = ui->drawArea->viewport()->width(),
              H = ui->drawArea->viewport()->height();

    if (surfacePersp) memFree(surfacePersp, DESIRED_N, DESIRED_M);

    surfacePersp = dataCopy(surface, DESIRED_N, DESIRED_M);
    applyPerspective(surfacePersp, DESIRED_N, DESIRED_M, W/2, H/2, 150);

    drawLines(surfacePersp, DESIRED_N, DESIRED_M);
}

void MainWindow::on_addColBtn_clicked()
{
    ui->table->insertColumn(ui->table->columnCount());
}

void MainWindow::on_deleteColBtn_clicked()
{
    if (ui->table->columnCount() > 3)
        ui->table->removeColumn(ui->table->columnCount() - 1);
}

void MainWindow::on_makeRotationBtn_clicked()
{
    const int W = ui->drawArea->viewport()->width(),
              H = ui->drawArea->viewport()->height();

    if (ui->angle == nullptr || ui->angle->text().isEmpty())
        return;

    double angle = ui->angle->text().toDouble() * 3.1415 * 0.00555556;

    moveM(surface, DESIRED_N, DESIRED_M, -W/2, -H/2, 0);

    if (ui->radioButtonX->isChecked()) rotateX(surface, DESIRED_N, DESIRED_M, angle);
    else if (ui->radioButtonY->isChecked()) rotateY(surface, DESIRED_N, DESIRED_M, angle);

    moveM(surface, DESIRED_N, DESIRED_M, W/2, H/2, 0);

    drawAxis();
    drawSurface();
}

void MainWindow::drawAxis()
{
    ui->drawArea->scene()->clear();
    const int W = ui->drawArea->viewport()->width(),
              H = ui->drawArea->viewport()->height();
    QLineF line = QLineF(W/2, 0, W/2, H);
    QLineF line2 = QLineF(0, H/2, W, H/2);
    ui->drawArea->scene()->addLine(line);
    ui->drawArea->scene()->addLine(line2);
}
