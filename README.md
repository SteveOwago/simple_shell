# simple_shell
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
TEAM PROJECT
AUTHORS: Steve Owago & Bellamine Bulinda

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
This is an ALX collaboration project on Shell. We were tasked to create a simple shell that mimics the Bash shell. Our shell shall be called hsh

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Project was completed using
C language
Shell
Betty linter

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
General Requirement for project
All files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Shell should not have any memory leaks
No more than 5 functions per file
All header files should be include guarded
Write a README with the description of the project
Description
hsh is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
How hsh works
Prints a prompt and waits for a command from the user
Creates a child process in which the command is checked
Checks for built-ins, aliases in the PATH, and local executable programs
The child process is replaced by the command, which accepts arguments
When the command is done, the program returns to the parent process and prints the prompt
The program is ready to receive a new command
To exit: press Ctrl-D or enter "exit" (with or without a status)
Works also in non interactive mode

Compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Invocation
Usage: hsh [filename]

To invoke hsh, compile all .c files in the repository and run the resulting executable.

hsh can be invoked both interactively and non-interactively. If hsh is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:

$ echo "echo 'hello'" | ./hsh
'hello'
$
If hsh is invoked with standard input connected to a terminal (determined by isatty(3)), an interactive shell is opened. When executing interactively, hsh displays the prompt $  when it is ready to read a command.

Example:

$./hsh
$
Alternatively, if command line arguments are supplied upon invocation, hsh treats the first argument as a file from which to read commands. The supplied file should contain one command per line. hsh runs each of the commands contained in the file in order before exiting.

Example:

$ cat test
echo 'hello'
$ ./hsh test
'hello'
$
Environment
Upon invocation, hsh receives and copies the environment of the parent process in which it was executed. This environment is an array of name-value strings describing variables in the format NAME=VALUE. A few key environmental variables are:

HOME
The home directory of the current user and the default directory argument for the cd builtin command.

$ echo "echo $HOME" | ./hsh
/home/projects
PWD
The current working directory as set by the cd command.

$ echo "echo $PWD" | ./hsh
/home/projects/alx/simple_shell
OLDPWD
The previous working directory as set by the cd command.

$ echo "echo $OLDPWD" | ./hsh
/home/projects/alx/printf
PATH
A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

$ echo "echo $PATH" | ./hsh
/home/projects/.cargo/bin:/home/projects/.local/bin:/home/projects/.rbenv/plugins/ruby-build/bin:/home/projects/.rbenv/shims:/home/projects/.rbenv/bin:/home/projects/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/projects/.cargo/bin:/home/projects/workflow:/home/projects/.local/bin
Command Execution
After receiving a command, hsh tokenizes it into words using " " as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command. hsh then proceeds with the following actions:

If the first character of the command is neither a slash (\) nor dot (.), the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
If the first character of the command is none of a slash (\), dot (.), nor builtin, hsh searches each element of the PATH environmental variable for a directory containing an executable file by that name.
If the first character of the command is a slash (\) or dot (.) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.
Exit Status
hsh returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

If a command is not found, the return status is 127; if a command is found but is not executable, the return status is 126.

All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

Signals
While running in interactive mode, hsh ignores the keyboard input Ctrl+c. Alternatively, an input of end-of-file (Ctrl+d) will exit the program.

User hits Ctrl+d in the third line.

$ ./hsh
$ ^C
$ ^C
$
Variable Replacement
hsh interprets the $ character for variable replacement.

$ENV_VARIABLE
ENV_VARIABLE is substituted with its value.

Example:

$ echo "echo $PWD" | ./hsh
/home/projects/alx/simple_shell
$?
? is substitued with the return value of the last program executed.

Example:

$ echo "echo $?" | ./hsh
0
$$
The second $ is substitued with the current process ID.

Example:

$ echo "echo $$" | ./hsh
6494
Comments
hsh ignores all words and characters preceeded by a # character on a line.

Example:

$ echo "echo 'hello' #this will be ignored!" | ./hsh
'hello'
Operators
hsh specially interprets the following operator characters:

; - Command separator
Commands separated by a ; are executed sequentially.

Example:

$ echo "echo 'hello' ; echo 'world'" | ./hsh
'hello'
'world'
&& - AND logical operator
command1 && command2: command2 is executed if, and only if, command1 returns an exit status of zero.

Example:

$ echo "error! && echo 'hello'" | ./hsh
./hsh: 1: error!: not found
$ echo "echo 'all good' && echo 'hello'" | ./hsh
'all good'
'hello'
|| - OR logical operator
command1 || command2: command2 is executed if, and only if, command1 returns a non-zero exit status.

Example:

$ echo "error! || echo 'but still runs'" | ./hsh
./hsh: 1: error!: not found
'but still runs'
The operators && and || have equal precedence, followed by ;.

hsh Builtin Commands
cd
Usage: cd [DIRECTORY]
Changes the current directory of the process to DIRECTORY.
If no argument is given, the command is interpreted as cd $HOME.
If the argument - is given, the command is interpreted as cd $OLDPWD and the pathname of the new working directory is printed to standad output.
If the argument, -- is given, the command is interpreted as cd $OLDPWD but the pathname of the new working directory is not printed.
The environment variables PWD and OLDPWD are updated after a change of directory.
Example:

$ ./hsh
$ pwd
/home/projects/alx/simple_shell
$ cd ../
$ pwd
/home/projects/alx
$ cd -
$ pwd
/home/projects/alx/simple_shell
alias
Usage: alias [NAME[='VALUE'] ...]
Handles aliases.
alias: Prints a list of all aliases, one per line, in the form NAME='VALUE'.
alias NAME [NAME2 ...]: Prints the aliases NAME, NAME2, etc. one per line, in the form NAME='VALUE'.
alias NAME='VALUE' [...]: Defines an alias for each NAME whose VALUE is given. If name is already an alias, its value is replaced with VALUE.
Example:

$ ./hsh
$ alias show=ls
$ show
AUTHORS            builtins_help_2.c  errors.c         linkedlist.c        shell.h       test
README.md          env_builtins.c     getline.c        locate.c            hsh
alias_builtins.c   environ.c          helper.c         main.c              split.c
builtin.c          err_msgs1.c        helpers_2.c      man_1_simple_shell  str_funcs1.c
builtins_help_1.c  err_msgs2.c        input_helpers.c  proc_file_comm.c    str_funcs2.c
exit
Usage: exit [STATUS]
Exits the shell.
The STATUS argument is the integer used to exit the shell.
If no argument is given, the command is interpreted as exit 0.
Example:

$ ./hsh
$ exit
env
Usage: env
Prints the current environment.
Example:

$ ./hsh
$ env
NVM_DIR=/home/projects/.nvm
...
setenv
Usage: setenv [VARIABLE] [VALUE]
Initializes a new environment variable, or modifies an existing one.
Upon failure, prints a message to stderr.
Example:

$ ./hsh
$ setenv NAME Poppy
$ echo $NAME
Poppy
unsetenv
Usage: unsetenv [VARIABLE]
Removes an environmental variable.
Upon failure, prints a message to stderr.
Example:

$ ./hsh
$ setenv NAME Poppy
$ unsetenv NAME
$ echo $NAME

$
What we learned:
How a shell works and finds commands
Creating, forking and working with processes
Executing a program from another program
Handling dynamic memory allocation in a large program
Pair programming and team work
Building a test suite to check our own code
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

TASKS
0. Betty would be proud
mandatory
Write a beautiful code that passes the Betty checks

1. Simple shell 0.1
Write a UNIX command line interpreter.

Usage: simple_shell
Your Shell should:

Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
You don’t have to:

use the PATH
implement built-ins
handle special characters : ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments

2. Simple shell 0.2
mandatory
Simple shell 0.1 +

Handle command lines with arguments

3. Simple shell 0.3
mandatory
Simple shell 0.2 +

Handle the PATH
fork must not be called if the command doesn’t exist

4. Simple shell 0.4
mandatory
Simple shell 0.3 +

Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit

5. Simple shell 1.0
mandatory
Simple shell 0.4 +

Implement the env built-in, that prints the current environment

6. Simple shell 0.1.1
#advanced
Simple shell 0.1 +

Write your own getline function
Use a buffer to read many chars at once and call the least possible the read system call
You will need to use static variables
You are not allowed to use getline
You don’t have to:

be able to move the cursor

7. Simple shell 0.2.1
#advanced
Simple shell 0.2 +

You are not allowed to use strtok

8. Simple shell 0.4.1
#advanced
Simple shell 0.4 +

handle arguments for the built-in exit
Usage: exit status, where status is an integer used to exit the shell

9. setenv, unsetenv
#advanced
Simple shell 1.0 +

Implement the setenv and unsetenv builtin commands

setenv
Initialize a new environment variable, or modify an existing one
Command syntax: setenv VARIABLE VALUE
Should print something on stderr on failure
unsetenv
Remove an environment variable
Command syntax: unsetenv VARIABLE
Should print something on stderr on failure

10. cd
#advanced
Simple shell 1.0 +

Implement the builtin command cd:

Changes the current directory of the process.
Command syntax: cd [DIRECTORY]
If no argument is given to cd the command must be interpreted like cd $HOME
You have to handle the command cd -
You have to update the environment variable PWD when you change directory
man chdir, man getcwd

11. ;
#advanced
Simple shell 1.0 +

Handle the commands separator ;

12. && and ||
#advanced
Simple shell 1.0 +

Handle the && and || shell logical operators

13. alias
#advanced
Simple shell 1.0 +

Implement the alias builtin command
Usage: alias [name[='value'] ...]
alias: Prints a list of all aliases, one per line, in the form name='value'
alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value

14. Variables
#advanced
Simple shell 1.0 +

Handle variables replacement
Handle the $? variable
Handle the $$ variable

15. Comments
#advanced
Simple shell 1.0 +

Handle comments (#)

16. File as input
#advanced
Simple shell 1.0 +

Usage: simple_shell [filename]
Your shell can take a file as a command line argument
The file contains all the commands that your shell should run before exiting
The file should contain one command per line
In this mode, the shell should not print a prompt and should not read from stdin


