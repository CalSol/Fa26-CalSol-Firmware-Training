# NOTE: this section is not necessary to complete this Firmware Training. The CAN TestBench is still a WIP, but for future continuity we have chosen to leave this section here. We will NOT be helping people set up CAN TestBench access as of 9/27/2026

# Remote SSH'ing into the CAN TestBench
CalSol's remote CAN Testbench allows you to upload your code to an ESP32-S3 without needing the physical hardware with you. Of course, there are limitations to what you can do.

## Part 1 — SSH access via Tailscale

We use [Tailscale](https://tailscale.com) to connect to the Pi securely from anywhere without opening any ports.

### Step 1 — Install Tailscale on your machine

Go to [tailscale.com/download](https://tailscale.com/download) and install the client for your OS (Mac, Windows, or Linux). Sign in with the account details shared with you by the team.

If you didn't recieve an invite, please contact Austin on Slack. 

### Step 2 — Find the Pi's Tailscale address

Once you're connected to the Tailscale network, the device's name will appear in your Tailscale device list.

You might also see a fixed IP like `100.x.x.x`. Ask a team admin for the exact address if you're unsure.

### Step 3 — SSH in

Your account has already been created for you. SSH in using your username:

```bash
ssh yourname@<device_name>
```

You can also try 

```bash
ssh yourname@<device_IP_address>
```

The first time you connect, you'll see a fingerprint prompt — type `yes` to accept it. This is normal and only happens once.

### Step 4 — Set up SSH key login (Optional)

Password login works but SSH keys are faster and more secure. If you don't have a key yet, generate one on **your own machine** (not the Pi):

<!> DO THIS ON YOUR OWN DEVICE IN THE ROOT DIRECTORY
```bash
ssh-keygen -t ed25519 -C "your@email.com"
```

Then copy it to the Pi:

```bash
ssh-copy-id yourname@<device_name>
```

After this, you won't need to type your password to log in.

---

## Part 2 — Changing your password

When your account is first created it has no password set (login is via SSH key or a temporary password given by an admin). You should set your own password on first login.

### Change your password

Once you're SSHed in, run:

```bash
passwd
```

You'll be prompted to enter a new password twice. Nothing will appear on screen as you type — that's normal, Linux hides password input.

```
Changing password for yourname.
New password:
Retype new password:
passwd: password updated successfully
```

Choose something strong. You'll need this password if you ever need to use `sudo`.

### If you forget your password

Ask a team admin — they can reset it for you with:

```bash
sudo passwd yourname
```

## Part 3 — Installing the ESP-IDF Toolchain

First install the ESP-IDF Toolchain via the following commands (you only have to do this once!)
```bash
cd /opt/esp-idf
./install.sh esp32
```

## Quick reference

| Task | Command |
|---|---|
| SSH into the Pi | `ssh yourname@<device_name>` |
| Change your password | `passwd` |
| Check who's logged in | `who` |

# Flashing Firmware

1. Copy the hello world example from ESP-IDF

   ```bash
   # <!> First, navigate into your projects directory! Let's see if you remember how to do this!
   cp -r /opt/esp-idf/examples/get-started/hello_world .
   cd hello_world
   ```

2. Source the ESP-IDF toolchain

   ```bash
   source /opt/esp-idf/export.sh
   ```

   Note: Sourcing manually every session gets old quickly. We HIGHLY recommend adding it to your `~/.bashrc` — a script that runs automatically every time you open a shell so that every time you ssh into the pi, the ESP-IDF toolchain is automatically sourced.

   <details>
   <summary>Setting up automatic sourcing (optional but highly recommended)</summary>
 
   Open your `.bashrc` in vim (a text editor that lives in the terminal):
    
   ```bash
   vim ~/.bashrc
   ```
    
   Vim has two modes — **normal mode** (for navigating) and **insert mode** (for typing). It opens in normal mode. To get to the bottom of the file and start editing:
   
   - Before trying to edit in Vim, do not try pressing anything with your mouse!!! It won't work!
    
   1. Press `Shift+G` to jump to the last line
   2. Press `o` to open a new line below and enter insert mode
   3. Type the lines:
   ```bash
   # gives you a manual shortcut to re-source it if needed (e.g. if something resets your environment)
   alias get_idf='source /opt/esp-idf/export.sh'
   
   # sources the toolchain automatically on every login, so idf.py is always available
   source /opt/esp-idf/export.sh
   ```
    
   4. Press `Esc` to go back to normal mode
   5. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
   If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.
    
   Run this command to apply the changes to your current session without having to log out:
    
   ```bash
   source ~/.bashrc
   ```
    
   What those two lines do:
    
   - `. /opt/esp-idf/export.sh` — sources the toolchain automatically on every login, so `idf.py` is always available
   - `alias get_idf=...` — gives you a manual shortcut to re-source it if needed (e.g. if something resets your environment)

   </details>

4. Generate the sdkconfig file for target chip (We use S3). You only have to do this once.
  
   ```bash
   idf.py set-target esp32s3
   ```

5. OPTIONAL: edit the sdkconfig file

   ```bash
   idf.py menuconfig
   ```

6. Build your code. This calls CMake and Ninja in right order to compile code, link libraries, and generate binary files (.bin) that can be flashed onto an ESP32 chip). The first build takes a few minutes — it's compiling the entire ESP-IDF stack. Subsequent builds only recompile files you've changed.

   ```bash
   idf.py build
   ```

5. Locate the port (this will show you the custom names of the ESPs connected to the test bench):

   ```bash
   ls /dev/esp32* 2>/dev/null
   ```

   if the custom names for the ESPs aren't working, try just getting the port numbers:
   ```bash
   ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null
   ```

   Note: We HIGHLY recommend setting up alias/shortcut for locating the port. This allows you to locate the port (first with the custom name of the ESP, then if that doesn't work with the port number) with a simple command such as:

   ```bash
   ports
   ```
   
   <details>
   <summary>Setting up ports alias shortcut for Linux (optional but highly recommended)</summary>
   
   Open your `.bashrc` in vim (a text editor that lives in the terminal):
   
   ```bash
   vim ~/.bashrc
   ```
   
   Vim has two modes — **normal mode** (for navigating) and **insert mode** (for typing). It opens in normal mode. To get to the bottom of the file and start editing:
   
   - Before trying to edit in Vim, do not try pressing anything with your mouse!!! It won't work!
   
   1. Press `Shift+G` to jump to the last line
   2. Press `o` to open a new line below and enter insert mode
   3. Type the following lines:
   
   ```bash
   # List connected serial/USB devices — custom esp32 names if udev rules matched, else generic Linux names
   alias ports='{
     for p in /dev/esp32* /dev/ttyACM* /dev/ttyUSB*; do
       [ -e "$p" ] || continue
       real=$(readlink -f "$p")
       echo "$real|$p"
     done
   } 2>/dev/null | sort -t"|" -k1,1 -u | awk -F"|" "{print \$2}"'
   ```
   
   1. Press `Esc` to go back to normal mode
   2. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
   If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.
   
   Run this command to apply the changes to your current session without having to log out:
   
   ```bash
   source ~/.bashrc
   ```
   
   Now you have a alias/shortcut to locate the port (first with the custom name of the ESP, then if that doesn't work with the port number):
   
   ```bash
   ports
   ```
   
   </details>

5. Flash your code. This uploads your firmware to the chip!

   ```bash
   idf.py -p [port e.g. /dev/ttyACM0] flash
   ```

6. Monitor your code

   ```bash
   idf.py -p [port e.g. /dev/ttyACM0] monitor
   ```

   You should see the bootloader output followed by:

   ```
   Hello world!
   This is esp32s3 chip with 2 CPU core(s), WiFi/BLE...
   Restarting in 10 seconds...
   ```
   
   The countdown and restart are expected. The Hello World example is designed to loop.

   **IMPORTANT:** Press `Ctrl+]` to exit the monitor. If that doesn't work, try `Ctrl+T` then `Ctrl+]`. Do not use `Ctrl+C` — that sends an interrupt to the chip, not to the monitor.*

You can alternatively do all three at the same time by running:

`idf.py -p [port e.g. /dev/ttyACM0] build flash monitor`

Or you can run any combinations involving two of the three like:

`idf.py -p [port e.g. /dev/ttyACM0] build flash`

`idf.py -p [port e.g. /dev/ttyACM0] build monitor`

`idf.py -p [port e.g. /dev/ttyACM0] flash monitor`
