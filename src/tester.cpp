#include "tester.h"
#include "ui_tester.h"
#include "viewreport.h"
#include <QDebug>

QString tester::example;

tester::tester(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tester)
{
    model = new QStandardItemModel();
    ui->setupUi(this);

    v = new viewReport();
    connect(ui->btn_view_report, SIGNAL(clicked()), v, SLOT(printList()));
}

tester::~tester()
{
    delete ui;
}

void tester::dodaj_u_listu(std::string type)
{
    QStandardItem *item = new QStandardItem();
    item->setData(QString::fromStdString(type), Qt::DisplayRole );
    ui->list_selected->setModel(model);
    model->appendRow( item );
}

void tester::on_btn_int_clicked()
{
    testType.push_back("int");
    dodaj_u_listu("Int");
}

void tester::on_btn_float_clicked()
{
    testType.push_back("float");
    dodaj_u_listu("Float");
}

void tester::on_btn_double_clicked()
{
    testType.push_back("double");
    dodaj_u_listu("Double");
}

void tester::on_btn_char_clicked()
{
    testType.push_back("char");
    dodaj_u_listu("Char");
}

void tester::on_btn_mail_clicked()
{
    testType.push_back("mail");
    dodaj_u_listu("Mail");
}

void tester::on_btn_test_file_clicked()
{
    QString testFile = QFileDialog::getOpenFileName(this, "Open test file", "C://");
    if(testFile.isEmpty())
        QMessageBox::information(this, "Warning", "File is not loaded, try again");

    //TODO da li je izabran makefile
}

void tester::on_btn_view_report_clicked()
{
    example = "example1->valid|example2->invalid|example3->valid";
}

void tester::on_btn_clear_list_clicked()
{
    testType.clear();
    model->clear();
    ui->list_selected->setModel(model);
}
