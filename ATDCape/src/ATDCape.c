/*
 ============================================================================
 Name        : ATDCape.c
 Author      : Chris Good, Sarah Waller, Logan Bonifer, Yaomin Zha
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {

	int file;
	char filename[40];
	int addr = 0b0110011; // The I2C address of the ADC
	char buf[15] = { 0 };

	//open the device file
	sprintf(filename, "/dev/i2c-3");
	if ((file = open(filename, O_RDWR)) < 0) {
		printf("Failed to open the bus.");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}
	//check the slave
	if (ioctl(file, I2C_SLAVE, addr) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}


	//write setup byte
	buf[0] = 0b10000010;
	if (write(file, buf, 1) != 1) {
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
		//buffer = g_strerror(errno);
		//printf(buffer);
		printf("\n\n");
	}

	//write Configuration Byte
	buf[0] = 0b00001111;

	if (write(file, buf, 1) != 1) {
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
		//buffer = g_strerror(errno);
		//printf(buffer);
		printf("\n\n");
	}


	float data;
	// Read the data for all channels and print
	if (read(file, buf, 16) != 16) {
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to read from the i2c bus.\n");
		//buffer = g_strerror(errno);
		//printf(buffer);
		printf("\n\n");
	} else {
		int i;
		for (i = 0; i < 16; i += 2) {
			data = (float) ((buf[i] & 0b00001111) << 8) + buf[i + 1];
			data = data / 4096 * 3.3;
			//channel = ((buf[0] & 0b00110000)>>4);
			printf("Data channel %d:  %04f\n", i / 2, data);
		}
	}
	return 0;
}
