/* README.txt
 * 
 * Miguel Villanueva
 * CS 270
 */

Instruction to compile and run Client-Server Calculator
    1) "make"
    ---------------------------------------------------
    2) In one session: 
       
       "./server port"

       Where port is a number in the range 4500-4525
    ---------------------------------------------------
    3) In another session:      
       
       "./client localhost port"

       Where port should match the server port
	 
Example:

    -bash-4.2$ make
[Session 1]
    -bash-4.2$ ./server 4511

[Session 2]
    -bash-4.2$ ./client localhost 4511

