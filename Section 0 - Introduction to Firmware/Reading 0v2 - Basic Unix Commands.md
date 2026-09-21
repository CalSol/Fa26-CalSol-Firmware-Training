# Basic Unix Commands 
 
### The prompt
 
You'll see something like this in the terminal:
 
```
(env) oski@stolerpi:~ $
```
 
This tells you: your environment (env), your username (`oski`), the you're machine's host name (`stolerpi`), and where you are in the filesystem (`~` means your home folder). The `$` or '%' is just a prompt character that means it's ready for a command.
 
### Moving around
 
```bash
pwd                  # "print working directory" — shows where you are right now
ls                   # list files in the current folder
ls -la               # same but shows hidden files and extra details like file sizes
cd projects          # move into a folder called "projects"
cd ..                # go up one level to the parent folder
cd ~                 # go back to your home folder from anywhere
```
 
### Working with files
 
```bash
mkdir myfolder          # create a new folder
cp notes.txt backup.txt # copy a file
mv notes.txt docs/      # move a file into a folder
mv notes.txt new.txt    # rename a file (move and rename are the same command)
rm old.txt              # delete a file — no trash bin, this is permanent
rm -r myfolder          # delete a folder and everything inside it
```
 
### Useful shortcuts
 
```bash
Ctrl + C             # terminates process (program) that is running
Ctrl + D             # log out of the session
Up arrow             # cycle through previous commands — saves a lot of retyping
Tab                  # autocomplete a filename or command
clear                # clear the screen
```
 
### Understanding file paths
 
There are two ways to refer to a file location:
 
- **Absolute path** — starts from the root of the filesystem with `/`. Works from anywhere.
  Example: `/home/oski/projects/hello_world`
- **Relative path** — starts from where you currently are. Shorter but depends on your location.
  Example: `projects/hello_world` (only works if you're already in `/home/oski`)
`~` is a shortcut for your home folder (`/home/yourname`), so `~/projects` and `/home/oski/projects` are the same thing.
 
### Getting help
 
If you're not sure what a command does, two options:
 
```bash
man ls               # opens the full manual page for a command — q to quit
ls --help            # shorter built-in help, works for most commands
```
