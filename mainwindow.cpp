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

void MainWindow::on_crt_clicked()
{
    NumTheoryFormulas::SUPERLONG numEqns = (ui->crtNumEqns->text()).toStdString();

    NumTheoryFormulas::SUPERLONG equations[][2];
    NumTheoryFormulas::SUPERLONG bigM = 1;
    NumTheoryFormulas::SUPERLONG num, mod;

    std::string s = (ui->crtEqns->text()).toStdString();
    std::string n,m;

    for(int i=0;i<numEqns.toUnsignedLongLong();i++)
    {
        sscanf_s(s,"%s %s",&n, &m);
        num=n;
        mod=m;
        equations[i][0] = num;
        equations[i][1] = mod;
        bigM *=mod;

    }

    std::string out = solver.CRT(numEqns.toInt(),equations).toString() + " mod " + bigM.toString();

    ui->crtOut->setText(QString::fromStdString(out));


}

void MainWindow::on_strongFermatTest_clicked()
{
    std::string number = (ui->strongFermatTestNum->text()).toStdString();
    std::string mod = (ui->strongFermatTestMod->text()).toStdString();

    std::string out;
    if(1==solver.strongFermatTest(number,mod))
    {
        string = "Probable prime.\n";
    }

    else
    {
        "Composite.\n";
    }

    ui->crtOut->setText(QString::fromStdString(out));
}

void MainWindow::on_rabinMillerTest_clicked()
{

    std::string mod = (ui->rabinMillerTestMod->text()).toStdString();
      NumTheoryFormulas::SUPERLONG rounds = (ui->rabinMillerTestRounds->text()).toStdString();
    std::string out;
    if(1==solver.millerRabinTest(rounds,mod))
    {
        out = "Probable prime after " + rounds.toUnsignedLongLong() + " rounds.\n";
    }
    else
    {
        out = "Composite.\n";
    }

    ui->rabinMillerTestOut->setText(QString::fromStdString(out));
}
