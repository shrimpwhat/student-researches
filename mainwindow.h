#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "departments.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_DBConnected();

signals:
    void sendID(int);

private:
    Ui::MainWindow *ui;
    Login *login;
    QSqlQueryModel *qmodel;
    int fl = 0;
    int GlobId;
    DepartmentsView* departments;
};
#endif // MAINWINDOW_H
