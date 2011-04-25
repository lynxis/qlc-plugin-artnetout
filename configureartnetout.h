/*
  Q Light Controller
  configureartnetout.h
  
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

#ifndef CONFIGUREARTNETOUT_H
#define CONFIGUREARTNETOUT_H

#include "ui_configureartnetout.h"

class ArtNetOut;

class ConfigureArtNetOut : public Ui_UI_ConfigureArtNetOut
{
  Q_OBJECT

 public:
  ConfigureArtNetOut(ArtNetOut* plugin);
  virtual ~ConfigureArtNetOut();

  void setDevice(QString deviceName);
  QString ip();

  void updateStatus();

 private slots:
  void slotActivateClicked();

 private:
  ArtNetOut* m_plugin;
};

#endif
