/**
 * ============================================================================
 * ATREUS_NOCHRYSALIS.ino - Complete Standalone Firmware
 * ============================================================================
 *
 * All functionality in firmware - NO Chrysalis/EEPROM needed.
 *
 * LAYERS:
 *   [0] QWERTY  - Default with dual-use keys
 *   [1] FUN     - Symbols, arrows, numpad
 *   [2] UPPER   - F-keys, navigation, media
 *   [3] MOUSE   - Mouse control, clipboard (Cmd+Z/X/C/V), numpad
 *
 * TAPDANCE (Double-tap shortcuts):
 *   ` ` → Cmd+Shift+V (Clipy paste)
 *   ; ; → Cmd+Tab (App Switcher)
 *   / / → Cmd+` (Window switch same app)
 *
 * DUAL-USE KEYS (Qukeys):
 *   R → tap=R, hold=Shift
 *   F → tap=F, hold=Layer1
 *   G → tap=G, hold=Shift
 *   H → tap=H, hold=Shift
 *   L → tap=L, hold=Cmd+Shift
 *   K → tap=K, hold=Alt+Shift
 *
 * LEADER KEY: Quote position (')
 *   LEAD + A → á, LEAD + E → é, etc.
 * ============================================================================
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "NoChrysalis build"
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include <Kaleidoscope-TapDance.h>
#include <Kaleidoscope-Leader.h>

// =============================================================================
// DEFINITIONS
// =============================================================================

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

// --- Macro IDs ---
enum {
  MACRO_VERSION_INFO
};

// --- TapDance IDs ---
enum {
  TD_TILDE,       // ` ` → Cmd+Shift+V (Clipy)
  TD_SEMICOLON,   // ; ; → Cmd+Tab (App Switcher)
  TD_SLASH        // / / → Cmd+` (Window switch)
};

// --- Symbol shortcuts ---
#define Key_Exclamation LSHIFT(Key_1)
#define Key_At LSHIFT(Key_2)
#define Key_Hash LSHIFT(Key_3)
#define Key_Dollar LSHIFT(Key_4)
#define Key_Percent LSHIFT(Key_5)
#define Key_Caret LSHIFT(Key_6)
#define Key_And LSHIFT(Key_7)
#define Key_Star LSHIFT(Key_8)
#define Key_Plus LSHIFT(Key_Equals)
#define Key_Tilde LSHIFT(Key_Backtick)
#define Key_LeftCurly LSHIFT(Key_LeftBracket)
#define Key_RightCurly LSHIFT(Key_RightBracket)

// --- Clipboard shortcuts ---
#define Key_CmdZ LGUI(Key_Z)
#define Key_CmdX LGUI(Key_X)
#define Key_CmdC LGUI(Key_C)
#define Key_CmdV LGUI(Key_V)

// --- Layer IDs ---
enum {
  QWERTY,
  FUN,
  UPPER,
  MOUSE
};

// =============================================================================
// KEYMAPS
// =============================================================================

/* *INDENT-OFF* */
KEYMAPS(

  // ---------------------------------------------------------------------------
  // LAYER 0: QWERTY
  // ---------------------------------------------------------------------------
  // TapDance: ` (TD_TILDE), ; (TD_SEMICOLON), / (TD_SLASH)
  // Leader: ' (Quote position)
  // Qukeys: R/G/H→Shift, F→Layer1, L→Cmd+Shift, K→Alt+Shift
  //
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E   ,Key_R   ,Key_T
      ,Key_A   ,Key_S   ,Key_D   ,Key_F   ,Key_G
      ,Key_Z   ,Key_X   ,Key_C   ,Key_V   ,Key_B         ,Key_LeftAlt
      ,Key_Esc ,TD(TD_TILDE) ,Key_LeftControl ,Key_LeftShift ,Key_Backspace ,Key_LeftGui

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,TD(TD_SEMICOLON)
       ,Key_Tab      ,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,TD(TD_SLASH)
       ,MO(FUN)      ,Key_Space ,Key_Minus  ,Key_Backslash ,LEAD(0)  ,Key_Enter
  ),

  // ---------------------------------------------------------------------------
  // LAYER 1: FUN - Symbols & Numpad
  // ---------------------------------------------------------------------------
  [FUN] = KEYMAP_STACKED
  (
       Key_Exclamation ,Key_At        ,Key_UpArrow   ,Key_Dollar    ,Key_Percent
      ,Key_LeftParen   ,Key_LeftArrow ,Key_DownArrow ,Key_RightArrow,Key_RightParen
      ,Key_LeftBracket ,Key_RightBracket ,Key_Hash   ,Key_LeftCurly ,Key_RightCurly ,Key_Caret
      ,MoveToLayer(QWERTY) ,TG(UPPER) ,TG(MOUSE)     ,Key_LeftShift ,Key_Delete     ,Key_LeftControl

                   ,Key_PageUp   ,Key_7 ,Key_8      ,Key_9 ,Key_Tilde
                   ,Key_0        ,Key_4 ,Key_5      ,Key_6 ,___
      ,Key_And     ,Key_Star     ,Key_1 ,Key_2      ,Key_3 ,Key_Plus
      ,Key_LeftAlt ,Key_Space    ,Key_KeypadDot ,Key_Minus ,Key_0 ,Key_Equals
   ),

  // ---------------------------------------------------------------------------
  // LAYER 2: UPPER - F-Keys & Navigation
  // ---------------------------------------------------------------------------
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
   ),

  // ---------------------------------------------------------------------------
  // LAYER 3: MOUSE - Mouse Control & Clipboard
  // ---------------------------------------------------------------------------
  [MOUSE] = KEYMAP_STACKED
  (
       ___              ,Key_mouseBtnL    ,Key_mouseUp      ,Key_mouseBtnR    ,___
      ,___              ,Key_mouseL       ,Key_mouseDn      ,Key_mouseR       ,___
      ,Key_CmdZ         ,Key_CmdX         ,Key_CmdC         ,Key_CmdV         ,___ ,___
      ,MoveToLayer(QWERTY) ,___           ,Key_LeftControl  ,Key_LeftShift    ,Key_Backspace ,Key_LeftGui

                ,Key_LeftArrow ,Key_Keypad7 ,Key_Keypad8 ,Key_Keypad9 ,Key_KeypadDivide
                ,Key_Keypad0   ,Key_Keypad4 ,Key_Keypad5 ,Key_Keypad6 ,Key_KeypadMultiply
      ,Key_UpArrow ,Key_RightArrow ,Key_Keypad1 ,Key_Keypad2 ,Key_Keypad3 ,Key_KeypadAdd
      ,Key_LeftArrow ,Key_DownArrow ,Key_KeypadDot ,Key_Minus ,Key_Keypad0 ,Key_Equals
   )
)
/* *INDENT-ON* */

// =============================================================================
// PLUGINS
// =============================================================================

KALEIDOSCOPE_INIT_PLUGINS(
  EEPROMSettings,
  Focus,
  Qukeys,
  TapDance,
  Leader,
  OneShot,
  Macros,
  MouseKeys
);

// =============================================================================
// MACROS
// =============================================================================

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
  case MACRO_VERSION_INFO:
    if (keyToggledOn(keyState)) {
      Macros.type(PSTR("Atreus NoChrysalis - "));
      Macros.type(PSTR(BUILD_INFORMATION));
    }
    break;
  }
  return MACRO_NONE;
}

// =============================================================================
// TAP DANCE
// =============================================================================
// Double-tap shortcuts (replaces Karabiner functionality)

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {

  case TD_TILDE:
    // ` → single=`, double=Cmd+Shift+V (Clipy)
    return tapDanceActionKeys(tap_count, tap_dance_action,
      Key_Backtick,
      LSHIFT(LGUI(Key_V)));

  case TD_SEMICOLON:
    // ; → single=;, double=Cmd+Tab (App Switcher)
    return tapDanceActionKeys(tap_count, tap_dance_action,
      Key_Semicolon,
      LGUI(Key_Tab));

  case TD_SLASH:
    // / → single=/, double=Cmd+` (Window switch)
    return tapDanceActionKeys(tap_count, tap_dance_action,
      Key_Slash,
      LGUI(Key_Backtick));
  }
}

// =============================================================================
// LEADER KEY SEQUENCES
// =============================================================================

// --- Portuguese Accents ---
static void accent_a(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(A))); }
static void accent_a_circ(uint8_t seq_index)  { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(A))); }
static void accent_a_til(uint8_t seq_index)   { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(A))); }
static void accent_e(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(E))); }
static void accent_e_circ(uint8_t seq_index)  { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(E))); }
static void accent_i(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(I))); }
static void accent_o(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(O))); }
static void accent_o_circ(uint8_t seq_index)  { Macros.play(MACRO(D(RightAlt),T(I),U(RightAlt),T(O))); }
static void accent_o_til(uint8_t seq_index)   { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(O))); }
static void accent_u(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(E),U(RightAlt),T(U))); }
static void accent_n(uint8_t seq_index)       { Macros.play(MACRO(D(RightAlt),T(N),U(RightAlt),T(N))); }
static void cedilla(uint8_t seq_index)        { Macros.play(MACRO(D(RightAlt),T(C),U(RightAlt))); }

// --- App Launchers ---
static void launch_alfred(uint8_t seq_index)    { Macros.play(MACRO(D(LeftAlt),D(LeftGui),D(LeftControl),T(A),U(LeftAlt),U(LeftGui),U(LeftControl))); }
static void launch_skitch(uint8_t seq_index)    { Macros.play(MACRO(D(LeftGui),D(LeftShift),T(5),U(LeftGui),U(LeftShift))); }
static void launch_emoticons(uint8_t seq_index) { Macros.play(MACRO(T(F17))); }

// --- Special Characters ---
static void click_backslash(uint8_t seq_index)     { Macros.play(MACRO(T(Backslash))); }
static void click_pipe(uint8_t seq_index)          { Macros.play(MACRO(T(Pipe))); }
static void click_open_question(uint8_t seq_index) { Macros.play(MACRO(D(LeftAlt),D(LeftShift),T(Slash),U(LeftAlt),U(LeftShift))); }

// --- Text Selection ---
static void select_and_copy_word(uint8_t seq_index) {
  Macros.play(MACRO(D(LeftAlt),T(LeftArrow),U(LeftAlt),D(LeftAlt),D(LeftShift),T(RightArrow),U(LeftShift),U(LeftAlt),D(LeftGui),T(C),U(LeftGui)));
}
static void select_and_copy_line(uint8_t seq_index) {
  Macros.play(MACRO(D(LeftGui),T(LeftArrow),U(LeftGui),D(LeftGui),D(LeftShift),T(RightArrow),U(LeftShift),U(LeftGui),D(LeftGui),T(C),U(LeftGui)));
}

// --- VI-Like Navigation ---
static void go_sol(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(LeftArrow),U(LeftGui))); }
static void go_eol(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(RightArrow),U(LeftGui))); }
static void go_sod(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(Home),U(LeftGui))); }
static void go_eod(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(End),U(LeftGui))); }
static void go_up_ten_lines(uint8_t seq_index) { Macros.play(MACRO(T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow),T(UpArrow))); }
static void go_down_ten_lines(uint8_t seq_index) { Macros.play(MACRO(T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow),T(DownArrow))); }

// --- Window Management ---
static void screen_left(uint8_t seq_index)  { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(LeftArrow),U(LeftGui),U(LeftAlt))); }
static void screen_right(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(RightArrow),U(LeftGui),U(LeftAlt))); }
static void screen_up(uint8_t seq_index)    { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(UpArrow),U(LeftGui),U(LeftAlt))); }
static void screen_down(uint8_t seq_index)  { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(DownArrow),U(LeftGui),U(LeftAlt))); }
static void screen_full(uint8_t seq_index)  { Macros.play(MACRO(D(LeftGui),D(LeftAlt),T(F),U(LeftGui),U(LeftAlt))); }

// --- Window Switching ---
static void change_window_same_app(uint8_t seq_index) { Macros.play(MACRO(D(LeftGui),T(Backtick),U(LeftGui))); }
static void alt_tab(uint8_t seq_index)                { Macros.play(MACRO(D(LeftGui),T(Tab),U(LeftGui))); }

// --- Leader Dictionary ---
static const kaleidoscope::plugin::Leader::dictionary_t leader_dictionary[] PROGMEM =
  LEADER_DICT(
    // Portuguese Accents
    { LEADER_SEQ(LEAD(0), Key_A), accent_a },
    { LEADER_SEQ(LEAD(0), LEAD(0), Key_A), accent_a_circ },
    { LEADER_SEQ(LEAD(0), LEAD(0), LEAD(0), Key_A), accent_a_til },
    { LEADER_SEQ(LEAD(0), Key_E), accent_e },
    { LEADER_SEQ(LEAD(0), LEAD(0), Key_E), accent_e_circ },
    { LEADER_SEQ(LEAD(0), Key_I), accent_i },
    { LEADER_SEQ(LEAD(0), Key_O), accent_o },
    { LEADER_SEQ(LEAD(0), LEAD(0), Key_O), accent_o_circ },
    { LEADER_SEQ(LEAD(0), LEAD(0), LEAD(0), Key_O), accent_o_til },
    { LEADER_SEQ(LEAD(0), Key_U), accent_u },
    { LEADER_SEQ(LEAD(0), Key_N), accent_n },
    { LEADER_SEQ(LEAD(0), Key_C), cedilla },
    // App Launchers
    { LEADER_SEQ(LEAD(0), Key_B), launch_alfred },
    { LEADER_SEQ(LEAD(0), Key_G, Key_N), launch_skitch },
    { LEADER_SEQ(LEAD(0), Key_G, Key_H), launch_emoticons },
    { LEADER_SEQ(LEAD(0), Key_G, Key_Y), alt_tab },
    { LEADER_SEQ(LEAD(0), Key_G, Key_T), change_window_same_app },
    // Special Characters
    { LEADER_SEQ(LEAD(0), Key_Slash), click_backslash },
    { LEADER_SEQ(LEAD(0), Key_Semicolon), click_pipe },
    { LEADER_SEQ(LEAD(0), Key_L), click_open_question },
    // Text Selection
    { LEADER_SEQ(LEAD(0), Key_Q, Key_W), select_and_copy_word },
    { LEADER_SEQ(LEAD(0), Key_Q, Key_E), select_and_copy_line },
    { LEADER_SEQ(LEAD(0), Key_Q, Key_Q), change_window_same_app },
    // VI-Like Navigation
    { LEADER_SEQ(LEAD(0), Key_V, Key_Y), go_sol },
    { LEADER_SEQ(LEAD(0), Key_V, Key_U), go_eol },
    { LEADER_SEQ(LEAD(0), Key_V, Key_N), go_sod },
    { LEADER_SEQ(LEAD(0), Key_V, Key_M), go_eod },
    { LEADER_SEQ(LEAD(0), Key_V, Key_R), go_up_ten_lines },
    { LEADER_SEQ(LEAD(0), Key_V, Key_T), go_down_ten_lines },
    // Window Management
    { LEADER_SEQ(LEAD(0), Key_M, Key_S), screen_left },
    { LEADER_SEQ(LEAD(0), Key_M, Key_F), screen_right },
    { LEADER_SEQ(LEAD(0), Key_M, Key_E), screen_up },
    { LEADER_SEQ(LEAD(0), Key_M, Key_D), screen_down },
    { LEADER_SEQ(LEAD(0), Key_M, Key_M), screen_full }
  );

// =============================================================================
// SETUP
// =============================================================================

void setup() {
  // Qukeys: Dual-function keys
  QUKEYS(
    // R → tap=R, hold=Shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 3), Key_LeftShift),
    // F → tap=F, hold=Layer1
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 3), ShiftToLayer(FUN)),
    // G → tap=G, hold=Shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 4), Key_LeftShift),
    // H → tap=H, hold=Shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 7), Key_LeftShift),
    // L → tap=L, hold=Cmd+Shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 10), LSHIFT(Key_LeftGui)),
    // K → tap=K, hold=Alt+Shift
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 9), LSHIFT(Key_LeftAlt))
  )

  Kaleidoscope.setup();
  Leader.dictionary = leader_dictionary;
}

// =============================================================================
// MAIN LOOP
// =============================================================================

void loop() {
  Kaleidoscope.loop();
}
