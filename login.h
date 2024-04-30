#ifndef LOGIN_H
#define LOGIN_H

#include <QGroupBox>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class Login;
}

class Login : public QGroupBox
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void InitDatabase();
    QMessageBox *message;

private slots:
    void on_ConnectButton_clicked();

private:
    Ui::Login *ui;
    QSqlDatabase db;
    void InitDatabaseDebug();

signals:
    void on_DBConnected();
};

#endif // LOGIN_H
