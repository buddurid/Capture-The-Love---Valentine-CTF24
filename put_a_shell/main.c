#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

int main(int argc, char const *argv[]){

	setup(); 
	
	printf("take this : %p\n",&printf);
	int a=0xcafe,b=0xbabe;
	char msg[40];
	read(0,msg,40);
	scanf(msg,&a,&b);
	puts(msg);


}