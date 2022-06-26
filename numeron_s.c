#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#ifdef __linux__
#endif

#define BUFFSIZE 1024
#define SOCKN 10   	 
#define R 12345
#define N 1000

int nmv(int num)
{
 if(num<100||num>999){return -1;}
 else {
 int n1=num/100;
 int n2=(num-n1*100)/10;
 int n3=(num-n1*100-n2*10);
 if (n1==n2||n2==n3||n3==n1){return -1;}
 else{return 0;}
 }
}

int eat(int num1,int num2)
{
 if(nmv(num2)==-1){return -1;}
 else{
 int a=0;
 int n11=num1/100;
 int n12=(num1-n11*100)/10;
 int n13=(num1-n11*100-n12*10);
 int n21=num2/100;
 int n22=(num2-n21*100)/10;
 int n23=(num2-n21*100-n22*10);
 if(n11==n21){a++;}
 if(n12==n22){a++;}
 if(n13==n23){a++;}
 return a;}
}

int bite(int num1,int num2)
{if(nmv(num2)==-1){return -1;}
else{
 int a=0;
 int n11=num1/100;
 int n12=(num1-n11*100)/10;
 int n13=(num1-n11*100-n12*10);
 int n21=num2/100;
 int n22=(num2-n21*100)/10;
 int n23=(num2-n21*100-n22*10);
 if(n11==n22){a++;}
 if(n11==n23){a++;}
 if(n12==n21){a++;}
 if(n12==n23){a++;}
 if(n13==n21){a++;}
 if(n13==n22){a++;}
 return a;}
}

void Numeron(int s[SOCKN], int sno1, int sno2) {
  char buff[BUFFSIZE];
  int turn=-1;
  fd_set fds, readfds;
  int maxfd;
  char ans1c[4];
  char ans2c[4];
  char num1c[4];
  char num2c[4];
  int ans1n;
  int ans2n;
  int num1n;
  int num2n;
  int end=0;
 
  FD_ZERO(&readfds);     	// init fd_set.
  FD_SET(s[sno1], &readfds); // register a socket.
  FD_SET(s[sno2], &readfds); // register a scooket.
  if (s[sno1] > s[sno2]) {   // register a max file discriptor
	maxfd = s[sno1];
  } else {
	maxfd = s[sno2];
  }


while(1){  
	if(turn==-1){
	sprintf(buff,"\x1b[31m３桁の数を指定してください\x1b[39m\n");
	write(s[sno1], buff, strlen(buff) + 1);
    
	sprintf(buff,"\x1b[34m相手が３桁の数を指定しています\x1b[39m\n");
	write(s[sno2], buff, strlen(buff) + 1);
	read(s[sno1], ans1c, N);
	ans1n = atoi(ans1c);

	while(nmv(ans1n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno1], buff, strlen(buff) + 1);
	read(s[sno1], ans1c, N);
	ans1n=atoi(ans1c);
	}
 
    
	turn++;
}

if(turn==0){
	sprintf(buff,"\x1b[31m３桁の数を指定してください\x1b[39m\n");
	write(s[sno2], buff, strlen(buff) + 1);
    
	sprintf(buff,"\x1b[34m相手が３桁の数を指定しています\x1b[39m\n");
	write(s[sno1], buff, strlen(buff) + 1);
	read(s[sno2], ans2c, N);
	ans2n = atoi(ans2c);
    
while(nmv(ans2n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno2], buff, strlen(buff) + 1);
	read(s[sno2], ans2c, N);
	ans2n=atoi(ans2c);
	}

	if(nmv(ans2n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno2], buff, strlen(buff) + 1);
	continue;
	}
    
    
	turn++;
}

if(turn==1){
sprintf(buff,"\n\x1b[31m%d あなたのターンです\x1b[39m\n",turn);
write(s[sno1], buff, strlen(buff) + 1);
sprintf(buff,"\n\x1b[34m%d 相手のターンです\x1b[39m\n",turn);
write(s[sno2], buff, strlen(buff) + 1);
}


if(turn>0 && turn%2==0&& end==0){

read(s[sno2], num2c, N);
num2n=atoi(num2c);

while(nmv(num2n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno2], buff, strlen(buff) + 1);
	read(s[sno2], num2c, N);
	num2n=atoi(num2c);
	}


if(eat(ans1n,num2n)!=3){
sprintf(buff,"%d eat %d bite です\n\n\x1b[34m%d 相手のターンです\x1b[39m\n",eat(ans1n,num2n),bite(ans1n,num2n),(turn+1));
write(s[sno2], buff, strlen(buff) + 1);
sprintf(buff,"相手の入力は %d で、%d eat %d bite です\n\n\x1b[31m%d あなたのターンです\x1b[39m\n",num2n,eat(ans1n,num2n),bite(ans1n,num2n),(turn+1));
write(s[sno1], buff, strlen(buff) + 1);
}

else
{sprintf(buff,"\x1b[46m当たり！あなたの勝ちです！\x1b[49m\n");
 write(s[sno2], buff, strlen(buff) + 1);
 sprintf(buff,"\x1b[41m当てられた！あなたの負けです！\x1b[49m\n");
 write(s[sno1], buff, strlen(buff) + 1);
 
 end=1;
 }

turn++;
}

if(turn>0 && turn%2==1 && end==0){


read(s[sno1], num1c, N);
num1n=atoi(num1c);

while(nmv(num1n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno1], buff, strlen(buff) + 1);
	read(s[sno1], num1c, N);
	num1n=atoi(num1c);
	}



    
if(eat(ans2n,num1n)!=3){
sprintf(buff,"%d eat %d bite です\n\n\x1b[34m%d 相手のターンです\x1b[39m\n",eat(ans2n,num1n),bite(ans2n,num1n),(turn+1));
write(s[sno1], buff, strlen(buff) + 1);
sprintf(buff,"相手の入力は %d で、%d eat %d bite です\n\n\x1b[31m%d あなたのターンです\x1b[39m\n",num1n,eat(ans2n,num1n),bite(ans2n,num1n),(turn+1));
write(s[sno2], buff, strlen(buff) + 1);
}

else
{sprintf(buff,"\x1b[33m当たり！次に当てられなければあなたの勝ちです！\x1b[39m\n\n\x1b[34m%d 相手のターンです\x1b[39m\n",(turn+1));
 write(s[sno1], buff, strlen(buff) + 1);
 sprintf(buff,"\x1b[36m当てられた！次に当てないとあなたの負けです！\x1b[39m\n\n\x1b[31m%d あなたのターンです\x1b[39m\n",(turn+1));
 write(s[sno2], buff, strlen(buff) + 1);

read(s[sno2], num2c, N);
num2n=atoi(num2c);
while(nmv(num2n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno2], buff, strlen(buff) + 1);
	read(s[sno2], num2c, N);
	num2n=atoi(num2c);
	}
if(eat(ans1n,num2n)!=3){
sprintf(buff,"\x1b[41m外れ...あなたの負けです！\x1b[49m\n");
write(s[sno2], buff, strlen(buff) + 1);
sprintf(buff,"\x1b[46m当てられなかった！あなたの勝ちです！\x1b[49m\n");
write(s[sno1], buff, strlen(buff) + 1);
}
else
{sprintf(buff,"\x1b[42m当たり！引き分けです！\x1b[49m\n");
 write(s[sno2], buff, strlen(buff) + 1);
 sprintf(buff,"\x1b[42m当てられた！引き分けです！\x1b[49m\n");
 write(s[sno1], buff, strlen(buff) + 1);
 
 }
 end=1;
 }

turn++;
}

}
}

int main(int argc, char **argv) {
  int i, j;
  int sock, s[SOCKN];
  struct sockaddr_in sin, csin;
  socklen_t csinlen;
  char buff[BUFFSIZE];
  int recvlen;
  int cid = 0;
  pid_t p_pid, pid;


  // make socket
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	perror("socket");
	exit(1);
  }

  // write server infomation
  bzero((char*)&sin, sizeof(sin));     	// zero clear
  sin.sin_family = AF_INET;
  sin.sin_port = htons(atoi(argv[1]));         	// convert to bigendian
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  // client is any

  // bind
  if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
	perror("bind");
	exit(1);
  }

  // listen: number of connecting client together
  if (listen(sock, 2) < 0) {
	perror("listen");
	exit(1);
  }
 
  // set parent process id
  p_pid = getpid();




  while (1) {
	// wait for connection
	csinlen = sizeof(csin);
	if ((s[cid] = accept(sock, (struct sockaddr*)&csin, &csinlen)) < 0) { // wait until connect from client
  	perror("accept");
  	exit(1);
	}
    
	printf("[cid=%d] client connection\n", cid++);
    
   
	if (cid % 2 == 0) {
  	switch (pid = fork()) {
  	case 0:  // child
    	Numeron(s, cid - 2, cid - 1);  
    	exit(0);
  	case -1:
    	perror("fork");
    	break;
  	default:
    	printf("[%d]generate child proc %d\n", p_pid, pid);
    	break;
  	}
	}
  }

  // end socket ns
  for (i = 0; i < cid; i++) {
	close(s[i]);
  }

  // end socket s
  close (sock);

  return 0;
}


ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
4桁numeron サーバ

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#ifdef __linux__
#endif

#define BUFFSIZE 1024
#define SOCKN 10   	 
#define R 12345
#define N 1000
int nmv(int num)
{
 if(num<1000||num>9999){return -1;}
 else {
 int n1=num/1000;
 int n2=(num-n1*1000)/100;
 int n3=(num-n1*1000-n2*100)/10;
 int n4=(num-n1*1000-n2*100-n3*10);
 if (n1==n2||n1==n3||n1==n4||n2==n3||n2==n4||n3==n4){return -1;}
 else{return 0;}
 }
}

int eat(int num1,int num2)
{
 if(nmv(num2)==-1){return -1;}
 else{
 int a=0;
 int n11=num1/1000;
 int n12=(num1-n11*1000)/100;
 int n13=(num1-n11*1000-n12*100)/10;
 int n14=(num1-n11*1000-n12*100-n13*10);
 int n21=num2/1000;
 int n22=(num2-n21*1000)/100;
 int n23=(num2-n21*1000-n22*100)/10;
 int n24=(num2-n21*1000-n22*100-n23*10);
 if(n11==n21){a++;}
 if(n12==n22){a++;}
 if(n13==n23){a++;}
 if(n14==n24){a++;}
 return a;}
}

int bite(int num1,int num2)
{if(nmv(num2)==-1){return -1;}
else{
 int a=0;
 int n11=num1/1000;
 int n12=(num1-n11*1000)/100;
 int n13=(num1-n11*1000-n12*100)/10;
 int n14=(num1-n11*1000-n12*100-n13*10);
 int n21=num2/1000;
 int n22=(num2-n21*1000)/100;
 int n23=(num2-n21*1000-n22*100)/10;
 int n24=(num2-n21*1000-n22*100-n23*10);
 if(n11==n22){a++;}
 if(n11==n23){a++;}
 if(n11==n24){a++;}
 if(n12==n21){a++;}
 if(n12==n23){a++;}
 if(n12==n24){a++;}
 if(n13==n21){a++;}
 if(n13==n22){a++;}
 if(n13==n24){a++;}
 if(n14==n21){a++;}
 if(n14==n22){a++;}
 if(n14==n23){a++;}
 
 return a;}
}

void Numeron(int s[SOCKN], int sno1, int sno2) {
  char buff[BUFFSIZE];
  int turn=-1;
  fd_set fds, readfds;
  int maxfd;
  char ans1c[5];
  char ans2c[5];
  char num1c[5];
  char num2c[5];
  int ans1n;
  int ans2n;
  int num1n;
  int num2n;
  int end=0;
 
  FD_ZERO(&readfds);     	// init fd_set.
  FD_SET(s[sno1], &readfds); // register a socket.
  FD_SET(s[sno2], &readfds); // register a scooket.
  if (s[sno1] > s[sno2]) {   // register a max file discriptor
	maxfd = s[sno1];
  } else {
	maxfd = s[sno2];
  }


while(1){  
	if(turn==-1){
	sprintf(buff,"\x1b[31m４桁の数を指定してください\x1b[39m\n");
	write(s[sno1], buff, strlen(buff) + 1);
    
	sprintf(buff,"\x1b[34m相手が４桁の数を指定しています\x1b[39m\n");
	write(s[sno2], buff, strlen(buff) + 1);
	read(s[sno1], ans1c, N);
	ans1n = atoi(ans1c);

	while(nmv(ans1n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno1], buff, strlen(buff) + 1);
	read(s[sno1], ans1c, N);
	ans1n=atoi(ans1c);
	}
 
    
	turn++;
}

if(turn==0){
	sprintf(buff,"\x1b[31m４桁の数を指定してください\x1b[39m\n");
	write(s[sno2], buff, strlen(buff) + 1);
    
	sprintf(buff,"\x1b[34m相手が４桁の数を指定しています\x1b[39m\n");
	write(s[sno1], buff, strlen(buff) + 1);
	read(s[sno2], ans2c,N);
	ans2n = atoi(ans2c);
    
while(nmv(ans2n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno2], buff, strlen(buff) + 1);
	read(s[sno2], ans2c, N);
	ans2n=atoi(ans2c);
	}

	if(nmv(ans2n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno2], buff, strlen(buff) + 1);
	continue;
	}
    
    
	turn++;
}

if(turn==1){
sprintf(buff,"\n\x1b[31m%d あなたのターンです\x1b[39m\n",turn);
write(s[sno1], buff, strlen(buff) + 1);
sprintf(buff,"\n\x1b[34m%d 相手のターンです\x1b[39m\n",turn);
write(s[sno2], buff, strlen(buff) + 1);
}


if(turn>0 && turn%2==0&& end==0){

read(s[sno2], num2c, N);
num2n=atoi(num2c);

while(nmv(num2n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno2], buff, strlen(buff) + 1);
	read(s[sno2], num2c, N);
	num2n=atoi(num2c);
	}


if(eat(ans1n,num2n)!=4){
sprintf(buff,"%d eat %d bite です\n\n\x1b[34m%d 相手のターンです\x1b[39m\n",eat(ans1n,num2n),bite(ans1n,num2n),(turn+1));
write(s[sno2], buff, strlen(buff) + 1);
sprintf(buff,"相手の入力は %d で、%d eat %d bite です\n\n\x1b[31m%d あなたのターンです\x1b[39m\n",num2n,eat(ans1n,num2n),bite(ans1n,num2n),(turn+1));
write(s[sno1], buff, strlen(buff) + 1);
}

else
{sprintf(buff,"\x1b[41m当たり！あなたの勝ちです！\x1b[49m\n");
 write(s[sno2], buff, strlen(buff) + 1);
 sprintf(buff,"\x1b[46m当てられた！あなたの負けです！\x1b[49m\n");
 write(s[sno1], buff, strlen(buff) + 1);
 
 end=1;
 }

turn++;
}

if(turn>0 && turn%2==1 && end==0){


read(s[sno1], num1c, N);
num1n=atoi(num1c);

while(nmv(num1n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno1], buff, strlen(buff) + 1);
	read(s[sno1], num1c, N);
	num1n=atoi(num1c);
	}



    
if(eat(ans2n,num1n)!=4){
sprintf(buff,"%d eat %d bite です\n\n\x1b[34m%d 相手のターンです\x1b[39m\n",eat(ans2n,num1n),bite(ans2n,num1n),(turn+1));
write(s[sno1], buff, strlen(buff) + 1);
sprintf(buff,"相手の入力は %d で、%d eat %d bite です\n\n\x1b[31m%d あなたのターンです\x1b[39m\n",num1n,eat(ans2n,num1n),bite(ans2n,num1n),(turn+1));
write(s[sno2], buff, strlen(buff) + 1);
}

else
{sprintf(buff,"\x1b[33m当たり！次に当てられなければあなたの勝ちです！\x1b[39m\n\n\x1b[34m%d 相手のターンです\x1b[39m\n",(turn+1));
 write(s[sno1], buff, strlen(buff) + 1);
 sprintf(buff,"\x1b[36m当てられた！次に当てないとあなたの負けです！\x1b[39m\n\n\x1b[31m%d あなたのターンです\x1b[39m\n",(turn+1));
 write(s[sno2], buff, strlen(buff) + 1);

read(s[sno2], num2c, N);
num2n=atoi(num2c);
while(nmv(num2n)==-1){
	sprintf(buff,"無効な値です\n");
	write(s[sno2], buff, strlen(buff) + 1);
	read(s[sno2], num2c, N);
	num2n=atoi(num2c);
	}
if(eat(ans1n,num2n)!=4){
sprintf(buff,"\x1b[46m外れ...あなたの負けです！\x1b[49m\n");
write(s[sno2], buff, strlen(buff) + 1);
sprintf(buff,"\x1b[41m当てられなかった！あなたの勝ちです！\x1b[49m\n");
write(s[sno1], buff, strlen(buff) + 1);
}
else
{sprintf(buff,"\x1b[42m当たり！引き分けです！\x1b[49m\n");
 write(s[sno2], buff, strlen(buff) + 1);
 sprintf(buff,"\x1b[42m当てられた！引き分けです！\x1b[49m\n");
 write(s[sno1], buff, strlen(buff) + 1);
 
 }
 end=1;
 }

turn++;
}

}
}

int main(int argc, char **argv) {
  int i, j;
  int sock, s[SOCKN];
  struct sockaddr_in sin, csin;
  socklen_t csinlen;
  char buff[BUFFSIZE];
  int recvlen;
  int cid = 0;
  pid_t p_pid, pid;


  // make socket
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	perror("socket");
	exit(1);
  }

  // write server infomation
  bzero((char*)&sin, sizeof(sin));     	// zero clear
  sin.sin_family = AF_INET;
  sin.sin_port = htons(atoi(argv[1]));         	// convert to bigendian
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  // client is any

  // bind
  if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
	perror("bind");
	exit(1);
  }

  // listen: number of connecting client together
  if (listen(sock, 2) < 0) {
	perror("listen");
	exit(1);
  }
 
  // set parent process id
  p_pid = getpid();




  while (1) {
	// wait for connection
	csinlen = sizeof(csin);
	if ((s[cid] = accept(sock, (struct sockaddr*)&csin, &csinlen)) < 0) { // wait until connect from client
  	perror("accept");
  	exit(1);
	}
    
	printf("[cid=%d] client connection\n", cid++);
    
   
	if (cid % 2 == 0) {
  	switch (pid = fork()) {
  	case 0:  // child
    	Numeron(s, cid - 2, cid - 1);  
    	exit(0);
  	case -1:
    	perror("fork");
    	break;
  	default:
    	printf("[%d]generate child proc %d\n", p_pid, pid);
    	break;
  	}
	}
  }

  // end socket ns
  for (i = 0; i < cid; i++) {
	close(s[i]);
  }

  // end socket s
  close (sock);

  return 0;
}
