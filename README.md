# C++ chapter 01

Just a bit of C++-- nothing too crazy here.

## Exercise 00: Megaphone

This project is a simple C++ program that acts like a megaphone, taking any string provided as an argument and printing it to the standard output in uppercase.

The `megaphone` program concatenates all its command-line arguments and converts them to uppercase. If no arguments are provided, it prints a default message simulating feedback noise.

### Usage

#### Compilation

To compile the program, navigate to the `ex00` directory and use the provided `Makefile`:

```bash
cd ex00
make
```

This will create the `megaphone` executable in the `ex00` directory.

#### Running the Program

To use the megaphone, run the executable from the root directory with one or more strings as arguments:

```bash
./ex00/megaphone "shhhhh... I think the students are asleep!"
```

**Output:**

```
SHHHHH... I THINK THE STUDENTS ARE ASLEEP!
```

You can provide multiple arguments:

```bash
./ex00/megaphone Damnit " ! " "Sorry students, I thought this thing was off."
```

**Output:**

```
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
```

If you run the program without any arguments, it will print a special message:

```bash
./ex00/megaphone
```

**Output:**

```
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

#### Cleaning Up

Inside the `ex00` directory, the `Makefile` also includes rules to clean up the build files:

- `make clean`: Removes the object files.
- `make fclean`: Removes the object files and the `megaphone` executable.
- `make re`: Recompiles the project from scratch.

## Exercise 01: My Awesome Phone Book

This project is a simple interactive phone book management system implemented in C++. It allows users to add, search, and view contact information.

The `phonebook` program runs in a loop, accepting commands from the user to manage a list of contacts. The phone book can store a maximum of 8 contacts. When a 9th contact is added, the oldest contact is replaced.

### Features

The program supports the following commands:

- **`ADD`**: Prompts the user to enter information for a new contact:
  - First Name
  - Last Name
  - Nickname
  - Phone Number
  - Darkest Secret
- **`SEARCH`**: Displays a list of all saved contacts with truncated fields. The user can then enter the index of a contact to view their full details.
- **`EXIT`**: Terminates the program.

### Usage

#### Compilation

To compile the program, navigate to the `ex01` directory and use the provided `Makefile`:

```bash
cd ex01
make
```

This will create the `phonebook` executable in the `ex01` directory.

#### Running the Program

To start the phonebook application, run the executable from the root directory:

```bash
./ex01/phonebook
```

The program will then prompt you for a command.

**Example Session:**

```txt
Enter command (ADD, SEARCH, EXIT): ADD
Enter name: Doe
Enter first name: John
Enter nickname: Johnny
Enter phone number: 555-1234
Enter darkest secret: He's afraid of the dark.
Contact added successfully.

Enter command (ADD, SEARCH, EXIT): SEARCH
  _1 |        Doe |       John |     Johnny |
Enter contact ID to view details (1-1): 1
╔══════════════════════════════════════════════════╗
║ Contact Details                                  ║
╠══════════════════════════════════════════════════╣
║ Name:            Doe                             ║
║ First Name:      John                            ║
║ Nickname:        Johnny                          ║
║ Phone Number:    555-1234                        ║
║ Darkest Secret:  He's afraid of the dark.        ║
╚══════════════════════════════════════════════════╝

Enter command (ADD, SEARCH, EXIT): EXIT
Exiting program.
```

#### Cleaning Up

Inside the `ex01` directory, the `Makefile` also includes rules to clean up the build files:

- `make clean`: Removes the object files.
- `make fclean`: Removes the object files and the `phonebook` executable.
- `make re`: Recompiles the project from scratch.
