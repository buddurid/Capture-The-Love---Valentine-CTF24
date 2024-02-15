#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void love(int arg1,int arg2,int arg3,int arg4){
	if (arg1==0xcafe & arg2==0xbabe & arg3==0xf00d & arg4==0x7419){
		char flag[50];
		int fp=open("flag.txt",0);
		read(fp,flag,50);
		puts("you found true love !! here's your gift ");
		puts(flag);
	}
	else {
		puts("you found love .but at what cost!!!");
	}
}
void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}
int main(int argc, char const *argv[])
{
	setup();
	int size;
	char description[27];
	puts("in how many words can you describe your future love !!!");
	scanf("%d%",&size);
	if (size>=27){
		puts("way too many words");
		exit(69);
	}
	puts("now describe it :");
	read(0,description,size-1);
	return 0;
}