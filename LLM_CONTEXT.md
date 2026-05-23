# LLM Context File - Atreus Keyboard Project

## Last Updated: 2026-05-23

## Current Status: WORKING

Firmware: `Atreus_NoChrysalis/Atreus_NoChrysalis.ino`

---

## Project Structure

```
Arduino/
├── Atreus__LF/
│   └── Atreus__LF.ino          # Original firmware WITH Chrysalis (NOT USED)
├── Atreus_NoChrysalis/
│   └── Atreus_NoChrysalis.ino  # Standalone firmware (RECOMMENDED)
├── config/
│   ├── karabiner.json          # Symlinked to ~/.config/karabiner/karabiner.json
│   └── hammerspoon_init.lua    # Symlinked to ~/.hammerspoon/init.lua
├── my_keyboard_setup.md        # User documentation
├── install.md                  # Setup instructions
├── LLM_CONTEXT.md              # This file
└── 2026.05.22_atreus.json      # Chrysalis export (reference only)
```

---

## Current Firmware Features

### Dual-Use Keys (Qukeys)

| Key | Position | Tap | Hold |
|-----|----------|-----|------|
| W | (0, 1) | w | Layer 2 (UPPER) |
| R | (0, 3) | r | Shift |
| F | (1, 3) | f | Layer 1 (FUN) |
| G | (1, 4) | g | Shift |
| H | (1, 7) | h | Shift |
| K | (1, 9) | k | Alt+Shift |
| L | (1, 10) | l | Cmd+Shift |

### TapDance (Double-Tap)

| Key | Position | Single Tap | Double Tap |
|-----|----------|------------|------------|
| ` | Thumb row left | Backtick | Cmd+Shift+V (Clipy) |
| ; | Thumb row right | Semicolon | Cmd+Tab (App Switcher) |
| / | Bottom row right | Slash | Cmd+` (Window switch) |

### Leader Key

Position: After L on home row (position 23)

---

## Layer Summary

### Layer 0: QWERTY
- Standard QWERTY with dual-use keys
- TapDance on `, ;, /
- Leader key after L

### Layer 1: FUN (hold F or MO1)
- Symbols: ! @ # $ % ^ & * ( ) [ ] { }
- Numbers: 0-9
- Arrows on WASD position
- Tilde (~) on P position (uses macro)

### Layer 2: UPPER (hold W or TG2)
- F-keys reorganized:
  - Right top: F10, F7, F8, F9
  - Right home: F11, F4, F5, F6
  - Right row 2: F12, F1, F2, F3
- Navigation on left side
- Volume controls
- Media keys

### Layer 3: MOUSE (TG3)
- Mouse movement and buttons
- Clipboard shortcuts (Cmd+Z/X/C/V)
- Numpad

---

## Key Technical Details

### Tilde Key Fix
The ~ key on Layer 1 (FUN+P position) uses a macro:
```cpp
case MACRO_TILDE:
  if (keyToggledOn(keyState)) {
    Macros.tap(LSHIFT(Key_Backtick));
  }
  break;
```
Direct `LSHIFT(Key_Backtick)` in keymap didn't work; macro approach is required.

### Why TapDance doesn't work with Chrysalis
EEPROMKeymap plugin overrides firmware keymap. Use `Atreus_NoChrysalis` firmware instead.

---

## Common Issues

### Multiple .ino files error
Arduino compiles ALL .ino files in a folder. Keep each firmware in its own folder.

### Port busy error
Close Chrysalis before uploading.

### Key outputs wrong character
Check keyboard layout in OS (should be US).

---

## Recent Changes (2026-05-23)

1. Fixed Leader key position (moved back to after L on home row)
2. Fixed tilde (~) key using macro approach
3. Added W as dual-use key (hold = Layer 2)
4. Reorganized Layer 2 F-keys for better ergonomics
5. Fixed thumb row: semicolon and hyphen positions
