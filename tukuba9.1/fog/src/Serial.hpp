//シリアル通信を行うクラス

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include<iostream>
#include<termios.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>

class Serial{

private:
	int fd;
	bool rock;
	
public:
	int receive_sci(unsigned char *data, int length, unsigned char *header, int header_size);
	int send_sci(unsigned char *data, int length);
	int init(const char *port_name, int baud_rate, int data_bit, int stop_bit, int parity);
	int close_sci();
	Serial();
	~Serial();
};

#endif
