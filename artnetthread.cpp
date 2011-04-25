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
ArtNetThread::ArtNetThread(QString ip)
{
  // we prob want to make this configurable at some stage
  int port_addr = 0 ;

  // new artnet node
  if (ip == QString(""))
    m_node = artnet_new(NULL, 1) ;  
  else
    m_node = artnet_new(ip.toAscii(), 1) ;
  
  // we need to return an error condition here 
  if ( m_node == NULL) 
    return ;

  artnet_set_node_type(m_node, ARTNET_SRV) ;
  artnet_set_short_name(m_node, "QLC") ;
  artnet_set_long_name(m_node,"Q Light Controller with libartnet") ;
  artnet_set_subnet_addr(m_node, 0) ;

  artnet_set_port_type(m_node, 0, ARTNET_ENABLE_INPUT, ARTNET_PORT_DMX) ;
  artnet_set_port_addr(m_node, 0, ARTNET_INPUT_PORT, port_addr);

  artnet_start(m_node) ;
}

ArtNetThread::~ArtNetThread()
{
  artnet_stop(m_node) ;

  // free node
 printf("destorying node\n") ;
 artnet_destroy(m_node) ;
 printf("done destory\n") ;

}

/* Attempt to open dmx device */
void ArtNetThread::run()
{
  uint8_t buf[512] ;
  int r, maxfd ;
  fd_set fds;
  struct timeval tv;
  int loop = 1 ;
  
  while (loop) 
    {
      FD_ZERO(&fds);
      maxfd = artnet_set_fdset(m_node, &fds) ;
      FD_SET(m_sd[1], &fds) ;
	  
      maxfd = maxfd > m_sd[1] ? maxfd : m_sd[1] ;

      tv.tv_sec = 1;		// one second timeout sounds ok
      tv.tv_usec = 0;
	 
      switch (select(maxfd+1, &fds, NULL, NULL, &tv) )
        {
          case 0:
             // time out
             break ;
          case -1:
             printf("artnetout: select error %s\n" , strerror(errno) ) ;
             break ;
          default:
              if(FD_ISSET(m_sd[1], &fds))
                {
                  // data to write from pipe
                  r = read(m_sd[1], buf, sizeof(buf)); 
  
                  // pipe has been closed, exit (and terminate thread)
                  if( r == 0) 
                    loop = 0 ;
  
                  if (r < 0)
                    printf("artnetout: Read error %s\n", strerror(errno) ) ;

                  // send artnet packet
				  printf("write dmx %i\n", r ) ;
                  artnet_send_dmx(m_node, 0, 512, buf) ;
				  printf("after write dmx\n") ;
                }
              else if (FD_ISSET(artnet_get_sd(m_node), &fds) )
                {
                  artnet_read(m_node,0);
                }
              else 
                {
                  // we have an error here
                  printf("artnetout: could not determine set fd, terminating thread\n") ;
                  loop = 0;
                }
              break;
        } 
    }

  close(m_sd[1]) ;
  return ; 

}
int ArtNetThread::write_dmx(uint8_t *data, int channels )
{
  int r ;
  
  // write to pipe
  r = write(m_sd[0], data, sizeof(uint8_t) * channels) ;

  if( r != int(channels * sizeof(uint8_t) ))
    printf("artnetout: Only wrote %i bytes %s\n", r, strerror(errno) ) ;

  return 0;
}

void ArtNetThread::start ( Priority priority )
{
  int r ;
  
  printf("new thread started\n") ;
  r = socketpair(AF_LOCAL , SOCK_STREAM , 0 , m_sd ) ;

  if(r)
    {
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
  return ;
}
