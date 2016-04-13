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

    list = tester::example.split(";");

    for(int i = 0; i < list.size() - 1; i++)
    {

        QStandardItem *input = new QStandardItem();
        QStandardItem *output = new QStandardItem();
        QStandardItem *status = new QStandardItem();

        QString pom = list.at(i);
        QStringList sub_list = pom.split("|");

        input->setData(sub_list.at(0), Qt::DisplayRole );
        output->setData(sub_list.at(1), Qt::DisplayRole );
        status->setData(sub_list.at(2), Qt::DisplayRole );

        model->setItem(i, 0, input);
        model->setItem(i, 1, output);
        model->setItem(i, 2, status);
    }
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 252);
    ui->tableView->setColumnWidth(1, 252);
    ui->tableView->setColumnWidth(2, 252);
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

        for(int i = 0; i < list.size() - 1; i++)
        {
            QString pom = list.at(i);
            QStringList sub_list = pom.split("|");
            out.append("Input: ").append(sub_list.at(0)).append("\n");
            out.append("Output: ").append(sub_list.at(1)).append("\n");
            out.append("Exit status: ").append(sub_list.at(2)).append("\n\n");
        }

        QTextStream outStream(&f);
        outStream << out;
        f.close();
    }

}
