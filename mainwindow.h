#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <qmath.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void readTableForm();
    void MiniMax();
    void proizved();
    QVector<qreal> x,y;
    int row;
};

#endif // MAINWINDOW_H
