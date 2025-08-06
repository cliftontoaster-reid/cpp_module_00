# Exercise 00: Megaphone

This project is a simple C++ program that acts like a megaphone, taking any string provided as an argument and printing it to the standard output in uppercase.

## Description

The `megaphone` program concatenates all its command-line arguments and converts them to uppercase. If no arguments are provided, it prints a default message simulating feedback noise.

## Usage

### Compilation

To compile the program, use the provided `Makefile`:

```bash
make
```

This will create the `megaphone` executable in the root directory.

### Running the Program

To use the megaphone, run the executable with one or more strings as arguments:

```bash
./megaphone "shhhhh... I think the students are asleep!"
```

**Output:**
```
SHHHHH... I THINK THE STUDENTS ARE ASLEEP!
```

You can provide multiple arguments:

```bash
./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
```

**Output:**
```
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
```

If you run the program without any arguments, it will print a special message:

```bash
./megaphone
```

**Output:**
```
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### Cleaning Up

The `Makefile` also includes rules to clean up the build files:
- `make clean`: Removes the object files.
- `make fclean`: Removes the object files and the `megaphone` executable.
- `make re`: Recompiles the project from scratch.
