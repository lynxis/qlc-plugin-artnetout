/*
  Q Light Controller
  artnetthread.cpp

  Copyright (c) Heikki Junnila
                Simon Newton

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  Version 2 as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details. The license is
  in the file "COPYING".

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "artnetthread.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

//
// Class implementation
//

int ArtNetThread::stopNode()
{
    if (m_node != NULL) {
        qDebug("closing node\n");
        artnet_stop(m_node);
        qDebug("destorying node\n");
        artnet_destroy(m_node);
    }
    return 0;
}

int ArtNetThread::startNode()
{
    // we prob want to make this configurable at some stage
    int port_addr = 0 ;
    m_configChanged = false;

    // new artnet node
    if (m_ip == QString("")) {
        m_node = artnet_new(NULL, 0) ;
    } else {
        m_node = artnet_new(m_ip.toAscii(), 0) ;
    }

    // we need to return an error condition here
    if ( m_node == NULL) {
        qDebug("ArtNetThread: not running");
        return -1;
    }
    artnet_set_node_type(m_node, ARTNET_SRV) ;
    artnet_set_short_name(m_node, "QLC") ;
    artnet_set_long_name(m_node,"Q Light Controller with libartnet") ;
    // artnet subclassing - has nothing to do with Ip !
    artnet_set_subnet_addr(m_node, 0) ;

    artnet_set_port_type(m_node, 0, ARTNET_ENABLE_OUTPUT, ARTNET_PORT_DMX) ;
    artnet_set_port_addr(m_node, 0, ARTNET_OUTPUT_PORT, port_addr);
    // broadcast only if there are more than 10 artnet nodes
    artnet_set_bcast_limit(m_node, 10);
    qDebug("artnode started");

    return artnet_start(m_node) ;
}

ArtNetThread::ArtNetThread(QString ip): m_ip(ip), m_newgw(ip), m_configChanged(false)
{
    startNode();
}

ArtNetThread::~ArtNetThread()
{
    stopNode();
}


void ArtNetThread::setIp(QString ip)
{
    if(m_ip == ip) {
        return;
    }
    m_ip = ip;
    m_configChanged = true;
}

/* Attempt to open dmx device */
void ArtNetThread::run()
{
    uint8_t buf[512] ;
    int r, maxfd ;
    fd_set fds;
    struct timeval tv;
    bool loop = true ;

    while (loop) {
        if(m_configChanged) {
            stopNode();
            startNode();
        }
        FD_ZERO(&fds);
        FD_SET(m_sd[1], &fds);

        maxfd = m_sd[1] ;

        tv.tv_sec = 1;		// one second timeout sounds ok
        tv.tv_usec = 0;
        // TODO dont run faster than ...
        switch (select(maxfd+1, &fds, NULL, NULL, &tv) ) {
        case 0:
            // time out
            break ;
        case -1:
            printf("artnetout: select error %s\n" , strerror(errno) ) ;
            break ;
        default:
            if(FD_ISSET(m_sd[1], &fds)) {
                // data to write from pipe
                r = read(m_sd[1], buf, sizeof(buf));

                // pipe has been closed, exit (and terminate thread)
                if( r == 0) {
                    loop = false;
                }

                if (r < 0) {
                    printf("artnetout: Read error %s\n", strerror(errno) ) ;
                }

                // send artnet packet
//				  printf("write dmx %i\n", r ) ;
                artnet_send_dmx(m_node, 0, 512, buf) ;
                //			  printf("after write dmx\n") ;
            } else if (FD_ISSET(artnet_get_sd(m_node), &fds) ) {
                // we can ignore packets from artnet.
            } else {
                // we have an error here
                printf("artnetout: could not determine set fd, terminating thread\n") ;
                loop = false;
            }
            break;
        }
    }

    close(m_sd[1]) ;

}
int ArtNetThread::write_dmx(uint8_t *data, int channels )
{
    int r ;

    // write to pipe
    r = write(m_sd[0], data, sizeof(uint8_t) * channels) ;

    if( r != int(channels * sizeof(uint8_t) )) {
        printf("artnetout: Only wrote %i bytes %s\n", r, strerror(errno) ) ;
    }

    return 0;
}

void ArtNetThread::start ( Priority priority )
{
    int r ;

    printf("new thread started\n") ;
    r = socketpair(AF_LOCAL , SOCK_STREAM , 0 , m_sd ) ;

    if(r) {
        printf("artnetout: Failed to create socket pair\n") ;
        return ;
    }

    // isn't there a super keyword ?
    QThread::start(priority) ;

}

// stop the thread
void ArtNetThread::stop()
{
    close(m_sd[0]) ;
}


QStringList ArtNetThread::getNodeIps()
{
    QStringList stringlist;
    artnet_node_config_t config;
    fd_set *set;
    Q_UNUSED(config);
    Q_UNUSED(set);

    if(m_node == NULL) {
        return stringlist;
    }
    artnet_dump_config(m_node);

    int artnet_fd = artnet_get_sd(m_node);
    Q_UNUSED(artnet_fd)

    return stringlist;
}
