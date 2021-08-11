; ************** beginning of file 


.extern flex
.entry MAIN
MAIN: add $3,$5,$9

jmp flex
sometag: stop $4

sometag: stop

; another comment

dtag: .dh 33,2340003, $12

.dw word, 5, 6, shnitzel eqr9j
.dh , 
call flex
jmp $5
call dtag
.asciz "this is not a valid "string " "

add $55, $56,     $78
la d
jmp dtag

.dw 2147483647, 2147483648, -2147483648, -2147483649