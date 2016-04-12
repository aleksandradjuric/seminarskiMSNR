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
    std::string tmp;

    if(type.compare("int") == 0)
    {
        std::ifstream f("Tests/int.txt");
        while(f)
        {
            getline(f, tmp);
            int_test.push_back(tmp);
        }
    }
    else if(type.compare("float") == 0)
    {
        std::ifstream f("Tests/float.txt");
        while(f)
        {
            getline(f, tmp);
            float_test.push_back(tmp);
        }
    }
    else if(type.compare("double") == 0)
    {
        std::ifstream f("Tests/double.txt");
        while(f)
        {
            getline(f, tmp);
            double_test.push_back(tmp);
        }
    }
    else if(type.compare("char") == 0)
    {
        std::ifstream f("Tests/char.txt");
        while(f)
        {
            getline(f, tmp);
            char_test.push_back(tmp);
        }
    }
    else if(type.compare("mail") == 0)
    {
        std::ifstream f("Tests/mail.txt");
        while(f)
        {
            getline(f, tmp);
            mail_test.push_back(tmp);
        }
    }
    else if(type.compare("time") == 0)
    {
        std::ifstream f("Tests/time.txt");
        while(f)
        {
            getline(f, tmp);
            time_test.push_back(tmp);
        }
    }
    else if(type.compare("date") == 0)
    {
        std::ifstream f("Tests/date.txt");
        while(f)
        {
            getline(f, tmp);
            date_test.push_back(tmp);
        }
    }
    else if(type.compare("path") == 0)
    {
        std::ifstream f("Tests/path.txt");
        while(f)
        {
            getline(f, tmp);
            path_test.push_back(tmp);
        }
    }
}

void tester::on_btn_start_clicked()
{
    if(ui->sb_num_repeat->value() == 0)
        QMessageBox::warning(this, "Warning", "Check number of repeat");
    else
    {
        QFile file( "temp.txt" );
        file.resize(0);
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
               else if(choosed.compare("float") == 0)
               {
                   if(float_test.empty())
                       fill_vector("float");

                   int rand_int = rand() % float_test.size();
                   temp << QString::fromStdString(float_test.at(rand_int));
                   temp << " ";
               }
               else if(choosed.compare("double") == 0)
               {
                   if(double_test.empty())
                       fill_vector("double");

                   int rand_int = rand() % double_test.size();
                   temp << QString::fromStdString(double_test.at(rand_int));
                   temp << " ";
               }
               else if(choosed.compare("char") == 0)
               {
                   if(char_test.empty())
                       fill_vector("char");

                   int rand_int = rand() % char_test.size();
                   temp << QString::fromStdString(char_test.at(rand_int));
                   temp << " ";
               }
               else if(choosed.compare("mail") == 0)
               {
                   if(mail_test.empty())
                       fill_vector("mail");

                   int rand_int = rand() % mail_test.size();
                   temp << QString::fromStdString(mail_test.at(rand_int));
                   temp << " ";
               }
               else if(choosed.compare("date") == 0)
               {
                   if(date_test.empty())
                       fill_vector("date");

                   int rand_int = rand() % date_test.size();
                   temp << QString::fromStdString(date_test.at(rand_int));
                   temp << " ";
               }
               else if(choosed.compare("time") == 0)
               {
                   if(time_test.empty())
                       fill_vector("time");

                   int rand_int = rand() % time_test.size();
                   temp << QString::fromStdString(time_test.at(rand_int));
                   temp << " ";
               }
               else if(choosed.compare("path") == 0)
               {
                   if(path_test.empty())
                       fill_vector("path");

                   int rand_int = rand() % path_test.size();
                   temp << QString::fromStdString(path_test.at(rand_int));
                   temp << " ";
               }
               else
               {
                   int rand_int;
                   QString tmp = QString::fromStdString(choosed);
                   QStringList array_num = tmp.split(" ");

                   if(array_num.at(1).compare("int") == 0)
                   {
                       if(int_test.empty())
                           fill_vector("int");

                       for(int i = 0; i < array_num.at(2).toInt(); i++)
                       {
                           rand_int = rand() % int_test.size();
                           temp << QString::fromStdString(int_test.at(rand_int));
                           temp << " ";
                       }
                   }
                   else if(array_num.at(1).compare("float") == 0)
                   {
                       if(float_test.empty())
                           fill_vector("float");

                       for(int i = 0; i < array_num.at(2).toInt(); i++)
                       {
                           rand_int = rand() % float_test.size();
                           temp << QString::fromStdString(float_test.at(rand_int));
                           temp << " ";
                       }
                   }
                   else if(array_num.at(1).compare("double") == 0)
                   {
                       if(double_test.empty())
                           fill_vector("double");

                       for(int i = 0; i < array_num.at(2).toInt(); i++)
                       {
                           rand_int = rand() % double_test.size();
                           temp << QString::fromStdString(double_test.at(rand_int));
                           temp << " ";
                       }
                   }
                   else
                   {
                       if(char_test.empty())
                           fill_vector("char");

                       for(int i = 0; i < array_num.at(2).toInt(); i++)
                       {
                           rand_int = rand() % char_test.size();
                           temp << QString::fromStdString(char_test.at(rand_int));
                           temp << " ";
                       }
                   }
               }
           }
           file.close();

        }
        else
            QMessageBox::warning(this, "warning", "File not opened", "try again");
    }
}

