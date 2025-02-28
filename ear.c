
/* The C Programming Language by Kernighan and Ritchie */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFLEN 1024

int main(int count ,char * arg[])
{
	int LISTENPORT=atoi(arg[1]);
	printf("%d",LISTENPORT);
  	int sockfd, len, n,start=0,end,arr,bufsize,check;
  	unsigned char buffer[BUFLEN],ch,ce,sendport[13],fileName1[60],use[50];
  	struct sockaddr_in receiverAddr, senderAddr;
	FILE *fp,*gp;
	char fileName2[20];
	char fileName3[20];
	char fileName4[20];
	char fileName5[20];
        snprintf(fileName2,sizeof(fileName2),"%s%s","inter",arg[1]);
        snprintf(fileName3,sizeof(fileName3),"%s%s","conf",arg[1]);
        snprintf(fileName4,sizeof(fileName4),"%s%s","miss",arg[1]);
        snprintf(fileName5,sizeof(fileName5),"%s%s","file",arg[1]);

  	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  	{
    		perror("socket system call failed");
    		exit(EXIT_FAILURE);
  	}

  	memset(&receiverAddr, 0, sizeof(receiverAddr));
  	memset(&senderAddr, 0, sizeof(senderAddr));

  	receiverAddr.sin_family = AF_INET;
  	receiverAddr.sin_addr.s_addr = INADDR_ANY;
  	receiverAddr.sin_port = htons(LISTENPORT);

  	if(bind(sockfd, (const struct sockaddr *)&receiverAddr, sizeof(receiverAddr)) < 0)
  	{
    		perror("bind syscall failed");
    		exit(EXIT_FAILURE);
  	}
  	len = sizeof(senderAddr);
  	
	while(1){
  		n = recvfrom(sockfd, (unsigned char *)buffer, BUFLEN, MSG_WAITALL, (struct sockaddr *) &senderAddr, &len);
  		buffer[n] = '\0';
		if(buffer[0]=='a'){
			start=1;
                        memset(use,0,50);
			fp=fopen(fileName2,"wb");
			gp=fopen(fileName5,"ab");
			while(buffer[start]!=' '){
				use[start-1]=buffer[start];
				fwrite(&buffer[start],sizeof(unsigned char ),1,gp);
				start++;
			}
			fwrite("\n",2,1,gp);
			fclose(gp);
			snprintf(fileName1,sizeof(fileName1),"%s%s",arg[1],use);
			memset(use,0,50);
			start++;
			end=0;
			while(buffer[start]!=' '){
				sendport[end]=buffer[start];
				fwrite(&buffer[start],sizeof(unsigned char ),1,fp);
				end++;
				start++;
			}
			sendport[end]='\0';
			end=0;
			start++;
			fwrite(" d",2,1,fp);
			 while(buffer[start]!=' '){
                                use[end]=buffer[start];
                                end++;
                                start++;
                        }


			len=atoi(use);
			char * parray=(char *)malloc((len)* sizeof(char ));
                        for(int i=0;i<len;i++){
                                parray[i]='0';
                        }


			memset(use,0,sizeof(use));
			start++;
                        end=0;
                        while(start<n){
                                use[end]=buffer[start];
                                end++;
                                start++;
                        }
			bufsize=atoi(use);
			fclose(fp);
			start=0;
			while(start==0){
				memset(buffer,0,sizeof(buffer));
  				n = recvfrom(sockfd, (unsigned char *)buffer, BUFLEN, MSG_WAITALL, (struct sockaddr *) &senderAddr, &len);
				if(buffer[0]=='c' || buffer[0]=='1'){
					start=1;	
				}
			}
			fp=fopen(fileName2,"wb");
			fclose(fp);
			fp=fopen(fileName1,"wb");
                        check=1;
                        start=1;
			while(check==1){
                                if(start==0){
                                        n = recvfrom(sockfd, (unsigned char *)buffer, BUFLEN, MSG_WAITALL, (struct sockaddr *) &senderAddr, &len);
                                        buffer[n] = '\0';
                                }
                                if(buffer[0]=='c' && check==1){
                                        start=0;
                                        for(int i=0;i<len;i++){
                                                if(parray[i]=='0'){
                                                        start++;
                                                }
                                        }
                                        gp=fopen(fileName2,"wb");
                                        memset(use,0,sizeof(use));
                                        fwrite(&sendport,strlen(sendport),1,gp);
                                        if(start>0){
                                                fwrite(" f",3,1,gp);
						start=atoi(arg[1]);
                                                memset(use,0,sizeof(use));
                                                sprintf(use,"%d",start);
                                                fwrite(&use,strlen(use),1,gp);
                                                fwrite(" ",1,1,gp);
                                                sprintf(use,"%d",start);
                                                fwrite(&use,strlen(use),1,gp);
                                                for(int i=0;i<len;i++){
                                                        if(parray[i]=='0'){
                                                                memset(use,0,sizeof(use));
                                                                sprintf(use,"%d",i);
                                                                fwrite(" ",1,1,gp);
                                                                fwrite(&use,strlen(use),1,gp);
                                                        }
                                                }
                                        }
                                        else{
                                                fwrite(" e",2,1,gp);
						start=atoi(arg[1]);
                                                memset(use,0,sizeof(use));
						sprintf(use,"%d",start);
						fwrite(&use,strlen(use),1,gp);
						check=0;
                                        	fclose(gp);
						sleep(1);
                                        	gp=fopen(fileName2,"wb");
						fclose(fp);	
                                        }
                                        fclose(gp);
                                        memset(fileName1,0,sizeof(fileName1));
                                        memset(sendport,0,sizeof(sendport));
                                        start=0;

                                }

                                if(buffer[0]=='1' && check==1){
                                        start=1;
                                        memset(use,0,sizeof(use));
                                        while(buffer[start]!=' '){
                                                use[start-1]=buffer[start];
                                                start++;
                                        }
                                        start++;
                                        end=atoi(use);
                                        parray[end]='1';
                                        end=end*bufsize;
                                        fseek(fp,end,SEEK_SET);
                                        while(start<n){
                                                fwrite(&buffer[start],sizeof(unsigned char ),1,fp);
                                                start++;
                                        }

                                        start=0;

                                }


                        }

		}
		if(buffer[0]=='d'){
			fp=fopen(fileName3,"wb");
			fwrite("d",1,1,fp);
			fclose(fp);
			sleep(1);
			fp=fopen(fileName3,"wb");
			fclose(fp);

		}

		if(buffer[0]=='e' || buffer[0]=='f'){
                        fp=fopen(fileName4,"wb");
                        for(int i=0;i<n;i++){
				fwrite(&buffer[i],1,1,fp);
			}
                        fclose(fp);
			sleep(2);
                        fp=fopen(fileName4,"wb");
                        fclose(fp);
			if (buffer[0]=='e'){
				printf("send");
			}
                }

		if(buffer[0]=='c'){
                        fp=fopen(fileName4,"wb");
                        fwrite("e",1,1,fp);
			start=atoi(arg[1]);
			memset(use,0,sizeof(use));
                        sprintf(use,"%d",start);
                       	fwrite(&use,strlen(use),1,gp);
                        fclose(fp);
			sleep(1);
                        fp=fopen(fileName4,"wb");
                        fclose(fp);
  			printf("data received: %s\n", buffer);
		}


		memset(buffer,0,sizeof(buffer));
  	}
  return 0;
}
