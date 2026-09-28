# Using ESP-IDF

Now that we've seen how ESP-IDF works, let's get it working on our system! There are two ways (CLI or GUI) that you can build, flash, and monitor ESP-IDF code on your computer. It is completely up to personal preference which one you use (and also just which one "magically" works).

_Note: the download processes have yet to be rigorously tested so please inform us if there are any steps missing when you begin downloading ESP-IDF onto your system_

## 1. ESP-IDF Installation

<details>
<summary>Windows Tutorial</summary>

### Step 1: Download the ESP-IDF Installation Manager

Go to the ESP-IDF Installation Manager [site](https://dl.espressif.com/dl/eim/) and download the most recent version.

### Step 2: Run the Setup Wizard

Open the manager and begin setup.

Follow the prompts to select your target ESP boards (ESP32-S3), choose the ESP-IDF version (v6.1), and confirm the installation path. The wizard automatically downloads and configures all necessary build tools, including Python environments, CMake, Ninja, and the required cross-compilers.

- If in the future you need to update the target ESP board, run `idf.py set target esp32s3`
- To config any settings, run `idf.py menuconfig`
- We use JTAG upload

### Step 3: Load the Environment Variables

You cannot run `idf.py` commands natively until the terminal knows where the tools are located. This must be done **every time you open a new terminal**. You have two ways to load them:

**The Easy Way (Standalone Terminal):**
Open your Windows Start menu and search for **"ESP-IDF PowerShell Environment"** or **"ESP-IDF Command Prompt"**. This launches a new terminal with all variables pre-loaded.

**The Manual Way (VSCode Integrated Terminal):**
If you want to use the integrated terminal inside VSCode, open it, navigate to your ESP-IDF installation folder (usually `C:\Espressif\frameworks\esp-idf` or `%userprofile%\esp\esp-idf`), and run the export script:

- **PowerShell:** `. .\export.ps1`
- **Command Prompt:** `export.bat`

Any example file directory may look like this:

```
C:\
└── esp\
    └── v6.1-beta1\
        └── esp-idf
            ├── docs
            ├── examples
            ...
            └── export.ps1        # this is what we need to run!
```

And so you would could run `C:\esp\v6.1-beta1\esp-idf\export.ps1` in your terminal before using ESP-IDF.

</details>

<details>
<summary>MacOS Tutorial</summary>

We'll be following [Espressif's MacOS installation guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/macos-setup.html). Using HomeBrew will make updating ESP-IDF much easier in the future so we highly recommend using the HomeBrew instructions! We're going to go ahead with the CLI version for quick installing default settings but feel free to follow the instructions yourself if you want to change installation location or anything in particular.

### Step 1: Install HomeBrew

Launch your terminal and paste and run the following command (see the [HomeBrew website](https://brew.sh/) for more info if you're curious about what you're running):

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.s
h)"
```

### Step 2: Install Espressif Installation Manager (EIM) with HomeBrew

If these commands doesn't work right after installing HomeBrew, try opening a new terminal first. Might take a bit so be patient!

```bash
# Add the EIM repository to Homebrew
brew tap espressif/eim
brew trust espressif/eim

# Install EIM
brew install eim

# Install ESP-IDF
eim install
```

If you encounter issues with `eim install` try installing with the wizard using `eim wizard`.
Otherwise, if things went smoothly you should see something like:

```bash
2026-09-28 04:22:50 -  4 - 09 - INFO - Wizard result: Ok
2026-09-28 04:22:50 -  4 - 09 - INFO - Successfully installed IDF
2026-09-28 04:22:50 -  4 - 09 - INFO - Now you can start using IDF tools
```

</details>

<details>
<summary>Linux Tutorial</summary>

- Tutorial for Linux Ubuntu [Here!](https://esp32tutorials.com/install-esp32-esp-idf-linux-ubuntu/)

</details>

## 2. VSCode Extension Installation and Usage

For convenience, we'll be installing the VSCode Extension for ESP-IDF. You should still try to familiarize yourself with the CLI, but it'll make some menial tasks easier. Make sure you've already installed VSCode and ESP-IDF before moving on.

<details>
<summary>Setup</summary>

### Install the ESP-IDF VSCode Extension

Follow step 1 at ["Install ESP-IDF and Tools"](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/installation.html). The rest of the instructions only apply if you don't already have ESP-IDF installed (like we installed earlier). Step 5 can only be completed in a workspace, so it doesn't apply to us quite yet.

</details>

<details>
<summary>Creating a Project</summary>

Follow the instructions at ["Create an ESP-IDF Project"](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/startproject.html#create-an-esp-idf-project) to create a project.

DURING COMMAND PALETTE STEP:
Make sure to press what's underlined in red below!
<img width="392" height="94" alt="fw10" src="https://github.com/user-attachments/assets/cc1f7ebf-385d-4ecb-8c71-8da7ddac3a49" />  
<br><br>

While creating New Project: Select a template project or any example project

<img width="250" height="105.5" alt="image" src="https://github.com/user-attachments/assets/cbeb0143-6103-4bc6-83e0-582a28728485" />

<br><br>

Project Attributes Breakdown:

<img width="315.5" height="221" alt="image" src="https://github.com/user-attachments/assets/289bc19e-56f6-48bc-9d3e-136a97fcdd1e" />

1) Project Name
2) Project Folder location of choice in your file manager
3) Target Device (We use the esp32s3)
4) Distinction between having built-in hardware for debugging (USB or JTAG) vs. needing to connect external hardware
5) Choosing the port on your computer that your ESP32 connects to (detect will automatically choose the port that's connected for you.)
6) Add locations of component folders (components explained later!)

<br><br>

### (Windows Only) At this step, if unsure about which port (place on your laptop/PC to connect ESP32 through cable), press hyperlinked ‘Establish Serial Communication.”

<img width="458" height="233" alt="fw11" src="https://github.com/user-attachments/assets/d14900ec-9507-442c-8b94-eb4b5ec84972" />  

<br><br>

Scroll down to ‘Check Port on Windows’:
To identify serial port, follow instructions
(!!!) Check that cable supports data-transfer (not just charge only)
If cable is data-transferrable, Upon connection, device manager page should automatically refresh and update w/ ESP32 connection

<img width="340" height="169" alt="fw12" src="https://github.com/user-attachments/assets/c63c07e7-a18b-40c3-8ad3-b4a7c9c0bc1a" />  

<br><br>

<i></i>**Congrats, you made your first project!**<i></i>

<br><br>
</details>

<details>
<summary>Accessing Your Projects</summary>

To edit/use the extension at any point, open VS Code, open the project folder (File > Open Folder..), and enable the ESP-IDF extension.

The Extension opens this left side-bar:

<img width="218" height="361" alt="image" src="https://github.com/user-attachments/assets/1699c93b-77b3-4081-be3d-7ef7ebae7a7a" />

- Choose your opened project folder as the current workspace using the first checkboxed command.

Each command (and more) with a checkbox should open a button used for that purpose at the bottom:

<img width="362.5" height="148" alt="image" src="https://github.com/user-attachments/assets/2825aebc-83b1-4705-bf6c-ddc72d4cfdfd" />

Info on the purpose of each file/folder in your project folder [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html).
(Great breakdown of components [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html)).

In project folder, go to ‘main’ file. (As per the C Basics section, the C/C++ extension in VS Code lets you write C/C++ code in this file).

</details>

## Flashing Firmware

There are two ways (CLI or GUI) that you can build, flash, and monitor ESP-IDF code on your computer. It is completely up to personal preference which one you use (and also just which one "magically" works). But _PLEASE_ try to familiarize yourself with both options!!!

### Option 1 - CLI

1. Source the ESP-IDF toolchain

   On Windows, this would be something like:

   ```bash
   C:\esp\v6.1-beta1\esp-idf\export.ps1
   ```

   On Mac, this would be something like:

   ```bash
   source $HOME/.espressif/tools/activate_idf_v5.5.2.sh
   ```

   On Linux, this would be something like:

   ```bash
   source /opt/esp-idf/export.sh
   ```

   NOTE: We HIGHLY recommend setting up alias/shortcut for sourcing the toolchain. This allows you to source the tool chain with a simple command such as:

   ```bash
   get_idf
   ```

   <details>
   <summary>Setting up alias shortcut (optional but highly recommended)</summary>
   <dl><dd>

   <details>
   <summary>Setting up alias shortcut for MacOS</summary>

   Open your `.zshrc` in vim (a text editor that lives in the terminal):

    ```bash
    vim ~/.zshrc
    ```

    Vim has two modes — **normal mode** (for navigating) and **insert mode** (for typing). It opens in normal mode. To get to the bottom of the file and start editing:

    - Before trying to edit in Vim, do not try pressing anything with your mouse!!! It won't work!

    1. Press `Shift+G` to jump to the last line
    2. Press `o` to open a new line below and enter insert mode
    3. Type the following line:

    ```bash
    alias get_idf='source $HOME/.espressif/tools/activate_idf_v5.5.2.sh'
    ```

    1. Press `Esc` to go back to normal mode
    2. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
    If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.

    Run this command to apply the changes to your current session without having to log out:

    ```bash
    source ~/.zshrc
    ```

    Now you have a alias/shortcut to source esp-idf by running:

    ```bash
    get_idf
    ```

   </details>

   <details>
   <summary>Setting up alias shortcut for Windows</summary>

    _Note: This is untested for windows (not sure if it works, please let us know!)_

   These steps use **PowerShell**. Your PowerShell profile (a file that runs every time you open PowerShell) is the Windows equivalent of `.zshrc` / `.bashrc`.

    First, make sure your profile file exists (this is safe to run even if it already does):

    ```powershell
    New-Item -Path $PROFILE -ItemType File -Force
    ```

    Open your PowerShell profile in vim (a text editor that lives in the terminal):

    ```powershell
    vim $PROFILE
    ```

    Vim has two modes — **normal mode** (for navigating) and **insert mode** (for typing). It opens in normal mode. To get to the bottom of the file and start editing:

    - Before trying to edit in Vim, do not try pressing anything with your mouse!!! It won't work!

    1. Press `Shift+G` to jump to the last line
    2. Press `o` to open a new line below and enter insert mode
    3. Type the following line:

    ```powershell
    function get_idf { & 'C:\esp\v6.1-beta1\esp-idf\export.ps1' }
    ```

    1. Press `Esc` to go back to normal mode
    2. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
    If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.

    Run this command to apply the changes to your current session without having to close PowerShell:

    ```powershell
    . $PROFILE
    ```

    If you get an error saying running scripts is disabled, run this once, then try again:

    ```powershell
    Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
    ```

    Now you have a alias/shortcut to source esp-idf by running:

    ```powershell
    get_idf
    ```

   </details>

   <details>
    <summary>Setting up alias shortcut for Linux</summary>

    Open your `.bashrc` in vim (a text editor that lives in the terminal):

    ```bash
    vim ~/.bashrc
    ```

    Vim has two modes — **normal mode** (for navigating) and **insert mode** (for typing). It opens in normal mode. To get to the bottom of the file and start editing:

    - Before trying to edit in Vim, do not try pressing anything with your mouse!!! It won't work!

    1. Press `Shift+G` to jump to the last line
    2. Press `o` to open a new line below and enter insert mode
    3. Type the following line:

    ```bash
    alias get_idf='source /opt/esp-idf/export.sh'
    ```

    1. Press `Esc` to go back to normal mode
    2. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
    If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.

    Run this command to apply the changes to your current session without having to log out:

    ```bash
    source ~/.bashrc
    ```

    Now you have a alias/shortcut to source esp-idf by running:

    ```bash
    get_idf
    ```

   </details>

   </dd></dl>
   </details>

2. Generate the sdkconfig file for target chip (We use S3). You only have to do this once.

   ```bash
   idf.py set-target esp32s3
   ```

3. OPTIONAL: edit the sdkconfig file

   ```bash
   idf.py menuconfig
   ```

4. Build your code. This calls CMake and Ninja in right order to compile code, link libraries, and generate binary files (.bin) that can be flashed onto an ESP32 chip). The first build takes a few minutes — it's compiling the entire ESP-IDF stack. Subsequent builds only recompile files you've changed.

   ```bash
   idf.py build
   ```

5. Flash your code. This uploads your firmware to the chip!

   ```bash
   idf.py flash
   ```

   OR specify the port using (check [Locating the Port](#locating-the-port) section bellow)

   ```bash
   idf.py -p [port e.g. COM6] flash
   ```

6. Monitor your code

   ```bash
   idf.py monitor
   ```

   OR specify the port using (check [Locating the Port](#locating-the-port) section bellow)

   ```bash
   idf.py -p [port e.g. COM6] monitor
   ```

   **IMPORTANT:** Press `Ctrl+]` to exit the monitor. If that doesn't work, try `Ctrl+T` then `Ctrl+]`. Do not use `Ctrl+C` — that sends an interrupt to the chip, not to the monitor.*

You can alternatively do all three at the same time by running:

`idf.py build flash monitor` (OR specify the port using:  `idf.py -p [port e.g. COM6] build flash monitor`)

Or you can run any combinations involving two of the three like:

`idf.py build flash` (OR specify the port using: `idf.py -p [port e.g. COM6] build flash`),

`idf.py build monitor` (OR specify the port using: `idf.py -p [port e.g. COM6] build monitor`),

`idf.py flash monitor` (OR specify the port using: `idf.py -p [port e.g. COM6] flash monitor`)

### Option 2 - GUI

You can use the GUI buttons provided by the VSCode exntension!

These commands will have matching buttons at the bottom of your screen that you press to execute:

<img width="180" height="111" alt="image" src="https://github.com/user-attachments/assets/5f18b35e-0109-40b3-9bf1-774e8b1bb322" />

## Locating the Port

<details>
<summary>MacOS</summary>
<dl><dd>

To find the port, run:

```bash
ls /dev/tty.* /dev/cu.* 2>/dev/null
```

Just like for sourcing the ESP-IDF tool chain (Step 1), we HIGHLY recommend setting up alias/shortcut for locating the port. This allows you to locate the port with a simple command such as:

```bash
ports
```

<details>
<summary>Setting up ports alias shortcut for MacOS (optional but highly recommended)</summary>

Open your `.zshrc` in vim (a text editor that lives in the terminal):

```bash
vim ~/.zshrc
```

Vim has two modes — **normal mode** (for navigating) and **insert mode** (for typing). It opens in normal mode. To get to the bottom of the file and start editing:

- Before trying to edit in Vim, do not try pressing anything with your mouse!!! It won't work!

1. Press `Shift+G` to jump to the last line
2. Press `o` to open a new line below and enter insert mode
3. Type the following line:

```bash
alias ports='ls /dev/tty.* /dev/cu.* 2>/dev/null'
```

1. Press `Esc` to go back to normal mode
2. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.

Run this command to apply the changes to your current session without having to log out:

```bash
source ~/.zshrc
```

Now you have a alias/shortcut to locate the port:

```bash
ports
```

</details>

</dd></dl>
</details>

<details>
<summary>Windows</summary>
<dl><dd>

For Windows you can see what ports are available using your device manager

</dd></dl>
</details>

<details>
<summary>Linux</summary>
<dl><dd>

To find the port, run:

```bash
ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null
```

Just like for sourcing the ESP-IDF tool chain (Step 1), we HIGHLY recommend setting up alias/shortcut for locating the port. This allows you to locate the port with a simple command such as:

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
3. Type the following line:

```bash
alias ports='ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null'
```

1. Press `Esc` to go back to normal mode
2. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.

Run this command to apply the changes to your current session without having to log out:

```bash
source ~/.bashrc
```

Now you have a alias/shortcut to locate the port:

```bash
ports
```

</details>

</dd></dl>
</details>

## General Tips

- Whenever edits to the file/code are made, rebuild before flashing.
- **Always full clean before rebuilding!**
- Sourcing your toolchain every single session is always a pain. See Reading 6v5 for an old sourcing toolchain walkthrough, no guarantees it will work though!
