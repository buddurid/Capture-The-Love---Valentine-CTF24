lets start by checksec'ing our binary . 

![checksec](/pwn/img/3/checksec.png)

no pie and partial relro is very helpful , but we're not gonna taka advantage of the relro in this chall . 
lets open our binary in disassembler . there are 2 functions that stand out . 

![main](/pwn/img/3/main.png)

![gadgets](/pwn/img/3/gadgets_empty.png)

why is gadgets function empty ? lets look it up at gdb .

![gadgets](/pwn/img/3/gadgets.png)

WOW ! looks like the author was generous enough to give us all gadgets we need to rop to shell . how kind of him !!
let's break down the main function now . 
1. the chall gives us a stack leak 
2. we can read up to 140 bytes in a string of size 128 >>> ```140-128-8=4``` so we got a 4 bytes BOF in our return address. 
well the question that comes to mind is how are we gonne exec our rop if we had only 4 bytes overflow , and even if it was 8 , or 16 ..... that wouldnt be enough to place our ropchain . lets suppose we have an 8 bytes overflow and see what happens. for that there is an interesting assembly instruction that you need to know which is **```leave```** instruction which is equivalent to  ```mov rsp,rbp ; pop rbp``` . this leave will be executed once by the end of main and as a result , rbp will be pointing to an address of our choosing as we will overflow it with our payload . but ```ret``` which is equivalent to ```pop rip``` will only answer to rsp and not rbp . so what if we execute leave again ? our rsp will be pointing to the address that we overflowed rbp with and if we cook it well , its gonna point to our rop chain . 
that would be ez if we had 8 bytes overflow as leave gadgets are available in our binary with no pie . but what about 4 bytes overflow ? we cant write a full adress with 4 bytes , right ? what if i told you we can .

 ![meme](/pwn/img/3/meme.jpg)

lets break at the ret at the end of main and see what value is there . 

![ret](/pwn/img/3/ret.png)

the 4 bytes we are going to overwrite are overwriting that address that points **__libc_start_main** that is in libc . one piece of information is that libc also contains gadgets . lets see the offset of one leave gadget in libc using ropper . 

![ropper-leave](/pwn/img/3/ropper-leave.png)

we are sure the the first three nibbles of that offset is correct but what about the rest of the bytes . 

![leave](/pwn/img/3/leave.png)

we can see that only the first 5 nibbles are different so if we brute force the first 3bytes we dont need to to change anything after that . 
so our payload should be a rop chain into overwriting the rbp with the stack leak -8 into trying to brute force leave gadget from libc so that rsp will at some point point to our rop . 
in our case we are going to write 3 bytes , and 3 nibbles from them are known so we are trying to brute force only 3 nibbles . that leaves u with a chance of 1/4095 which is very good . try to test your script locally first as it is quick and wont take more than 2 minutes . but it will take a lil bit longer in remote . 

![flag](/pwn/img/3/flag.png)

hope you had learnt something reading this writeup and im excited to write more challenges in the future . see you in future ctf's and writeups. 