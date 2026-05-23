# Installation Guide

Instructions for setting up this keyboard configuration on a new Mac.

---

## Prerequisites

Install the following apps:

| App | Purpose | Install |
|-----|---------|---------|
| [Arduino IDE](https://www.arduino.cc/en/software) | Flash keyboard firmware | Download from website |
| [Chrysalis](https://github.com/keyboardio/Chrysalis/releases) | GUI keymap editor | Download from GitHub |
| [Karabiner-Elements](https://karabiner-elements.pqrs.org/) | Double-tap shortcuts | `brew install --cask karabiner-elements` |
| [Hammerspoon](https://www.hammerspoon.org/) | Hyper key app launcher | `brew install --cask hammerspoon` |
| [Clipy](https://clipy-app.com/) | Clipboard history | `brew install --cask clipy` |

### Optional (for window management)

| App | Purpose | Install |
|-----|---------|---------|
| [Rectangle](https://rectangleapp.com/) | Window snapping | `brew install --cask rectangle` |

---

## Quick Install (Homebrew)

```bash
# Install all apps at once
brew install --cask karabiner-elements hammerspoon clipy rectangle
```

---

## Step 1: Clone This Repository

```bash
cd ~/Documents
git clone https://github.com/guishogt/keyboardgt.git Arduino
cd Arduino
```

---

## Step 2: Create Symlinks for Config Files

Run these commands to link the config files to their expected locations:

```bash
# Karabiner
mkdir -p ~/.config/karabiner
ln -sf ~/Documents/Arduino/config/karabiner.json ~/.config/karabiner/karabiner.json

# Hammerspoon
mkdir -p ~/.hammerspoon
ln -sf ~/Documents/Arduino/config/hammerspoon_init.lua ~/.hammerspoon/init.lua
```

### Verify symlinks

```bash
ls -la ~/.config/karabiner/karabiner.json
ls -la ~/.hammerspoon/init.lua
```

Both should show arrows (`->`) pointing to files in `~/Documents/Arduino/config/`.

---

## Step 3: Reload Configurations

### Karabiner
- Open Karabiner-Elements
- It will auto-detect the config file
- Or: Menu bar icon → Preferences → Check "Show profile name"

### Hammerspoon
- Open Hammerspoon
- Click menu bar icon → "Reload Config"
- Or: Press `Cmd+Shift+R` when Hammerspoon console is focused

---

## Step 4: Flash Keyboard Firmware (Atreus)

### Install Kaleidoscope

Follow the [Kaleidoscope setup guide](https://kaleidoscope.readthedocs.io/en/latest/setup_toolchain.html).

### Flash firmware

1. Open `Atreus__LF/Atreus__LF.ino` in Arduino IDE
2. Select board: **Keyboardio Atreus**
3. Connect keyboard via USB
4. Press the physical **reset button** on the keyboard (small hole on bottom)
5. Click **Upload** within 10 seconds

---

## Step 5: Load Chrysalis Keymap

1. Open Chrysalis
2. Connect to your Atreus
3. Go to **Layout → Import**
4. Select `2026.05.22_atreus.json`
5. Click **Save to keyboard**

---

## Step 6: Grant Permissions

### Karabiner-Elements
- System Settings → Privacy & Security → Input Monitoring
- Enable `karabiner_grabber` and `karabiner_observer`

### Hammerspoon
- System Settings → Privacy & Security → Accessibility
- Enable **Hammerspoon**

---

## File Locations

| File | Location | Symlinked From |
|------|----------|----------------|
| Karabiner config | `~/.config/karabiner/karabiner.json` | `config/karabiner.json` |
| Hammerspoon config | `~/.hammerspoon/init.lua` | `config/hammerspoon_init.lua` |
| Atreus firmware | `Atreus__LF/Atreus__LF.ino` | (not symlinked) |
| Chrysalis keymap | `2026.05.22_atreus.json` | (not symlinked) |

---

## Troubleshooting

### Karabiner not working
1. Check permissions in System Settings → Privacy & Security → Input Monitoring
2. Restart Karabiner-Elements
3. Verify symlink: `ls -la ~/.config/karabiner/karabiner.json`

### Hammerspoon not working
1. Check permissions in System Settings → Privacy & Security → Accessibility
2. Reload config: Menu bar → Reload Config
3. Open Console (Menu bar → Console) to see errors

### Keyboard not detected by Chrysalis
1. Unplug and replug the keyboard
2. Try a different USB port/cable
3. Make sure no other app (Arduino IDE) is using the port

### Firmware upload fails
1. Press reset button and upload within 10 seconds
2. Check Arduino IDE has correct board selected
3. Close Chrysalis before uploading

---

## Updating

After making changes to configs in this repo:

```bash
# Karabiner auto-reloads on file change

# Hammerspoon - reload manually
# Click menu bar icon → Reload Config
```

---

## Backup

The original config files were backed up during initial setup:
- `~/.config/karabiner/karabiner.json.backup`
- `~/.hammerspoon/init.lua.backup`

To restore originals:
```bash
rm ~/.config/karabiner/karabiner.json
mv ~/.config/karabiner/karabiner.json.backup ~/.config/karabiner/karabiner.json

rm ~/.hammerspoon/init.lua
mv ~/.hammerspoon/init.lua.backup ~/.hammerspoon/init.lua
```
