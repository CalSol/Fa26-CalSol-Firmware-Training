# Running the SILVER Telemetry Backend on the Raspberry Pi

These instructions get the CalSol `new-telemetry` backend (InfluxDB + Grafana + the Python ingestor) running on the Pi over SSH. The Pi runs Debian Linux (aarch64), so the Mac and Windows steps in the main telemetry setup page do **not** apply here. Same pieces, different install commands.

**IMPORTANT: Never edit `main.py`.** The Pi has no screen, so one of the ingestors (`pynput`, used by the keyboard ingestor) crashes looking for a display. We fix this by running the backend through `xvfb-run` (a fake display) instead of changing any code. Always launch with `xvfb-run -a uv run main.py`, and never use `./run.sh` on the Pi (it opens a Terminal window with `osascript`, which is Mac-only).

## Part 1 — Get the code onto the Pi

### Step 1 — SSH into the Pi with agent forwarding

Use `-A` so the Pi can borrow the SSH key already on your laptop. No new key is needed.

```bash
ssh -A yourname@<device_name>
```

### Step 2 — Check that GitHub accepts you

```bash
ssh -T git@github.com
```

You should see `Hi <your-github-username>! You've successfully authenticated...`. If you see `Permission denied (publickey)`, your laptop's key isn't on GitHub (or you forgot `-A`). Reconnect with `-A`, or see the troubleshooting table at the bottom.

### Step 3 — Clone the repo

```bash
cd ~
git clone git@github.com:CalSol/new-telemetry.git
```

(If you can't use SSH, `git clone https://github.com/CalSol/new-telemetry.git` also works. It will ask for your GitHub username and a personal access token if the repo is private.)

## Part 2 — Install uv

`uv` manages the Python version and dependencies for the project, so you don't install Python packages by hand.

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
source $HOME/.local/bin/env
```

Check it worked:

```bash
uv --version
```

Note: the `source` line only affects your current shell. See [Part 8](#part-8--optional-bashrc-shortcuts) to make it automatic.

## Part 3 — Install InfluxDB

### Step 1 — Add the InfluxData apt repository

You'll be asked for your **Pi account password** (the one you use for `sudo`).

```bash
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://repos.influxdata.com/influxdata-archive.key | sudo gpg --dearmor -o /etc/apt/keyrings/influxdata.gpg
echo "deb [signed-by=/etc/apt/keyrings/influxdata.gpg] https://repos.influxdata.com/debian stable main" | sudo tee /etc/apt/sources.list.d/influxdata.list
```

### Step 2 — Install InfluxDB 2 and the CLI

```bash
sudo apt update && sudo apt install -y influxdb2 influxdb2-cli
```

**You will probably see a blue "Package configuration" screen** titled *Modified configuration file*, asking what to do about `influxdata.list`. This happens because the package ships its own copy of the repo file we just created by hand.

1. Use the arrow keys to highlight **install the package maintainer's version**. It starts on "keep the local version", so move it.
2. Press `Tab` to jump to `<Ok>`, then press `Enter`.

The install then finishes on its own. (Choosing the maintainer's version is harmless. It points at the same repo and keeps future updates clean.)

### Step 3 — Start InfluxDB and run the one-time setup

```bash
sudo systemctl enable --now influxdb
influx setup --username admin --password password --token token --org calsol --bucket influx --force
```

This is identical to the Mac setup command. You should see a table showing user `admin`, organization `calsol`, bucket `influx`.

InfluxDB now runs as a background service and starts automatically on boot. You never need to launch it yourself.

## Part 4 — Install Grafana

```bash
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://apt.grafana.com/gpg.key | sudo gpg --dearmor -o /etc/apt/keyrings/grafana.gpg
echo "deb [signed-by=/etc/apt/keyrings/grafana.gpg] https://apt.grafana.com stable main" | sudo tee /etc/apt/sources.list.d/grafana.list
sudo apt update && sudo apt install -y grafana
```

Allow Grafana to auto-refresh faster than 5 seconds (needed for a real-time stream):

```bash
sudo sed -i 's/^;*min_refresh_interval.*/min_refresh_interval = 100ms/' /etc/grafana/grafana.ini
```

Then start it and make it run on boot:

```bash
sudo systemctl enable --now grafana-server
```

(If the config edit doesn't seem to take effect, run `sudo systemctl restart grafana-server`.)

## Part 5 — Install xvfb (the fake display)

```bash
sudo apt install -y xvfb
```

This is what lets `pynput` load without a monitor attached, so we never have to modify `main.py`. It pulls in a couple dozen small packages. That's normal.

## Part 6 — Configure the backend

```bash
cd ~/new-telemetry
nano config/main.json5
```

Use the same values as on your Mac: the Influx org (`calsol`), bucket (`influx`), token (`token`), and which loggers/ingestors/processors you want running. In `nano`, save with `Ctrl+O` then `Enter`, and exit with `Ctrl+X`.

Do **not** edit `main.py`. All configuration happens in `config/main.json5`.

## Part 7 — Run it

```bash
cd ~/new-telemetry
xvfb-run -a uv run main.py
```

What to expect:

- **First run is slow.** `uv` downloads/creates the virtual environment and installs the dependencies. A `SyntaxWarning` from `filterpy` is harmless.
- **"Recent session detected" prompt:** On a brand-new setup you won't see this. If you do, press `Enter` to reuse the last settings or type any other key + `Enter` to pick fresh ones.
- **XBee port prompt:** The ingestor lists available serial ports and asks which one is the XBee. If it says "No obvious XBee found", it will ask again. Type the port's index (for example `0`) or its name (for example `/dev/ttyACM0`). Run `ports` (see the [firmware training page](#)) or `ls /dev/ttyUSB* /dev/ttyACM*` beforehand if you're unsure which device is which.
- **Stop it** with `Ctrl+C`.


## Part 8 — Optional: `.bashrc` shortcuts

Like the ESP-IDF setup, you can put these in `~/.bashrc` so they work every time you SSH in. Both are optional but recommended.

**Add these two things:**

```bash
# makes uv available (for the telemetry backend)
source $HOME/.local/bin/env

# cd into CalSol telemetry repo and start the backend
alias telem='cd $HOME/new-telemetry && xvfb-run -a uv run main.py'
```

These work **alongside** the ESP-IDF line (`source /opt/esp-idf/export.sh`). They don't conflict, because the `uv` line only adds `uv` to your PATH, and ESP-IDF sets up its own toolchain. Keep the ESP-IDF line first and put these below it.

<details>
<summary>Setting up the shortcuts (step by step)</summary>
<dl><dd>

Open your `.bashrc` in vim:

```bash
vim ~/.bashrc
```

Vim has two modes: **normal mode** (for navigating) and **insert mode** (for typing). It opens in normal mode.

- Before trying to edit in Vim, do not try pressing anything with your mouse!!! It won't work!

1. Press `Shift+G` to jump to the last line
2. Press `o` to open a new line below and enter insert mode
3. Type (or paste) the lines:
   ```bash
   # makes uv available (for the telemetry backend)
   source $HOME/.local/bin/env

   # cd into CalSol telemetry repo and start the backend
   alias telem='cd $HOME/new-telemetry && xvfb-run -a uv run main.py'
   ```
4. Press `Esc` to go back to normal mode
5. Type `:wq` and hit `Enter` to save and quit (`w` = write, `q` = quit)
   If you make a mistake and want to bail out without saving, press `Esc` then type `:q!` and hit `Enter`.

Apply the changes to your current session without logging out:

```bash
source ~/.bashrc
```

Now you can start the backend from anywhere with just:

```bash
telem
```

What those lines do:

- `source $HOME/.local/bin/env`: puts `uv` on your PATH in every new shell
- `alias telem=...`: goes to the repo and launches the backend through `xvfb-run` in one command

</dd></dl>
</details>

You can also append the two entries without opening an editor:

```bash
echo '
# makes uv available (for the telemetry backend)
source $HOME/.local/bin/env

# cd into CalSol telemetry repo and start the backend
alias telem='"'"'cd $HOME/new-telemetry && xvfb-run -a uv run main.py'"'"'' >> ~/.bashrc
source ~/.bashrc
```

## Part 9 — Viewing Grafana

Grafana runs on port 3000 of the Pi. Pick one:

**Option A — Open it directly** from a browser on your laptop (both devices on the same Tailscale network):

```
http://<device_name>:3000
```

**Option B — SSH tunnel**, which also works if the direct link doesn't. Run this on **your own machine**, leave it open, then visit `http://localhost:3000`:

```bash
ssh -L 3000:localhost:3000 yourname@<device_name>
```

The default login is Username: `admin`, Password: `admin`. On first login, press **SKIP** when it asks you to change the password, so you don't have to remember a different one later.

Then make a dashboard to see your data, as described in the main telemetry setup page.

## Quick reference

| Task | Command |
|---|---|
| SSH in (with GitHub key forwarding) | `ssh -A yourname@<device_name>` |
| Start the backend | `cd ~/new-telemetry && xvfb-run -a uv run main.py` (or `telem`) |
| Stop the backend | `Ctrl+C` |
| Check InfluxDB is running | `systemctl status influxdb` |
| Check Grafana is running | `systemctl status grafana-server` |
| Restart Grafana | `sudo systemctl restart grafana-server` |
| Update the repo | `cd ~/new-telemetry && git pull` |

## Troubleshooting

| Problem | Fix |
|---|---|
| `git@github.com: Permission denied (publickey)` | The Pi has no key on GitHub. Reconnect with `ssh -A` (and make sure your laptop's key works with `ssh -T git@github.com`), or clone over HTTPS. |
| `uv: command not found` | Run `source $HOME/.local/bin/env`, or add it to `~/.bashrc` (Part 8). |
| `ImportError: this platform is not supported ... failed to acquire X connection` | You ran `uv run main.py` directly. Use `xvfb-run -a uv run main.py` instead. **Do not edit `main.py`.** |
| `./run.sh: osascript: command not found` | `run.sh` is Mac-only. Use `xvfb-run -a uv run main.py`. |
| `sudo: 3 incorrect password attempts` | That's your Pi account password, not your Mac or GitHub password. If you've lost it, ask a team admin to run `sudo passwd yourname`. |
| Blue "Modified configuration file" screen during the Influx install | Choose **install the package maintainer's version**, then `Tab` to `<Ok>` and `Enter` (Part 3, Step 2). |
| "Unauthorized Access" errors from the Python code | Re-run the `influx setup ... --force` command from Part 3, and double-check the token in `config/main.json5` matches. |
| XBee not found at the port prompt | Check the XBee is plugged in, then pick the port by index or name from the printed list. |
| Can't reach Grafana from your laptop | Confirm it's running (`systemctl status grafana-server`) and try the SSH tunnel in Part 9. |
