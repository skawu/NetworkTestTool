#include "networktest.h"
#include "ui_networktest.h"
#include <QNetworkDatagram>
#include <QtWidgets>


NetworkTest::NetworkTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NetworkTest)
{
    ui->setupUi(this);
    if(load_plugin())
        qDebug() << __FUNCTION__ << ": " << __LINE__;
    else
        qDebug() << __FUNCTION__ << ": " << __LINE__;
}

NetworkTest::~NetworkTest()
{
    delete ui;
}


void NetworkTest::on_pushBt_localinfo_clicked()
{
    if(nullptr != udp_socket) {
        ui->pushBt_localinfo->setText("打开");
        udp_socket->close();
        delete udp_socket;
        udp_socket = nullptr;
        return ;
    }

    udp_socket = new QUdpSocket(this);

    // 获取用户输入的IP和端口号
    local_ip = ui->lineEdit_localIP->text();
    local_port = ui->lineEdit_localPort->text().toInt();

    if(udp_socket->bind(QHostAddress(local_ip), local_port)) {
        ui->pushBt_localinfo->setText("关闭");
    } else {
        delete udp_socket;
        udp_socket = nullptr;
        return ;
    }

    zmj_udp_protocol_interface->udp_protocol_layout_enable(true);

    // 绑定数据接收函数
    connect(udp_socket, SIGNAL(readyRead()),
                  this, SLOT(readPendingDatagrams()));
}

void NetworkTest::readPendingDatagrams()
{
    QHostAddress remote_address;
//    qint64 len = 0;
//    char* data;
    while (udp_socket->hasPendingDatagrams()) {

        recv_count += (qint64)udp_socket->pendingDatagramSize();
//        data = (char *)udp_recv_data.data();

        ui->label_recvnum->setText(QString::number(recv_count));

        udp_recv_data.resize(udp_socket->pendingDatagramSize());
        udp_socket->readDatagram(udp_recv_data.data(), udp_recv_data.size(), &remote_address, &remote_port);

        if(recv_total)                  // 仅统计接收数据
            return ;
        remote_ip = remote_address.toString();
        qDebug() << remote_ip.size();
        if(remote_ip.size() > 0)
            ui->lineEdit_remoteIP->setText(remote_ip);
        ui->lineEdit_remotePort->setText(QString::number(remote_port));

//        emit recv_data_ok();
        zmj_udp_protocol_interface->disp_array_to_udp(udp_recv_data);

        if(recv_data_hex_dis) {                                     // 是否为16进制显示
            if(recv_data_dis_new_line){                             // 是否换行显示
                ui->textEdit_recv->append(udp_recv_data.toHex());
            } else {
                ui->textEdit_recv->textCursor().insertText(udp_recv_data.toHex());
                ui->textEdit_recv->textCursor().movePosition(QTextCursor::End);
            }
        } else {

            if(recv_data_dis_new_line){
                ui->textEdit_recv->append(udp_recv_data.data());
            } else {
                ui->textEdit_recv->textCursor().insertText(udp_recv_data.data());
                ui->textEdit_recv->textCursor().movePosition(QTextCursor::End);
            }
        }
    }
}

void NetworkTest::on_pushBt_countRST_clicked()
{
    recv_count = 0;
    send_count = 0;

    ui->label_recvnum->setText(QString::number(recv_count));
    ui->label_recvnum->setText(QString::number(send_count));
}

QByteArray& NetworkTest::udp_get_recv_data()
{
    return udp_recv_data;
}

void NetworkTest::on_checkBox_auto_indent_stateChanged(int arg1)
{
    if(2 == arg1) {
        recv_data_dis_new_line = true;
    } else if(0 == arg1) {
        recv_data_dis_new_line = false;
    }
}

void NetworkTest::on_checkBox_recv_hex_stateChanged(int arg1)
{
    if(2 == arg1) {
        recv_data_hex_dis = true;
    } else if(0 == arg1) {
        recv_data_hex_dis = false;
    }
}

void NetworkTest::on_pushButton_clicked()
{
    ui->textEdit_recv->clear();
}

void NetworkTest::on_pushButton_2_clicked()
{
    ui->textEdit_send->clear();
}

void NetworkTest::on_checkBox_stateChanged(int arg1)
{
    if(2 == arg1) {
        recv_total = true;
    } else if(0 == arg1) {
        recv_total = false;
    }
}

bool NetworkTest::load_plugin()
{
    QDir pluginsDir(qApp->applicationDirPath());

    pluginsDir.cd("G:/Application/qt/plugin_reop");

    foreach(QString fileName, pluginsDir.entryList(QDir::Files))
    {
        qDebug() << fileName;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();

        if(plugin) {
            zmj_udp_protocol_interface = qobject_cast<ZMJ_UDP_Protocol_Interface *>(plugin);
            if(zmj_udp_protocol_interface)
                return true;
        }
    }

    return false;
}
