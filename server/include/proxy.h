//
// Created by qiguo on 1/21/18.
//

#ifndef __TINYRPC_PROXY_H__
#define __TINYRPC_PROXY_H__

#include "util.h"
#include "config.h"
#include "event.h"
#include "conn.h"
#include "protocol.h"
#include "pool.h"
#include <vector>

namespace tinyrpc
{
    class Proxy : util::noncopyable
    {
    public:
        explicit Proxy(const Config & config);

        void start();
        void stop();

        // dispatch request to a specific server process
        void dispatch(std::shared_ptr<tinynet::TcpConn> & client, const Message & msg);

    protected:
        void handleAccept(std::shared_ptr<tinynet::TcpConn> client);

        void clientError(std::shared_ptr<tinynet::TcpConn> & client, const std::string & errmsg);
        void clientOk(std::shared_ptr<tinynet::TcpConn> & client, const Message & retval);

    private:
        tinynet::EventLoop                      m_loop;
        std::shared_ptr<tinynet::TcpServer>     m_proxy;
        Pool< std::shared_ptr<
                tinynet::TcpConn> >             m_client_pool;
        Config                                  m_config;
    };
}

#endif //TINYRPC_RPCPROXY_H