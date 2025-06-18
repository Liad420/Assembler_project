; This is a test
mcro my_macro
    mov r1, r2
mcroend

start: add #4, r3
my_macro
stop