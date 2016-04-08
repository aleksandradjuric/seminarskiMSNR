#include "viewreport.h"
#include "ui_viewreport.h"
#include "tester.h"
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTextStream>
#include <QFile>

viewReport::viewReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewReport)
{

    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

viewReport::~viewReport()
{
    delete ui;
}

void viewReport::on_btn_viewReport_cancle_clicked()
{
    this->close();
}

void viewReport::printList()
{
    this->show();

    QStandardItemModel *model = new QStandardItemModel();

    QStringList list = tester::example.split("|");

    for(int i = 0; i < list.size(); i++)
    {
        QStandardItem *test = new QStandardItem();
        QStandardItem *valid = new QStandardItem();
        QString pom = list.at(i);
        QStringList sub_list = pom.split("->");

        test->setData(sub_list.at(0), Qt::DisplayRole );
        valid->setData(sub_list.at(1), Qt::DisplayRole );

        model->setItem(i, 0, test);
        model->setItem(i, 1, valid);
    }
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 379);
    ui->tableView->setColumnWidth(1, 379);
}

void viewReport::on_btn_viewReport_save_clicked()
{
    QString testReport = QFileDialog::getSaveFileName(this, "Save test report", "C://", "Text file (*txt)");

    QFile f(testReport);
    f.open( QIODevice::WriteOnly );
    if(!f.isOpen())
        QMessageBox::information(this, "Warning", "File is not saved, try again");
    else
    {
        QString out = "";
        QStringList list = tester::example.split("|");

        for(int i = 0; i < list.size(); i++)
        {
            QString pom = list.at(i);
            QStringList sub_list = pom.split("->");
            out.append(sub_list.at(0));
            out.append(": ");
            out.append(sub_list.at(1));
            out.append("\n");
        }

        QTextStream outStream(&f);
        outStream << out;
        f.close();
    }

}
