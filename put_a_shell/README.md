first of all , lets look at our binary in a disassembler
we got a main function 
![functions](/pwn/img/2/functions.png)
unlike the previous challenge , we dont have a win function . thats when you start realizing the meaning of the challenge name.
so we'll have to pop our own shell and for that we need to check the security measures on the binary with the checksec command.
![checksec](/pwn/img/2/checksec.png)
1. partial relro : means that the got and plt entries are writable . we'll explain what those 2 sections are in a sec . 
2. no pie : means our binary has fixed base . which is useful

lets break down the program now  
![main](/pwn/img/2/main.png)
quick look on the program and you can tell there is no BOF . But if you look at the scanf , the format is given by the user . For example if we send ```"%d %d``` to read, this scanf will get executed ```scanf("%d %d",&v6,&v5)```. This is the infamous **format string** vulnerability. I encourage you to read about it in this [link](https://ir0nstone.gitbook.io/notes/types/stack/format-string) as i wont explain format strings from scratch in this writeup . 
now back to the plt ang got section . lets see happens when you call a libc function like puts for example:
1. the puts@plt gets called
![puts-plt](/pwn/img/2/puts-plt.png)
2. the function jumps to whatever pointer is inside the <puts@got.plt> , and in normal cases it would be the adress of printf inside of libc.
and guess what ? this region is writeable in our challenge because relro is partial.

dont forget we have a libc leak , that enables us to calculate libc.address then calcualte the system function address within libc.
so our plan now is to overwrite the puts got entry with the system function address so that when we call puts(buf) , system(buf) gets called instead . and whats crazier is that buf is in our control , so we can just read /bin/sh\x00 into buf . well that wouldnt be a good idea because with the null byte scanf will stop its execution and our payload wont have any effect . one way around this would be to instead of executing a clean ```system("/bin/sh\x00")``` we can execute ```system("/bin/sh;bunch_of_junk")```so we can pass /bin/sh;format_string_payload . 

now to the overwriting part . if you read the article , you know that the sixth argument and going on will be taken from the stack . so saying %7$d means the second value on the stack . so we need to push the adress we want to overwrite which is ```0x404000``` on the stack then refer to it with %offset$s . so when scanf gets called the payload we sent reads a string into ```0x404000``` and we'll write system address in libc . 

one thing to mention is that system address always starts with 0x20 which is ascii for 'space' and that will fuck up our overwriting so we'll need to overwrite puts got with ```system+5``` which is the nearest instruction .
and that is it . look up the payload in my solver in challenge files . 

![flag](/pwn/img/2/flag.png)
