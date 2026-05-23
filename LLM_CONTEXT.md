# LLM Context File - Atreus Keyboard Project

## Current Issue (2026-05-23)

**Problem**: Compilation error due to multiple `.ino` files in the same folder.

Arduino IDE compiles ALL `.ino` files in a folder together, causing:
```
error: redefinition of 'void setup()'
error: redefinition of 'void loop()'
```

**Files causing conflict**:
- `Atreus__LF/Atreus__LF.ino` - Original firmware WITH Chrysalis/EEPROM support
- `Atreus__LF/Atreus__LF_full.ino` - Should NOT exist here (duplicate)

**Solution**: Delete `Atreus__LF_full.ino` from `Atreus__LF/` folder. The standalone firmware lives in `Atreus_NoChrysalis/`.

---

## Project Structure

```
Arduino/
├── Atreus__LF/
│   └── Atreus__LF.ino          # Original firmware WITH Chrysalis support
├── Atreus_NoChrysalis/
│   └── Atreus_NoChrysalis.ino  # Standalone firmware WITHOUT EEPROM
├── config/
│   ├── karabiner.json          # Symlinked to ~/.config/karabiner/karabiner.json
│   └── hammerspoon_init.lua    # Symlinked to ~/.hammerspoon/init.lua
├── my_keyboard_setup.md        # Keyboard documentation
├── install.md                  # Setup instructions
└── 2026.05.22_atreus.json      # Chrysalis keymap export
```

---

## Two Firmware Options

### Option 1: `Atreus__LF/Atreus__LF.ino`
- Uses EEPROMKeymap - keymap stored in EEPROM
- Works with Chrysalis GUI for editing
- TapDance DOES NOT work (EEPROM overrides firmware keymap)

### Option 2: `Atreus_NoChrysalis/Atreus_NoChrysalis.ino`
- All keymap hardcoded in firmware
- NO Chrysalis support
- TapDance WORKS
- Contains all functionality from Chrysalis export

---

## TapDance Implementation

Currently in `Atreus_NoChrysalis.ino`:

| Key | Single tap | Double tap |
|-----|------------|------------|
| ` | Backtick | Cmd+Shift+V (Clipy) |
| ; | Semicolon | Cmd+Tab (App Switcher) |
| / | Slash | Cmd+` (Window switch) |

**Pending**: User wants to add `yy` double-tap shortcut but hasn't specified what action it should perform.

---

## Key Technical Details

- **Keyboard**: Keyboardio Atreus
- **Firmware**: Kaleidoscope
- **Plugins used**: Qukeys, Leader, TapDance, MouseKeys, Macros

### Why TapDance doesn't work with Chrysalis:
The EEPROMKeymap plugin overrides the firmware keymap at runtime. When you put `TD(TD_SOMETHING)` in the firmware keymap, EEPROM replaces it with whatever key is stored in EEPROM (from Chrysalis).

### To add a new TapDance key:
1. Add enum value: `enum { TD_EXISTING, TD_NEW };`
2. Add to keymap: `TD(TD_NEW)`
3. Add case in `tapDanceAction()`:
```cpp
case TD_NEW:
  return tapDanceActionKeys(tap_count, tap_dance_action,
    Key_SingleTap, MODIFIER(Key_DoubleTap));
```

---

## Next Steps

1. Delete `Atreus__LF/Atreus__LF_full.ino` if it exists
2. Ask user what `yy` should do when double-tapped
3. Add the TapDance for Y key
4. Compile and upload `Atreus_NoChrysalis.ino`
5. Update documentation
