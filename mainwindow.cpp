#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NumTheoryFormulas.h"
#include <string.h>
#include <QString>

NumTheoryFormulas solver = NumTheoryFormulas();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_euclidAlg_clicked()
{
   std::string a = (ui->euclidAlgLeft->text()).toStdString();
   std::string b = (ui->euclidAlgRight->text()).toStdString();

  std::string out("A   Q   B   R   GCD\n");


  std::vector<std::vector<NumTheoryFormulas::SUPERLONG>> t = solver.EuclideanAlgorithm(a,b);

  for (auto i = t.begin(); i !=t.end(); i++)
  {
      if (i != t.end() - 2)
      {
          for (int j = 0; j < 5; j++)
          {
              //printf("%li", (*i).at(j));
              //printf("%s", "   ");

              out += ((*i).at(j)).toString();
              out+="     ";
          }

          out += "     \n";

        //  printf("\n");
      }
  }


  ui->euclidAlgOutput->setText(QString::fromStdString(out));

}

void MainWindow::on_modExp_clicked()
{
    std::string b =(ui->mExpBase->text()).toStdString();
    std::string e =(ui->mExpExp->text()).toStdString();
    std::string m =(ui->mExpMod->text()).toStdString();

    ui->mExpOutput->setText(QString::fromStdString((solver.ModExponent(b,e,m)).toString()));
}

void MainWindow::on_MultInverse_clicked()
{
    std::string val = (ui->mInvBase->text()).toStdString();
    std::string mod = (ui->mInvMod->text()).toStdString();

    ui->mInvOut->setText(QString::fromStdString((solver.MultInverse(val,mod)).toString()));

}

void MainWindow::on_order_clicked()
{
    std::string val = (ui->orderBase->text()).toStdString();
    std::string mod = (ui->orderMod->text()).toStdString();

    ui->orderOut->setText(QString::fromStdString((solver.order(val,mod)).toString()));
}

void MainWindow::on_dLog_clicked()
{
    std::string pRoot = (ui->discreteLogPRoot->text()).toStdString();
    std::string val = (ui->discreteLogValue->text()).toStdString();
    std::string mod = (ui->discreteLogMod->text()).toStdString();

    ui->discreteLogOut->setText(QString::fromStdString((solver.discreteLogBruteForce(pRoot,val,mod)).toString()));
}
