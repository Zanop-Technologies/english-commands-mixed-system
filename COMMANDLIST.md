# Cheatsheet for Commands

Here are all the commands in ECMXS (aka Zanop Shell):

## File Management

| Command | Meaning |
|---------|---------|
|`chd`| **Move into the next directory.** |
|`con`| **List the contents of a directory.** |
|`cre`| **Create a file.** |
|`cre dir` | **Create a new directory.** |
|`del` or `rm` | **Remove a file.** |
|`del --dir` or `rm --dir` | **Delete a directory.** |

## List of Installed Programs (Forgotten Commands)

| Command | Meaning |
|---------|---------|
|`lis app`| **List apps that are installed.** |
|`lis app --spef` | **List specific apps with the specific letter.** |
|`lis app --search` | **Search an app that is already on your device.** | 
|`lis app --mul --spef --search` | **List multiple apps with a specific letter.** |
|`lis app --mul --spef --wd --search` | **List multiple apps with a specific word.** |

## Networking

> NOTE: **curl** and **wget** do not follow standard linux flags.

### CURL and WGET

#### CURL and WGET (They can use the same flags.)

| Command | Meaning |
|---------|---------|
|`curl --int <URL>`| **Interact something from the internet.** |
|`curl --int --log <URL>`| **Same as the first `curl` command but with logs.** |
|`curl --int --log --sim <URL>` | **Same but simulated.** |
|`curl --dd <URL>` | **Download something from the internet.** |
|`curl --dd --log <URL>` | **Download with logs.** |
|`frt -i -p <packets> <ip>`| **Ping a network.** |

## System

| Command | Meaning |
|---------|---------|
|`sy stat`| **Stats of your computer.** |
|`sy stat --log`| **The explicit logs of your computer.** |
|`sy stat --spef --prt`| **Specfic part of your computer that needs the statistic table.** |
|`sy tsk`| **Task manager.** |
|`sy tsk --end --spef`| **End a specific task.** |
|`sy tsk --end --l`| **End all tasks.** |

## Package Management

| Command | Meaning |
|---------|---------|
|`sft check pkg`| **Check a packages info.** |
(all package management commands will be added soon)

## Misc

### Users

`usr --adm --cre <username>` &RightArrow; **Create a user.**

`usr --adm --cre --pas <username> <password>` &RightArrow; **Create a user with a password.**

`usr --adm --del <username> > /acc` &RightArrow; **Delete a user.**

`usr --sy --info <username>` &RightArrow; **Info of a user.**

### Utilities

`sdown` &rightarrow; Shut the computer.

`lg` &rightarrow; Log out of the computer on the account you are using.

`lg --all` &rightarrow; Logout of everything.