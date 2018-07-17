# Machine Instruction Simulartor:

This is a project for Nile University Advanced programming concepts course. the project is a c++ program that simulates a set of instructions and act as interpreter and excutes those commands found in test.mis file and produce the outputs of these commands in output.out file and catch any errors in these commands and put them in error.err file.

## Used c++ Feature:

- OOP:

this program is all designed using object oriented design using c++ classes and objects.

- Socket programming:

The software is splitted into two parts: the first part is the server side where It contains the code that is used to parse and excute the required commands while the second part is the client side where it sends the file to the server. The client is connected to the server over port `9999` and IP `127.0.0.1`

- Multithreading:

The software has a part in which it executes multiple instructions in parallel by putting each instruction of them in  a thread and executes each thread. The indicator for the thread execution is the word `THREAD_BEGIN` and `THREAD_END`.

## summary of the program flow:

The flow of the software is as follows:

- The client side part reads the instructions need to be executed from the .mis file and put them in a buffer.
- The client sends the buffer to the server side to be executed.
- the server side receive that buffer and put the content of that buffer in a vector.
- the server side parse the file content.
- After parsing, the server loops over the instructions and starts to execute these instructions line by line.
- while execution, when the program finds the word `OUT` it puts the what is after it in the output.out file and when it catches an error it produces the error and its type in the error.err file.
- After finishing execution of the instructions, the server side sends the content of the error.err and output.out files to the client side and the client side put them in its .out and .err file.
- the server still working waiting for any other file to be executed till you terminate the server using `ctrl+c`.

### How to build:

put the following command in linux terminal in case of using linux operating system to run the server side

```
g++ -std=c++11 charvar.cpp Connection.cpp GarbageCollector.cpp numericvar.cpp parse.cpp realvar.cpp server.cpp stringvar.cpp TCPServerSocket.cpp TCPSocket.cpp Thread.cpp Threadexe.cpp Threadmanage.cpp var.cpp wrap.cpp -lpthread -o output
```

then change the directory to the file containing the client side and put the following command in the terminal

```

g++ -std=c++11 main_client.cpp client.cpp -o output
```

OR
You could type the word `make` in the terminal to execute using the make file
### Authors:

- Ehab Adel EL-Kady

A computer science student at Nile Unniversity.

- Youssef Ibrahim El-masry

A computer engineering student at Nile University.

-> A PDF file with the complete description of the software containing a table of the full functionalities of the program. 
