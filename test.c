#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
int main(){
	FILE *f1,*f2;
	f1=fopen("./1.png","rb");
	f2=fopen("./2.png","rb");
	
	fseek(f1,0,SEEK_END);
    unsigned long long int f1_size=ftell(f1);
    fseek(f1,0,SEEK_SET);

    fseek(f2,0,SEEK_END);
    unsigned long long int f2_size=ftell(f2);
    fseek(f2,0,SEEK_SET);

    char buf1[f1_size];
    char buf2[f2_size];

    fread(buf1,sizeof(buf1),1,f1) ;
    fread(buf2,sizeof(buf2),1,f2) ;

    if(strcmp(buf1,buf2)==0) printf("6");
	return 0;
}
