

# Project 1 Report 

Ali Asif & Sanjaysriram Garimella

23 January 2019


### **Implementation Design Choices** 

###### Parsing:
The command given is parsed char by char and is appended into a 2D array 
allArguments. The size of the matrix is based on the assumptions provided by 
the professor that the program will have at most 16 arguments and length of
each token will not exceed 32. Each row of the marix denotes a word given. A
word is identified by searching for a space (or multiple spaces) between two
alpha-numeric chars. Each row of the 2D array holds one token word. Within 
that token word is the array of chars for that token. If there is remaining 
space between the maximum token size (32) and the acual size of the token, a 
/0 will be added.

allArguments[0] denotes the first word in the command and is used to identify
the type of command provided. For example, in the command "echo go lakers!",
allArguments[0] helps identify that 'echo' is the type of command. The array 
wihin the first row will contain values ['e','c','h','o'].


###### Built-In Commands:

If the command is builtin such as *ls*, the program will use the strcat to
concatinate */bin/* to *ls* to create the */bin/ls* and refers to the 
executable file. This allows users to type commands like *ls* and recieve the 
list of files and directories. 


###### Implemented Commands:

The commands being implemented were *exit, cd,* and *pwd*: 

*exit*: This provided command prints the phrase "Bye..." and is followed by a 
break statment. As a result of this, the program is closed. 

*cd*: Once allArguments[0] is verified to be *cd*, the program will call 
*chdir* on allArguments[1]. allArguments[1] is the token appearing after the 
term *cd*. An example of a command could be *cd User/Batman/Desktop/ECS150*. 
Here, *User/Batman/Desktop/ECS150* would be allArguments[1]. The program would
then *chdir* into the *User/Batman/Desktop/ECS150* directory. The function 
*getcwd()* is called where it obtains the current working directory (in this 
case, *UserBatman/Desktop/ECS150*) and saves it in new array *cwd*. The 
program then prints the value for *cwd* which is now the new directory. In the 
end, the *memset()* function is used to reset all values in *cwd* to 0. This 
is necessary as clearing the array will allow it to be used again in each loop.

*pwd*: Once allArguments[0] is verified to be *pwd*, again, an empty array 
*cwd* will be created. The function *getcwd* is called to obtain the current 
working directory. The current working directory is then printed for the user 
to see. In the end, as in *cd* In the *memset()* function is used to reset all
values in *cwd* to 0. This is necessary as clearing the array will allow it to 
be used again in each loop.


###### Output Redirection:

The next feature implemented was output redirection. In the child process, the 
team started by granting S_IRUSR, S_IWUSR, and S_IROTH permissions to the 
variable *mode*. S_IRUSR and S_IWUSRTh allows access for read and write for 
the owner. S_IROTH allows read access by others. 

Upon looking for the '>' token and parsing to find the name of the file. The 
name of the file is saved to value outputFileName. The file is then accessed 
using the *opne()* function, passing O_RDWR|O_CREAT as well as the *mode* 
value. O_RDWR|O_CREAT will grant read and write access to the file.  

Next, the system call dup2 is used to duplicates the file descriptor. The 
value STDOUT_FILENO is also passed in as an integer file descriptor. This will 
be used for writing. 

The execv function is now called with parameters *concat* and *args2*. Both of 
these variables are computed via parsing the original command. Upon searching 
for the '>' symbol, *concat* is the type of command being made while *args2* 
is the rest of the command before the '>' symbol. For example, in command 
*echo Porquet 2020>candidates.txt*, *concat* is 'echo' as it is the type of 
command being executed. The value 'echo Porquet 2020' is saved to *args2*. The 
above is all running in the child process while the parent process waits for 
the completion of the child. As a result of this, if the user were to view 
candidates.txt using vim they would see the statment "Porque 2020" which would 
verify the implementation is done properly. 

The final args2 array is reset using memset as this will allow it to be used 
again in each loops.


###### Piping:

At this time, the group has not implemented piping. The plan was to find the 
'|' character in the string and seperate values before and after the 
character. The string seen before the '|' character would be read in similar 
to any other command in the program. The result of this command would be fed 
into the command on the right side of the pipe. 



### **Testing Procedures**

During the earlier phases of the project, testing was done by manually typing 
commands to the shell. The team would type commands such as "echo I love you", 
"ls", and "cd User/Sanjay/ECS150" and ensured the shell was returning the 
correct values. All of the development and testing was done while remotely 
connected to CSIF via ssh. 

While implementing, the team made an effort to include line-by-line printf 
statments such as "Made it to line 127" to help debug the code faster. 

After a bulk of features had been implemented, the professor's testing script 
was used by copy-pasting commands line by line and ensuring the results 
matched the expected out put. 



### **Sources Used**

The group used online resources such as StackOverflow and Geeks for Geeks to 
look up how to produce 2D arrays, library functions to change directories, 
empty out values of arrays, and the like. The group also engaged in verbal 
discussion with other groups (without sharing code) to see for example, if 
they parsed the command using a 2D char array or token by token. 

Lastly, the group also attended CS Tutoring on two different occasions to help 
with debugging in some of their implementation along with building the Makefile. 
One question in particular was regarding he output redirection in which the 
tutor, Elias, was able to help. 






