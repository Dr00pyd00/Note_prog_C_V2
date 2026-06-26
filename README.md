
# Note CLI for linux/wsl V2

In this project I build a CLI for taking notes.  
This time I use SQLITE3 as database.

--- 

### Goal 

When you do some Networks stuff for example, you have to note multiple IP, outputs , error messages etc. This program is here for stock some text data and have fast access to it. This is like a fast-to-use bloc note.  
This is the V2.

---

### Stack

- Full C program
- sqlite3 as database
- gcc as compiler

---

### How it Work 

You have 4 mecanisms:

```bash 
# add a new note
note "my first note" 

# see all notes 
note all

# see note detail by id
note see <note_id>

# delete note by id 
note del <note_id>

```

### How to Install 

You have multiples ways to install:

#### 1/ Create the path in your home :

For this you have to ensure this path is in $PATH.

```bash 
git clone https://github.com/Dr00pyd00/Note_prog_C_V2.git 
cd Note_prog_C_V2
make
mkdir -p ~/.local/bin
cp note ~/.local/bin/note

# force path to exist:
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

#### 2/ Use /usr/local/bin :

For this you need use **sudo** for move binary file.
```bash 
git clone https://github.com/Dr00pyd00/Note_prog_C_V2.git 
cd Note_prog_C_V2
make
sudo cp note /usr/local/bin/note
```

--- 


### BONUS — Static Binary


On minimal machines without shared libraries installed, you can build a fully autonomous binary.  
The tradeoff is binary size — **~2.8 MB** instead of 16 KB.


```bash
gcc src/*.c -Iinclude -lsqlite3 -static -lm -o cnote_static
```
Move it wherever you want in your PATH.


