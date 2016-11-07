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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_euclidAlg_clicked();
    void on_modExp_clicked();
    void on_MultInverse_clicked();
    void on_order_clicked();
    void on_dLog_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
