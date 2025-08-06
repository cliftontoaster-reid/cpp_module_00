# Exercise 01: My Awesome PhoneBook

This project is a simple interactive phonebook management system implemented in C++. It allows users to add, search, and view contact information.

## Description

The `phonebook` program runs in a loop, accepting commands from the user to manage a list of contacts. The phonebook can store a maximum of 8 contacts. When a 9th contact is added, the oldest contact is replaced.

## Features

The program supports the following commands:

- **`ADD`**: Prompts the user to enter information for a new contact:
  - First Name
  - Last Name
  - Nickname
  - Phone Number
  - Darkest Secret
- **`SEARCH`**: Displays a list of all saved contacts with truncated fields. The user can then enter the index of a contact to view their full details.
- **`EXIT`**: Terminates the program.

## Usage

### Compilation

To compile the program, use the provided `Makefile`:

```bash
make
```

This will create the `phonebook` executable in the root directory.

### Running the Program

To start the phonebook application, run the executable:

```bash
./phonebook
```

The program will then prompt you for a command.

**Example Session:**

```txt
Enter command (ADD, SEARCH, EXIT): ADD
Enter name: Doe
Enter first name: John
Enter nickname: Johnny
Enter phone number: 555-1234
Enter darkest secret: He'''s afraid of the dark.
Contact added successfully.

Enter command (ADD, SEARCH, EXIT): SEARCH
  1 |        Doe |       John |     Johnny |
Enter contact ID to view details (1-1): 1
╔══════════════════════════════════════════════════╗
║ Contact Details                                  ║
╠══════════════════════════════════════════════════╣
║ Name:            Doe                             ║
║ First Name:      John                            ║
║ Nickname:        Johnny                          ║
║ Phone Number:    555-1234                        ║
║ Darkest Secret:  He'''s afraid of the dark.      ║
╚══════════════════════════════════════════════════╝

Enter command (ADD, SEARCH, EXIT): EXIT
Exiting program.
```

### Cleaning Up

The `Makefile` also includes rules to clean up the build files:

- `make clean`: Removes the object files.
- `make fclean`: Removes the object files and the `phonebook` executable.
- `make re`: Recompiles the project from scratch.
