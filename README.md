# Assignment 2 -- Writing a Basic Command Shell

**This project *must* be done in a group of two**

##Coding Requirements
Write a command shell called rshell in C++. Your shell will perform the following steps: 
1. Print a command prompt (e.g. $)
2. Read in a command on one line. Commands will have the form:

cmd = executable [ argumentList] [connector cmd]

connector = || or && or ;

where executable is an executable program in the PATH and argumentList is a list of zero or more arguments separated by spaces. The connector is an optional way you can run multiple commands at once. If a command is followed by ;, then the next command is always executed; if a command is followed by &&, then the next command is executed only if the first one succeeds; if a command is followed by ||, then the next command is executed only if the first one fails. For example:
```bash
$ ls -a
$ echo hello
$ mkdir test
```
is equivalent to: 
```bash
$ ls -a; echo hello; mkdir test
```
You are required to use the **composite pattern** when representing the commands and operators in your program. There should be no limit to the number of commands that can be chained together using the operators, and your program must be able to handle any combination of operators. For example, you should be able to handle the command:
```bash
$ ls -a; echo hello && mkdir test || echo world; git status
```
1. Execute the command. This will require using the syscalls fork, execvp, and waitpid. Previous cs100 students created two video tutorials ([a fun cartoon tutorial](https://www.youtube.com/watch?v=2c4ow5RoKA8&feature=youtu.be) ; [more serious explanation](https://www.youtube.com/watch?v=xVSPv-9x3gk)). You should also refer to the man pages for detailed instructions.
2. You must have a special built-in command of exit which exits your shell.
3. Anything that appears after a # character should be considered a comment. For example, in the command ls -lR /, you would execute the program /bin/ls passing into it the parameters -lR and /. But in the command ls # -lR /, you would execute /bin/ls, but you would not pass any parameters because they appear in the comment section. You should also note that the # may or may not be followed by a space before the comment begins

**IMPORTANT:** Most bash commands are actually executables located in /bin, /usr/bin/ (e.g. ls). But some commands are built-in to bash (e.g. cd). So while the ls command should "just work" in your shell, the cd command won't.

**HINT:** Pay careful attention to how you parse the command string the user enters. There are many ways to mess this up and introduce bugs into your program. You will be adding more parsing features in future assignments, so it will make your life much easier if you do it right the first time! I recommend using either the strtok function from the C standard libraries or the Tokenizer class provided in the boost library. Students often don't do this section of the assignment well and end up having to redo all of this assignment in order to complete the future assignments.

##Project Structure
You must have a directory called src which contains all the source files for the project, additionally you may either have a folder header which contains your header files or you may keep them in the src directory.

You must have a Makefile in the root directory. In the Makefile you will have two targets. The first target is called all and the second target is called rshell. Both of these targets will compile your program using g++ with the flags: -Wall -Werror -ansi -pedantic.

You must NOT have a directory called bin in the project; however, when the project is built, this directory must be created and all executable files placed here.

You must have a LICENSE file in your project. You may select any open source license. I recommend either GPL or BSD3.

You must have a README.md file. This file should briefly summarize your project. In particular, it must include a list of known bugs. If you do not have any known bugs, then you probably have not sufficiently tested your code! [Read this short intro](https://robots.thoughtbot.com/how-to-write-a-great-readme) to writing README files to help you. You must use the Markdown formatting language when writing your README.

You must have a directory called tests. The directory should contain a bash script that fully tests each segment of the program mentioned in the rubric. This means that for a completed project, you should have the following files (with these exact names):

|Filename|Explanation|
|:---|---|
|single_command.sh| tests single commands|
|multi_command.sh|tests commands with connectors|
|commented_command.sh|tests commands with comments|
|exit.sh|tests exit and commands with exit|

Each of these files should contain multiple commands in order to fully test each functionality. Proper testing is the most important part of developing software. It is not enough to simply show that your program works in some cases. You must show that it works in every possible edge case

**IMPORTANT:** The file/directory names above are a standard convention. You must use the exact same names in your project, including capitalization.

You must also update your design document from Assignment 1 to match your implementation for this assignment. Keeping up to date documentation is one of the most important (and most overlooked) parts of writing software.

##Submission Instructions
Your code must not generate any warnings on compilation.

You must follow the [CalTech coding guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cppstyle.html), as stated in the syllabus.

Your final executable must have no memory leaks.

Every time you run a syscall, you must check for an error condition. If an error occurs, then call perror. For every syscall you use that is not error checked, you will receive an automatic -5 points. For examples on when, how, and why to use perror, see [this video tutorial](https://izbicki.me/blog/videoguide-for-github-vim-bash.html#perror).

###Collaboration Policy

You MAY NOT look at the source code of any other student.

You MAY discuss with other students in general terms how to use the unix functions.

You are ENCOURAGED to talk with other students about test cases. You are allowed to freely share ideas in this regard.

You are ENCOURAGED to look at [bash's source code](https://www.gnu.org/software/bash/) for inspiration.

Create a new project on Github called rshell. Create a branch called exec. Do all of your work under this branch. When finished, merge the exec branch into the master branch, and create a tag called hw2. Remember that tags and branches in git are case sensitive!

**NOTE:** git push will not automatically push tags to your repository. Use git push origin hw2 to update your repository to include the hw2 tag.

You should verify these commands work for your repository on hammer.cs.ucr.edu to verify that you've submitted your code successfully. 

**Do not wait to upload your assignment to Github until the project due date.** You should be committing and uploading your assignment continuously. If you wait until the last day and can't figure out how to use git properly, then you will get a zero on the assignment. NO EXCEPTIONS.

##Grading

|Rubric| |
|:---:|:---|
|5 pts|well commented code|
|5 pts|following style guidelines (see wiki)|
|10 pts|sufficient test cases|
|10 pts|updated design document|
|20 pts|executing single commands|
|20 pts|executing commands with connectors|
|20 pts|executing commands with comments|
|10 pts|exit commands|
|**100**|**Total**|

**IMPORTANT:** Your project structure is not explicitly listed in the grading schedule above, however not following the correct structure will result in a 20 point deduction.

**IMPORTANT:** Projects that do not correctly compile as described above will receive no points.

##Extra Credit
Many shells display extra information in the prompt besides just a simple $. For example, it is common to display the currently logged in user, and the hostname of the machine the user is logged into. If your username is jdoe001, and if you’re logged into the machine alpha023, then your prompt would look like:

jdoe001@alpha023$

You can get up to 10 points of extra credit if your prompt prints this extra information. You will need to lookup the man pages for the functions getlogin and gethostname. You must not hard code the username or hostname!
