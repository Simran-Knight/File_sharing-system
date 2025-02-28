#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFLEN 100

int main(int re,char * arg[])
{
 	int sockfd,start=0,end,REMOTEPORT,packet,count,ptr;
  	unsigned char buffer[BUFLEN],ce,ch,sysmsg[100];
  	struct sockaddr_in   receiverAddr;
  	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  	{
    		perror("socket failed");
    		exit(EXIT_FAILURE);
  	}
	
	char fileName1[10];
        snprintf(fileName1,sizeof(fileName1),"%s%s","msg",arg[1]);
        char fileName2[10];
        snprintf(fileName2,sizeof(fileName2),"%s%s","send",arg[1]);
        char fileName3[10];
        char fileName4[10];
        char fileName6[20];
        char fileName5[10];
        snprintf(fileName3,sizeof(fileName3),"miss%s",arg[1]);
        snprintf(fileName5,sizeof(fileName5),"conf%s",arg[1]);
        snprintf(fileName6,sizeof(fileName6),"inter%s",arg[1]);

	FILE *fp,*gp,*kp;
  	memset(&receiverAddr, 0, sizeof(receiverAddr));
  	receiverAddr.sin_family = AF_INET;
  	receiverAddr.sin_addr.s_addr = INADDR_ANY;
	while(1){
		fp=fopen(fileName1,"rb");
		start=ftell(fp);
		fseek(fp,0,SEEK_END);
		end=ftell(fp);
		fclose(fp);
		if((end-start)>0){
			start=0;
			gp=fopen(fileName2,"rb");
			kp=fopen("system.txt","rb");
			fseek(gp,0,SEEK_SET);
			ch=getc(gp);
			while(ch !='\n'){
                                buffer[start]=ch;
                                fread(&ch,sizeof(unsigned char ),1,gp);
                                start++;
                        }
			fclose(gp);
			for(int j = 1 ;j <atoi(buffer);j++){
                                while((ch=getc(kp) != '\n')){}

                        }
			memset(buffer, 0, sizeof(buffer));
			start = 0;
                        while((ch=getc(kp)!=' ')){}
                        while((ch=getc(kp))!='\n'){
                                buffer[start]=ch;
                                start++;
                        }
			fclose(kp);
                        REMOTEPORT=atoi(buffer);
			receiverAddr.sin_port = htons(REMOTEPORT);
			memset(buffer, 0, sizeof(buffer));
			fp=fopen(fileName1,"rb");
			fseek(fp,0,SEEK_SET);
			start=0;
			buffer[start]='a';
			start++;
			end=0;
			ch=getc(fp);
			while(ch!=EOF && ch!='\n'){
				fileName4[end]=ch;
				buffer[start]=ch;
				ch=getc(fp);
				start++;	
				end++;
			}
			fileName4[end]='\0';
			buffer[start]=' ';
			start++;
			fclose(fp);
			fp=fopen(fileName4,"rb");
			fseek(fp,0,SEEK_END);
			end=ftell(fp);
			ptr=end;
			packet=end/(BUFLEN-6);
			if((end%(BUFLEN-6))!=0){
				packet++;
			}
			memset(sysmsg,0,sizeof(sysmsg));
			count=atoi(arg[1]);
                        sprintf(sysmsg,"%d",count);
			for(int j=0;j < strlen(sysmsg);j++){
                                buffer[start]=sysmsg[j];
                                start++;
                        }
                        buffer[start]=' ';
			start++;
			memset(sysmsg,0,sizeof(sysmsg));
                        sprintf(sysmsg,"%d",packet);
			for(int j=0;j < strlen(sysmsg);j++){
                        	buffer[start]=sysmsg[j];
                	        start++;
              	        }
			buffer[start]=' ';
			start++;
			memset(sysmsg,0,sizeof(sysmsg));
			end=BUFLEN-6;
			sprintf(sysmsg,"%d",end);		
			for(int j=0;j < strlen(sysmsg);j++){
                                buffer[start]=sysmsg[j];
                                start++;
                        }
			start=0;
			fclose(fp);
			while(start==0){
  				sendto(sockfd, (const unsigned char *)buffer, strlen(buffer), 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));
				sleep(1);
				gp=fopen(fileName5,"rb");
				fseek(gp,0,SEEK_END);
				end=ftell(gp);
				fseek(gp,0,SEEK_SET);
				start=ftell(gp);
				start=end-start;
				fclose(gp);

			}
			sleep(1);
			int ot=0;
			fp=fopen(fileName4,"rb");
                        for(int k=0;k<packet;k++){
                                memset(sysmsg,0,sizeof(sysmsg));
                                memset(buffer,0,sizeof(buffer));
                                sprintf(sysmsg,"%d",k);
                                buffer[0]='1';
                                start = 1;
                                for(int j=0;j < strlen(sysmsg);j++){

                                        buffer[start]=sysmsg[j];
                                        start++;
                                }
                                buffer[start]=' ';
                                start++;
                                count=k*(BUFLEN-6);
                                fseek(fp,count,SEEK_SET);
				fread(&ch,sizeof(unsigned char),1,fp);
                                end=0;
                                while(end<(BUFLEN-6) && ot<ptr)
                                {
			//		printf("%c",ch);
	//				printf("");
                                        buffer[start]=ch;
                                        start++;
                                        end++;
					ot++;
					fread(&ch,sizeof(unsigned char),1,fp);
                                }
                                sendto(sockfd, (const unsigned char *)buffer, start, 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));

                        }
			memset(buffer, 0, sizeof(buffer));
                        buffer[0]='c';
			buffer[1]='\0';
                        start=0;

			while(start==0){
				sendto(sockfd, (const unsigned char *)buffer, strlen(buffer), 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));
                                sleep(1);
				gp=fopen(fileName3,"rb");
                                fseek(gp,0,SEEK_END);
                                start=ftell(gp);
				fclose(gp);
				if(start>0){
					start=0;
                                	gp=fopen(fileName3,"rb");
                                        fread(&ce,sizeof(unsigned char),1,gp);
                                        fread(&ch,sizeof(unsigned char),1,gp);
					if(ce=='f'){
						fread(&ch,sizeof(unsigned char),1,gp);
                                 	       	start=0;
                                        	memset(sysmsg,0,sizeof(sysmsg));
                                        	while(ch!=' '){
                                        	        sysmsg[start]=ch;
                                        	        fread(&ch,sizeof(unsigned char),1,gp);
                                        	        start++;
                                        	}
                                        	fread(&ch,sizeof(unsigned char),1,gp);
						memset(sysmsg,0,sizeof(sysmsg));
                                                while(ch!=' '){
                               			        sysmsg[start]=ch;
                                                        fread(&ch,sizeof(unsigned char),1,gp);
                                                        start++;
                                                }
                                                end=atoi(sysmsg);
       	                                        for(int i=0;i<end;i++){
                                                        fread(&ch,sizeof(unsigned char),1,gp);
                                                        start=0;
                                                        memset(sysmsg,0,sizeof(sysmsg));
                                                        memset(buffer, 0, sizeof(buffer));
                                                        while(ch!=' ' && ch!='\n' && ch!=EOF){
        	                                                sysmsg[start]=ch;
                                                                fread(&ch,sizeof(unsigned char),1,gp);
                                                                start++;
                                                        }
                                                        packet=atoi(sysmsg);
                                                        packet=(packet*(BUFLEN-6));
                                                        fseek(fp,packet,SEEK_SET);
                                                        fread(&ch,sizeof(unsigned char),1,fp);
                                                        while(ch!=255 && start<(BUFLEN-6)){
                                                                buffer[start]=ch;
                                                                fread(&ch,sizeof(unsigned char),1,fp);
                                                                start++;
                                                        }
                                                        start--;
                                                        sendto(sockfd, (const unsigned char *)buffer, start, 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));
                               	                }
                                                start=0;
                                                memset(buffer, 0, sizeof(buffer));
                                                buffer[0]='c';

					}	
					if(ce=='e'){
						start=1;
					}
				}
				
			}
                        fclose(fp);
			fp=fopen(fileName1,"wb");
                	fclose(fp);
			start=0;
			end=0;
			printf("done");
		
		}
		fp=fopen(fileName6,"rb");
                start=ftell(fp);
                fseek(fp,0,SEEK_END);
                end=ftell(fp);
                fclose(fp);
		if((end-start)>0){
			fp=fopen(fileName6,"rb");
                        memset(sysmsg,0,sizeof(sysmsg));
                        memset(buffer, 0, sizeof(buffer));
			ch=getc(fp);
			start=0;
			while(ch!=' '){
				sysmsg[start]=ch;
				start++;
				ch=getc(fp);
			}
			REMOTEPORT=atoi(sysmsg);
			receiverAddr.sin_port = htons(REMOTEPORT);
			ch=getc(fp);
			start=0;
			while(ch!=255){
				buffer[start]=ch;
				ch=getc(fp);
				start++;
			}
                	fclose(fp);
                        sendto(sockfd, (const unsigned char *)buffer, strlen(buffer), 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));
			sleep(1);
		}
		start=0;
		end=0;

	}
  	close(sockfd);
	return 0;
}

