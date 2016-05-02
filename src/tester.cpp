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
    connect(ui->btn_start, SIGNAL(clicked()), v, SLOT(printList()));
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
    {
        ui->btn_start->setDisabled(false);
        dir_of_file = strdup(path_of_file.substr(0,path_of_file.length()-9).c_str());
    }

}

void tester::on_btn_clear_list_clicked()
{
    testType.clear();
    model->clear();
    ui->list_selected->setModel(model);
}

void tester::fill_vector(std::string type)
{

    if(chdir(start_dir)<0)
        QMessageBox::warning(this, "Warning", "problem with chdir");

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

    if(chdir(dir_of_file)<0)
        QMessageBox::warning(this, "Warning", "problem with chdir");
}

std::string tester::getStatus(int status)
{
    if(WIFEXITED(status))
      return "exited normally";
    if(WIFSIGNALED(status))
      return "exited with signal";
    if(WIFSTOPPED(status))
      return "stopped";
    else
        return "unknown status";
}

void tester::on_btn_start_clicked()
{
    char buffer[PATH_MAX];

    /* get initial path */
    if((start_dir= getcwd(buffer,PATH_MAX+1))==NULL)
        QMessageBox::warning(this, "Warning", "problem with getcwd");

    /* check number of repeat */
    if(ui->sb_num_repeat->value() == 0)
        QMessageBox::warning(this, "Warning", "Check number of repeat");
    /* check name of final executable file */
    else if(ui->le_prg_name->text() == "")
        QMessageBox::warning(this, "Warning", "Check final name of program");
    else
    {
        if(chdir(dir_of_file)<0)
            QMessageBox::warning(this, "Warning", "problem with chdir");
        else
        {
            pid_t pid;
            int status;

            /* make executable file */
            if((pid=fork())<0)
              QMessageBox::warning(this, "Warning", "problem with fork");
            else if((pid == 0))
            {
              if(execlp("/bin/sh", "bash", "-c", "make", (char*)0)<0)

                  QMessageBox::warning(this, "Warning", "problem with fork");
            }
            else
              if(waitpid(pid, &status, 0)<0)
                  QMessageBox::warning(this, "Warning", "problem with fork");

            std::string command = "";
            command += "./";
            command += ui->le_prg_name->text().toStdString();
            command += "<ulaz.txt >izlaz.txt";

            /* make log file for all input output and exit status */
            QFile log("log.txt");
            if ( log.open(QIODevice::WriteOnly) )
            {
                QTextStream log_stream(&log);
                log.resize(0);


                srand(time(NULL));
                example.clear();
                unsigned repeat_num = ui->sb_num_repeat->value();
                for(unsigned counter = 0; counter < repeat_num; counter++)
                {
                    QFile file( "ulaz.txt" );
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
                               else
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

                           }
                       }

                     }
                    else
                        QMessageBox::warning(this, "Warning", "problem with ulaz.txt");
                    file.close();

                    /* start program */
                    if((pid=fork())<0)
                        QMessageBox::warning(this, "Warning", "problem with fork");
                    else if((pid == 0))
                    {
                      if(execlp("/bin/sh", "bash", "-c", command.c_str(), (char*)0)<0)
                          QMessageBox::warning(this, "Warning", "problem with calling bash");
                    }
                    else
                      if(waitpid(pid, &status, 0)<0)
                          QMessageBox::warning(this, "Warning", "problem with C program");

                    QFile ulaz_fajl("ulaz.txt");
                    QFile izlaz_fajl("izlaz.txt");
                    if(ulaz_fajl.open(QIODevice::ReadOnly) && izlaz_fajl.open(QIODevice::ReadOnly))
                    {
                        QString ulaz_tekst = QTextStream(&ulaz_fajl).readAll();
                        log_stream << "ulaz: " << ulaz_tekst << "\n";
                        QString izlaz_tekst = QTextStream(&izlaz_fajl).readAll();
                        log_stream << "izlaz: " << izlaz_tekst << "\n";
                        log_stream << "exit status: " << QString::fromStdString(getStatus(status)) << "\n";
                        ulaz_fajl.close();
                        izlaz_fajl.close();
                    }
                    else
                        QMessageBox::warning(this, "Warning", "problem with ulaz.txt or izlaz.txt");

                    if(counter == repeat_num - 1)
                    {
                       log.close();

                        QFile log_fajl("log.txt");
                        if(log_fajl.open(QIODevice::ReadOnly))
                        {
                            QTextStream ts(&log_fajl);

                            for(unsigned i = 0; i < repeat_num; i++)
                            {
                                QString ulaz_linija = ts.readLine();
                                QString izlaz_linija = ts.readLine();
                                QString status_linija = ts.readLine();

                                std::string pom1 = ulaz_linija.toStdString();
                                std::string pom2 = pom1.substr(pom1.find_first_of(':') + 2, pom1.size());
                                example.append(QString::fromStdString(pom2)).append("|");

                                pom1 = izlaz_linija.toStdString();
                                pom2 = pom1.substr(pom1.find_first_of(':') + 2, pom1.size());
                                example.append(QString::fromStdString(pom2)).append("|");

                                pom1 = status_linija.toStdString();
                                pom2 = pom1.substr(pom1.find_first_of(':') + 2, pom1.size());
                                example.append(QString::fromStdString(pom2).append(";"));
                            }
                            log_fajl.close();
                        }
                        else
                            QMessageBox::warning(this, "Warning", "problem with log.txt");
                    }
                }
            }
            else
                if(chdir(start_dir)<0)
                    QMessageBox::warning(this, "Warning", "problem with chdir");
        }
    }
}
