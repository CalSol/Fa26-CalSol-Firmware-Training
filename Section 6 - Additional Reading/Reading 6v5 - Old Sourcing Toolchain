---

# Sourcing the ESP-IDF Toolchain

First install the ESP-IDF Toolchain via the following commands (you only have to do this once!)
```bash
cd /opt/esp-idf
./install.sh esp32
```
 
Before you can use `idf.py` or any ESP-IDF tools in any new terminal session, you need to **source** the toolchain. But what does sourcing actually mean?
 
When you run a normal script like `bash script.sh`, it runs in a **child process** — a temporary shell that inherits your environment, does its work, and then disappears. Any changes it makes (like adding something to your `PATH`) vanish when it exits, because they only existed in that child process.
 
**Sourcing** runs a script directly in your current shell instead:
 
```bash
. /opt/esp-idf/export.sh
# the dot is shorthand for "source" — these are identical:
source /opt/esp-idf/export.sh
```
 
Because it runs in your current shell, any environment variables it sets — like `$IDF_PATH` and the path to `xtensa-esp32s3-elf-gcc` — stick around for the rest of your session. That's why `idf.py` works after sourcing but not before: your shell simply doesn't know where to find it until `export.sh` adds it to your `$PATH`.
 
You can see what it adds by running:
 
```bash
echo $IDF_PATH         # should print /opt/esp-idf
which idf.py           # should print the full path to the idf.py script
```
 
### Setting up your .bashrc
 
Sourcing manually every session gets old quickly. The fix is to add it to your `~/.bashrc` — a script that runs automatically every time you open a shell.
 
Open your `.bashrc` in vim (a text editor that lives in the terminal):
 
```bash
vim ~/.bashrc
```
 
Vim has two modes — **normal mode** (for navigating) and **insert mode** (for typing). It opens in normal mode. To get to the bottom of the file and start editing:

- Before trying to edit in Vim, do not try pressing anything with your mouse!!! It won't work!
 
1. Press `Shift+G` to jump to the last line
2. Press `o` to open a new line below and enter insert mode
3. Type the two lines:
```bash
alias get_idf=". /opt/esp-idf/export.sh"
. /opt/esp-idf/export.sh
```
 
4. Press `Esc` to go back to normal mode
5. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.
 
Apply the changes to your current session without logging out:
 
```bash
source ~/.bashrc
```
 
What those two lines do:
 
- `. /opt/esp-idf/export.sh` — sources the toolchain automatically on every login, so `idf.py` is always available
- `alias get_idf=...` — gives you a manual shortcut to re-source it if needed (e.g. if something resets your environment)

# Building, Flashing, and Monitoring Your First Project

## Step 1 — Copy the hello world example from ESP-IDF

```bash
# <!> First, navigate into your projects directory! Let's see if you remember how to do this!
cp -r /opt/esp-idf/examples/get-started/hello_world .
cd hello_world
```

## Step 2 — Set the target chip (We use S3)

```bash
idf.py set-target esp32s3
```

## Step 3 — Build

Build means to compile code, link libraries, and generate binary files (.bin) that can be flashed onto an ESP32 chip. 

```bash
idf.py build
```

First build takes a few minutes — it's compiling the entire ESP-IDF stack. Subsequent builds only recompile files you've changed.

## Step 4 — Find your device

Plug in your ESP32-S3 and run:

```bash
ls /dev/ttyACM* /dev/ttyUSB*
```

You'll see something like `/dev/ttyACM0`. If multiple devices show up, unplug and replug your board and run it again to see which one appears — that's yours.

## Step 5 — Flash and monitor

```bash
idf.py -p /dev/ttyACM0 flash monitor
```

Replace `/dev/ttyACM0` with whatever port you found in Step 4. This flashes the firmware and immediately opens the serial monitor so you can see the chip's output.

You should see the bootloader output followed by:

```
Hello world!
This is esp32s3 chip with 2 CPU core(s), WiFi/BLE...
Restarting in 10 seconds...
```

The countdown and restart are expected. The Hello World example is designed to loop.

## Exiting the monitor

Press `Ctrl+]` to exit. If that doesn't work, try `Ctrl+T` then `Ctrl+]`.

Do not use `Ctrl+C` — that sends an interrupt to the chip, not to the monitor.
