#ifndef SER_H
#define SER_H

#include <QSerialPort>
#include <QObject>
#include <QTimer>
#include <QSerialPortInfo>

class Ser : public QObject
{
    Q_OBJECT
public:
    explicit Ser(QObject *parent = nullptr);


signals:
    void is_connected(bool conn);
    void arduioData(QString);
    void show_info(QString info);

public slots:
    void sendData(QString data);
    void connection();

private:
   QSerialPort *serial = nullptr;
   QTimer *timer = nullptr;
   QTimer *timer_chakePort = nullptr;
   bool conn=false;
   QList<QString> ports;
   int c_port=-1;
   int n_chake=0;
   void findPort(QString port);
   void readData();
   void chakePort();
   void chakeConnection();
   void seialErrors(QSerialPort::SerialPortError error);
};

#endif // SER_H
