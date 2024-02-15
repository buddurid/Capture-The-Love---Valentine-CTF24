#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void gadgets(){

	__asm__("pop %rdi ; ret"); 	
	__asm__("pop %rsi ; ret");
	__asm__("pop %rdx ; ret");
	__asm__("syscall ");
	__asm__("pop %rax ; ret");

}


void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

int main(int argc, char const *argv[])
{
	setup();
	
	char input[128];
	printf("here's your valentine :  %p\n",input);
	read(0,input,140);
	printf("happy valentine %s .",input);
	return 0;

}