#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
/*
FILE *flog;//日志
flog = fopen("./log.txt","a+");
fprintf(flog,"\n ? \n", ? );
fclose(flog);
*/
char encrypt(char *in,char *password)
{   
    int a=sizeof(in);
    int b[1024]={0};
    for(int j=0;j<(1024/strlen(password));j++)
    {
        for(int i=0;i<strlen(password);i++)
        {
            b[i+j*strlen(password)]=password[i];
        }
    }
    for(int i=0;i<1024%strlen(password);i++)
    {
        b[1024-1024%strlen(password)+i]=password[i];
    }
/*
    for(int i=0;i<1024;i++)
    {
        FILE *flog;//日志
        flog = fopen("./log.txt","a+");
        fprintf(flog,"%c",b[i]);
        fclose(flog);
    }
    FILE *flog;//日志
    flog = fopen("./log.txt","a+");
    fprintf(flog,"\n\n");
    fclose(flog);
*/

    for (int i=0;i<a;i++)
    {
        in[i]=in[i]^(int)b[i];
    }
}

char *out_file(char *a,char *b)//输出的文件名
{
    if(NULL !=a)
    {
        //获取原文件名
        char e='\\';
        char d[strlen(strrchr(a,e))-1];
        for(int i=0;i<(strlen(strrchr(a,e))-1);i++)
        {
            d[i]=a[strlen(a)-strlen(strrchr(a,e))+i+1];
        }
        char *f=d;

        //获取用户输入文件名
        char *c=b;
        printf("输入文件名:");
        scanf("%s",c);

        if(strcmp(f,c)==0)
        {
            strcat(c,"_1");
        }

        /*
        FILE *flog;//日志
        flog = fopen("./log.txt","a+");
        fprintf(flog,"\n%s\n%s\n%s\n\n",a,b,f);
        fclose(flog);
        */
        return c;
    }
    else
    {
        printf("无路径传入,键入回车键退出");
        scanf("%c");
        exit(0);
    }

    /*
    if(NULL !=a)
    {
        char c='.';//搜索最后一个“.”得出原文件名的后缀长度
        int b=strlen(strrchr(a,c));

        if(b>0)
        {
            char d[b];
            for(int i=0;i<b;i++)
            {
                d[i]=a[(int)strlen(a)-b+i];
                //a[(int)strlen(a)-b+i]='\0';
            }
            //strcat(a,"_1");
            strcat(a,d);
            return a;
        }
        else
        {
            strcat(a,"_1");
            return a;
        }
    }
    else
        exit(0);

    */
}



int main(int argc, char *argv[])
{
    SetConsoleOutputCP(65001);

    time_t now_time;//(面向CSDN编程。。。)
    time(&now_time);//(主要是老师没教捏，边查边写)

    FILE *fin,*fout; 
    fin = fopen(argv[1],"rb");//argv[1]是文件拖入程序后输入的文件指针
    char outname[255];
    fout = fopen(out_file(argv[1],outname),"a+b");
    char password[1024]={0};
    printf("密码:");
    scanf("%s",password);

    //文件大小：
    fseek(fin,0,SEEK_END);//移动指针到文件尾
    unsigned long long int file_size=ftell(fin);//读取字节偏移量
    fseek(fin,0,SEEK_SET);//还原指针位置



    /*
    fread(buffer,sizeof(buffer),1,fin) ;//读入缓冲区
    encrypt(buffer,123);
    fwrite(buffer,sizeof(buffer),1,fout);//处理后从缓冲区输出
    */

    int buffer_size;//缓冲区大小

    if(file_size>=1024)
    {
        buffer_size=1024;
        char complement_buffer[file_size%1024];//缓冲区的补余
        char buffer[buffer_size];//缓冲区

        for(int i=0;i<(file_size/1024);i++)//每次处理1k的数据块
        {
            fread(buffer,sizeof(buffer),1,fin) ;
            encrypt(buffer,password);
            fwrite(buffer,sizeof(buffer),1,fout);
            
            fseek(fin,((long)i+1)*1024,SEEK_SET);//移动指针
            /*
            FILE *flog;//日志
            flog = fopen("./log.txt","a+");
            fprintf(flog,"\n%p\n%d\n",fin);
            fclose(flog);
            */
        }

        //处理不足1k的最后的数据
        fread(complement_buffer,sizeof(complement_buffer),1,fin) ;
        encrypt(buffer,password);
        fwrite(complement_buffer,sizeof(complement_buffer),1,fout);
    }
    else
    {
        //处理小于1k的文件
        buffer_size=file_size;
        char buffer[buffer_size];
        for(int i=0;i<(file_size/1024);i++)
        {
            fread(buffer,sizeof(buffer),1,fin) ;
            encrypt(buffer,password);
            fwrite(buffer,sizeof(buffer),1,fout);
        }
    }


    fclose(fin);//关闭文件
    fclose(fout);

/*
    FILE *flog;//日志
    flog = fopen("./log.txt","a+");
    fprintf(flog,"%s\n文件:%s\n字节数:%d---\n\n",ctime(&now_time),argv[1],file_size);
    fclose(flog);
*/
    return 0;
}
