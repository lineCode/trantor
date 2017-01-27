//
// Created by antao on 2017/1/24.
//

#ifndef TRANTOR_SOCKET_H
#define TRANTOR_SOCKET_H
#include <trantor/utils/NonCopyable.h>
#include <trantor/net/InetAddress.h>
#include <trantor/utils/Logger.h>
#include <string>
#include <unistd.h>

namespace trantor
{
    class Socket:NonCopyable
    {
    public:
        static int createNonblockingSocketOrDie(int family)
        {
            int sock = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
            if (sock < 0)
            {
                LOG_SYSERR << "sockets::createNonblockingOrDie";
                exit(-1);
            }
            return sock;
        }
        explicit Socket(int sockfd):
                sockFd_(sockfd)
        {}
        ~Socket()
        {
            LOG_TRACE<<"Socket deconstructed";
            if(sockFd_>=0)
                close(sockFd_);
        }
        /// abort if address in use
        void bindAddress(const InetAddress& localaddr);
        /// abort if address in use
        void listen();
        int accept(InetAddress* peeraddr);
        void closeWrite();
        int read(char *buffer,uint64_t len);
        int fd(){return sockFd_;}
        static struct sockaddr_in6 getLocalAddr(int sockfd);
        static struct sockaddr_in6 getPeerAddr(int sockfd);
    protected:
        int sockFd_;

    };
}



#endif //TRANTOR_SOCKET_H