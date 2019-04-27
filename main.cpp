#include "networktest.h"
#include <QApplication>
#include <QHostInfo>

QByteArray NetworkTest::udp_recv_data = 0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkTest w;

    //获取主机名
        QString localHostName = QHostInfo::localHostName();
        qDebug() << "localHostName" << localHostName;

        //获取本机的IP地址(可能有多条）
        QHostInfo info = QHostInfo::fromName(localHostName);
        qDebug()<<"IP Address："<< info.addresses();

        //只输出IPv4地址（可能有多条）
        foreach(QHostAddress address,info.addresses())
        {
            if(address.protocol() == QAbstractSocket::IPv4Protocol)

                qDebug() <<"My localhost IPv4 address: "<< address.toString();
        }

    w.show();

    return a.exec();
}
