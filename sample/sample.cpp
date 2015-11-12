#include "sample.h"
#include "ui_sample.h"
#include <QtSerialPort/QSerialPort>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QDebug>
#include <QTextBrowser>
#include <QThread>

QSerialPort *serial;
Sample::Sample(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sample)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serial->setPortName("COM8");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QSerialPort::ReadWrite);
    ui->label->setText("command");
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceived()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(serialSend()));
}

Sample::~Sample()
{
    delete ui;
    serial->close();
}

void Sample::serialReceived()
{
    QThread::msleep(30);
    //QTest::qSleep(100);
    //ui->textBrowser->setText(serial->readAll());
    ui->textBrowser->append(serial->readLine());
}
void Sample::serialSend()
{
    serial->write(ui->lineEdit->text().toLatin1());
    serial->write("\n");
}

void Sample::on_lineEdit_returnPressed()
{
    ui->textBrowser->append(ui->lineEdit->text());
    ui->label->setText(ui->lineEdit->text());
    serial->write(ui->lineEdit->text().toLatin1());
    serial->write("\n");

}

void Sample::Write()
{
    QString pass = "C:/Users/KamihiraRintaro/Documents/QT/Data/";
    QString time =  QTime::currentTime().toString("HH_mm_ss");
    QString date =  QDate::currentDate().toString("yyyy_MM_dd");
    QString filename = date +"_" + time;
    QString extension = ".txt";
    QString fileinfo = pass + filename + extension;

    QFile file(fileinfo);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << ui->textBrowser->document()->toPlainText();

        file.flush();
        file.close();
        qDebug() << filename+" was saved";
    }
}

void Sample::on_pushButton_2_clicked()
{
    Write();
}
