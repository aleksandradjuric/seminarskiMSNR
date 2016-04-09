#ifndef TESTER_H
#define TESTER_H

#include <QMainWindow>
#include <vector>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include "viewreport.h"
#include <iostream>
#include <fstream>

namespace Ui {
class tester;
}

class tester : public QMainWindow
{
    Q_OBJECT

public:
    explicit tester(QWidget *parent = 0);
    ~tester();
    std::vector<std::string> testType;
    static QString example;


private slots:
    void on_btn_int_clicked();
    void on_btn_float_clicked();
    void on_btn_double_clicked();
    void on_btn_char_clicked();
    void on_btn_mail_clicked();
    void on_btn_test_file_clicked();
    void on_btn_view_report_clicked();
    void on_btn_clear_list_clicked();
    void on_btn_apply_num_element_clicked();
    void on_btn_date_clicked();
    void on_btn_time_clicked();
    void on_btn_path_clicked();
    void on_btn_start_clicked();

private:
    Ui::tester *ui;
    void dodaj_u_listu(std::string);
    void fill_vector(std::string);
    QStandardItemModel *model;
    viewReport *v;
    std::string path_of_file;
    std::vector<std::string>int_test;
    std::vector<std::string>double_test;
    std::vector<std::string>float_test;
    std::vector<std::string>char_test;
    std::vector<std::string>mail_test;
    std::vector<std::string>date_test;
    std::vector<std::string>time_test;
    std::vector<std::string>path_test;
};

#endif // TESTER_H
