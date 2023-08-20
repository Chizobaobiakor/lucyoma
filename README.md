0x16. C - Simple Shell
THIS IS A GROUP PROJECT DONE BY OBIAKOR LUCY AND AYOOLA NUATIN

A "simple shell" is a basic command-line interface that lets users interact with an operating system by entering text commands. It allows users to execute commands, manage files, redirect input/output, work with environment variables, chain commands together, run processes in the background, and create scripts. This type of shell is often used for educational purposes to teach the fundamentals of how shells and operating systems work. The features and capabilities of a simple shell implementation can vary, but it generally provides core functionalities for text-based interaction with a computer.

BASIC FUNCTIONALITY
Command Execution: Users can enter commands, and the shell executes them by invoking the corresponding programs or processes.

File Management: Users can navigate directories, list files, create, copy, move, and delete files and directories.

Input/Output Redirection: Users can redirect the input and output of commands using symbols like >, <, and |.

Environment Variables: Users can set, modify, and access environment variables, which are used to store configuration information for the shell and other programs.

Pipelines: Users can chain commands together, where the output of one command serves as the input for another using the | symbol.

Background Processes: Users can run commands in the background, allowing them to continue using the shell while the command is running.

Scripting: Users can create shell scripts, which are sequences of commands saved in a file and executed together.

Basic Built-in Commands: Some simple shells might include a few built-in commands like cd to change the current directory or echo to print text.

Output
Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)
Example of error with sh:

$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
Same error with your program hsh:

$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$

Compilation
Your shell will be compiled this way:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Testing
Your shell should work like this in interactive mode:

$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
But also in non-interactive mode:

$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$

TASK
0. Betty would be proud  1. Simple shell 0.1  2. Simple shell 0.2  3. Simple shell 0.3  4. Simple shell 0.4
5. Simple shell 1.0  6. Simple shell 0.1.1  7. Simple shell 0.2.1  8. Simple shell 0.4.1  9. setenv, unsetenv
10. cd  11. ;  12. && and ||  13. alias  14. Variables  15. Comments  16. File as input

CONTRIBUTION GUIDELINE
A contribution guide is supposed to be written in a separate file, but permit this here for sometimes. To contribute:
***fork this repo,
***create a branch,
***Update, Fixed, or add what you feel this project needs
***Add, commit, push to the repo
***Create a pull request
***On reviewing, if it is beneficially and not conflicting, it will be merged and you will be added to the master branch.
Then you are a CONTRIBUTOR.
