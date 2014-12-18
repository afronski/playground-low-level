    .global _start

    .text
_start:
    # write(1, message, 13)
    mov     $1, %rax                # System call ID - '1' is write.
    mov     $1, %rdi                # File handle - '1' is stdout.
    mov     $message, %rsi          # Address of string to output.
    mov     $13, %rdx               # String length.
    syscall

    # exit(0)
    mov     $60, %rax               # System call ID - '60' is exit.
    xor     %rdi, %rdi              # We want return code 0.
    syscall

message:
    .ascii  "Hello, world\n"
