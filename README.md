Simple Shell

A simple UNIX command interpreter project developed as part of the ALX Software Engineering program. This shell is capable of executing basic commands and supports features like command line arguments, PATH handling, and built-in commands.

Table of Contents

- Getting Started
- Usage
- Features
- Built-in Commands
- File Input Mode



Getting Started
To get started with this Simple Shell project, follow these steps:

- Clone the repository to your local machine:

git clone https://github.com/wajdi-khelifi/simple_shell.git


Features

- Basic command execution.
- Command line arguments support.
- PATH environment variable handling.
- Built-in commands: exit and env.
- File input mode for batch processing.

Built-in Commands

The Simple Shell supports the following built-in commands:

"exit"
Exits the shell. Usage: exit [status].

"env"
Displays the current environment variables.

"cd"
Changes the current directory. Usage: cd [DIRECTORY].

"alias"
Defines or displays aliases for commands. Usage: alias [name[='value']].

File Input Mode

You can use the shell in file input mode by providing a filename as a command line argument. The shell will read and execute commands from the file, one command per line.

