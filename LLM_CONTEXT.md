# LLM Context File - Atreus Keyboard Project

## Last Updated: 2026-05-23

## Current Status: WORKING

The firmware `Atreus_NoChrysalis/Atreus_NoChrysalis.ino` is verified against the
Chrysalis export `2026.05.22_atreus.json` and all keys are correctly mapped.

---

## Project Structure

```
Arduino/
├── Atreus__LF/
│   └── Atreus__LF.ino          # Original firmware WITH Chrysalis support
├── Atreus_NoChrysalis/
│   └── Atreus_NoChrysalis.ino  # Standalone firmware WITHOUT EEPROM (RECOMMENDED)
├── config/
│   ├── karabiner.json          # Symlinked to ~/.config/karabiner/karabiner.json
│   └── hammerspoon_init.lua    # Symlinked to ~/.hammerspoon/init.lua
├── my_keyboard_setup.md        # Keyboard documentation
├── install.md                  # Setup instructions
├── LLM_CONTEXT.md              # This file
└── 2026.05.22_atreus.json      # Chrysalis keymap export (reference)
```

---

## Two Firmware Options

### Option 1: `Atreus__LF/Atreus__LF.ino` (NOT RECOMMENDED)
- Uses EEPROMKeymap - keymap stored in EEPROM
- Works with Chrysalis GUI for editing
- TapDance DOES NOT work (EEPROM overrides firmware keymap)

### Option 2: `Atreus_NoChrysalis/Atreus_NoChrysalis.ino` (RECOMMENDED)
- All keymap hardcoded in firmware
- NO Chrysalis support
- TapDance WORKS
- Contains all functionality from Chrysalis export
- Fully documented with visual key layouts

---

## TapDance Implementation

Currently in `Atreus_NoChrysalis.ino`:

| Key | Position | Single tap | Double tap |
|-----|----------|------------|------------|
| ` | Thumb row (left) | Backtick | Cmd+Shift+V (Clipy) |
| ; | Home row (after L) | Semicolon | Cmd+Tab (App Switcher) |
| / | Bottom row (right) | Slash | Cmd+` (Window switch) |

---

## Layer 0 Thumb Row (Right Side) - Critical Reference

Position order: `[MO(FUN)] [Space] [;] [-] [LEAD] [Enter]`

```
Position 42: MO(FUN)       - Hold for Layer 1
Position 43: Key_Space     - Space
Position 44: Key_Semicolon - Semicolon (plain, not TapDance)
Position 45: Key_Minus     - Hyphen/Minus
Position 46: LEAD(0)       - Leader key (for accents)
Position 47: Key_Enter     - Enter
```

---

## Key Technical Details

- **Keyboard**: Keyboardio Atreus
- **Firmware**: Kaleidoscope
- **Plugins used**: Qukeys, Leader, TapDance, MouseKeys, Macros

### Why TapDance doesn't work with Chrysalis:
The EEPROMKeymap plugin overrides the firmware keymap at runtime. When you put
`TD(TD_SOMETHING)` in the firmware keymap, EEPROM replaces it with whatever key
is stored in EEPROM (from Chrysalis).

### To add a new TapDance key:
1. Add enum value: `enum { TD_EXISTING, TD_NEW };`
2. Add to keymap: `TD(TD_NEW)` at desired position
3. Add case in `tapDanceAction()`:
```cpp
case TD_NEW:
  return tapDanceActionKeys(tap_count, tap_dance_action,
    Key_SingleTap, MODIFIER(Key_DoubleTap));
```

---

## Common Issues

### Multiple .ino files error
Arduino compiles ALL .ino files in a folder together. Never put two .ino files
in the same folder. Each firmware must be in its own folder.

### Port busy error
Close Chrysalis before uploading firmware.

### TapDance not working
If using Chrysalis-compatible firmware, TapDance won't work. Use the
`Atreus_NoChrysalis` firmware instead.

---

## Pending Tasks

- User mentioned wanting `yy` double-tap shortcut but hasn't specified action
