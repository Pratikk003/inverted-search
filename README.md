# Inverted Search in C

A command-line program that builds an **inverted index** (word → files → count)
from a set of text files, using a hash table of linked lists. You can search
for a word and see which files contain it and how many times, update the index
with more files, and save/load the database to a file.

## How it works

The database is a hash table with 27 slots:

- Slots `0`-`25` hold words starting with `a`-`z` (case-insensitive)
- Slot `26` holds words starting with any other character (digits, symbols)

Each slot is a linked list of **main nodes** (one per unique word). Each main
node has a linked list of **sub nodes** (one per file containing that word,
with the word's count in that file).

```
ht[7] -> [hello | 1 file]  -> [hi | 2 files] -> ...
              |                    |
        file1.txt : 1        file2.txt : 1 -> file1.txt : 1
```

## Build

Requires `gcc` and `make`.

```bash
make          # builds ./inverted_search
make run      # builds and runs with sample files
make clean    # removes object files and the executable
make help     # prints usage
```

## Usage

Pass one or more `.txt` files on the command line:

```bash
./inverted_search file1.txt file2.txt file3.txt
```

Files that are not `.txt`, do not exist, or are empty are skipped with a
message. Duplicate file names are ignored. The following menu is then shown:

| Option | Action |
|--------|--------|
| 1. Create Database | Builds the index from the validated files (only once) |
| 2. Display Database | Prints every word with its files and counts |
| 3. Search Database | Asks for a word and prints the files it appears in |
| 4. Update Database | Adds a new `.txt` file to the existing database |
| 5. Save Database | Writes the database to a `.txt` file you name |
| 6. Exit | Quits the program |

### Saved database format

One line per word:

```
#<index>;<word>;<file_count>;<file1>;<count1>;<file2>;<count2>...
```

Example (`db.txt`):

```
#7;hello;1;file1.txt;1
#7;hi;2;file2.txt;1;file1.txt;1
```

A saved database file cannot be used as an input file for *Update Database*.

## Project structure

| File | Purpose |
|------|---------|
| `main.c` | Hash table setup and the menu loop |
| `header.h` | Structures (`Flist`, `Slist`, `Mlist`, `Hash_t`) and function prototypes |
| `validation.c` | Command-line argument validation and file list creation |
| `Create_db.c` | Reads files and builds the inverted index |
| `display_db.c` | Displays the database |
| `Search_db.c` | Searches for a word |
| `update_db.c` | Adds a new file to the database |
| `Save_db.c` | Saves the database to a file |
| `Makefile` | Build script |
| `file1.txt` ... `file5.txt` | Sample input files |
| `db.txt` | Sample saved database |

## Limitations

- Only `.txt` input files are supported.
- Search is case-sensitive for the full word, though the first letter picks the
  hash slot case-insensitively.
- The saved database can be written, but not loaded back into the program.
- File names and search words are limited to 99 characters.

## Possible improvements

- Load a saved database on startup
- Case-insensitive search
- Better input handling in the menu (non-numeric input)

---

Author: Pratik Kambire
