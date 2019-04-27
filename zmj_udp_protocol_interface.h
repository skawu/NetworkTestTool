#ifndef ZMJ_UDP_PROTOCOL_INTERFACE_H
#define ZMJ_UDP_PROTOCOL_INTERFACE_H

#include <QByteArray>

class ZMJ_UDP_Protocol_Interface
{
public:
    virtual ~ZMJ_UDP_Protocol_Interface() {}
    virtual void udp_protocol_layout_enable(bool isEnable){}
    virtual void disp_array_to_udp(QByteArray &data){}
};

#define ZMJ_UDP_Protocol_Interface_iid   "ZMJ.Plugin.ZMJ_UDP_Protocol_Interface"

Q_DECLARE_INTERFACE(ZMJ_UDP_Protocol_Interface, ZMJ_UDP_Protocol_Interface_iid)

#endif // ZMJ_UDP_PROTOCOL_INTERFACE_H
