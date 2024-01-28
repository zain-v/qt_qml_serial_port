#include "ser.h"
#include "qdebug.h"

Ser::Ser(QObject *parent)
    : QObject{parent},
    serial(new QSerialPort(this)),
    timer(new QTimer(this)),
    timer_chakePort(new QTimer(this))
{
    connect(timer_chakePort,&QTimer::timeout, this, &Ser::chakePort);
    connect(timer,&QTimer::timeout, this, &Ser::chakeConnection);
    connect(serial, &QSerialPort::readyRead, this, &Ser::readData);
    connect(serial, &QSerialPort::errorOccurred, this, &Ser::seialErrors);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
}

void Ser::findPort(QString port)
{
    timer->stop();
    serial->close();
    serial->setPortName(port);

    if (serial->open(QIODevice::ReadWrite)) {

        timer->start(50);
        timer_chakePort->stop();
        // qDebug() << "chake port on" << port;
        emit show_info( "chake port:" + port);
    }

}

void Ser::readData()
{
    if(!conn){
        const QByteArray data = serial->readAll();
        QString rData = QString::fromUtf8(data);
        if(rData == "c++\r\n"){
            conn = true;
            emit is_connected(conn);
            emit show_info("connect on port: " + serial->portName());
            timer->stop();
            timer_chakePort->stop();
            c_port = -1;
            n_chake = 0;
            return;
        }
    }else{
        const QByteArray data = serial->readAll();
        QString rData = QString::fromUtf8(data);
        QStringList splitData = rData.split(",");
        qDebug() << splitData.length();
        if(splitData.length() > 4){
            if(splitData[0] == "s" && splitData[4] == "e\r\n")
                emit arduioData(rData);
        }
    }
    // qDebug() << data;
}

void Ser::sendData(QString data)
{
    QByteArray sdata = data.toUtf8();
    serial->write(sdata);
}

void Ser::chakePort()
{
    c_port ++;
    if(c_port>=ports.length()) {
        timer_chakePort->stop();
        c_port =-1;
        serial->close();
        emit show_info("not find device");
    }else{
        QString po = ports[c_port];
        findPort(po);
    }
}

void Ser::chakeConnection()
{
    if(conn) timer_chakePort->stop();
    serial->write("c");
    n_chake ++;
    if(n_chake == 4){
        timer->stop();
        timer_chakePort->start(10);
        n_chake =0;
    }
}

void Ser::seialErrors(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        emit is_connected(false);
        conn = false;
        emit show_info("connection fild");
        // qDebug() << "Error" << serial->errorString();
    }
}

void Ser::connection()
{
    ports.clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ports.append(info.portName());
    }
    timer_chakePort->start(10);
}
