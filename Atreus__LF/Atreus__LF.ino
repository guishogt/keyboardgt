/**
 * ============================================================================
 * ATREUS__LF.ino - Custom Keyboardio Atreus Firmware
 * ============================================================================
 *
 * Author: Luis Fernandez
 * Last Updated: 2026-05-22
 *
 * OVERVIEW
 * --------
 * Custom Kaleidoscope firmware for the Keyboardio Atreus with:
 *   - 3 layers: QWERTY (default), FUN (symbols/numpad), UPPER (F-keys/nav)
 *   - Portuguese accent support via Leader key sequences
 *   - Dual-function keys (Qukeys) for modifier combos
 *   - TapDance for double-tap shortcuts
 *   - macOS-optimized shortcuts for window management and text editing
 *
 * LAYER SUMMARY
 * -------------
 *   [0] QWERTY  - Default typing layer
 *   [1] FUN     - Hold MO(FUN): symbols on left, numpad on right, arrows
 *   [2] UPPER   - Toggle from FUN: F-keys, navigation, media controls
 *
 * TAPDANCE (Double-tap shortcuts)
 * -------------------------------
 *   Double-tap Alt (TEST) → Cmd+Tab (App Switcher)
 *   Future: ` ` → Clipy, ; ; → App Switcher, / / → Window switch
 *
 * LEADER KEY REFERENCE (Quick)
 * ----------------------------
 *   LEAD + A/E/I/O/U  → acute accent (á, é, í, ó, ú)
 *   LEAD + LEAD + A/E/O → circumflex (â, ê, ô)
 *   LEAD + LEAD + LEAD + A/O → tilde (ã, õ)
 *   LEAD + N → ñ,  LEAD + C → ç
 *   LEAD + B → Alfred,  LEAD + V + ... → VI navigation
 *   LEAD + M + ... → Window management
 *
 * QUKEYS (Hold Behavior)
 * ----------------------
 *   Hold L → Cmd+Shift    Hold K → Alt+Shift
 *   Hold / → Hyper (Ctrl+Cmd+Alt+Shift for Karabiner)
 *
 * ============================================================================
 */

#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope.h>

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

// =============================================================================
// INCLUDES
// =============================================================================

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"    // Chrysalis communication
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"        // Sticky modifiers
#include "Kaleidoscope-Qukeys.h"         // Dual-function keys (tap vs hold)
#include "Kaleidoscope-SpaceCadet.h"     // Disabled - shift as parens
#include <Kaleidoscope-TapDance.h>       // Multi-tap keys
#include <Kaleidoscope-Leader.h>         // Leader key sequences

// =============================================================================
// LAYER & MACRO DEFINITIONS
// =============================================================================

#define MO(n) ShiftToLayer(n)  // Momentary layer switch (hold)
#define TG(n) LockLayer(n)     // Toggle layer on/off

// --- Macro IDs ---
enum {
  MACRO_QWERTY,        // Legacy: switch to QWERTY layer
  MACRO_VERSION_INFO,  // Types firmware version string
  MACRO_HYPER          // Types á (used by TapDance)
};

// --- TapDance IDs ---
// Double-tap shortcuts (like Karabiner, but in firmware)
enum {
  TD_A_ACCENT,    // Legacy: double-tap A → á (index 0)
  TD_ALT_TEST,    // TEST: Alt position - double-tap → Cmd+Tab
  TD_TILDE,       // Future: ` ` → Cmd+Shift+V (Clipy paste)
  TD_SEMICOLON,   // Future: ; ; → Cmd+Tab (App Switcher)
  TD_SLASH        // Future: / / → Cmd+` (Window switch same app)
};

// Shifted symbol shortcuts for cleaner keymap definitions
#define Key_Exclamation LSHIFT(Key_1)
#define Key_At LSHIFT(Key_2)
#define Key_Hash LSHIFT(Key_3)
#define Key_Dollar LSHIFT(Key_4)
#define Key_Percent LSHIFT(Key_5)
#define Key_Caret LSHIFT(Key_6)
#define Key_And LSHIFT(Key_7)
#define Key_Star LSHIFT(Key_8)
#define Key_Plus LSHIFT(Key_Equals)

// --- Layer IDs ---
enum {
  QWERTY,  // Layer 0: Default typing
  FUN,     // Layer 1: Symbols + Numpad (momentary)
  UPPER    // Layer 2: F-keys + Navigation (toggled)
};

// =============================================================================
// KEYMAPS
// =============================================================================
// Atreus physical layout (44 keys):
//
//    Left Hand                          Right Hand
//  ┌───┬───┬───┬───┬───┐          ┌───┬───┬───┬───┬───┐
//  │ 0 │ 1 │ 2 │ 3 │ 4 │          │ 5 │ 6 │ 7 │ 8 │ 9 │
//  ├───┼───┼───┼───┼───┤          ├───┼───┼───┼───┼───┤
//  │10 │11 │12 │13 │14 │          │15 │16 │17 │18 │19 │
//  ├───┼───┼───┼───┼───┼───┐  ┌───┼───┼───┼───┼───┼───┤
//  │20 │21 │22 │23 │24 │25 │  │26 │27 │28 │29 │30 │31 │
//  ├───┼───┼───┼───┼───┼───┤  ├───┼───┼───┼───┼───┼───┤
//  │32 │33 │34 │35 │36 │37 │  │38 │39 │40 │41 │42 │43 │
//  └───┴───┴───┴───┴───┴───┘  └───┴───┴───┴───┴───┴───┘
//                    Thumbs ──▲      ▲── Thumbs

/* *INDENT-OFF* */
KEYMAPS(

  // ---------------------------------------------------------------------------
  // LAYER 0: QWERTY - Default Layer
  // ---------------------------------------------------------------------------
  // Standard QWERTY with:
  //   - Backtick and Backslash on inner columns
  //   - MO(FUN) on right thumb for layer access
  //   - TD(TD_ALT_TEST) on Alt position for TapDance testing
  //
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B, Key_Backtick
      ,Key_Esc ,Key_Tab ,Key_LeftGui ,Key_LeftShift ,Key_Backspace ,Key_LeftControl

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_LeftAlt  ,Key_Space ,MO(FUN)    ,Key_Minus ,Key_Quote  ,Key_Enter
  ),

  // ---------------------------------------------------------------------------
  // LAYER 1: FUN - Symbols & Numpad (Hold MO(FUN) to access)
  // ---------------------------------------------------------------------------
  // Left side:  Symbols (!@#$%^&*) and arrow keys
  // Right side: Numpad (7-8-9 / 4-5-6 / 1-2-3 / 0)
  // TG(UPPER) toggles to Layer 2
  //
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

  // ---------------------------------------------------------------------------
  // LAYER 2: UPPER - F-Keys & Extended Navigation (Toggle from FUN)
  // ---------------------------------------------------------------------------
  // Left side:  Insert/Delete, Home/End, Page Up/Down, Volume
  // Right side: F1-F12, PrintScreen, Media controls
  // Press MoveToLayer(QWERTY) to return to base layer
  //
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

// =============================================================================
// PLUGINS
// =============================================================================

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,       // Persistent settings storage
  EEPROMKeymap,         // Persistent keymap (for Chrysalis edits)
  Focus,                // Serial protocol for Chrysalis
  FocusEEPROMCommand,
  FocusSettingsCommand,
  Qukeys,               // Dual-function keys (tap vs hold)
  Leader,               // Leader key sequences
  SpaceCadet,           // Shift-as-parens (disabled in setup)
  OneShot,              // Sticky modifiers
  Macros,               // Custom macros
  TapDance,             // Multi-tap actions
  MouseKeys             // Mouse control via keyboard
);

// =============================================================================
// MACROS
// =============================================================================

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_QWERTY:
    // Legacy compatibility: old EEPROM layouts may reference this
    Layer.move(QWERTY);
    break;

  case MACRO_VERSION_INFO:
    // Types: "Keyboardio Atreus - Kaleidoscope [build info]"
    if (keyToggledOn(keyState)) {
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
    }
    break;

  case MACRO_HYPER:
    // Types: á (acute A) - RightAlt+E releases dead key, then A
    return MACRO(D(RightAlt),T(E),U(RightAlt),T(A));
    break;

  default:
    break;
  }
  return MACRO_NONE;
}

// =============================================================================
// TAP DANCE
// =============================================================================
// Double-tap shortcuts - like Karabiner but in firmware
//
// TD_ALT_TEST: Testing on Alt key position
//   - Single tap: Alt (normal behavior)
//   - Double tap: Cmd+Tab (App Switcher)
//
// Future implementation:
//   TD_TILDE:     ` → Cmd+Shift+V (Clipy paste)
//   TD_SEMICOLON: ; → Cmd+Tab (App Switcher)
//   TD_SLASH:     / → Cmd+` (Window switch)

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {

  case TD_A_ACCENT:  // Legacy: double-tap A → á
    return tapDanceActionKeys(tap_count, tap_dance_action, Key_A, M(MACRO_HYPER));

  case TD_ALT_TEST:
    // TEST: Y position - tap = Y, double-tap = Cmd+Tab
    return tapDanceActionKeys(tap_count, tap_dance_action,
      Key_Y,                 // Single tap: Y
      LGUI(Key_Tab));        // Double tap: Cmd+Tab (App Switcher)

  case TD_TILDE:
    // Double-tap ` → Cmd+Shift+V (Clipy paste)
    return tapDanceActionKeys(tap_count, tap_dance_action,
      Key_Backtick,          // Single tap: `
      LSHIFT(LGUI(Key_V)));  // Double tap: Cmd+Shift+V

  case TD_SEMICOLON:
    // Double-tap ; → Cmd+Tab (App Switcher)
    return tapDanceActionKeys(tap_count, tap_dance_action,
      Key_Semicolon,         // Single tap: ;
      LGUI(Key_Tab));        // Double tap: Cmd+Tab

  case TD_SLASH:
    // Double-tap / → Cmd+` (Switch window in same app)
    return tapDanceActionKeys(tap_count, tap_dance_action,
      Key_Slash,             // Single tap: /
      LGUI(Key_Backtick));   // Double tap: Cmd+`
  }
}

// =============================================================================
// LEADER KEY SEQUENCES
// =============================================================================
// Reference: https://www.learn-portuguese-with-rafa.com/portuguese-keyboard-characters.html
//
// How it works:
//   1. Press LEAD(0) - the Leader key (mapped elsewhere, e.g., via Qukey)
//   2. Type the sequence (e.g., A for á, or V then Y for start-of-line)
//   3. The macro executes automatically
//
// Dead key method (macOS): RightAlt + accent key, then letter
//   RightAlt+E = acute (´)    RightAlt+I = circumflex (^)
//   RightAlt+N = tilde (~)    RightAlt+` = grave (`)
//   RightAlt+C = cedilla (ç)

// --- Portuguese Accents ---------------------------------------------------

static void accent_a(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(A))); }  // á
static void accent_a_circ(uint8_t seq_index)  { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(A))); }  // â
static void accent_a_til(uint8_t seq_index)   { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(A))); }  // ã
static void accent_a_grave(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(Backtick),U(RightAlt),T(A))); } // à (unused)

static void accent_e(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(E))); }  // é
static void accent_e_circ(uint8_t seq_index)  { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(E))); }  // ê

static void accent_i(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(I))); }  // í

static void accent_o(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(O))); }  // ó
static void accent_o_circ(uint8_t seq_index)  { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(O))); }  // ô
static void accent_o_til(uint8_t seq_index)   { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(O))); }  // õ
static void accent_o_grave(uint8_t seq_index) { Macros.play(MACRO(D(RightAlt),T(Backtick),U(RightAlt),T(O))); } // ò (unused)

static void accent_u(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(U))); }  // ú
static void accent_n(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(N))); }  // ñ
static void cedilla(uint8_t seq_index)        { Macros.play(MACRO(D(RightAlt),T(C),U(RightAlt))); }       // ç

// --- App Launchers (macOS) ------------------------------------------------

static void launch_alfred(uint8_t seq_index)    { Macros.play(MACRO(D(LeftAlt),D(LeftGui),D(LeftControl),T(A),U(LeftAlt),U(LeftGui),U(LeftControl))); }  // Ctrl+Cmd+Alt+A
static void launch_skitch(uint8_t seq_index)    { Macros.play(MACRO(D(LeftGui),D(LeftShift),T(5),U(LeftGui),U(LeftShift))); }  // Cmd+Shift+5 (screenshot)
static void launch_emoticons(uint8_t seq_index) { Macros.play(MACRO(T(F17))); }  // F17 (mapped to emoji picker externally)

// --- Special Characters ---------------------------------------------------

static void click_backslash(uint8_t seq_index)     { Macros.play(MACRO(T(Backslash))); }  // backslash
static void click_pipe(uint8_t seq_index)          { Macros.play(MACRO(T(Pipe))); }       // |
static void click_open_question(uint8_t seq_index) { Macros.play(MACRO(D(LeftAlt),D(LeftShift),T(Slash),U(LeftAlt),U(LeftShift))); }  // ¿

// --- Text Selection & Clipboard -------------------------------------------

static void select_and_copy_word(uint8_t seq_index) {
  // Select word under cursor and copy: Alt+← Alt+Shift+→ Cmd+C
  Macros.play(MACRO(D(LeftAlt),T(LeftArrow),U(LeftAlt),D(LeftAlt),D(LeftShift),T(RightArrow),U(LeftShift),U(LeftAlt),D(LeftGui),T(C),U(LeftGui)));
}

static void select_and_copy_line(uint8_t seq_index) {
  // Select line and copy: Cmd+← Cmd+Shift+→ Cmd+C
  Macros.play(MACRO(D(LeftGui),T(LeftArrow),U(LeftGui),D(LeftGui),D(LeftShift),T(RightArrow),U(LeftShift),U(LeftGui),D(LeftGui),T(C),U(LeftGui)));
}

// --- VI-Like Navigation ---------------------------------------------------

static void go_sol(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(LeftArrow),U(LeftGui))); }   // Start of line (Cmd+←)
static void go_eol(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(RightArrow),U(LeftGui))); }  // End of line (Cmd+→)
static void go_sod(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(Home),U(LeftGui))); }        // Start of document
static void go_eod(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(End),U(LeftGui))); }         // End of document

static void go_up_ten_lines(uint8_t seq_index) {
  // Move up 12 lines quickly
  Macros.play(MACRO(T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow)));
}

static void go_down_ten_lines(uint8_t seq_index) {
  // Move down 12 lines quickly
  Macros.play(MACRO(T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow)));
}

// --- Window Management (requires Rectangle/Magnet/similar) ----------------

static void screen_left(uint8_t seq_index)  { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(LeftArrow),U(LeftGui),U(LeftAlt))); }   // Window → left half
static void screen_right(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(RightArrow),U(LeftGui),U(LeftAlt))); }  // Window → right half
static void screen_up(uint8_t seq_index)    { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(UpArrow),U(LeftGui),U(LeftAlt))); }     // Window → top half
static void screen_down(uint8_t seq_index)  { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(DownArrow),U(LeftGui),U(LeftAlt))); }   // Window → bottom half
static void screen_full(uint8_t seq_index)  { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(F),U(LeftGui),U(LeftAlt))); }           // Window → fullscreen

// --- Window Switching -----------------------------------------------------

static void change_window_same_app(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(Backtick),U(LeftGui))); }  // Cmd+` (next window)
static void alt_tab(uint8_t seq_index)                { Macros.play(MACRO(D(LeftGui),T(Tab),U(LeftGui))); }       // Cmd+Tab (app switcher)
static void alt_accent(uint8_t seq_index)             { Macros.play(MACRO(D(LeftGui),T(Backtick),U(LeftGui))); }  // Cmd+` (same as above)


// --- Leader Dictionary ----------------------------------------------------
// NOTE: Shorter sequences must come BEFORE longer ones with same prefix,
//       otherwise the shorter match triggers and longer is unreachable.

static const kaleidoscope::plugin::Leader::dictionary_t leader_dictionary[] PROGMEM =
  LEADER_DICT(

    // === PORTUGUESE ACCENTS ===
    // Single LEAD + vowel → acute accent
    { LEADER_SEQ(LEAD(0), Key_A), accent_a },                        // LEAD A → á
    { LEADER_SEQ(LEAD(0), LEAD(0), Key_A), accent_a_circ },          // LEAD LEAD A → â
    { LEADER_SEQ(LEAD(0), LEAD(0), LEAD(0), Key_A), accent_a_til },  // LEAD LEAD LEAD A → ã

    { LEADER_SEQ(LEAD(0), Key_E), accent_e },                        // LEAD E → é
    { LEADER_SEQ(LEAD(0), LEAD(0), Key_E), accent_e_circ },          // LEAD LEAD E → ê

    { LEADER_SEQ(LEAD(0), Key_I), accent_i },                        // LEAD I → í

    { LEADER_SEQ(LEAD(0), Key_O), accent_o },                        // LEAD O → ó
    { LEADER_SEQ(LEAD(0), LEAD(0), Key_O), accent_o_circ },          // LEAD LEAD O → ô
    { LEADER_SEQ(LEAD(0), LEAD(0), LEAD(0), Key_O), accent_o_til },  // LEAD LEAD LEAD O → õ

    { LEADER_SEQ(LEAD(0), Key_U), accent_u },                        // LEAD U → ú
    { LEADER_SEQ(LEAD(0), Key_N), accent_n },                        // LEAD N → ñ
    { LEADER_SEQ(LEAD(0), Key_C), cedilla },                         // LEAD C → ç

    // === APP LAUNCHERS ===
    { LEADER_SEQ(LEAD(0), Key_B), launch_alfred },                   // LEAD B → Alfred
    { LEADER_SEQ(LEAD(0), Key_G, Key_N), launch_skitch },            // LEAD G N → Screenshot
    { LEADER_SEQ(LEAD(0), Key_G, Key_H), launch_emoticons },         // LEAD G H → Emoji picker
    { LEADER_SEQ(LEAD(0), Key_G, Key_Y), alt_tab },                  // LEAD G Y → App switcher
    { LEADER_SEQ(LEAD(0), Key_G, Key_T), alt_accent },               // LEAD G T → Window switcher

    // === SPECIAL CHARACTERS ===
    { LEADER_SEQ(LEAD(0), Key_Slash), click_backslash },             // LEAD / → backslash
    { LEADER_SEQ(LEAD(0), Key_Semicolon), click_pipe },              // LEAD ; → pipe |
    { LEADER_SEQ(LEAD(0), Key_L), click_open_question },             // LEAD L → ¿

    // === TEXT SELECTION ===
    { LEADER_SEQ(LEAD(0), Key_Q, Key_W), select_and_copy_word },     // LEAD Q W → Select+copy word
    { LEADER_SEQ(LEAD(0), Key_Q, Key_E), select_and_copy_line },     // LEAD Q E → Select+copy line
    { LEADER_SEQ(LEAD(0), Key_Q, Key_Q), change_window_same_app },   // LEAD Q Q → Next window (same app)

    // === VI-LIKE NAVIGATION ===
    { LEADER_SEQ(LEAD(0), Key_V, Key_Y), go_sol },                   // LEAD V Y → Start of line
    { LEADER_SEQ(LEAD(0), Key_V, Key_U), go_eol },                   // LEAD V U → End of line
    { LEADER_SEQ(LEAD(0), Key_V, Key_N), go_sod },                   // LEAD V N → Start of document
    { LEADER_SEQ(LEAD(0), Key_V, Key_M), go_eod },                   // LEAD V M → End of document
    { LEADER_SEQ(LEAD(0), Key_V, Key_R), go_up_ten_lines },          // LEAD V R → Up 12 lines
    { LEADER_SEQ(LEAD(0), Key_V, Key_T), go_down_ten_lines },        // LEAD V T → Down 12 lines

    // === WINDOW MANAGEMENT ===
    { LEADER_SEQ(LEAD(0), Key_M, Key_S), screen_left },              // LEAD M S → Window left
    { LEADER_SEQ(LEAD(0), Key_M, Key_F), screen_right },             // LEAD M F → Window right
    { LEADER_SEQ(LEAD(0), Key_M, Key_E), screen_up },                // LEAD M E → Window up
    { LEADER_SEQ(LEAD(0), Key_M, Key_D), screen_down },              // LEAD M D → Window down
    { LEADER_SEQ(LEAD(0), Key_M, Key_M), screen_full }               // LEAD M M → Fullscreen
  );


// =============================================================================
// SETUP
// =============================================================================

void setup() {
  // --- Qukeys: Dual-function keys (tap = normal, hold = modifier) ---
  QUKEYS(
    // Row 2, Col 11 (/ key): Hold → Hyper (Ctrl+Cmd+Alt+Shift) for Karabiner
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 11), Key_Hyper),

    // Row 1, Col 10 (L key): Hold → Cmd+Shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 10), LSHIFT(Key_LeftGui)),

    // Row 1, Col 9 (K key): Hold → Alt+Shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 9), LSHIFT(Key_LeftAlt)),

    // Row 0, Col 9 (O key): Hold → Cmd
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 9), Key_LeftGui)
  )

  Kaleidoscope.setup();
  SpaceCadet.disable();           // Disable shift-as-parens (using Qukeys instead)
  EEPROMKeymap.setup(10);         // 10 layers available via Chrysalis
  Leader.dictionary = leader_dictionary;
}

// =============================================================================
// MAIN LOOP
// =============================================================================

void loop() {
  Kaleidoscope.loop();
}
