# Assembly: Freelancer Admnistration System

## What is Assembly? 

In computer programming, assembly language often referred to simply as Assembly and commonly abbreviated as ASM or asm, is a low-level programming language with a very strong correspondence between the instructions in the language and the architecture's machine code instructions.

Assembly language is a step closer to machine language than high-level programming languages like Java, Python, or C++. Assembly language instructions correspond to specific machine language instructions and provide a direct representation of the machine's architecture, allowing programmers to write highly optimized code that executes efficiently and with minimal use of system resources.

It uses human-readable mnemonics to form shortcodes. These shortcodes are then converted into binary through the use of programs called assemblers.

## Setup
1. Make sure to download [visual studio code.](https://code.visualstudio.com/Download)
2. Install Ubuntu.
3. Go to the extensions section of vs code and search for WSL.
4. Open WSL on your laptop
5. Type in the code below which will open another window of vs code: 
```code .``` 
6. Now to install the compiler type in on WSL:
```
sudo apt install nasm
```

## Getting Started with Assembly+ Hello World
We will have a higher level view of assembly in this section and give some more details along the tutorial.

#### Registers
A register, is a temporary storage or working location built into the CPU .Computations are typically performed by the CPU using registers. Below are found the registers you will see during this tutorial.
![](https://i.imgur.com/8Tq6RE5.png)

An operation in assembly comprises of an opcode which is the instruction itself and then the operands which participate in the operation.
![](https://i.imgur.com/Z9n6OZe.png)

**Some examples:**
![](https://i.imgur.com/WL1ywEQ.png)

After seeing a little bit of a high level view let's jump right to how to write hello world in assembly.
```asm
; where the constant variables stay
section .data
  SYS_write equ 1 ; call code for write
  SYS_exit equ 60 ; call code to exit
  STDOUT equ 1    ; call code for standard output
  SYS_read equ 0  ; call code to read
  Null_Terminator equ 10
  SUCCESS equ 0 ; Successful operation
  hello_world db "Hello, World!", Null_Terminator ; creating the hello world variable
  hello_world_length equ $-hello_world ; getting the length

; where the code stays
section .text
   global _start
   _start:
   mov rax, SYS_write ; setting to system write
   mov rdi, STDOUT ; setting to standard output
   mov rsi, hello_world ; giving the adress of the variable
   mov rdx, hello_world_length ; giving the length
   syscall

_exit:
   mov rax, SYS_exit ; exiting
   mov rdi, SUCCESS
   syscall
   sysexit
```
#### Compiling and Running
![](https://i.imgur.com/BS8FXCq.png)


## Our Assignment
Write a program that stores the client, salary, and rating of 5 different freelancers. Ask the user to select the freelancer and then a menu to print all the information for every freelancer and to delete the information as well. This mainly involves user input/output, control flow and file handling.

### Steps Taken
After understanding a little bit about assembly and how the code was executed we had to break down what needed to be known/researched in order to fulfil the task. After some thought we divided the research into:
1. Understanding more about registers and operations in assembly.
2. Figuring out the basics such as functions, loops and conditional statements.
3. Understanding input and output.
4. Understanding file handling.

### Basics
In this project our main focus was shifted to input/output from the console and also input/ouput from files. As our assignment suggested we had to understand how to output the menu and results to the console and read the choices of the user. All of the data used in the program was stored into a file. With the choices given to the user, the program reads, writes and modifies the file.
#### Input/Output 

*1. Input:*

To read from the console the system service is system read (SYS_read).Like a high-level language, for the console, characters are read from standard input (STDIN). This task might be a little comlicated since the number of characters that need to be read should be provided when using the system service to read from the keyboard.
The arguments for the system service are as follows:
![](https://i.imgur.com/YEz3TDI.png)
An example of the code to read two characters from the console looks like following:
```asm
_input:
    mov rax, 0
    mov rdi, 0
    mov rsi, tmp
    mov rdx, 2
    syscall
```
In the first line we move 0 to rax with 0 being the value for the system call code in this case system read (SYS_read). 
With the second line, we assign the input location by moving 0 to rdi which is here the standard input (STDIN).
We then move the variable that we are using to store the read value from the console to rsi:
```asm
mov rsi, tmp
```
We specify the number of characters that we are about to read from the console and finally make our system call.

*2. Output:*

Just like the input, the system service to output characters to the console is simply the system write (SYS_write). Again like a high-level language characters are written to standard out (STDOUT) which is the console. 
The arguments for the system service are as follows: 
![](https://i.imgur.com/PTjtUdL.png)
If we also take a look at the corresponding code for outputting one character to the console it will be as follows:
```asm
_output:
    mov rax, 1
    mov rdi, 1
    mov rsi, inChar
    mov rdx, 1 
    syscall
```
We here move 1 to both rax and rdi to define our call code and output location to SYS_write and STDOUT.
In the third line we assign the address of the character that we want to ouput to rsi. This character is defined in the .data section for example this way:
```asm
inChar db "a", NULL
```
We move the length of what we want to print to rdx in this case it's one character so 1 then we make the system call.

#### File Handling 
In order to perform file operations such as read and write, the file must first be opened.
There are two file open operations, open and open/create. In our program we used open/create so that the person who uses the code will have the file on their computer.
Since the file is being created, the access mode must include the file permissions that will be set when the file is created. This access mode is set by:

• Read-Only Access → O_RDONLY
• Write-Only Access → O_WRONLY
• Read/Write Access → O_RDWR

Our following function creates a file with the name that we specified in the .data section and writes into it the list of our freelancers and the hours they have worked:
```asm
CreateInputFile:
    mov rax, SYS_creat ; file open/create
    mov rdi, fileName ; file name string
    mov rsi, S_IRUSR | S_IWUSR ; allow read/write
    syscall ; call the kernel
    cmp rax, 0 ; check for success
    jl error_file
    mov qword [fileDesc], rax ; save descriptor
    ret
```
The file being created, we open it using an open function:
```asm
file_open:
    mov rax, SYS_open ; file open 
    mov rdi, fileName ; file name string
    mov rsi, O_WRONLY ; read only access 
    syscall ; call the kernel 
    cmp rax, 0 ; check for success
    jl error_to_read
    mov qword [fileDesc], rax ; save descriptor
```
We are using an error function every time just to make sure that the file actions are being executed correctly, you can costumize that one to your preferences.
As you have guessed, after creating and opening the file we now are going to write the list of freelancers into it using a write function that can implemented as following:
```asm
write_to_file:
    mov rax, SYS_write ;writing to a file
    mov rdi, [fileDesc] ; stdout
    mov rsi, freelancers_list ; address of string
    mov rdx, list_len ; length of string
    syscall
    ; check if error
    cmp rax, 0
    jl error_file
    ret
```
So the first step is always defining our call code in this case SYS_write. In the second line, the brackets around "fileDesc" indicate that it is a memory address, rather than a value stored directly in a register. So, the "mov" instruction loads the value stored at the memory location pointed to by "fileDesc" into the "rdi" register.

The variable "freelancers_list"  contains a memory address pointing to our list string, such as a list of freelancers. The "mov" instruction loads this memory address into the "rsi" register, allowing the program to access the data in the list by dereferencing the pointer stored in "rsi". 
We then also provide the length of our string and make the system call to write this string into our file. We check for any error as usual then return to our main function.

Finally for the last step, we saw how to delete from a file. In order to do so, there are two options that you can go with, first deleting the whole file itself or overwriting its content.
We opted for the second option since we still want the file to be there and we just wanted to remove what is already written into it. 
For that, we implemented the following function:
```asm
_delete_all:
    call file_open
    mov r8, 1000 ; loop counter
    jmp _Loop 
    ret
```
This function first calls file_open to open the needed file. Then it calls another function called loop which is here the main key to delete. The _Loop function as its name says loops around and writes a single character to the file over and over again until all the data in the file is overwritten. 
That is done as following:
For that, we implemented the following function:
```asm
_Loop:
    mov rax, SYS_write ; writing to a file
    mov rdi, [fileDesc] ; file descriptor set to write
    mov rsi, erased ; address of the characters
    mov rdx, erased_len ;stores amount of characters 
    syscall
    dec r8 ; decrement loop counter
    cmp r8, 0
    ;je _quit
    jne _Loop
    cmp rax, 0
    jl error_file
    ret
```
The register r8 is set in the _delete_all function, its value decrements everytime it goes through the _Loop function until it reaches 0 that's when we quit the _Loop function. Every time we execute this function the character erased is printed into the file. Erased is initialized in the .data section as follows:
```asm
erased db " ", NULL
erased_len equ $-erased
```
After these two functions, our file is now empty.
And as everyone knows, after using a file we should always finish by closing it. For that we use the close_file function:
```asm 
close_file:
    mov rax, SYS_close
    mov rdi, [fileDesc]
    syscall
    cmp rax, 0
    jl error_file
    ret
```

## Why you should learn it
Just like any computer science student, you would to get a deeper understanding of the computer's hardware. And the closest we can come to the processor of a machine is by learning and using the assmebly language. This would help with a lot of different subjects like:

- **Better understanding of architecture issues**
Learning and spending some time working at the assembly language level provides a richer understanding of the underlying computer architecture. 
- **Understand compiler scope** 
It helps ensure programmers understand the scope and capabilities of a compiler and understand how compiler optimizations work.
- **Understand the toolchain** 
Working at the low-level can help provide the basis for understanding and appreciating the details of the tool chain
- **Complete control over a system's resources**
You can write code to access the registers and even deal with memory addresses directly for retrieving values and pointers.

## Conclusion
In conclusion, assembly is a very useful language to learn and it is an enjoyable experience. It teaches more about debugging, architecture and much more. We advise and encourage everyone to try to learn at least the basics of it as it will also bring more gratefulness towards higher level languages.