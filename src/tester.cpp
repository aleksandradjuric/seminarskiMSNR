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

void tester::on_btn_date_clicked()
{
    testType.push_back("date");
    dodaj_u_listu("Date");
}

void tester::on_btn_time_clicked()
{
    testType.push_back("time");
    dodaj_u_listu("Time");
}

void tester::on_btn_path_clicked()
{
    testType.push_back("path");
    dodaj_u_listu("Path");
}


void tester::on_btn_apply_num_element_clicked()
{
    if(ui->sp_num_element->value() == 0 && ui->cb_infinity->checkState() == false)
        QMessageBox::warning(this, "Warning", "Wrong number of elements, try again");
    else
    {
        QString array = "Array ";
        array.append(ui->cb_type_array->currentText()).append(" ");

        if(ui->cb_infinity->checkState() == true)
        {
            int num = rand() % 200;
            array.append(num);
        }
        else
            array.append(QString::number(ui->sp_num_element->value()));

        dodaj_u_listu(array.toStdString());
        std::string temp = array.toStdString();
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        testType.push_back(temp);
    }
}


void tester::on_btn_test_file_clicked()
{
    QString testFile = QFileDialog::getOpenFileName(this, "Open test file", "C://");
    if(testFile.isEmpty())
        QMessageBox::information(this, "Warning", "File is not loaded, try again");

    path_of_file = testFile.toStdString();
    if(path_of_file.substr(path_of_file.length()-8).compare("Makefile") != 0)
    {
        QMessageBox::warning(this, "Error", "Loaded file is not makefile, try again");
        ui->btn_start->setDisabled(true);
    }
    else
        ui->btn_start->setDisabled(false);
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

void tester::fill_vector(std::string type)
{
    // TODO: make switch for all types
    // location of file int.txt is folder build-msnr.....
    std::ifstream f("int.txt");
    std::string tmp;

    while(f)
    {
        getline(f,tmp);
        int_test.push_back(tmp);
    }
}

void tester::on_btn_start_clicked()
{
    if(ui->sb_num_repeat->value() == 0)
        QMessageBox::warning(this, "Warning", "Check number of repeat");
    else
    {
        QFile file( "temp.txt" );
        if ( file.open(QIODevice::ReadWrite) )
        {
           QTextStream temp( &file );

           for(unsigned i = 0; i < testType.size(); i++)
           {
               std::string choosed = testType.at(i);
               if(choosed.compare("int") == 0)
               {
                   if(int_test.empty())
                       fill_vector("int");

                   int rand_int = rand() % int_test.size();
                   temp << QString::fromStdString(int_test.at(rand_int));
                   temp << " ";
               }
               // TODO: cover all types
           }
        }
        else
            QMessageBox::warning(this, "warning", "File not opened", "try again");
    }
}
