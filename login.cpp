#include "login.h"
#include "ui_login.h"
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
    db.close();
}

void Login::InitDatabaseDebug() {
    QString host = "localhost";
    uint port = 5432;
    QString database_name = "nirs";
    QString user = "postgres";
    QString password = "p120s45";
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(database_name);
    db.setUserName(user);
    db.setPassword(password);
}

void Login::InitDatabase()  {
    QString host = ui->ServerInput->text();
    uint port = ui->PortInput->text().toUInt();
    QString database_name = ui->DbNameInput->text();
    QString user = ui->LoginInput->text();
    QString password = ui->PasswordInput->text();
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(database_name);
    db.setUserName(user);
    db.setPassword(password);
}

void Login::on_ConnectButton_clicked()
{
//    InitDatabase();
    InitDatabaseDebug();
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Ошибка", "Соединение не установлено");
        return;
    }
    emit on_DBConnected();
}

