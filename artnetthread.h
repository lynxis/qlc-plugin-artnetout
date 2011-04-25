/*
  Q Light Controller
  artnetthread.h

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

#ifndef ARTNETTHREAD_H
#define ARTNETTHREAD_H

#include <qthread.h>
#include <qstring.h>
#include <artnet/artnet.h>
#include <sys/types.h>

class ArtNetThread : public QThread 
{

 public:
  ArtNetThread(QString ip);
  ~ArtNetThread();

  // methods
  virtual void run();
  void start ( Priority priority = InheritPriority) ;
  void stop() ;
  int write_dmx(uint8_t *data , int channels) ;

 private:
  int m_sd[2] ;
  artnet_node m_node ;

};

#endif
