.org    0x400590
exit:
.org    0x4005a0
open:
.org    0x4005e0
puts:
.org    0x400610
read:

.org    0x411468
        adrp x0, 411000
        add x0, x0, #filename - 0x411000
        mov x1, #0
        bl open
        cmp w0, #-1
        b.ne cont
        ret
cont:
        mov x2, #99
        adrp x1, 411000
        add x1, x1, #hello - 0x411000
        bl read

        adrp x0, 411000
        add x0, x0, #hello - 0x411000
        bl puts

        adrp x1, 411000
        add x1, x1, #hello - 0x411000

        ldrb w2, [x1, #0]       // index
        cmp x2, 50              // value

        b.hi hello

        bl exit
filename:
        .string "/home/ty/flag"
        .byte 0, 0, 0, 0, 0, 0
hello:
        .string "hell"
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 0, 0, 0, 0
        .byte 1,1,1,1
