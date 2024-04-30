#include "login.h"
#include "ui_login.h"
#include <QtSql>
#include <QDebug>

Login::Login(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    message = new QMessageBox();
    ui->ServerInput->setFocus();
}

Login::~Login()
{
    delete ui;
    delete message;
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
        qDebug() << db.lastError();
        message->setText("Соединение не установлено!");
        message->show();
        return;
    }
    emit on_DBConnected();
}

