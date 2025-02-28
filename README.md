#BABYSTEPS

####AUTHORS:
	YASH LICHADE ,ROLL NO - 23111056
	SIMRAN SINGH ,ROLL NO - 23111059

####DESCRIPTION:This is an assignment given to us for the course,`CS-603 SYSTEM-III` during 3rd semster of academic year 2024 , with the aim to understand the features of networking in real-time application .
In this sender has send a large size messages into smaller chunks and receiver receive the small chunks to form a messages where messages can be a text file , images , videos . We have been using UDP Socket and C language to develop communication between multiple terminals(processes).

Brief description :-

-We have system.txt -> In which all system with their name and port number is listed . 
-send file -> To whom we send the message .
-miss file -> Stored missing packets number or all packet received msg.
-conf file -> Confirmation file , stored acknowledgment from the receiver side .
-inter file ->Intermediate file , between ear and mouth.
-msg file  -> Message file , stored filename from user.
-file file -> stored all filename that we have received.

Process Flow

-User Input:
        -The user provides a system number, which is stored in the send file.
        -The user specifies a filename (e.g., text file, image, or video), which is stored in the message file.

-Determining the Target System:
        -The system number is retrieved from the send file.
        -The corresponding port number is found by reading the system.txt file, which contains a list of systems and their port numbers.

-File Processing:
        -The filename is retrieved from the message file.
        -The specified file is opened, and packets are computed based on the system’s buffer size.

-Instruction Message Creation:
        -A structured instruction message is created, consisting of:
            -Header (a)
            -Filename
            -Sender’s port number
            -Total number of packets
            -Maximum data size per packet

-Acknowledgment Exchange:
        -The receiver’s "ear" component receives the instruction message and connects to its "mouth" via an inter-process file to send an acknowledgment.
        -The sender’s "ear" receives this acknowledgment and logs it in the console file.

-Data Transmission:
        -The sender’s "mouth" transmits packets with:
            -Header (1)
            -Packet number

-Completion and Verification:
        -After sending all packets, the sender transmits a completion acknowledgment with the header (c).
        -The receiver checks for missing packets. If any packets are missing, it sends a request with the header (f), listing the missing packet numbers.
        -The sender logs the missing packets in the miss file and resends them.

-Final Acknowledgment:
        -Once all packets are successfully received, the receiver sends a final acknowledgment with the header (e), confirming the successful transmission.
####RUN:
Type `make` in your terminal to execute the Makefile.
`./a.out` <system name> <port number>

####CLEAN:
Enter `make clean` to remove all the object files and their final exectuable.
Also remove all miss , send , conf , inter , msg , file files.

   


 

