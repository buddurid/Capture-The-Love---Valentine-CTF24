we start looking at our binary in a disassembler and we can notice love function AKA win function which means this chall wont be annoying . 
here's how the win func looks like !!

![win](/img/1/win.png)

4 condtions so we can get a flag ? looks like a pain in the ass but we'll look at that later . 
let's have a look at our main function . 

![main](/img/1/main.png)

looks like the program will read an int in a size variable from the user then read size-1 bytes . Notice how he compares our requested size with 27 , but it looks like he forgot about negative numbers . you might ask what happens if we pass 0 to size , well the ```size-1=-1``` .-1 is represented in memory as an int like this : **0xffffffff** . the thing is when we execute ```read(0,buffer,-1)``` , the -1 in memory wont be treated as an int but as an unsigned int in other words **0xffffffff** because third argument gets casted to ```size_t``` type which is basically ```unsigned int``` . 

thats what is supposed to be happening but after debugging and looking closely at gdb , you notice a strange line  

![movsxd](/img/1/movsxd.png) 

just before executing the line , $rax contains just what we thought it should have . **0xffffffff**

![eax](/img/1/eax.png)

look at the value of rdx after executing that line.

![rdx](/img/1/rdx.png)

rdx should be having **0x00000000ffffffff** right ? thats what wouldve happened if it was MOV . in our case MOVSXD , copies eax into rdx , then extends the sign bit into the rest of the register .Our sign bit is 1 because -1 is negative so it will fill the remaining bits with 1 thus rdx will contain **0xffffffffffffffff** . and passing this big number to read , it simply wont accept it . 
so up until now what we got 2 things :
1. we can pass 0 or negative numbers as size
2. size-1 must have sign bit 0 so it doesnt fill the rest of rdx with fffff

so if we pass (int)0x80000000 which is **-2147483648** ```0x80000000-1=7fffffff``` which is of sign bit 0 and actually huge which will cause a buffer overflow on the next read . 

we got our BOF now all we need is overwrite ret address with address of love . 

![wrongwin](/img/1/wrong-win.png)

the love function will give us the flag only if ```arg1==0xcafe & arg2==0xbabe & arg3==0xf00d & arg4==0x7419``` which we obviously didnt do . 
lets have a closer look at **love** in gdb 

![win-gdb](/img/1/love-gdb.png)

why go through all those comparaisons when you can skip them by jumping just after them ? that would mean jump to **love+79** instead of the beginning of love . 

One more thing . When you're crafting you payload give the saved RBP a valid writeable memory because love will write the flag relatively to rbp . so dont fill rbp with 0 and choose an adress from vmmap that has W permission

![vmmap](/img/1/vmmap.png)

you can look up my solver in challenge files

![flag](/img/1/flag.png)
