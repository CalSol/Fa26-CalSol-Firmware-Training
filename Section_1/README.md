# ESP-IDF & C-Make Walkthrough

Table of Contents
- [Microcontroller & ESP32-S3 introduction](#microcontroller--esp32-s3-introduction)
- [ESP-IDF & CMake introduction](#esp-idf--cmake-introduction)
- [Building, flashing, and monitoring your first project](#building-flashing-and-monitoring-your-first-project)

# Microcontroller & ESP32-S3 introduction

# ESP-IDF & CMake introduction

In order to program our ESP32-S3 DEV boards, we chose to use the ESP-IDF toolchain (there are plenty of other options). Which begs the following question...

### What is ESP-IDF?
 
[ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/) (Espressif IoT Development Framework) is the official software development kit (SDK) for programming ESP32 chips. It gives you everything you need to write firmware, such as a standard c library, drivers (like an API) for the chip's hardware/engines (WiFi, Bluetooth, GPIO, SPI, I2C, etc.), a real-time operating system ([FreeRTOS](https://www.freertos.org/)), and a build system to compile it all together.
 
When you write code for the ESP32-S3, you're writing C (or C++) that runs directly on the chip so ESP-IDF provides the layer that manages hardware access, task scheduling, and memory, so you don't have to do it from scratch.
 
### What is CMake?
 
[CMake](https://cmake.org/) is a build system generator, a fancy way to call a tool that figures out how to compile your project, but it's not actualy doing the compiling itself (translating human readable code like C to machine code 1's and 0's). When you have a project with many `.c` files, headers, and libraries, CMake reads a configuration file (`CMakeLists.txt`) and generates the exact compiler commands needed to turn all of it into a binary that can run on the chip. Otherwise you would need write these compiler commands yourself and it's annoying. 
 
ESP-IDF uses CMake under the hood, so every ESP-IDF project has a `CMakeLists.txt` that describes what files to compile and what libraries to link.
 
### What is Ninja?
 
[Ninja](https://ninja-build.org/) is the tool that actually runs the compiler. There's a division of labour here that can be confusing at first:
 
- **CMake** reads your `CMakeLists.txt` and figures out *what* needs to be compiled and in what order
- **Ninja** takes that plan and *executes* it as fast as possible — it's designed to run many compile jobs in parallel and only recompile files that have actually changed
Think of CMake as the architect drawing the blueprint, and Ninja as the construction crew building it. You never call Ninja directly — `idf.py` handles everything.
 
### How they fit together
 
```
Your code (.c files)
      +
CMakeLists.txt  ──▶  CMake  ──▶  Ninja  ──▶  firmware.bin
      +                        (runs compiler)
ESP-IDF (drivers, FreeRTOS, libraries)
```
 
[`idf.py`](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-guides/tools/idf-py.html) is the command you'll actually use — it's a wrapper that calls CMake and Ninja in the right order so you don't have to think about them directly.
 
### A minimal project structure
 
Every ESP-IDF project looks like this:
 
```
my_project/
├── CMakeLists.txt        # top-level build config — tells CMake this is an IDF project
├── sdkconfig             # generated config file — don't edit by hand
└── main/
    ├── CMakeLists.txt    # registers your source files with the build system
    └── main.c            # your code
```
 
The top-level `CMakeLists.txt` is always the same two lines:
 
```cmake
cmake_minimum_required(VERSION 3.16)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(my_project)
```
 
The `main/CMakeLists.txt` lists the files you want to compile:
 
```cmake
idf_component_register(SRCS "main.c"
                        INCLUDE_DIRS ".")
```
 
That's it. CMake and ESP-IDF handle everything else.

### What compiler does ESP-IDF use?
 
ESP-IDF uses **GCC** (GNU Compiler Collection, most popular C compiler), but a special cross-compiling variant called **Xtensa GCC**. This is because regular GCC compiles code/programs that runs on machines like your own Windows computer with an x86 CPU. However, ESP32-S3 have two Xtensa CPU cores which use an CPU Instruction Set Architecture called **Xtensa LX7**. Espressif maintains their own fork of XtensaGCC, and it gets run every time you compile your project on the CAN TestBench, hence the binary name you'll see referenced occasionally:
 
```
xtensa-esp32s3-elf-gcc
```
 
Breaking that down:
- `xtensa` — target CPU architecture
- `esp32s3` — specific chip variant
- `elf` — the binary format it outputs (Executable and Linkable Format, standard for embedded systems)
- `gcc` — the actual compiler
This is called a **cross-compiler** — it runs on one architecture (ARM on the Raspberry Pi used for the CAN TestBench) and produces code for another (Xtensa on the ESP32). When you ran `./install.sh esp32s3` during setup, the main thing it was downloading was this toolchain. ESP-IDF also supports [Clang](https://clang.llvm.org/) as an alternative compiler, but Xtensa GCC is the default.
 
### The sdkconfig file
 
Running `idf.py set-target esp32s3` generates a `sdkconfig` file that controls hundreds of compile-time options — things like how much stack space FreeRTOS tasks get, whether WiFi is enabled, clock speeds, and so on. You can edit these with:
 
```bash
idf.py menuconfig
```
 
This opens a terminal UI for browsing all options. For most projects, you won't need to touch it, but it's there when you do.
 
---

# Sourcing the ESP-IDF Toolchain
 
Before you can use `idf.py` or any ESP-IDF tools, you need to **source** the toolchain. But what does sourcing actually mean?
 
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
cd ~/projects
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







