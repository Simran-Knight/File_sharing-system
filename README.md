#BABYSTEPS

## AUTHORS:
- **Yash Lichade**, Roll No: 23111056  
- **Simran Singh**, Roll No: 23111059  

## DESCRIPTION:  
This is an assignment for the course **CS-603 SYSTEM-III** during the **3rd semester of the academic year 2024**.  
The aim is to understand networking features in real-time applications.  

In this project:  
- The **sender** transmits large messages by breaking them into smaller chunks.  
- The **receiver** reconstructs the original message from these chunks.  
- Messages can include **text files, images, and videos**.  
- We use **UDP Sockets** and **C language** to enable communication between multiple terminals (processes).  

---

### **File Descriptions**  

- `system.txt` → Contains a list of system names and their corresponding port numbers.  
- `send` → Stores the system number to which the message is being sent.  
- `miss` → Stores missing packet numbers or indicates that all packets have been received.  
- `conf` → Confirmation file storing acknowledgments from the receiver.  
- `inter` → Intermediate file facilitating communication between the receiver’s "ear" and "mouth".  
- `msg` → Stores the filename specified by the user.  
- `file` → Stores all received filenames.  

---

## **Process Flow**  

### **1. User Input**  
- The user provides a system number, which is stored in the `send` file.  
- The user specifies a filename (e.g., text file, image, or video), which is stored in the `msg` file.  

### **2. Determining the Target System**  
- The system number is retrieved from the `send` file.  
- The corresponding port number is found by reading `system.txt`, which contains a list of systems and their port numbers.  

### **3. File Processing**  
- The filename is retrieved from the `msg` file.  
- The specified file is opened, and packets are computed based on the system’s buffer size.  

### **4. Instruction Message Creation**  
A structured instruction message is created, consisting of:  
- **Header:** `a`  
- **Filename**  
- **Sender’s port number**  
- **Total number of packets**  
- **Maximum data size per packet**  

### **5. Acknowledgment Exchange**  
- The receiver’s **"ear"** receives the instruction message and connects to its **"mouth"** via an intermediate file (`inter`) to send an acknowledgment.  
- The sender’s **"ear"** receives this acknowledgment and logs it in the `console` file.  

### **6. Data Transmission**  
- The sender’s **"mouth"** transmits packets with:  
  - **Header:** `1`  
  - **Packet number**  

### **7. Completion and Verification**  
- After sending all packets, the sender transmits a completion acknowledgment with the **header:** `c`.  
- The receiver checks for missing packets. If any packets are missing, it sends a request with **header:** `f`, listing the missing packet numbers.  
- The sender logs the missing packets in the `miss` file and resends them.  

### **8. Final Acknowledgment**  
- Once all packets are successfully received, the receiver sends a **final acknowledgment** with **header:** `e`, confirming successful transmission.  


####**RUN:**
Type `make` in your terminal to execute the Makefile.
`./a.out` <system name> <port number>

####**CLEAN:**
Enter `make clean` to remove all the object files and their final exectuable.
Also remove all miss , send , conf , inter , msg , file files.

   


 

