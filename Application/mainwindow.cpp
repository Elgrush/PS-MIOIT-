#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "xml.hpp"
#include "motor.h"

void checkForColours(Ui::MainWindow *ui)
{
    if(ui->cVelocity->value() > ui->tVelocity->value())
         ui->cVelocity->setStyleSheet("QDoubleSpinBox { background-color : red; color : blue; }");
    else
    if(ui->cVelocity->value() < ui->mVelocity->value())
        ui->cVelocity->setStyleSheet("QDoubleSpinBox { background-color : blue; color : white; }");
    else
        ui->cVelocity->setStyleSheet("QDoubleSpinBox { background-color : white; color : black; }");

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        qDebug() << "\n"
                 << "Port:" << portInfo.portName() << "\n"
                 << "Location:" << portInfo.systemLocation() << "\n"
                 << "Description:" << portInfo.description() << "\n"
                 << "Manufacturer:" << portInfo.manufacturer() << "\n"
                 << "Serial number:" << portInfo.serialNumber() << "\n"
                 << "Vendor Identifier:" << (portInfo.hasVendorIdentifier()
                                                 ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                                                 : QByteArray()) << "\n"
                 << "Product Identifier:" << (portInfo.hasProductIdentifier()
                                                  ? QByteArray::number(portInfo.productIdentifier(), 16)
                                                  : QByteArray());
    }

    port = new QSerialPort;

    port->setBaudRate(9600);
    port->setParity(QSerialPort::Parity::NoParity);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setPort(QSerialPortInfo("COM20"));

    opened = port->open(QIODevice::ReadWrite);
    qDebug() << opened;
    if (opened) {
        startTimer(1000);
    }

    QString sa, sb;

    if(parseXmlFile(QString("settings.xml"), &sa, &sb))
    {
        ui->tVelocity->setValue(std::stod(sa.toStdString()));
        ui->mVelocity->setValue(std::stod(sb.toStdString()));
    }

    checkForColours(ui);

}

MainWindow::~MainWindow()
{

    if(writeXmlFile(QString("settings.xml"), ui->tVelocity->textFromValue(ui->tVelocity->value()), ui->mVelocity->textFromValue(ui->mVelocity->value()))){}

    delete ui;
    if (opened) {
        port->close();
    }
}

void MainWindow::timerEvent(QTimerEvent *e) {
    if (port->bytesAvailable()>=1)
    {
        auto data = port->readAll();

        int idata = data.toInt();

        qDebug() << idata;
    }
}

void MainWindow::on_togglePushButton_released()
{
    if(!opened)
    {
        opened = port->open(QIODevice::ReadWrite);
    }
    if(opened)
    {
        uint8_t d = Motor::getLimit(ui->cVelocity->value(), 182);

        port->write((char*)(&d), sizeof(d));
    }

}


void MainWindow::on_cVelocity_valueChanged(double arg1)
{
    checkForColours(ui);
}

void MainWindow::on_tVelocity_valueChanged(double arg1)
{
    checkForColours(ui);
}
void MainWindow::on_mVelocity_valueChanged(double arg1)
{
    checkForColours(ui);
}
