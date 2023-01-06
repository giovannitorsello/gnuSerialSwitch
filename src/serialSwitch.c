#include "serialSwitch.h"
int serial_port = 0;
unsigned char buf_serial_read[8];
struct termios tty;

int convert_command_string(char *buf_string, char *buf_cmd)
{
  int num_bytes = 0;
  char temp_buf[24];
  memset(temp_buf, 0, 24);
  strcpy(temp_buf, buf_string);
  for (int i = 0; i < 23; i += 3)
  {
    char buf_byte[2];
    buf_byte[0] = temp_buf[i];
    buf_byte[1] = temp_buf[i + 1];
    buf_byte[2] = 0;
    int hex_val = 0;
    sscanf(buf_byte, "%x", &hex_val);
    buf_cmd[num_bytes] = hex_val;
    num_bytes++;
  }
  /* char *token = strtok(temp_buf, " ");
 while (token != NULL && num_bytes < BUF_CMD_LEN)
 {
   int val = atoi(token);
   buf_cmd[num_bytes] = atoi(token);
   token = strtok(NULL, " ");
   num_bytes++;
 }*/
  return num_bytes;
}

int read_response()
{
  if (serial_port == 0)
    return -1;
  memset(buf_serial_read, 0, BUF_READ_LEN);
  int num_bytes = read(serial_port, buf_serial_read, BUF_READ_LEN);

  if (num_bytes < 0 || num_bytes > BUF_READ_LEN)
  {
    printf("Error reading: %s", strerror(errno));
    return -1;
  }
  else
  {
    for (int i = 0; i < num_bytes; i++)
      printf("%x ", buf_serial_read[i]);

    printf(" (%i) \n", num_bytes);
  }
  usleep(READ_TIME_WAIT);
  return num_bytes;
}

int write_command(char *buf)
{
  if (serial_port == 0)
    return -1;
  unsigned char hex_buf[8];
  int num_bytes_to_write = convert_command_string(buf, hex_buf);
  int num_bytes_written = write(serial_port, hex_buf, num_bytes_to_write);
  usleep(WRITE_TIME_WAIT);
  if (num_bytes_written > 0)
    return num_bytes_written;
  else
    return -1;
}

int open_serial_connection(char *serial_device)
{
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
  printf("Send on port %s ... \n", serial_device);
  serial_port = open(serial_device, O_RDWR);
  printf("Serial device opened. Id is %d\n", serial_port);
  // Create new termios struct, we call it 'tty' for convention
  struct termios tty;

  // Read in existing settings, and handle any error
  if (tcgetattr(serial_port, &tty) != 0)
  {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    return 1;
  }

  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag &= ~CSIZE;  // Clear all bits that set the data size
  tty.c_cflag |= CS8;     // 8 bits per byte (most common)
  // tty.c_cflag &= ~CRTSCTS;       // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

  tty.c_lflag &= ~ICANON;
  // tty.c_lflag &= ~ECHO; // Disable echo
  tty.c_lflag &= ~ECHOE; // Disable erasure
  // tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG;                                                        // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                      // Turn off s/w flow ctrl
  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes

  // tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  // tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  //  tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  //  tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

  tty.c_cc[VTIME] = 10; // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
  tty.c_cc[VMIN] = 0;

  // Set in/out baud rate to be 9600
  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);
  int input_speed = cfgetispeed(&tty);
  int output_speed = cfgetospeed(&tty);
  printf("Input  speed is: %d\n", input_speed);
  printf("Output speed is: %d\n", output_speed);

  // Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
  {
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    return 1;
  }
}

int close_serial_connection()
{
  if (serial_port == 0)
    return -1;
  close(serial_port);
  return 0;
}
