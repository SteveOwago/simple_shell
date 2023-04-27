# General
- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)
- Write a README with the description of your project
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

# List of allowed functions and system calls
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

# Write a beautiful code that passes the Betty checks	

## Write a UNIX command line interpreter.

# Usage: simple_shell
### Your Shell should:

- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
### Handle errors.
- You have to handle the “end of file” condition (Ctrl+D)
+ You don’t have to:
- use the PATH
- implement built-ins
- handle special characters : ", ', `, \, *, &, #
- be able to move the cursor
- handle commands with arguments
- execve will be the core part of your Shell, don’t forget to pass the environ to it…

# Simple shell 0.1 +
- Handle command lines with arguments

# Simple shell 0.2 +

- Handle the PATH
- fork must not be called if the command doesn’t exist

# Simple shell 0.3 +
- Implement the exit built-in, that exits the shell
- Usage: exit
- You don’t have to handle any argument to the built-in exit

# Simple shell 0.4 +
- Implement the env built-in, that prints the current environment

# Simple shell 0.1 +
- Write your own getline function
- Use a buffer to read many chars at once and call the least possible the read system call
- You will need to use static variables
- You are not allowed to use getline
- You don’t have to:

- be able to move the cursor

# Simple shell 0.2 +
- You are not allowed to use strtok

# Simple shell 0.4 +
- handle arguments for the built-in exit
- Usage: exit status, where status is an integer used to exit the shell

# Simple shell 1.0 +

## Implement the setenv and unsetenv builtin commands

+ setenv
- Initialize a new environment variable, or modify an existing one
- Command syntax: setenv VARIABLE VALUE
- Should print something on stderr on failure
+ unsetenv
- Remove an environment variable
- Command syntax: unsetenv VARIABLE
- Should print something on stderr on failure

# Simple shell 1.0 +

## Implement the builtin command cd:

- Changes the current directory of the process.
- Command syntax: cd [DIRECTORY]
- If no argument is given to cd the command must be interpreted like cd $HOME
- You have to handle the command cd -
- You have to update the environment variable PWD when you change directory

# Simple shell 1.0 +

- Handle the commands separator ;
# Project By Steve and Bellarmine
