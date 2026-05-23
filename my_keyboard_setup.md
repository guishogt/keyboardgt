# My Keyboardio Atreus Setup

Custom firmware and Chrysalis configuration for the Keyboardio Atreus keyboard, optimized for macOS with Portuguese accent support, window management, and productivity shortcuts.

---

## Table of Contents

1. [Overview](#overview)
2. [How It Works](#how-it-works)
3. [Layers](#layers)
4. [Dual-Use Keys (Tap vs Hold)](#dual-use-keys-tap-vs-hold)
5. [Leader Key Sequences](#leader-key-sequences)
6. [Setup Instructions](#setup-instructions)
7. [Files Reference](#files-reference)

---

## Overview

This setup combines:
- **Firmware** (`Atreus__LF/Atreus__LF.ino`) - Compiled and flashed via Arduino IDE
- **EEPROM Configuration** (`2026.05.22_atreus.json`) - Loaded via Chrysalis app

The firmware defines plugins and macros (Leader sequences, TapDance, etc.), while Chrysalis configures the actual keymap stored in EEPROM.

---

## How It Works

### Components

| Component | Purpose | Tool |
|-----------|---------|------|
| Kaleidoscope | Keyboard firmware framework | Arduino IDE |
| Chrysalis | GUI keymap editor | Chrysalis app |
| EEPROM | Stores keymap on keyboard | Persists between flashes |
| Karabiner | macOS key remapping (optional) | Karabiner-Elements |

### Workflow

1. Flash firmware once (defines available features)
2. Use Chrysalis to edit keymap (no reflashing needed)
3. Export Chrysalis config as JSON for backup

---

## Layers

### Layer 0: QWERTY (Default)

Main typing layer with dual-use modifier keys.

```
┌─────┬─────┬─────┬─────┬─────┐          ┌─────┬─────┬─────┬─────┬─────┐
│  Q  │  W  │  E  │ R/⇧ │  T  │          │  Y  │  U  │  I  │  O  │  P  │
├─────┼─────┼─────┼─────┼─────┤          ├─────┼─────┼─────┼─────┼─────┤
│  A  │  S  │  D  │ F/L1│ G/⇧ │          │ H/⇧ │  J  │  K  │  L  │LEAD │
├─────┼─────┼─────┼─────┼─────┼─────┐┌───┼─────┼─────┼─────┼─────┼─────┤
│  Z  │  X  │  C  │  V  │  B  │ Alt ││Tab│  N  │  M  │  ,  │  .  │  /  │
├─────┼─────┼─────┼─────┼─────┼─────┤├───┼─────┼─────┼─────┼─────┼─────┤
│ Esc │  `  │ Ctrl│ ⇧   │ Bksp│ Cmd ││ L1│Space│  ;  │  -  │  '  │Enter│
└─────┴─────┴─────┴─────┴─────┴─────┘└───┴─────┴─────┴─────┴─────┴─────┘
```

**Special Keys on Layer 0:**

| Key | Tap | Hold |
|-----|-----|------|
| `R` | r | Shift |
| `F` | f | Layer 1 (FUN) |
| `G` | g | Shift |
| `H` | h | Shift |
| `;` position | **Leader Key** | — |
| Bottom-left thumb | — | Layer 1 (momentary) |

---

### Layer 1: FUN (Symbols + Numpad)

Access by holding `F` or the Layer 1 thumb key.

```
┌─────┬─────┬─────┬─────┬─────┐          ┌─────┬─────┬─────┬─────┬─────┐
│  !  │  @  │  ↑  │  $  │  %  │          │PgUp │  7  │  8  │  9  │  ~  │
├─────┼─────┼─────┼─────┼─────┤          ├─────┼─────┼─────┼─────┼─────┤
│  (  │  ←  │  ↓  │  →  │  )  │          │  0  │  4  │  5  │  6  │     │
├─────┼─────┼─────┼─────┼─────┼─────┐┌───┼─────┼─────┼─────┼─────┼─────┤
│  [  │  ]  │  #  │  {  │  }  │  ^  ││ & │  *  │  1  │  2  │  3  │  +  │
├─────┼─────┼─────┼─────┼─────┼─────┤├───┼─────┼─────┼─────┼─────┼─────┤
│ →L0 │Lock2│Lock3│ ⇧   │ Del │ Ctrl││Alt│Space│  .  │  -  │  0  │  =  │
└─────┴─────┴─────┴─────┴─────┴─────┘└───┴─────┴─────┴─────┴─────┴─────┘
```

**Layer Switching from FUN:**

| Key | Action |
|-----|--------|
| Bottom-left corner | Move to Layer 0 (QWERTY) |
| Second from left | **Lock to Layer 2** (UPPER) |
| Third from left | **Lock to Layer 3** (Mouse) |

---

### Layer 2: UPPER (F-Keys + Navigation)

Access by pressing Lock #2 from Layer 1.

```
┌─────┬─────┬─────┬─────┬─────┐          ┌─────┬─────┬─────┬─────┬─────┐
│ Ins │Home │  ↑  │ End │PgUp │          │  ↑  │ F7  │ F8  │ F9  │ F10 │
├─────┼─────┼─────┼─────┼─────┤          ├─────┼─────┼─────┼─────┼─────┤
│ Del │  ←  │  ↓  │  →  │PgDn │          │  ↓  │ F4  │ F5  │ F6  │ F11 │
├─────┼─────┼─────┼─────┼─────┼─────┐┌───┼─────┼─────┼─────┼─────┼─────┤
│Macro│ Vol+│     │     │     │     ││   │     │ F1  │ F2  │ F3  │ F12 │
├─────┼─────┼─────┼─────┼─────┼─────┤├───┼─────┼─────┼─────┼─────┼─────┤
│ →L0 │ Vol-│     │     │     │     ││   │     │ →L0 │PrScn│ScrLk│ ⏯  │
└─────┴─────┴─────┴─────┴─────┴─────┘└───┴─────┴─────┴─────┴─────┴─────┘
```

**Special Keys:**

| Key | Action |
|-----|--------|
| Macro (Z position) | Types firmware version info |
| Vol+ / Vol- | Volume control |
| ⏯ | Play/Pause media |
| →L0 | Return to Layer 0 |

---

### Layer 3: Mouse + Clipboard

Access by pressing Lock #3 from Layer 1. Provides mouse control and common clipboard shortcuts.

```
┌─────┬─────┬─────┬─────┬─────┐          ┌─────┬─────┬─────┬─────┬─────┐
│     │M.Lft│M. ↑ │M.Rgt│     │          │  ←  │ KP7 │ KP8 │ KP9 │ KP/ │
├─────┼─────┼─────┼─────┼─────┤          ├─────┼─────┼─────┼─────┼─────┤
│     │M. ← │M. ↓ │M. → │     │          │ KP0 │ KP4 │ KP5 │ KP6 │ KP* │
├─────┼─────┼─────┼─────┼─────┼─────┐┌───┼─────┼─────┼─────┼─────┼─────┤
│⌘+Z  │⌘+X  │⌘+C  │⌘+V  │     │     ││ ↑ │  →  │ KP1 │ KP2 │ KP3 │ KP+ │
├─────┼─────┼─────┼─────┼─────┼─────┤├───┼─────┼─────┼─────┼─────┼─────┤
│ →L0 │     │ Ctrl│ ⇧   │ Bksp│ Cmd ││ ← │  ↓  │ KP. │  -  │ KP0 │  =  │
└─────┴─────┴─────┴─────┴─────┴─────┘└───┴─────┴─────┴─────┴─────┴─────┘
```

**Layer 3 Features:**

| Key | Action |
|-----|--------|
| M.Lft / M.Rgt | Mouse left/right click |
| M. ↑↓←→ | Mouse cursor movement |
| ⌘+Z | Undo |
| ⌘+X | Cut |
| ⌘+C | Copy |
| ⌘+V | Paste |
| KP0-9 | Numpad digits |

---

## Dual-Use Keys (Tap vs Hold)

These keys perform different actions depending on whether you tap or hold them.

### From Firmware (Qukeys)

Defined in `Atreus__LF.ino`, always active:

| Key Position | Tap | Hold | Notes |
|--------------|-----|------|-------|
| L (home row) | `l` | **Cmd+Shift** | Quick access to shifted commands |
| K (home row) | `k` | **Alt+Shift** | For app-specific shortcuts |
| `/` (bottom-right) | `/` or `?` | **Hyper** (Ctrl+Cmd+Alt+Shift) | For Karabiner mappings |
| O position | `o` | **Cmd** | Quick command key |

> **Note:** The `/` key is at the far right of the third row (right hand). Tap for `/`, Shift+tap for `?`, or hold for Hyper.

### From Chrysalis (EEPROM)

Configured in Chrysalis, editable without reflashing:

| Key | Tap | Hold |
|-----|-----|------|
| R | `r` | Shift |
| F | `f` | **Layer 1** (FUN) |
| G | `g` | Shift |
| H | `h` | Shift |

---

## Leader Key Sequences

The **Leader key** is mapped to the `;` position (right hand, home row, pinky).

Press Leader, then type a sequence to trigger an action.

### Portuguese Accents

| Sequence | Output | Description |
|----------|--------|-------------|
| `LEAD` → `A` | á | A with acute |
| `LEAD` → `LEAD` → `A` | â | A with circumflex |
| `LEAD` → `LEAD` → `LEAD` → `A` | ã | A with tilde |
| `LEAD` → `E` | é | E with acute |
| `LEAD` → `LEAD` → `E` | ê | E with circumflex |
| `LEAD` → `I` | í | I with acute |
| `LEAD` → `O` | ó | O with acute |
| `LEAD` → `LEAD` → `O` | ô | O with circumflex |
| `LEAD` → `LEAD` → `LEAD` → `O` | õ | O with tilde |
| `LEAD` → `U` | ú | U with acute |
| `LEAD` → `N` | ñ | N with tilde |
| `LEAD` → `C` | ç | C with cedilla |

### App Launchers (macOS)

| Sequence | Action | Shortcut Sent |
|----------|--------|---------------|
| `LEAD` → `B` | Launch Alfred | Ctrl+Cmd+Alt+A |
| `LEAD` → `G` → `N` | Screenshot (Skitch) | Cmd+Shift+5 |
| `LEAD` → `G` → `H` | Emoji picker | F17 |
| `LEAD` → `G` → `Y` | App Switcher | Cmd+Tab |
| `LEAD` → `G` → `T` | Window Switcher (same app) | Cmd+` |

### Special Characters

| Sequence | Output |
|----------|--------|
| `LEAD` → `/` | `\` (backslash) |
| `LEAD` → `;` | `\|` (pipe) |
| `LEAD` → `L` | `¿` (inverted question) |

### Text Selection & Clipboard

| Sequence | Action |
|----------|--------|
| `LEAD` → `Q` → `W` | Select word under cursor + Copy |
| `LEAD` → `Q` → `E` | Select entire line + Copy |
| `LEAD` → `Q` → `Q` | Switch windows in same app |

### VI-Like Navigation

| Sequence | Action | macOS Shortcut |
|----------|--------|----------------|
| `LEAD` → `V` → `Y` | Go to start of line | Cmd+← |
| `LEAD` → `V` → `U` | Go to end of line | Cmd+→ |
| `LEAD` → `V` → `N` | Go to start of document | Cmd+Home |
| `LEAD` → `V` → `M` | Go to end of document | Cmd+End |
| `LEAD` → `V` → `R` | Move up 12 lines | ↑×12 |
| `LEAD` → `V` → `T` | Move down 12 lines | ↓×12 |

### Window Management

Requires a window manager app (Rectangle, Magnet, BetterSnapTool, etc.)

| Sequence | Action | Shortcut Sent |
|----------|--------|---------------|
| `LEAD` → `M` → `S` | Window → Left half | Cmd+Alt+← |
| `LEAD` → `M` → `F` | Window → Right half | Cmd+Alt+→ |
| `LEAD` → `M` → `E` | Window → Top half | Cmd+Alt+↑ |
| `LEAD` → `M` → `D` | Window → Bottom half | Cmd+Alt+↓ |
| `LEAD` → `M` → `M` | Window → Fullscreen | Cmd+Alt+F |

---

## Karabiner Double-Tap Shortcuts

These shortcuts are configured in **Karabiner-Elements** (`~/.config/karabiner/karabiner.json`), not in the keyboard firmware. They work by detecting two quick taps within 250ms.

| Double-Tap | Action | Shortcut Sent |
|------------|--------|---------------|
| `` ` ` `` | Paste from Clipy (clipboard history) | Cmd+Shift+V |
| `; ;` | App Switcher | Cmd+Tab |
| `/ /` | Switch window (same app) | Cmd+` |

### How They Work

1. **First tap** - Sets a variable and starts a 250ms timer
2. **Second tap within 250ms** - Triggers the action
3. **No second tap** - Types the normal character

### Other Karabiner Settings

| Setting | Description |
|---------|-------------|
| F6 → F17 | Remapped globally (for emoji picker) |
| Cmd ↔ Option swap | On one specific external keyboard |

---

## Hammerspoon Shortcuts

These shortcuts use the **Hyper key** (Ctrl+Cmd+Alt+Shift), which you trigger by holding the `/` key on the Atreus (via Qukeys).

Config: `~/.hammerspoon/init.lua`

### App Focus/Launch (Hyper + key)

| Hyper + | Action |
|---------|--------|
| F | Focus or open **Finder** |
| M | Focus or open **Messages** |
| S | Focus or open **Slack** |
| B | Focus or open **Bear** |
| C | Focus **Google Chrome** |
| T | Focus **Microsoft Teams** |

### Window Management (Hyper + key)

| Hyper + | Action |
|---------|--------|
| Z | **Fullscreen** current window |
| O | Move window to **next screen** |
| P | **Clipboard history** (ClipboardTool) |

---

## Setup Instructions

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) (2.x recommended)
- [Kaleidoscope](https://github.com/keyboardio/Kaleidoscope) library
- [Chrysalis](https://github.com/keyboardio/Chrysalis/releases) app
- macOS (for the shortcuts to work as intended)

### Step 1: Install Kaleidoscope

```bash
# Clone the Kaleidoscope repository
git clone https://github.com/keyboardio/Kaleidoscope.git

# Or install via Arduino Library Manager
```

Follow the [Kaleidoscope setup guide](https://kaleidoscope.readthedocs.io/en/latest/setup_toolchain.html).

### Step 2: Flash the Firmware

1. Open `Atreus__LF/Atreus__LF.ino` in Arduino IDE
2. Select board: **Keyboardio Atreus**
3. Connect keyboard via USB
4. Press the physical reset button on the keyboard
5. Click **Upload**

### Step 3: Load Chrysalis Configuration

1. Open Chrysalis app
2. Connect to your Atreus
3. Go to **File → Import** or **Layout → Import**
4. Select `2026.05.22_atreus.json`
5. Click **Save to keyboard**

### Step 4: Configure macOS Apps (Optional)

#### For Window Management
Install one of:
- [Rectangle](https://rectangleapp.com/) (free)
- [Magnet](https://magnet.crowdcafe.com/) (paid)
- [BetterSnapTool](https://folivora.ai/bettersnaptool) (paid)

Configure shortcuts to match:
- `Cmd+Alt+←` → Left half
- `Cmd+Alt+→` → Right half
- `Cmd+Alt+↑` → Top half
- `Cmd+Alt+↓` → Bottom half
- `Cmd+Alt+F` → Fullscreen

#### For Alfred
Set Alfred hotkey to `Ctrl+Cmd+Alt+A`

#### For Emoji Picker
Map F17 to emoji picker in System Settings → Keyboard → Shortcuts, or use Karabiner.

#### For Hyper Key (Karabiner)
The Hyper key (Ctrl+Cmd+Alt+Shift) can be used with Karabiner-Elements to trigger custom actions.

---

## Files Reference

| File | Purpose |
|------|---------|
| `Atreus__LF/Atreus__LF.ino` | Main firmware source code |
| `2026.05.22_atreus.json` | Chrysalis keymap export (EEPROM config) |
| `Atreus__LF/Model100/Model100.ino` | Separate firmware for Model 100 keyboard |
| `chrysalis/*.json` | Archived Chrysalis configurations |
| `config/karabiner.json` | Karabiner double-tap shortcuts |
| `config/hammerspoon_init.lua` | Hammerspoon Hyper key shortcuts |
| `install.md` | Installation instructions for new machines |

**Note:** The config files are symlinked from their original locations:
- `~/.config/karabiner/karabiner.json` → `config/karabiner.json`
- `~/.hammerspoon/init.lua` → `config/hammerspoon_init.lua`

---

## Quick Reference Card

```
LEADER KEY: ; (right pinky, home row)

ACCENTS:          LEAD + vowel     = acute (á é í ó ú)
                  LEAD + LEAD + vowel = circumflex (â ê ô)
                  LEAD + LEAD + LEAD + A/O = tilde (ã õ)
                  LEAD + N = ñ,  LEAD + C = ç

NAVIGATION:       LEAD + V + Y = start of line
                  LEAD + V + U = end of line
                  LEAD + V + N = start of doc
                  LEAD + V + M = end of doc

WINDOWS:          LEAD + M + S/F/E/D = left/right/up/down half
                  LEAD + M + M = fullscreen

CLIPBOARD:        LEAD + Q + W = select+copy word
                  LEAD + Q + E = select+copy line

APPS:             LEAD + B = Alfred
                  LEAD + G + N = Screenshot
                  LEAD + G + H = Emoji

SPECIAL CHARS:    LEAD + / = backslash
                  LEAD + ; = pipe
                  LEAD + L = ¿

HOLD BEHAVIORS:   Hold F = Layer 1 (symbols/numpad)
                  Hold R/G/H = Shift
                  Hold L = Cmd+Shift
                  Hold K = Alt+Shift

DOUBLE-TAP:       ` ` = Paste from Clipy (Cmd+Shift+V)
(Karabiner)       ; ; = App Switcher (Cmd+Tab)
                  / / = Window in same app (Cmd+`)

HYPER KEY:        Hold / = Hyper (Ctrl+Cmd+Alt+Shift)
(Hammerspoon)     Hyper+F = Finder    Hyper+M = Messages
                  Hyper+S = Slack     Hyper+B = Bear
                  Hyper+C = Chrome    Hyper+T = Teams
                  Hyper+Z = Fullscreen window
                  Hyper+O = Move window to next screen
                  Hyper+P = Clipboard history
```

---

## Troubleshooting

### Leader sequences not working
- Ensure firmware is flashed (not just Chrysalis config)
- Leader key must be pressed and released, then type the sequence
- There's a timeout - type the sequence within ~1 second

### Accents producing wrong characters
- Ensure macOS keyboard is set to **U.S.** or **ABC**
- The accent macros use dead keys via `RightAlt`

### Dual-use keys not responding to hold
- Qukeys have a timing threshold
- Hold for ~200ms to trigger the hold behavior
- If typing fast, the tap behavior triggers

### Chrysalis shows different layout than expected
- The JSON file must be imported after connecting
- Check that you saved to keyboard (not just to file)

---

*Last updated: 2026-05-22*
?