#ifndef NETWORKTEST_H
#define NETWORKTEST_H

#include <QMainWindow>
#include <QUdpSocket>

#include "zmj_udp_protocol_interface.h"


namespace Ui {
class NetworkTest;
}

class NetworkTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetworkTest(QWidget *parent = 0);
    ~NetworkTest();

private slots:
    void on_pushBt_localinfo_clicked();

    void on_pushBt_countRST_clicked();

    void on_checkBox_auto_indent_stateChanged(int arg1);

    void on_checkBox_recv_hex_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

public slots:
    void readPendingDatagrams();

public:
   static QByteArray& udp_get_recv_data();

signals:
   void recv_data_ok();         // 定义一个信号，当有数据接收后发送，供外部处理数据

private:
    Ui::NetworkTest *ui;

    QUdpSocket *udp_socket = nullptr;
    QString local_ip;
    int local_port;
    QString remote_ip;
    quint16 remote_port;

    // 统计数据
    long send_count = 0;
    long recv_count = 0;

    // 接收到的数据，提供接口供外部调用
    static QByteArray udp_recv_data;

    // 控制型变量
    bool recv_data_hex_dis = false;         // 接收到的数据hex显示，默认为ascii显示
    bool recv_data_dis_new_line = false;    // 接收数据换行显示
    bool send_data_by_hex  = false;         // 以hex格式发送数据，默认为ascii格式发送
    bool recv_total = false;                // 接收数据统计

    // 插件接口
    ZMJ_UDP_Protocol_Interface *zmj_udp_protocol_interface;
    bool load_plugin();
};

#endif // NETWORKTEST_H
