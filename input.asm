.text
main:
    addi x1, x0, 5
    addi x2, x0, 5
loop:
    sub  x1, x1, x2
    bne  x1, x0, loop

.data
.word 25
.byte 65
.end
