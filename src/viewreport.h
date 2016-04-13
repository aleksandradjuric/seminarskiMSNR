#ifndef VIEWREPORT_H
#define VIEWREPORT_H

#include <QDialog>

namespace Ui {
class viewReport;
}
class viewReport : public QDialog
{
    Q_OBJECT

public:
    explicit viewReport(QWidget *parent = 0);
    ~viewReport();

private slots:
    void on_btn_viewReport_cancle_clicked();
    void on_btn_viewReport_save_clicked();
    void printList();

private:
    Ui::viewReport *ui;
    QStringList list;
};

#endif // VIEWREPORT_H
