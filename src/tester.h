#ifndef TESTER_H
#define TESTER_H

#include <QMainWindow>
#include <vector>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include "viewreport.h"

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

private:
    Ui::tester *ui;
    void dodaj_u_listu(std::string);
    QStandardItemModel *model;
    viewReport *v;
};

#endif // TESTER_H
