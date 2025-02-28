#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define len 1024 

int main(int cot,char* mg[])
{
	printf("system name:- %s\n",mg[1]);
	printf("port id:- %s\n",mg[2]);
    	int pid[2], i=0, re, userchoice,count;
     	char ca,iper[len],id[5],fileN[50];
	unsigned char ce;
    	char *otherprogram = "./ear"; /* this path may change on your Linux system */
    	char *args[3]; /* array to hold arguments to pass to exec system call */
	

	char fileName1[10];
        snprintf(fileName1,sizeof(fileName1),"recv%s",mg[2]);

        char fileName2[10];
        snprintf(fileName2,sizeof(fileName2),"send%s",mg[2]);

        char fileName3[10];
        snprintf(fileName3,sizeof(fileName3),"msg%s",mg[2]);
	
        char fileName4[20];
        snprintf(fileName4,sizeof(fileName4),"inter%s",mg[2]);

        char fileName5[10];
        snprintf(fileName5,sizeof(fileName5),"conf%s",mg[2]);

        char fileName6[10];
        snprintf(fileName6,sizeof(fileName6),"file%s",mg[2]);
	
	FILE *gp;
	gp=fopen(fileName1,"wb");
	fclose(gp);
	gp=fopen(fileName2,"wb");
	fclose(gp);
	gp=fopen(fileName3,"wb");
	fclose(gp);
	gp=fopen(fileName4,"wb");
	fclose(gp);
	gp=fopen(fileName5,"wb");
	fclose(gp);
	gp=fopen(fileName6,"wb");
	fclose(gp);


    	args[0]= otherprogram;
    	args[1]= mg[2];
    	args[2]= NULL;

    	int pi[2],j=0, fe;
    	char *other="./mouth";
    	char *arg[3];

   	arg[0]= other;
   	arg[1]= mg[2];
   	arg[2]= NULL;

	pi[j] = fork();
                                if(pi[j]>=0){
                                        if(pi[j] == 0){
                                                fe = execv(otherprogram, (char **) args);
                                                if(fe == -1)
                                                {
                                                        printf("Error in running %s \n",other);
                                                        perror("see the errno\n");
                                                        return 0;
                                                }
                                                return 0;
                                        }
                                }
                                else
                                {
                                        printf("Error calling fork() \n");
                                        perror("see the errno\n");
                                        return 0;
                                }

				pi[j] = fork();
                                if(pi[j]>=0){
                                        if(pi[j] == 0){
                                                fe = execv(other, (char **) arg);
                                                if(fe == -1)
                                                {
                                                        printf("Error in running %s \n",other);
                                                        perror("see the errno\n");
                                                        return 0;
                                                }
                                                return 0;
                                        }
                                }
                                else
                                {
                                        printf("Error calling fork() \n");
                                        perror("see the errno\n");
                                        return 0;
                                }

				FILE *fp;
    do
    {
        printf("Enter 1 to see the message\n");
        printf("Enter 2 to send the message\n");
        printf("Enter 3 to go offline\n");
        printf("Your choice please: \n");

        scanf("%d",&userchoice);
        getchar();/* not very important; it's a part of the ritual to use scanf somewhat sensibly on Linux */
		

        switch(userchoice)
        {

			case 1:
                                gp = fopen(fileName6,"rb");
                                fseek(gp,0,SEEK_END);
                                count=ftell(gp);
                                fseek(gp,0,SEEK_SET);
                                for(int i=0;i<count;i++){
                                      fread(&ca,sizeof(char),1,gp);
                                      printf("%c",ca);
                                }
                                fclose(gp);
				printf("enter 1 for txt file\n");
				printf("enter 2 for video,image..etc file\n");
				fgets(iper,5,stdin);
				printf("enter file:-");
				fgets(fileN,50,stdin);
				printf("%s",fileN);
				if(iper[0]=='1'){
					gp=fopen(fileN,"rb");
					fread(&ce,sizeof(unsigned char),1,gp);
					while(ce!=255){
						printf("%c",ce);
						fread(&ce,sizeof(unsigned char),1,gp);
					}
					fclose(gp);
				}
				break;

                        case 2:
                                
				gp=fopen(fileName2,"wb");
				printf("enter the system number:- ");
                                fgets(id,5,stdin);
                                printf("%s",id);
                                fwrite(&id,strlen(id),1,gp);
				memset(id,0,sizeof(id));
                                fclose(gp);

				printf("Enter file name:- ");	
				fp=fopen(fileName3,"wb");
                                fgets(iper,len,stdin);
                                count=strlen(iper);
                                for(int i=0;i<count;i++){
                                        fwrite(&iper[i],sizeof(char),1,fp);
                                }
				memset(id,0,sizeof(id));
				memset(iper,0,sizeof(iper));
                                fclose(fp);
				
				
        }

    }while (userchoice == 2 || userchoice ==1);
  
	return 0;
}
