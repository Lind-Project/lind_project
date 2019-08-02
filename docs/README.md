#How to run a program using lind

The build process of a program in lind is made easier by using the lindsh function. This guide will tell you how to build your program using lindsh. Lindsh relies on rlwrap, and if you don't want to or can't install rlwrap, and don't need autocompletion or command history, you can use the lindprompt command.
Lindsh is a very simple wrapper for lindprompt, and should not need to be edited.
However, in order to get either command working on your system, you need to specify where your lind project is located. The default value is /home/lind/lind\_project, and you should replace the first line of the bash script with the directory that lind is located on your file system

## Compilation

In order to compile a program using lindsh, you should type
```
gcc example.c example2.c -o example.nexe
```
.
In addition to using the gcc command to compile, using the commands "compile" or "cc" also work.
These commands run NaCl's version of gcc and produce a nacl executable, which should be created with the extension .nexe for clarity.
All gcc flags you'd need should work.

## Moving into lind file system

In order to move any file into the lind file system (although this will usually be used for .nexe files) using the lindsh command, you must use the cp command. For the file "example.nexe" in directory /home/user/Documents/Lind, we will find a parent directory of that file (it doesn't have to be the immediate parent), let's say /home/lind. This parent directory is our first argument. Our second argument must be the location of example.nexe relative to that parent directory--i.e. Documents/Lind/example.nexe. This command
```
cp /home/user/Documents Lind/example.nexe
```
will copy that file into the lind file system with the path /Lind/example.nexe (the full second argument from the root directory). If you want to put the file in a different location, you must move it in the posix file system to a relative path to some directory that is ultimately what you want in your lind file system.

The cp command can also recursively copy directories--if your second argument is a directory it will copy the directory and any of its contents recursively, their paths are still relative to the first argument.

## Running within the lind file system

In order to run a NaCl executable within the lind file system, you must use the run command (alternate aliases for this command are r, exec, and execute) with an argument of the absolute path of that file within the lind file system. For example:
```
run /Lind/example.nexe
```
.

