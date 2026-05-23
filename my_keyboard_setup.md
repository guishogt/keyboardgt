# My Keyboardio Atreus Setup

Standalone firmware for the Keyboardio Atreus keyboard, optimized for macOS with Portuguese accent support, window management, and productivity shortcuts.

**Firmware**: `Atreus_NoChrysalis/Atreus_NoChrysalis.ino` (NO Chrysalis needed)

---

## Table of Contents

1. [Layers](#layers)
2. [Dual-Use Keys (Qukeys)](#dual-use-keys-qukeys)
3. [TapDance (Double-Tap)](#tapdance-double-tap)
4. [Leader Key Sequences](#leader-key-sequences)
5. [Setup Instructions](#setup-instructions)

---

## Layers

### Layer 0: QWERTY (Default)

```
+----+----+----+----+----+     +----+----+----+----+----+
| Q  |W/L2| E  |R/Sh| T  |     | Y  | U  | I  | O  | P  |
+----+----+----+----+----+     +----+----+----+----+----+
| A  | S  | D  |F/L1|G/Sh|     |H/Sh| J  |K/AS|L/CS|LEAD|  <- LEADER KEY
+----+----+----+----+----+----+----+----+----+----+----+----+
| Z  | X  | C  | V  | B  |Alt |Tab | N  | M  | ,  | .  |//''|  // = Cmd+`
+----+----+----+----+----+----+----+----+----+----+----+----+
|Esc |`/''|Ctrl|Shft|Bksp|Cmd |MO1 |Spc |;//;;| -  | '  |Entr|  `` = Clipy
+----+----+----+----+----+----+----+----+----+----+----+----+
                                   ^^^
                              ;; = Cmd+Tab
```

**Dual-Use Keys:**
| Key | Tap | Hold |
|-----|-----|------|
| W | w | Layer 2 (UPPER) |
| R | r | Shift |
| F | f | Layer 1 (FUN) |
| G | g | Shift |
| H | h | Shift |
| K | k | Alt+Shift |
| L | l | Cmd+Shift |

---

### Layer 1: FUN (Symbols + Numbers)

Access by: **Hold F** or **Hold MO1 thumb key**

```
+----+----+----+----+----+     +----+----+----+----+----+
| !  | @  | Up | $  | %  |     |PgUp| 7  | 8  | 9  | ~  |
+----+----+----+----+----+     +----+----+----+----+----+
| (  | Lt | Dn | Rt | )  |     | 0  | 4  | 5  | 6  |    |
+----+----+----+----+----+----+----+----+----+----+----+----+
| [  | ]  | #  | {  | }  | ^  | &  | *  | 1  | 2  | 3  | +  |
+----+----+----+----+----+----+----+----+----+----+----+----+
|L0  |TG2 |TG3 |Shft|Del |Ctrl|Alt |Spc | .  | -  | 0  | =  |
+----+----+----+----+----+----+----+----+----+----+----+----+
 ^    ^    ^
 L0=QWERTY, TG2=Lock UPPER, TG3=Lock MOUSE
```

---

### Layer 2: UPPER (F-Keys + Navigation)

Access by: **Hold W** or **TG2 from Layer 1**

```
+----+----+----+----+----+     +----+----+----+----+----+
|Ins |Home| Up |End |PgUp|     |F10 | F7 | F8 | F9 |    |
+----+----+----+----+----+     +----+----+----+----+----+
|Del | Lt | Dn | Rt |PgDn|     |F11 | F4 | F5 | F6 |    |
+----+----+----+----+----+----+----+----+----+----+----+----+
|Ver |Vol+|    |    |    |    |F12 | F1 | F2 | F3 |    |    |
+----+----+----+----+----+----+----+----+----+----+----+----+
|L0  |Vol-|    |    |    |    |    |    |L0  |PrSc|ScrL|Play|
+----+----+----+----+----+----+----+----+----+----+----+----+
```

**F-Key Access (Hold W + ...):**
| W + Key | Output |
|---------|--------|
| W + Y | F10 |
| W + U | F7 |
| W + I | F8 |
| W + O | F9 |
| W + H | F11 |
| W + J | F4 |
| W + K | F5 |
| W + L | F6 |
| W + N | F12 |
| W + M | F1 |
| W + , | F2 |
| W + . | F3 |

---

### Layer 3: MOUSE (Mouse + Clipboard)

Access by: **TG3 from Layer 1**

```
+----+----+----+----+----+     +----+----+----+----+----+
|    |MsLB|MsUp|MsRB|    |     | Lt |Kp7 |Kp8 |Kp9 | /  |
+----+----+----+----+----+     +----+----+----+----+----+
|    |MsLt|MsDn|MsRt|    |     |Kp0 |Kp4 |Kp5 |Kp6 | *  |
+----+----+----+----+----+----+----+----+----+----+----+----+
|CmdZ|CmdX|CmdC|CmdV|    |    | Up | Rt |Kp1 |Kp2 |Kp3 | +  |
+----+----+----+----+----+----+----+----+----+----+----+----+
|L0  |    |Ctrl|Shft|Bksp|Cmd | Lt | Dn |Kp. | -  |Kp0 | =  |
+----+----+----+----+----+----+----+----+----+----+----+----+
```

---

## Dual-Use Keys (Qukeys)

| Key | Tap | Hold |
|-----|-----|------|
| W | w | Layer 2 (UPPER) |
| R | r | Shift |
| F | f | Layer 1 (FUN) |
| G | g | Shift |
| H | h | Shift |
| K | k | Alt+Shift |
| L | l | Cmd+Shift |

---

## TapDance (Double-Tap)

These are in the firmware (no Karabiner needed):

| Key | Single Tap | Double Tap |
|-----|------------|------------|
| ` (next to Esc) | Backtick | Cmd+Shift+V (Clipy paste) |
| ; (thumb row) | Semicolon | Cmd+Tab (App Switcher) |
| / (bottom right) | Slash | Cmd+` (Window switch same app) |

---

## Leader Key Sequences

**Leader key is after L on home row** (right pinky position).

Press Leader, then type a sequence:

### Portuguese Accents

| Sequence | Output |
|----------|--------|
| LEAD + A | a |
| LEAD + LEAD + A | a |
| LEAD + LEAD + LEAD + A | a |
| LEAD + E | e |
| LEAD + LEAD + E | e |
| LEAD + I | i |
| LEAD + O | o |
| LEAD + LEAD + O | o |
| LEAD + LEAD + LEAD + O | o |
| LEAD + U | u |
| LEAD + N | n |
| LEAD + C | c |

### App Launchers

| Sequence | Action |
|----------|--------|
| LEAD + B | Alfred (Cmd+Alt+Ctrl+A) |
| LEAD + G + N | Screenshot (Cmd+Shift+5) |
| LEAD + G + H | Emoji picker (F17) |
| LEAD + G + Y | App Switcher (Cmd+Tab) |
| LEAD + G + T | Window switch same app (Cmd+`) |

### Special Characters

| Sequence | Output |
|----------|--------|
| LEAD + / | \ (backslash) |
| LEAD + ; | \| (pipe) |
| LEAD + L | ? (inverted question) |

### Text Selection

| Sequence | Action |
|----------|--------|
| LEAD + Q + W | Select word + Copy |
| LEAD + Q + E | Select line + Copy |

### VI-Like Navigation

| Sequence | Action |
|----------|--------|
| LEAD + V + Y | Start of line (Cmd+Left) |
| LEAD + V + U | End of line (Cmd+Right) |
| LEAD + V + N | Start of document |
| LEAD + V + M | End of document |
| LEAD + V + R | Up 12 lines |
| LEAD + V + T | Down 12 lines |

### Window Management

| Sequence | Action |
|----------|--------|
| LEAD + M + S | Window left half |
| LEAD + M + F | Window right half |
| LEAD + M + E | Window top half |
| LEAD + M + D | Window bottom half |
| LEAD + M + M | Window fullscreen |

---

## Setup Instructions

### Flash Firmware

1. Open `Atreus_NoChrysalis/Atreus_NoChrysalis.ino` in Arduino IDE
2. Select board: **Keyboardio Atreus**
3. Connect keyboard via USB
4. Press reset button on keyboard
5. Click **Upload**

**Note:** This firmware does NOT use Chrysalis. All settings are in the code.

---

## Quick Reference

```
DUAL-USE KEYS:    Hold W = Layer 2 (F-keys)
                  Hold F = Layer 1 (symbols/numbers)
                  Hold R/G/H = Shift
                  Hold L = Cmd+Shift
                  Hold K = Alt+Shift

DOUBLE-TAP:       ` ` = Clipy paste
                  ; ; = App Switcher
                  / / = Window switch

LEADER KEY:       After L on home row
                  LEAD + vowel = accent
                  LEAD + B = Alfred
                  LEAD + G + H = Emoji
                  LEAD + M + ... = Window management

F-KEYS:           Hold W + J/K/L = F4/F5/F6
                  Hold W + U/I/O = F7/F8/F9
                  Hold W + Y/H/N = F10/F11/F12
                  Hold W + M/,/. = F1/F2/F3
```

---

*Last updated: 2026-05-23*
