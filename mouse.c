/* +-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
 |   2 |   8 |   SDA.1 |  OUT | 1 |  3 || 4  |   |      | 5v      |     |     |
 |   3 |   9 |   SCL.1 |  OUT | 1 |  5 || 6  |   |      | 0v      |     |     |
 |   4 |   7 | GPIO. 7 |  OUT | 0 |  7 || 8  | 1 | OUT  | TxD     | 15  | 14  |
 |     |     |      0v |      |   |  9 || 10 | 1 | IN   | RxD     | 16  | 15  |
 |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
 |  27 |   2 | GPIO. 2 |  OUT | 0 | 13 || 14 |   |      | 0v      |     |     |
 |  22 |   3 | GPIO. 3 |  OUT | 1 | 15 || 16 | 1 | OUT  | GPIO. 4 | 4   | 23  |
 |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
 |  10 |  12 |    MOSI |  OUT | 1 | 19 || 20 |   |      | 0v      |     |     |
 |   9 |  13 |    MISO | ALT0 | 0 | 21 || 22 | 1 | IN   | GPIO. 6 | 6   | 25  |
 |  11 |  14 |    SCLK |  OUT | 1 | 23 || 24 | 1 | OUT  | CE0     | 10  | 8   |
 |     |     |      0v |      |   | 25 || 26 | 1 | OUT  | CE1     | 11  | 7   |
 |   0 |  30 |   SDA.0 |  OUT | 1 | 27 || 28 | 0 | OUT  | SCL.0   | 31  | 1   |
 |   5 |  21 | GPIO.21 |  OUT | 0 | 29 || 30 |   |      | 0v      |     |     |
 |   6 |  22 | GPIO.22 |  OUT | 1 | 31 || 32 | 1 | OUT  | GPIO.26 | 26  | 12  |
 |  13 |  23 | GPIO.23 |  OUT | 1 | 33 || 34 |   |      | 0v      |     |     |
 |  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
 |  26 |  25 | GPIO.25 |  OUT | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
 |     |     |      0v |      |   | 39 || 40 | 1 | OUT  | GPIO.29 | 29  | 21  |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+
*/


#include <stdio.h>    // Used for printf() statements
  
#include <wiringPi.h> // Include WiringPi library!
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

 
#define dtik 1
// pin number declarations. We're using the Broadcom chip pin numbers.
const int p21pin = 2; // PWM LED - Broadcom pin 18, P1 pin 12
const int p22pin = 3; // Regular LED - Broadcom pin 23, P1 pin 16
const int p23pin = 4; // Active-low button - Broadcom pin 17, P1 pin 11
const int p24pin = 17;
const int p25pin = 27; // Use this to set an LED brightness
const int p26pin = 22;
const int p11pin = 10;
const int p12pin = 9;
const int p13pin = 11;
const int p14pin = 5;
const int p15pin = 6;
const int p16pin = 13;
const int papin = 8;
const int pbpin = 23;
const int pcpin = 12;
const int pdpin = 20;
const int pepin = 21;
const int pfpin = 24;
const int pgpin = 18;
const int pdppin = 16;

const int butpin = 26;


int xmouse=111111;
int ymouse=222222;
int xdpi=0;
int ydpi=0;

int programstate=0;

int sensitivity=800;

char digsy[6],digsx[6];




void ledcontrol();
void setledxchar (int count,int klen);
void setledychar (int count,int klen);
void set1char(void);
void set2char(void);
void set3char(void);
void set4char(void);
void set5char(void);
void set6char(void);
void set7char(void);
void set8char(void);
void set9char(void);
void set0char(void);

PI_THREAD (waitForIt);
PI_THREAD (waitForBut);
PI_THREAD (waitForMouse);


void psetupGPIO(void);

int main(void)
{
    // Setup stuff:
	FILE *fp;
	char strsens[5];
	fp = fopen("sensitivity.txt", "r");
	if(fp == NULL) 
	{
      perror("Error opening file");
      return(-1);
	}
	if( fgets (strsens, 5, fp)!=NULL ) 
	{
      /* writing content to stdout */
      sensitivity=atoi(strsens);
	 }
	 fclose(fp);	
	
	// Setup wiringPi

	wiringPiSetupSys () ;


	piThreadCreate (waitForIt) ;
	piThreadCreate (waitForBut) ;
	piThreadCreate (waitForMouse) ;
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

	psetupGPIO();
	
	piLock(0);
	xmouse=123456;
	ymouse=654321;
	piUnlock(0);
    // Loop (while(1)):
	
	
    while(1)
    {
	
		
		delay(1000);
    }

    return 0;
}
 
 
 
 void ledcontrol(){
	 
	 
		
	 int kxlen=0;
		int	 klenxmouse, klenymouse;
		int kylen=0;
	 klenxmouse=xmouse;
     while (klenxmouse > 0)
    {
        klenxmouse /= 10;
        kxlen++;
    } 
	 klenymouse=ymouse;
     while (klenymouse > 0)
    {
        klenymouse /= 10;
        kylen++;
    }
	 
	
	 
	 sprintf(digsx, "%d0", xmouse);
	 
	 sprintf(digsy, "%d0", ymouse);


	 
	digitalWrite(p21pin, LOW);
	setledychar(1,kylen);
	delay(dtik);
	digitalWrite(p21pin, HIGH); 
	digitalWrite(p22pin, LOW);
	setledychar(2,kylen);
	delay(dtik);
	digitalWrite(p22pin, HIGH); 
	digitalWrite(p23pin, LOW);
	setledychar(3,kylen);
	delay(dtik);
	digitalWrite(p23pin, HIGH); 
	digitalWrite(p24pin, LOW);
	setledychar(4,kylen);
	digitalWrite(pdppin, HIGH);
	delay(dtik);
	digitalWrite(pdppin, LOW);
	digitalWrite(p24pin, HIGH); 
	digitalWrite(p25pin, LOW);
	setledychar(5,kylen);
	delay(dtik);
	digitalWrite(p25pin, HIGH); 
	digitalWrite(p26pin, LOW);
	setledychar(6,kylen);
	delay(dtik);
	digitalWrite(p26pin, HIGH); 
	digitalWrite(p11pin, LOW);
	setledxchar(1,kxlen);
	delay(dtik);
	digitalWrite(p11pin, HIGH); 
	digitalWrite(p12pin, LOW);
	setledxchar(2,kxlen);
	delay(dtik);
	digitalWrite(p12pin, HIGH); 
	digitalWrite(p13pin, LOW);
	setledxchar(3,kxlen);
	delay(dtik);
	digitalWrite(p13pin, HIGH); 
	digitalWrite(p14pin, LOW);
	setledxchar(4,kxlen);
	digitalWrite(pdppin, HIGH);
	delay(dtik);
	digitalWrite(pdppin, LOW);
	digitalWrite(p14pin, HIGH); 
	digitalWrite(p15pin, LOW);
	setledxchar(5,kxlen);
	delay(dtik);
	digitalWrite(p15pin, HIGH); 
	digitalWrite(p16pin, LOW);
	setledxchar(6,kxlen);
	delay(dtik);
	digitalWrite(p16pin, HIGH); 

	 
 }
 void setledxchar (int count,int klen){
	   
	 count--;
	 if((count-(6-klen))>=0)
	 {
	 switch ( digsx[count-(6-klen)] ) {
		case '1':
		set1char();
		break;
		case '2':
		set2char();
		break;
		case '3':
		set3char();
		break;
		case '4':
		set4char();
		break;
		case '5':
		set5char();
		break;
		case '6':
		set6char();
		break;
		case '7':
		set7char();
		break;
		case '8':
		set8char();
		break;
		case '9':
		set9char();
		break;
		case '0':
		set0char();
		break;
		default:
		set0char();
		break;
		}
	 }else{
		set0char(); 
	 }
 }
 
 void setledychar (int count,int klen){
	 
	 
	 count--;
	 if((count-(6-klen))>=0)
	 {
	 switch ( digsy[count-(6-klen)] ) {
		case '1':
		set1char();
		break;
		case '2':
		set2char();
		break;
		case '3':
		set3char();
		break;
		case '4':
		set4char();
		break;
		case '5':
		set5char();
		break;
		case '6':
		set6char();
		break;
		case '7':
		set7char();
		break;
		case '8':
		set8char();
		break;
		case '9':
		set9char();
		break;
		case '0':
		set0char();
		break;
		default:
		set0char();
		break;
		}
	 }else{
		set0char(); 
	 }

 }
 
void set1char(void){
	
		digitalWrite(papin, LOW); 
		digitalWrite(pbpin, HIGH); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, LOW); 
		digitalWrite(pepin, LOW); 
		digitalWrite(pfpin, LOW); 
		digitalWrite(pgpin, LOW); 
		
}
void set2char(void){
	
		digitalWrite(papin, HIGH); 
		digitalWrite(pbpin, HIGH); 
		digitalWrite(pcpin, LOW); 
		digitalWrite(pdpin, HIGH); 
		digitalWrite(pepin, HIGH); 
		digitalWrite(pfpin, LOW); 
		digitalWrite(pgpin, HIGH); 
		
}
void set3char(void){
	
		digitalWrite(papin, HIGH); 
		digitalWrite(pbpin, HIGH); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, HIGH); 
		digitalWrite(pepin, LOW); 
		digitalWrite(pfpin, LOW); 
		digitalWrite(pgpin, HIGH); 
		
}
void set4char(void){
	
		digitalWrite(papin, LOW); 
		digitalWrite(pbpin, HIGH); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, LOW); 
		digitalWrite(pepin, LOW); 
		digitalWrite(pfpin, HIGH); 
		digitalWrite(pgpin, HIGH); 
		
}
void set5char(void){
	
		digitalWrite(papin, HIGH); 
		digitalWrite(pbpin, LOW); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, HIGH); 
		digitalWrite(pepin, LOW); 
		digitalWrite(pfpin, HIGH); 
		digitalWrite(pgpin, HIGH); 
		
}
void set6char(void){
	
		digitalWrite(papin, HIGH); 
		digitalWrite(pbpin, LOW); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, HIGH); 
		digitalWrite(pepin, HIGH); 
		digitalWrite(pfpin, HIGH); 
		digitalWrite(pgpin, HIGH); 
		
}
void set7char(void){
	
		digitalWrite(papin, HIGH); 
		digitalWrite(pbpin, HIGH); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, LOW); 
		digitalWrite(pepin, LOW); 
		digitalWrite(pfpin, LOW); 
		digitalWrite(pgpin, LOW); 
		
}
void set8char(void){
	
		digitalWrite(papin, HIGH); 
		digitalWrite(pbpin, HIGH); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, HIGH); 
		digitalWrite(pepin, HIGH); 
		digitalWrite(pfpin, HIGH); 
		digitalWrite(pgpin, HIGH); 
		
}
void set9char(void){
	
		digitalWrite(papin, HIGH); 
		digitalWrite(pbpin, HIGH); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, HIGH); 
		digitalWrite(pepin, LOW); 
		digitalWrite(pfpin, HIGH); 
		digitalWrite(pgpin, HIGH); 
		
}
void set0char(void){
	
		digitalWrite(papin, HIGH); 
		digitalWrite(pbpin, HIGH); 
		digitalWrite(pcpin, HIGH); 
		digitalWrite(pdpin, HIGH); 
		digitalWrite(pepin, HIGH); 
		digitalWrite(pfpin, HIGH); 
		digitalWrite(pgpin, LOW); 
		
}
 
 
PI_THREAD (waitForIt)
{
	
 

  (void)piHiPri (1) ;	// Set this thread to be low priority
	while(1)
	{
		ledcontrol();
			
	
	}
  
}

PI_THREAD (waitForBut)
{
	int buttstateplus=0;
 int buttstate=0;
FILE *fp;
	char strsens[5];
	
  (void)piHiPri (2) ;	// Set this thread to be low priority
	while(1)
	{
		
		if (digitalRead(butpin)) // Button is released if this returns 1
        {
			if(buttstate>0){
				
				buttstate--;
			}
			if(buttstate<5)
			{
				buttstateplus=0;
			}
			if (programstate==0){
				if (buttstate>5){
					xdpi=0;
					ydpi=0;
					piLock(0);
					xmouse=0;
					ymouse=0;
					piUnlock(0);
					buttstateplus=1;
				}
			}
			if (programstate==1){
			
				if ((buttstate>4)&&(buttstateplus==0)){
					
					buttstateplus=1;
					if(sensitivity<8000){
						sensitivity+=50;
					}else{
						sensitivity=600;
					}
					
					piLock(0);
					xmouse=sensitivity;
					ymouse=sensitivity;
					piUnlock(0);
					buttstate=0;
				}
			}
        }
        else // If digitalRead returns 0, button is pressed
        {
			if(buttstate<1000)
			buttstate+=2;
        }	
		if (programstate==0){
			
			if (buttstate>200){
				buttstateplus=1;
				programstate=1;
				digitalWrite(pdppin, LOW);
				piLock(0);
				xmouse=sensitivity;
				ymouse=sensitivity;
				piUnlock(0);
				buttstate=0;
			
			}
		}
		if (programstate==1){
			
				
			if (buttstate>800){
				programstate=0;
				xdpi=0;
				ydpi=0;
				piLock(0);
				xmouse=0;
				ymouse=0;		
				piUnlock(0);
				buttstate=0;
				buttstateplus=1;
				fp = fopen("sensitivity.txt", "w");
				if(fp == NULL) 
				{
				  perror("Error opening file");
				  //return(-1);
				}
				snprintf(strsens,5,"%d",sensitivity);
				fputs(strsens,fp);
				 
				
				fclose(fp);
			}				
		}

		delay(10);
	}
  
}

void psetupGPIO(void)
{
	 pinMode(p21pin, OUTPUT); 
	 pinMode(p22pin, OUTPUT);
	 pinMode(p23pin, OUTPUT);
	 pinMode(p24pin, OUTPUT);
	 pinMode(p25pin, OUTPUT);
	 pinMode(p26pin, OUTPUT);
	 pinMode(p11pin, OUTPUT);
	 pinMode(p12pin, OUTPUT);
	 pinMode(p13pin, OUTPUT);
	 pinMode(p14pin, OUTPUT);
	 pinMode(p15pin, OUTPUT);
	 pinMode(p16pin, OUTPUT);
	 pinMode(papin, OUTPUT);
	 pinMode(pbpin, OUTPUT);
	 pinMode(pcpin, OUTPUT);
	 pinMode(pdpin, OUTPUT);
	 pinMode(pepin, OUTPUT);
	 pinMode(pfpin, OUTPUT);
	 pinMode(pgpin, OUTPUT);
	 pinMode(pdppin, OUTPUT);
	 
     pinMode(butpin, INPUT);      // Set button as INPUT
     pullUpDnControl(butpin, PUD_UP); // Enable pull-up resistor on button

	digitalWrite(p21pin, HIGH); 
	digitalWrite(p22pin, HIGH); 
    digitalWrite(p23pin, HIGH); 
	digitalWrite(p24pin, HIGH); 
    digitalWrite(p25pin, HIGH); 
	digitalWrite(p26pin, HIGH); 
    digitalWrite(p11pin, HIGH); 
	digitalWrite(p12pin, HIGH); 
    digitalWrite(p13pin, HIGH); 
	digitalWrite(p14pin, HIGH); 
    digitalWrite(p15pin, HIGH); 
	digitalWrite(p16pin, HIGH); 
    
	digitalWrite(papin, LOW); 
	digitalWrite(pbpin, LOW); 
	digitalWrite(pcpin, LOW); 
	digitalWrite(pdpin, LOW); 
	digitalWrite(pepin, LOW); 
	digitalWrite(pfpin, LOW); 
	digitalWrite(pgpin, LOW); 
	digitalWrite(pdppin, LOW); 
	
	
	printf("Blinker is running! Press CTRL+C to quit.\n");

}
PI_THREAD (waitForMouse)
{
	int fd, bytes;
    unsigned char data[3];

    int left,right;
    signed char x, y;
    const char *pDevice = "/dev/input/mice";

   (void)piHiPri (10) ;	// Set this thread to be high priority
	
    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        //return -1;
    }

    while(1)
    {
        // Read Mouse     
        bytes = read(fd, data, sizeof(data));
		if (programstate==0){
			if(bytes > 0)
			{
				left = data[0] & 0x1;
				if(left==1)
				{
					piLock(0);
					xdpi=0;
					ydpi=0;
					piUnlock(0);	
				}

				x = data[1];
				y = data[2];
				xdpi+=x;
				ydpi+=y;
				piLock(0);
				xmouse=xdpi*2540/sensitivity;
				ymouse=ydpi*2540/sensitivity;
				piUnlock(0);
				printf("x=%d, y=%d, left=%d\n", x, y, left);
			}   
		}
		
		if (programstate==1){
			if(bytes > 0)
			{
				left = data[0] & 0x1;
				
				if(left==1)
				{
					if(sensitivity>600){
						sensitivity-=50;
					}else{
						sensitivity=8000;
					}	
				}
				piLock(0);
				xmouse=sensitivity;
				ymouse=sensitivity;
				piUnlock(0);
			}
		}
    }
  
}
