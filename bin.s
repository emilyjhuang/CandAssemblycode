      .text
      .globl    _insert_node

_insert_node:
        push %rbp
        mov %rsp, %rbp
        
        cmpq  $0, _root(%rip)
        jne START
        movq %rdi, _root(%rip)
        pop %rbp
        ret
        

START:
        movq _root(%rip), %r8
        jmp TRAVERSE_LOOP

TRAVERSE_LOOP:
        //(%r9) is new_n->person.id
        //(%r8) is p->person.id
        movq (%rdi), %r9
        cmpq (%r8), %r9
        je END

        push %rdi
        push %r8
        
        leaq 116(%rdi), %rdi
        leaq 116(%r8), %rsi
        
        call _strcmp
        
        pop %r8
        pop %rdi
        
        cmpq $0, %rax
        je FIRST_NAME
        jl GOLEFT
        jmp GORIGHT


FIRST_NAME:
        push %rdi
        push %r8
    
        leaq 16(%rdi), %rdi
        leaq 16(%r8), %rsi
        
        call _strcmp
        
        pop %r8
        pop %rdi
        
        cmpq $0, %rax
        jl GOLEFT
        jmp GORIGHT

GOLEFT:
        cmpq $0, 216(%r8)
        jne TRAVERSEL
        movq %rdi, 216(%r8)
        jmp END


TRAVERSEL:
        movq 216(%r8), %r8
        jmp TRAVERSE_LOOP

GORIGHT:
        cmpq $0, 224(%r8)
        jne TRAVERSER
        movq %rdi, 224(%r8)
        jmp END
        
        
TRAVERSER:
        movq 224(%r8), %r8
        jmp TRAVERSE_LOOP


END:
        pop %rbp
        ret


    // Uncomment these three lines:
    .text
    .globl    _remove_smallest

_remove_smallest:
        push %rbp
        mov %rsp, %rbp

        cmpq $0, _root(%rip)
        jne STARTS
        movq $0, %rax
        pop %rbp
        ret

STARTS:
        movq _root(%rip), %r8
        cmpq $0, 216(%r8)
        jne LEFT
        
        movq _root(%rip), %rax
        movq 224(%r8), %r8
        movq %r8, _root(%rip)
        pop %rbp
        ret

LEFT:
        jmp SMALL_LOOP
        
SMALL_LOOP:
        movq 216(%r8), %r10
        cmpq $0, 216(%r10)
        je BREAK
        movq %r10, %r8
        jmp SMALL_LOOP
        
BREAK:
        movq %r10, %rax
        movq 224(%r10), %r10
        movq %r10, 216(%r8)
        pop %rbp
        ret
