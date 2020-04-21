
        global  _set_bit_elem
        global  _get_bit_elem
        section .text

_set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col


        ; add your code here
        ; GET DATA/ ARRAY POINTER
        mov rax, rdx ; move the row into rax
        imul rax, 10 ; multiply the row width
        add rax, rcx ; add the column at this point it should equal 8
        sal rax, 1
        add rax, rdx
        add rax, rcx ; add column
        sal rax, 4   ; multiply by the element size (is it 4 in this case?)
        add rax, rdi  ;

        ; works to here

        ; MAKE MASK
        mov rdi, rdx        ; save a copy of the row in rdi for later use
        imul rdi, 10
        add rdi, rcx        ; rdi contains the index
        imul rdx, 10        ; compute - multiply by the row width
        add rdx, rcx        ; add column - rdx is now the index
        and rdx, 7          ; modulo 8 to calculate byte_offset, byte offset now in rdx
        imul rdx, 8         ; multiply the byte offset by 8
        sub rdi, rsp        ; subtract 8*byte_offset from the index (rdi), rdi now holds the bit_offset
        sub rdi, 1          ; subtract 1 from the index, rdi now contains the mask

        mov rsi, 0          ; put 8 in rsi to create mask
        sub rsi, rdi        ; create mask, rsi holds mask


        ; OR
        or rax, rsi
        cmp rax, 0
        setg al
        movsx rax, al       ; is it a problem that rax is the output and also the what we were holding data in

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax




_get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col



        ; add your code here - for now returning 0
        ; GET DATA/ ARRAY POINTER
        mov rax, rdx ; move the row into rax
        imul rax, 10 ; multiply the row width
        add rax, rcx ; add the column at this point it should equal 8
        sal rax, 1
        add rax, rdx
        add rax, rcx ; add column
        sal rax, 4   ; multiply by the element size (is it 4 in this case?)
        add rax, rdi  ;


        ; MAKE MASK
        mov rdi, rdx        ; save a copy of the row in rdi for later use
        imul rdi, 10
        add rdi, rcx        ; rdi contains the index
        imul rdx, 10        ; compute - multiply by the row width
        add rdx, rcx        ; add column - rdx is now the index
        and rdx, 7          ; modulo 8 to calculate byte_offset, byte offset now in rdx
        imul rdx, 8         ; multiply the byte offset by 8
        sub rdi, rsp        ; subtract 8*byte_offset from the index (rdi), rdi now holds the bit_offset
        sub rdi, 1          ; subtract 1 from the index, rdi now contains the mask

        mov rsi, 0          ; put 8 in rsi to create mask
        sub rsi, rdi        ; create mask, rsi holds mask


;       ;AND
        and rax, rsi

        cmp rax, 0
        setg al
        movsx rax, al       ; is it a problem that rax is the output and also the what we were holding data in

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
