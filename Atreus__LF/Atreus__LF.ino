/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018, 2019  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include <Kaleidoscope.h>
#include <Kaleidoscope-TapDance.h>
// Support for Leader
#include <Kaleidoscope-Leader.h>


#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO,
  MACRO_HYPER
};

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At LSHIFT(Key_2)
#define Key_Hash LSHIFT(Key_3)
#define Key_Dollar LSHIFT(Key_4)
#define Key_Percent LSHIFT(Key_5)
#define Key_Caret LSHIFT(Key_6)
#define Key_And LSHIFT(Key_7)
#define Key_Star LSHIFT(Key_8)
#define Key_Plus LSHIFT(Key_Equals)

enum {
  QWERTY,
  FUN,
  UPPER
};

/* *INDENT-OFF* */
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B, Key_Backtick
      ,Key_Esc ,Key_Tab ,Key_LeftGui ,Key_LeftShift ,Key_Backspace ,Key_LeftControl

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       /*,Key_N     ,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash*/
       ,Key_LeftAlt  ,Key_Space ,MO(FUN)    ,Key_Minus ,Key_Quote  ,Key_Enter
  ),

  [FUN] = KEYMAP_STACKED
  (
       Key_Exclamation ,Key_At           ,Key_UpArrow   ,Key_Dollar           ,Key_Percent
      ,Key_LeftParen   ,Key_LeftArrow    ,Key_DownArrow ,Key_RightArrow       ,Key_RightParen
      ,Key_LeftBracket ,Key_RightBracket ,Key_Hash      ,Key_LeftCurlyBracket ,Key_RightCurlyBracket ,Key_Caret
      ,TG(UPPER)       ,Key_Insert       ,Key_LeftGui   ,Key_LeftShift        ,Key_Delete         ,Key_LeftControl

                   ,Key_PageUp   ,Key_7 ,Key_8      ,Key_9 ,Key_Backspace
                   ,Key_PageDown ,Key_4 ,Key_5      ,Key_6 ,___
      ,Key_And     ,Key_Star     ,Key_1 ,Key_2      ,Key_3 ,Key_Plus
      ,Key_LeftAlt ,Key_Space    ,___   ,Key_Period ,Key_0 ,Key_Equals
   ),

  [UPPER] = KEYMAP_STACKED
  (
       Key_Insert            ,Key_Home                 ,Key_UpArrow   ,Key_End        ,Key_PageUp
      ,Key_Delete            ,Key_LeftArrow            ,Key_DownArrow ,Key_RightArrow ,Key_PageDown
      ,M(MACRO_VERSION_INFO) ,Consumer_VolumeIncrement ,XXX           ,XXX            ,___ ,___
      ,MoveToLayer(QWERTY)   ,Consumer_VolumeDecrement ,___           ,___            ,___ ,___

                ,Key_UpArrow   ,Key_F7              ,Key_F8          ,Key_F9         ,Key_F10
                ,Key_DownArrow ,Key_F4              ,Key_F5          ,Key_F6         ,Key_F11
      ,___      ,XXX           ,Key_F1              ,Key_F2          ,Key_F3         ,Key_F12
      ,___      ,___           ,MoveToLayer(QWERTY) ,Key_PrintScreen ,Key_ScrollLock ,Consumer_PlaySlashPause
   )
)
/* *INDENT-ON* */

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusEEPROMCommand,
  FocusSettingsCommand,
  Qukeys,
  Leader,
  SpaceCadet,
  OneShot,
  Macros,
  TapDance,
  MouseKeys
);

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
  case MACRO_QWERTY:
    // This macro is currently unused, but is kept around for compatibility
    // reasons. We used to use it in place of `MoveToLayer(QWERTY)`, but no
    // longer do. We keep it so that if someone still has the old layout with
    // the macro in EEPROM, it will keep working after a firmware update.
    Layer.move(QWERTY);
    break;
  case MACRO_VERSION_INFO:
    if (keyToggledOn(keyState)) {
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
    }
    break;
  case MACRO_HYPER:
    return MACRO(D(RightAlt),T(E),U(RightAlt),T(A));
    break; 
  
 
  default:
    break;
  }
  return MACRO_NONE;
}


void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
  case 0 :
    return tapDanceActionKeys(tap_count, tap_dance_action, Key_A, M(MACRO_HYPER));
  }
}


//functions to tie to the leader key
//https://www.learn-portuguese-with-rafa.com/portuguese-keyboard-characters.html
static void accent_a(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(A)));}
static void accent_a_circ(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(A)));}
static void accent_a_til(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(A)));}
static void accent_a_grave(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(Backtick),U(RightAlt),T(A)));}


static void accent_e(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(E)));}
static void accent_e_circ(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(E)));}


static void accent_i(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(I)));}

static void accent_o(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(O)));}
static void accent_o_circ(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(O)));}
static void accent_o_til(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(O)));}
static void accent_o_grave(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(Backtick),U(RightAlt),T(O)));}

static void accent_u(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(U)));}
static void accent_n(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(N)));}
static void cedilla(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(C),U(RightAlt)));}


static void launch_alfred(uint8_t seq_index) { Macros.play(MACRO(D(LeftAlt),D(LeftGui),D(LeftControl), T(A), U(LeftAlt),U(LeftGui),U(LeftControl)  ));}//Alfred
static void launch_skitch(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),D(LeftShift), T(5), U(LeftGui),U(LeftShift)  ));}//skitch
static void launch_emoticons(uint8_t seq_index) { Macros.play(MACRO( T(F17) ));} //emoticons
static void click_backslash(uint8_t seq_index) { Macros.play(MACRO( T(Backslash) ));}//backslash
static void click_pipe(uint8_t seq_index) { Macros.play(MACRO( T(Pipe) ));}//pipe
static void click_open_question(uint8_t seq_index) { Macros.play(MACRO(D(LeftAlt),D(LeftShift), T(Slash), U(LeftAlt),U(LeftShift) ));}//openquestion¿¿¿¿¿

static void select_and_copy_word(uint8_t seq_index) { Macros.play(MACRO( D(LeftAlt),T(LeftArrow),U(LeftAlt), D(LeftAlt),D(LeftShift),T(RightArrow),U(LeftShift),U(LeftAlt),D(LeftGui),T(C),U(LeftGui)));}//select and copy word
static void select_and_copy_line(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),T(LeftArrow),U(LeftGui), D(LeftGui),D(LeftShift),T(RightArrow),U(LeftShift),U(LeftGui),D(LeftGui),T(C),U(LeftGui)));}//select and copy line

static void go_sol(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),T(LeftArrow),U(LeftGui)));}//startline
static void go_eol(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),T(RightArrow),U(LeftGui)));}//eol

static void change_window_same_app(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),T(Backtick),U(LeftGui)));}//change window in the same app


static void go_sod(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),T(Home),U(LeftGui)));}//start of document
static void go_eod(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),T(End),U(LeftGui)));}//end of document
static void go_up_ten_lines(uint8_t seq_index) { Macros.play(MACRO(T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow) ));}//ten lines up
static void go_down_ten_lines(uint8_t seq_index) { Macros.play(MACRO(T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow) ));}//ten lines up


static void screen_left(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),D(LeftAlt),T(LeftArrow),U(LeftGui),U(LeftAlt)));}//screen left
static void screen_right(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),D(LeftAlt),T(RightArrow),U(LeftGui),U(LeftAlt)));}//start of document
static void screen_up(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),D(LeftAlt),T(UpArrow),U(LeftGui),U(LeftAlt)));}//start of document
static void screen_down(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),D(LeftAlt),T(DownArrow),U(LeftGui),U(LeftAlt)));}//start of document
static void screen_full(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),D(LeftAlt),T(F),U(LeftGui),U(LeftAlt)));}//start of document
static void alt_tab(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),T(Tab),U(LeftGui)));}//alt tab
static void alt_accent(uint8_t seq_index) { Macros.play(MACRO( D(LeftGui),T(Backtick),U(LeftGui)));}//alt accent





static const kaleidoscope::plugin::Leader::dictionary_t leader_dictionary[] PROGMEM =
 LEADER_DICT(
    // Move
    // 1 key sequence : Caution need to have first, 1 keys sequences, after 2, 3 because the sequence will be matched first and wait the timeout notably if you some sequence with the same first keys
    // moveFileStart
    { LEADER_SEQ(LEAD(0), Key_A), accent_a},
    { LEADER_SEQ(LEAD(0),LEAD(0), Key_A), accent_a_circ},
    { LEADER_SEQ(LEAD(0),LEAD(0),LEAD(0), Key_A), accent_a_til},
    //{ LEADER_SEQ(LEAD(0),LEAD(0),LEAD(0), LEAD(0), Key_A), accent_a_til}, for some reason, a fourth leader didnt go through
    
    


    { LEADER_SEQ(LEAD(0), Key_E), accent_e},
    { LEADER_SEQ(LEAD(0),LEAD(0), Key_E), accent_e_circ},
    
    { LEADER_SEQ(LEAD(0), Key_I), accent_i},
    
    { LEADER_SEQ(LEAD(0), Key_O), accent_o},
    { LEADER_SEQ(LEAD(0),LEAD(0), Key_O), accent_o_circ},
    { LEADER_SEQ(LEAD(0),LEAD(0),LEAD(0), Key_O), accent_o_til},
    
    { LEADER_SEQ(LEAD(0), Key_U), accent_u},
    { LEADER_SEQ(LEAD(0), Key_N), accent_n},
    { LEADER_SEQ(LEAD(0), Key_C), cedilla},

    
    { LEADER_SEQ(LEAD(0), Key_B), launch_alfred}, //Alfred
    { LEADER_SEQ(LEAD(0), Key_G, Key_N), launch_skitch},  //skitchv
    { LEADER_SEQ(LEAD(0), Key_G, Key_H), launch_emoticons}, //emoticons
    { LEADER_SEQ(LEAD(0), Key_G, Key_Y), alt_tab  }, //alt tab
    { LEADER_SEQ(LEAD(0), Key_G, Key_T), alt_accent}, //alt accent
    
    { LEADER_SEQ(LEAD(0), Key_Slash), click_backslash}, //backslash
    { LEADER_SEQ(LEAD(0), Key_Semicolon), click_pipe}, //pipe
    { LEADER_SEQ(LEAD(0), Key_L), click_open_question}, //open question


    


    
    { LEADER_SEQ(LEAD(0), Key_Q,Key_W),select_and_copy_word}, //select and copy word
    { LEADER_SEQ(LEAD(0), Key_Q,Key_E),select_and_copy_line}, //select and copy line
    { LEADER_SEQ(LEAD(0), Key_Q,Key_Q),change_window_same_app}, //select and copy word


  

    //VI-Like
    { LEADER_SEQ(LEAD(0), Key_V,Key_Y),go_sol}, //start of line
    { LEADER_SEQ(LEAD(0), Key_V,Key_U),go_eol}, //end of line
    { LEADER_SEQ(LEAD(0), Key_V,Key_N),go_sod}, //start of docv
    { LEADER_SEQ(LEAD(0), Key_V,Key_M),go_eod}, //end of doc
    { LEADER_SEQ(LEAD(0), Key_V,Key_R),go_up_ten_lines}, //ten lines up
    { LEADER_SEQ(LEAD(0), Key_V,Key_T),go_down_ten_lines}, //ten lines down
    
    { LEADER_SEQ(LEAD(0), Key_M,Key_S),screen_left}, //
    { LEADER_SEQ(LEAD(0), Key_M,Key_F),screen_right}, //
    { LEADER_SEQ(LEAD(0), Key_M,Key_E),screen_up}, //    
    { LEADER_SEQ(LEAD(0), Key_M,Key_D),screen_down}, //
    { LEADER_SEQ(LEAD(0), Key_M,Key_M),screen_full} //


    );





void setup() {
  QUKEYS(
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 11), Key_Hyper),   //qeu es ?, lo convierte en ctrl+cmnd+alt+shift para Karabiner
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 10), LSHIFT(Key_LeftGui) ),// letter l, when hold, becomes command+shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 9), Key_LeftGui) //letter k, when hold becomes command
    )
  //QUKEYS(kaleidoscope::plugin::Qukey(1, KeyAddr(3, 1), Key_Hyper)); //qeu es ?, lo convierte en ctrl+cmnd+alt+shift para Karabiner
  Kaleidoscope.setup();
  SpaceCadet.disable();
  EEPROMKeymap.setup(10);
  Leader.dictionary = leader_dictionary;

}

void loop() {
  Kaleidoscope.loop();
}
