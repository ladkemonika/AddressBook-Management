# Qt AddressBook Application

This is a simple AddressBook management application written in C++ using the Qt framework (Qt 5 or Qt 6 Widgets).

## Features
- **Add Contact**: Store a contact's Name, Mobile, Email address, and Birthday.
- **Edit Contact**: Modify an existing contact's details.
- **Delete Contact**: Remove a contact from your address book.
- **Persistent Storage**: Contacts are saved automatically in a robust local JSON file (`contacts.json`) so they remain safe when you close the app.
- **Cross-Platform**: Designed with standard Qt and standard C++ to run across OSs, although explicitly targetted and buildable on Debian GNU/Linux.

## Prerequisites (Debian GNU/Linux)

To build this application on a Debian-based Linux system (like Ubuntu or Debian), you will need the Qt development packages and a C+ compiler.

Install the required dependencies using apt:

```bash
sudo apt-get update
sudo apt-get install -y build-essential qtbase5-dev qt5-qmake
```

## Build Instructions

This project uses `qmake` as its build system. To build the application from the command line, follow these steps:

1. Open a terminal and navigate to the project directory containing `AddressBook.pro`.
2. Generate the Makefile using `qmake`:
   ```bash
   qmake AddressBook.pro
   ```
3. Compile the application using `make`:
   ```bash
   make
   ```

## Running the Application

After a successful build, the executable `AddressBook` will be created in your current directory. 

Run it via the terminal:

```bash
./AddressBook
```

## Storage Location
The application uses `QStandardPaths` to store the data file (`contacts.json`) in an OS-appropriate application data directory.
- On Linux typically: `~/.local/share/AddressBook/contacts.json` (or similar depending on desktop environment config).
