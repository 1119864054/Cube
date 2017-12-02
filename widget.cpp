#include "widget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

#include <iostream>
#include <Qtsql/QSqlDatabase>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSql>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("登录界面"));

    userNameLabel = new QLabel(tr("用户名："));
    passWordLabel = new QLabel(tr("密码："));

    userNameLineEdit = new QLineEdit;
    passWordLineEdit = new QLineEdit;
    passWordLineEdit->setEchoMode(QLineEdit::Password);

    login = new QPushButton(tr("登录"));

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(userNameLabel,0,0);
    mainLayout->addWidget(passWordLabel,1,0);
    mainLayout->addWidget(userNameLineEdit,0,1);
    mainLayout->addWidget(passWordLineEdit,1,1);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    mainLayout->addLayout(hBoxLayout,2,0,1,2);
    hBoxLayout->addStretch();
    hBoxLayout->addWidget(login);

    connect(login,SIGNAL(clicked()),this,SLOT(slotLogin()));

    connect(passWordLineEdit,SIGNAL(returnPressed()),this,SLOT(slotLogin()));


}

Widget::~Widget()
{

}

void Widget::slotLogin(){
    /*
    qDebug() << "输入用户名："<< userNameLineEdit->text();
    qDebug() << "输入密码：" << passWordLineEdit->text();
    */
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Cube");
    db.setUserName("root");
    db.setPassword("");
    QString username;
    QString password;
    if(db.open())
    {
        QSqlQuery query;
        query.exec("select * from user");
        while(query.next())
        {
            username = query.value(5).toString();
            password = query.value(6).toString();
            //qDebug() << username << "|" << password;
        }
        db.close();
    }
    else
    {
        qDebug() << "opened error";
    }
    if (userNameLineEdit->text() == username && passWordLineEdit->text() == password)
    {
        qDebug() << "登录成功！";
        QMessageBox::information(this,tr("登录提示"),tr("登录成功"));
    }
    else
    {
        qDebug() << "用户名或密码错误！";
        QMessageBox::information(this,tr("登录提示"),tr("用户名或密码错误！"));
    }
}
