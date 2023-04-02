;A segmentation fault occurs when a program attempts to access a memory location that it is 
;not allowed to access, or attempts to access a memory location in a way that is not allowed
;cd /mnt/c/Users/HP/Advanced-Programming-Concepts
;nasm -felf64 adelina.asm
; ld adelina.o -o hh.a
; ./hh.a
;static variables


;
;; REMAINING TASKS
; find a specific freelancer and show information or delete
; delete everything from a file

section .data
      STDOUT equ 1 ; standard output
      STDIN equ 0
      STDERR equ 2 ; standard error
      SYS_write equ 1 ; call code for write
      SYS_exit equ 60 ; call code to exit
      SYS_write equ 1 ; write
      SYS_open equ 2 ; file open
      SYS_close equ 3 ; file close
      SYS_fork equ 57 ; fork created different processes
      SYS_exit equ 60 ; terminate
      SYS_creat equ 85 ; file open/create
      SYS_read equ 0 ; call code for read
      O_CREAT equ 0x40
      O_TRUNC equ 0x200
      O_APPEND equ 0x400
      O_RDWR equ 000002q ; read and write
      S_IRUSR equ 00400q
      S_IWUSR equ 00200q
      O_RDONLY equ 000000q ; read only
      O_WRONLY equ 000001q ; read only
      NULL equ 0 ; end of string
      S_IXUSR equ 00100q
      fileName db "urll.txt", NULL
      error_msg db "open,modify or close the file",NULL
      error_msg_len equ $-error_msg
      read_error db "read",NULL
      read_len equ $-read_error
      msg db "Welcome to the Freelancer Admnistration System!",0dh,0ah, "Choose one of the options below:", 0dh,0ah, "1) Show all freelancers.", 0dh,0ah, "2) Delete all freelancers.", 0dh,0ah, "3) Quit the program.",10
      msgLen equ $-msg
      freelancers_list db "Ines 46 20", 0dh, 0ah, "Adelina 90 21",0dh,0ah,"Adey 76 19",0dh,0ah,"Alex 60 66",0dh,0ah,"Steven 10 1",10
      list_len equ $-freelancers_list
      tmp: db 0,0
      choice: db 0,0
      erased db " ", NULL
      erased_len equ $-erased
      tmplen equ $-tmp

      
section .bss
    fileDesc resq 1 
    buf resb 1025

;the actual code
section .text
       global _start
_start:
    call CreateInputFile
    call write_to_file
    call close_file
    call _menu
    call _choice
    ;call close_file
    call _quit
   
_choice: 
   call _input
   cmp byte[rsi], '1'
   je _display_all
   cmp byte[rsi], '2'
   je _delete_all
   cmp byte[rsi], '3'
   je _quit

CreateInputFile:
    mov rax, SYS_creat ; file open/create
    mov rdi, fileName ; file name string
    mov rsi, S_IRUSR | S_IWUSR ; allow read/write
    syscall ; call the kernel
    cmp rax, 0 ; check for success
    jl error_file
    mov qword [fileDesc], rax ; save descriptor
    ret

error_file:
    mov rdi, error_msg
    call print
      
file_open:
   mov rax, SYS_open ; file open 
    mov rdi, fileName ; file name string
    mov rsi, O_WRONLY ; read only access 
    syscall ; call the kernel 
    cmp rax, 0 ; check for success
    jl error_to_read
    mov qword [fileDesc], rax ; save descriptor

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

print_error:
   mov rdi,  error_msg
   call print
   call _quit


close_file:
    mov rax, SYS_close
    mov rdi, [fileDesc]
    syscall
    cmp rax, 0
    jl error_file
    ret


print: 
    push rbp
    mov rbp, rsp
    push rbx
    ; -----
    ; Count characters in string.
    mov rbx, rdi
    mov rdx, 0
    ret
    


_display_all:
    mov rax, SYS_open ; file open 
    mov rdi, fileName ; file name string
    mov rsi, O_RDONLY ; read only access 
    syscall ; call the kernel 
    cmp rax, 0 ; check for success
    jl error_to_read
    mov qword [fileDesc], rax ; save descriptor

    mov rax, 0
    mov rdi,  [fileDesc]
    mov rsi, buf
    mov rdx, 1025
    syscall
    cmp rax, 0
    jl error_to_read
    mov rsi, buf
    mov byte [rsi+rax], NULL
    mov rdi, buf
    call print
    ret

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
    

_delete_all:
    call file_open
    ; mov rax, SYS_open ; file open 
    ; mov rdi, fileName ; file name string
    ; mov rsi, O_WRONLY ; write only access 
    ; syscall ; call the kernel 
    ; cmp rax, 0 ; check for success
    ; jl error_to_read
    ; mov qword [fileDesc], rax ; save descriptor
    mov r8, 1000 ; loop counter
    jmp _Loop 
    ret

_menu:
    mov rax, SYS_write
    mov rdi, STDOUT
    mov rsi, msg ; msg address
    mov rdx, msgLen ; length value
    syscall
    ret


_input:
    mov rax, SYS_read
    mov rdi, STDIN
    mov rsi, tmp
    mov rdx, 1000
    syscall
    ret

_quit:
    mov rax, SYS_exit
    mov rdi, 0
    syscall
    sysexit

error_to_read:
    mov rdi, read_error
    call print
    call _quit
