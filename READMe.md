### Bash made by Vansh Marda
### 2021101089
### IIIT H - CSE

=======================================
                    HOW TO RUN ?
- make
- ./shell

========================================

                    About commands
### shell.c 
-    contains the main while loop
-    reads and parses inputs and sends it to correct handlers
-    cd andpinfo are handled in shell.c 
### echo_history_ls.c
- contains implementation for ls , echo , history command
### stater.c 
 -   contains implementation for frequently used functions like handling ~, min, max , removing        white_spaces , printing shell name , clearing scree etc
### headers.h
-    contains most commonly used headers and user defined headers
### backgroung_process_killer.c 
-    contains implementation for for handling children processes which have become zombies
### stater.c 
 -   It also contains functions such as fg , bg , sig , jobs and other processes .
### redirection.c
-    Implements input/output redirection

===========================================
         MY ASSUMPTIONS

- buffer size is of 5000
- type_flag , file_name ,target_dir have length of less than 100 in discover,c
- please ignore the warning that comes when we run make
- colored files with yellow and directories with blue in discover command
- provides sum taken of the time required to exit fromthe background process
- Always use piping with spacese .

==============================================
        IMPLETED TILL NOW FROM ASSIGNMENT 3
- fg
- bg
- input/output redirection
- piping
- sig
- jobs
- CLTR-D
