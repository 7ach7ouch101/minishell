# minishell

This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.

The task is to create a shell program called Minishell, which allows users to interact with a computer using a command-line interface. The program should adhere to the following requirements:

Display a prompt when waiting for a new command.
Have a working history feature to store previously executed commands.
Search for and execute the correct executable file based on the PATH variable, or using a relative or absolute path.
Use only one global variable, with its purpose clearly explained.
Not interpret unclosed quotes or special characters like backslash () or semicolon (;) unless necessary.
Handle single quotes (') to prevent interpretation of metacharacters within the quoted sequence.
Handle double quotes (") to prevent interpretation of metacharacters within the quoted sequence, except for the dollar sign ($).
Implement redirections:
< to redirect input.
to redirect output.

<< followed by a delimiter to read input until a line containing the delimiter is encountered (without updating the history).
to redirect output in append mode.

Implement pipes (|) to connect the output of one command to the input of the next command.
Handle environment variables (sequences starting with $) by expanding them to their respective values.
Handle $? to expand to the exit status of the most recently executed foreground pipeline.
Handle ctrl-C, ctrl-D, and ctrl-\ signals, behaving similar to bash.
ctrl-C displays a new prompt on a new line.
ctrl-D exits the shell.
ctrl-\ does nothing.
Implement the following built-in commands:
echo with the -n option.
cd with only a relative or absolute path.
pwd with no options.
export with no options.
unset with no options.
env with no options or arguments.
exit with no options.
Limit the shell program to the requirements specified and do not introduce additional functionality unless explicitly asked.
Memory leaks caused by the readline() function do not need to be fixed, but the code written by the developer should not have memory leaks.
The shell program should meet these requirements and can reference the behavior of bash for any ambiguous requirements.
