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
#include <sys/time.h>

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
	buf[0] = 0b10000010;;
	if (write(file, buf, 1) != 1) {
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
		//buffer = g_strerror(errno);
		//printf(buffer);
		printf("\n\n");
	}
	int i;
	while (1){//(i = 0; i < 10000; i++) {

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
				printf("Data channel %d:  %f", i / 2, data);
				data = data / 4096 * 24 * 2 - 24;
				//channel = ((buf[0] & 0b00110000)>>4);
				printf("Data channel %d:  %04f\n", i / 2, data);
				FILE *fileWrite;
				char fileName[16] = "valueX.txt";
				fileName[5] = '1' + i/2;
				fileWrite = fopen(fileName, "w");
				fprintf(fileWrite, "%f", data);
				fclose(fileWrite);
				//printf("%f\n", data);

			}
		}
		printf("\n");
		usleep(100000);
	}

//	//write Configuration Byte
//
//	double data;
//	double voltage;
//	double reference = 3.3;
//	double dividerMultiplier = (8.15);
////	double dividerMultiplier = 1;
//	int twosComplement = 1;
//	int j;
//	int negative;
//	printf("about to start the loop of 10k\n\n");
//	// Read the data for all channels and print
//	for (j = 0; j < 10000; j++) {
//		buf[0] = 0b00000000;
//
//		if (write(file, buf, 1) != 1) {
//			/* ERROR HANDLING: i2c transaction failed */
//			printf("Failed to write to the i2c bus.\floatn");
//			//buffer = g_strerror(errno);
//			//printf(buffer);
//			printf("\n\n");
//		}
//	//		gettimeofday(starttime, NULL);
//		if (read(file, buf, 2) != 2) {
//			/* ERROR HANDLING: i2c transaction failed */
//			printf("Failed to read from the i2c bus.\n");
//			//buffer = g_strerror(errno);
//			//printf(buffer);
//			printf("\n\n");
//		} else {
//			int i;
//			for (i = 0; i < 2; i += 2) {
//	//			printf("%d %d\n", buf[i] & 0b00001111, buf[i + 1]);
//				negative = 0;
////				if (twosComplement) {
////					if (buf[i] & 0b00001000) {
////						buf[i] = buf[i] ^ 0b11111111;
////	//					buf[i] = buf[i] & 0b00000111;
////						buf[i + 1] = buf[i + 1] ^ 0b11111111;
////						negative = 1;
////					}
////					data = ((buf[i] & 0b00000111) << 8) + buf[i + 1];
////	//					printf("%d %d\n", buf[i], buf[i + 1]);
////					data++;
////					if (negative) {
////
////						data = 0 - data;
////					}
////
////				} else {
//				data = ((buf[i] & 0b00001111) << 8) + buf[i + 1];
////				}
//
//				voltage = (data / 4096.0) * 24 - 12; // - (reference * 100/(715+100)) / 2;
//	//			channel = ((buf[0] & 0b00110000)>>4);
//					printf("Data channel %d:  %04f Voltage: %04f \n\n", i / 2, data, voltage);
//				FILE *fileWrite;
//				fileWrite = fopen("value.txt","w");
//				fprintf(fileWrite,"%f",voltage);
//				fclose(fileWrite);
//				printf("%f\n", voltage);
//			}
//		}
//	//		gettimeofday(endtime, NULL);
//	//		double timechange = (1000000 * endtime.tv_sec + endtime.tv_usec)
//	//				- (1000000 * starttime.tv_sec + starttime.tv_usec);
//
//				usleep(10000);
//	}

//	int file;
//	char filename[40];
//	int addr = 0b0110011; // The I2C address of the ADC
//	char buf[15] = { 0 };
//
////open the device file
//	sprintf(filename, "/dev/i2c-3");
//	if ((file = open(filename, O_RDWR)) < 0) {
//		printf("Failed to open the bus.");
//		/* ERROR HANDLING; you can check errno to see what went wrong */
//		exit(1);
//	}
////check the slave
//	if (ioctl(file, I2C_SLAVE, addr) < 0) {
//		printf("Failed to acquire bus access and/or talk to slave.\n");
//		/* ERROR HANDLING; you can check errno to see what went wrong */
//		exit(1);
//	}
//
////write setup byte
//	buf[0] = 0b10000010;
//	if (write(file, buf, 1) != 1) {
//		/* ERROR HANDLING: i2c transaction failed */
//		printf("Failed to write to the i2c bus.\n");
////buffer = g_strerror(errno);
////printf(buffer);
//		printf("\n\n");
//	}
//
////write Configuration Byte
//	buf[0] = 0b00001111;
//
//	if (write(file, buf, 1) != 1) {
//		/* ERROR HANDLING: i2c transaction failed */
//		printf("Failed to write to the i2c bus.\n");
////buffer = g_strerror(errno);
////printf(buffer);
//		printf("\n\n");
//	}
//
//	float data;
//// Read the data for all channels and print
//	if (read(file, buf, 16) != 16) {
//		/* ERROR HANDLING: i2c transaction failed */
//		printf("Failed to read from the i2c bus.\n");
////buffer = g_strerror(errno);
////printf(buffer);
//		printf("\n\n");
//	} else {
//		int i;
//		for (i = 0; i < 16; i += 2) {
//			data = (float) ((buf[i] & 0b00001111) << 8) + buf[i + 1];
//			//data = data / 4096 * 3.3;
////channel = ((buf[0] & 0b00110000)>>4);
//			printf("Data channel %d: %04f\n", i / 2, data);
//		}
//	}
//
//	return 0;
}
