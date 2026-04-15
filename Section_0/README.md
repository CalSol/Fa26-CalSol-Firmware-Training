# Remote SSH'ing into the CAN TestBench
If you are not a part of CalSol or do not have a version of our CAN TestBench set up, but would still like to follow along with your own ESP32-S3, feel free to jump to Section 1.

## Part 1 — SSH access via Tailscale

We use [Tailscale](https://tailscale.com) to connect to the Pi securely from anywhere without opening any ports.

### Step 1 — Install Tailscale on your machine

Go to [tailscale.com/download](https://tailscale.com/download) and install the client for your OS (Mac, Windows, or Linux). Sign in with the account details shared with you by the team.

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

---

## Quick reference

| Task | Command |
|---|---|
| SSH into the Pi | `ssh yourname@stolerpi.tail1234ab.ts.net` |
| Change your password | `passwd` |
| Check who's logged in | `who` |


# Basic Unix Commands 
