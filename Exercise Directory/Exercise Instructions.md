# Getting Started with the Exercises

Every exercise in this folder is a small ESP-IDF project. This guide shows you how to set up your computer once, and then how to open, build, and run any exercise, **with or without an ESP32 board**.

> This guide is written for **Windows**. Mac and Linux follow the same steps, but the install folders and terminal commands are different. Ask a firmware lead if you get stuck.

## Table of Contents
1. [Install the Tools (one time)](#1-install-the-tools-one-time)
2. [Get the Exercises](#2-get-the-exercises)
3. [Open an Exercise](#3-open-an-exercise)
4. [Build Your Code](#4-build-your-code)
5. [Run Your Code](#5-run-your-code)
   - [Option A: Without a board (QEMU emulator)](#option-a-without-a-board-qemu-emulator)
   - [Option B: On a real ESP32-S3](#option-b-on-a-real-esp32-s3)
6. [Troubleshooting](#6-troubleshooting)

---

# 1. Install the Tools (one time)

You only need to do this section once per computer.

### VS Code and extensions
1. Install VS Code. See `Section 0 - Introduction to Firmware/Reading 0v4 - Setting up VSCode.md`.
2. In VS Code, open the **Extensions** tab and install:
   - **ESP-IDF** (publisher: Espressif Systems)
   - **C/C++** (publisher: Microsoft)

### ESP-IDF
ESP-IDF is Espressif's toolkit for programming the ESP32. It includes the C compiler, so you do **not** need to install C separately.

1. Open the ESP-IDF extension (the Espressif icon on the left sidebar) and start the setup.
2. The setup opens the **ESP-IDF Installation Manager (EIM)**.
3. Choose version **v6.1**. Everyone in the lab should be on the same version.
4. Keep the default install folders:
   - ESP-IDF: `C:\esp\v6.1\esp-idf`
   - Tools: `C:\Espressif\tools`
5. Wait for the install to finish. It can take 10+ minutes.

For more detail and screenshots, see `Section 2 - ESP32 Basics/Reading 2v3 - ESP-IDF Setup.md`.

---

# 2. Get the Exercises

In this section you'll use the terminal to make a folder for CalSol work and download (clone) this repository into it.

> New to the command line? Read [Command Line Basics](../Section%200%20-%20Introduction%20to%20Firmware/Reading%200v2%20-%20Command%20Line%20Basics.md) first. It explains `pwd`, `ls`, `cd`, `mkdir`, and file paths. This will also be a great exercise to prepare you for your lower-division CS classes (CS 61A/B/C)!

For Git and GitHub, see [Setting up GitHub](../Section%200%20-%20Introduction%20to%20Firmware/Reading%200v3%20-%20Setting%20up%20GitHub.md).

### Step 1: Open a terminal
Use either one of these:
- **Windows PowerShell:** press the Windows key, type `PowerShell`, and open **Windows PowerShell**.
- **VS Code:** go to **Terminal → New Terminal** (or press `` Ctrl+` ``).

You'll see a prompt like this, showing the folder you're currently in:

```
PS C:\Users\oski>
```

> PowerShell understands most of the commands from the Command Line Basics reading (`pwd`, `ls`, `cd`, `mkdir`, `cd ..`, `cd ~`). Some flags differ; for example, use `ls -Force` instead of `ls -la` to show hidden files.

### Step 2: Check that Git is installed

```powershell
git --version
```

If you see something like `git version 2.x.x`, you're good. If you get `'git' is not recognized`, install Git from [git-scm.com](https://git-scm.com/downloads), close the terminal, and open a new one.

### Step 3: Make a folder for CalSol work
Go to your Documents folder, create a `CalSol` folder, and move into it:

```powershell
cd ~\Documents      # go to your Documents folder
mkdir CalSol        # create a new folder called CalSol
cd CalSol           # move into it
pwd                 # check where you are
```

`pwd` should print something like `C:\Users\oski\Documents\CalSol`.

### Step 4: Clone the repository

```powershell
git clone https://github.com/CalSol/Fa26-CalSol-Firmware-Training.git
```

This downloads the whole training into a new folder called `Fa26-CalSol-Firmware-Training`. Check that it's there:

```powershell
ls
```

### Step 5: Look around the exercises

```powershell
cd Fa26-CalSol-Firmware-Training
cd "Exercise Directory"
ls
```

You'll see one folder per exercise, for example `Exercise 1v1 - C Basics`. Inside each one, the only file you edit is **`main/main.c`**.

> **Folder names with spaces need quotes.** `cd Exercise Directory` fails, but `cd "Exercise Directory"` works. Even easier: type `cd Exer` and press `Tab`, and the terminal fills in the name (and quotes) for you.

---

# 3. Open an Exercise

### Step 1: Open the exercise folder itself
In VS Code, go to **File → Open Folder** and select the exercise folder, for example:

```
Fa26-CalSol-Firmware-Training\Exercise Directory\Exercise 1v1 - C Basics
```

> IMPORTANT: Open the **exercise folder**, not the whole repository. ESP-IDF needs the folder that contains `CMakeLists.txt` and `main/`.

<!-- TODO: screenshot of VS Code with the exercise folder open -->

### Step 2: Set the target chip to `esp32s3`
Our boards are **ESP32-S3**. In the blue status bar at the bottom of VS Code, click the chip name (it shows `esp32` by default) and choose **esp32s3**. If it asks how the board connects, pick **"ESP32-S3 chip (via builtin USB-JTAG)"**.

<!-- TODO: screenshot of the status bar target picker -->

> If you skip this, you'll get the error *"sdkconfig was generated for target 'esp32s3', but environment variable IDF_TARGET is set to 'esp32'"*. **Don't** run the `idf.py set-target esp32` command it suggests, because that would build for the wrong chip. Set the target in the status bar instead.

### Step 3: Open an ESP-IDF terminal
Press `Ctrl+Shift+P` to open the Command Palette and run:

```
ESP-IDF: Open ESP-IDF Terminal
```

A regular PowerShell terminal won't recognize `idf.py`. Use this terminal for all the commands below.

<!-- TODO: screenshot of the ESP-IDF terminal command -->

---

# 4. Build Your Code

Building compiles your C code into a program the ESP32 can run. **You do not need a board to build.**

```powershell
idf.py build
```

The first build takes a few minutes. Later builds are much faster. A successful build ends with:

```
Project build complete.
```

If you made a mistake in your C code (a typo or a missing `;`), the build fails here and tells you the file and line number. Fix it and build again.

---

# 5. Run Your Code

You have two options. Use **Option A** if you don't have a board with you, this will likely be the case when you are doing the exercise, and **Option B** when you do, this will happen during your check off!

## Option A: Without a board (QEMU emulator)

QEMU is an emulator: it pretends to be an ESP32-S3 on your computer, so you can see your program's output without any hardware.

### Step 1: Add QEMU to your terminal (every new terminal)
QEMU is installed with ESP-IDF, but the terminal doesn't know where to find it. Paste this line into your ESP-IDF terminal (NOT YOUR POWERSHELL TERMINAL!):

```powershell
$env:PATH = (Resolve-Path "C:\Espressif\tools\tools\qemu-xtensa\*\qemu\bin").Path + ";$env:PATH"
```

This only lasts until you close the terminal, so repeat it whenever you open a new one.

> If this line gives an error, QEMU isn't installed yet. Install it with the command below in your ESP-IDF terminal, then paste the line above again.
> ```powershell
> python $env:IDF_PATH\tools\idf_tools.py install qemu-xtensa
> ```

### Step 2: Run the program

```powershell
idf.py qemu
```

This builds your code (if it changed) and runs it. Your output appears directly in the terminal:

```
Task 1:
Temperature: 75

Task 2:
...
Done!
```

To **quit QEMU**, press `Ctrl+A`, let go, then press `X`.

>  **Some Debugging Tips**
> - Use `idf.py qemu`, **not** `idf.py qemu monitor`. With `monitor`, the program finishes before the monitor connects, so you'll only see "Done".
> - The line `W (...) rtcinit: o_code calibration fail` is a harmless emulator warning. Ignore it.
> - After editing `main.c`, just run `idf.py qemu` again. It rebuilds automatically.

> QEMU works for exercises that only print output, like **Exercise 1v1 - C Basics**. Exercises that use real hardware (GPIO, CAN, UART, I2C, SPI) need a real board.

## Option B: On a real ESP32-S3

### Step 1: Plug in the board and find its port
1. Connect the ESP32-S3 with a USB cable that supports **data**. Some cables only charge, and the board won't show up with them.
2. Open **Device Manager → Ports (COM & LPT)**. A new entry should appear when you plug in the board, for example `USB Serial Device (COM5)` or `USB JTAG/serial debug unit (COM5)`. Remember the COM number.

<!-- TODO: screenshot of Device Manager showing the ESP32 COM port -->

### Step 2: Flash and monitor
"Flashing" uploads your program to the board, and "monitoring" shows what it prints.

**Using VS Code buttons:** select your COM port in the status bar, then click the flame icon (**Build, Flash and Monitor**).

**Using the terminal** (replace `COM5` with your port):

```powershell
idf.py -p COM5 flash monitor
```

To **quit the monitor**, press `Ctrl+]`.

> If flashing fails with a connection error, put the board in download mode: **hold BOOT, tap RST, release BOOT**, and try again.

---

# 6. Troubleshooting

| Problem | Fix |
|---|---|
| `'idf.py' is not recognized` | You're in a regular terminal. Open an **ESP-IDF terminal** ([Section 3, Step 3](#step-3-open-an-esp-idf-terminal)). |
| `sdkconfig ... generated for target 'esp32s3', but ... IDF_TARGET is set to 'esp32'` | Set the target to **esp32s3** in the status bar ([Section 3, Step 2](#step-2-set-the-target-chip-to-esp32s3)), then open a new terminal. For a quick fix in the current terminal, run `$env:IDF_TARGET = "esp32s3"`. |
| `qemu-system-xtensa is not installed` | Add QEMU to your terminal ([Option A, Step 1](#step-1-add-qemu-to-your-terminal-every-new-terminal)). |
| QEMU only shows "Done" | Run `idf.py qemu` instead of `idf.py qemu monitor`. |
| No COM port shows up | Try a different USB cable (it must support data) or a different USB port. |
| `Failed to connect to ESP32-S3` when flashing | Hold **BOOT**, tap **RST**, release **BOOT**, then flash again. |
| Build fails with an error in `main.c` | Read the error message: it gives the file and line number of your mistake. |

Still stuck? Ask a firmware helper on Slack(Howard Yao, Kadon Liang, Emma Chikere, and Simon Nguyen), and include the full error message from your terminal.
