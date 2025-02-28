#BABYSTEPS

####AUTHORS:
	YASH LICHADE ,ROLL NO - 23111056
	SIMRAN SINGH ,ROLL NO - 23111059

####DESCRIPTION:This is an assignment given to us for the course,`CS-603 SYSTEM-III` during 3rd semster of academic year 2024 , with the aim to understand the features of networking in real-time application .
In this sender has send a large size messages into smaller chunks and receiver receive the small chunks to form a messages where messages can be a text file , images , videos . We have been using UDP Socket and C language to develop communication between multiple terminals(processes).

Brief description :-

We have system.txt -> In which all system with their name and port number is listed . 
	send file -> To whom we send the message .
	miss file -> Stored missing packets number or all packet received msg.
	conf file -> Confirmation file , stored acknowledgment from the receiver side .
	inter file ->Intermediate file , between ear and mouth.
	msg file  -> Message file , stored filename from user.
	file file -> stored all filename that we have received.

Take input from user for system number, this input is writing in send file , another input from user is filename (eg. text file , image , video) , which is writing into message file.
By reading send file we found out system number , to determine port number of that system we read system.txt file in which all system with their port number listed already.
By reading message file we found filename which user want to send , open that file and compute the packets according to system buffer size .
By all these information we create instruction message which consist header 'a' , filename , sender's port number ,  total number of packets , maximum data size in one packet .
On receiver side after receiving(ear) instruction message , ear connect with its mouth through inter file to send acknowlegdment to sender .
On sender side after receiving acknowledgment ear will put this message in console file. and then sender's mouth send messages with header '1' and packet number.
On sender side after sending all the packets , sender send a acknowledgment to receiver with header 'c' that all packets are send from sender side . 
On receiver side after receiving header 'c' message , if some packets are missing then it will send a message to sender with header 'f' and missing packets number.
On sender side after receiving acknowledgment with header 'f' , create miss file in which all missing packets number is stored .
If there are some missing packets then it will resend that packets otherwise receiver will send acknowledgment with header 'e' as all packets are received .

####RUN:
Type `make` in your terminal to execute the Makefile.
`./a.out` <system name> <port number>

####CLEAN:
Enter `make clean' to remove all the object files and their final exectuable.
Also remove all miss , send , conf , inter , msg , file files.

   


 

