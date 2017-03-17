#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int main(){
	
	printf("Hello world\n");

//	int fd = open("/dev/ttyUSB0", O_WRONLY);

    char *portname = "/dev/ttyUSB0";
    int fd;
    int wlen;

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    /*baudrate 115200, 8 bits, no parity, 1 stop bit */
    set_interface_attribs(fd, B115200);
    //set_mincount(fd, 0);                /* set to pure timed read */

    /* simple output */
    int running = 1;
    while (running){
    	int in = getch();
		if ( in == 27)
		{
			getch();
			//printf("%c\n", getch() );
			in = getch();
			//printf("%c\n", in);
			void * in_p = &in;
   		 	wlen = write(fd, in_p, 1);
		}
		else if (in == '.')
		{
			break;
		}
	
    }
    tcdrain(fd);    /* delay for output */

	close(fd);

	// int c;
	// /* use system call to make terminal send all keystrokes directly to stdin */
	// system ("/bin/stty raw");
	// while( (c=getchar()) != '.') {
		
	// 	getchar() >> /dev/null;
	// 	c = getchar();
	// 	 type a period to break out of the loop, since CTRL-D won't work raw 
	// 	if (c == 65){
	// 		//char in[5];
	// 		//sprintf(in, "%d",c);
	// 		printf("Received UP\n");
			
			
	// 	}
	// 	//putchar(c);
	// }
	// /* use system call to set terminal behaviour to more normal behaviour */
	// system ("/bin/stty cooked");

return 0;
	// exit(0);

}