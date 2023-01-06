#ifndef ____SERIAL_SWITCH_H_
#define ____SERIAL_SWITCH_H_

#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()
#include "switch_codes.h"

#define BUF_CMD_LEN 8
#define BUF_READ_LEN 8

// in us (microseconds)
#define READ_TIME_WAIT 200000
#define WRITE_TIME_WAIT 200000

int convert_command_string(char *buf_string, char *buf_cmd);
int read_response();
int write_command(char *buf);
int open_serial_connection(char *serial_device);
int close_serial_connection();

#endif