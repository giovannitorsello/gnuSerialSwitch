#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>

#include "serialSwitch.h"
#include "switch_codes.h"

/* A string listing valid short options letters.  */
const char *const short_options = "hacd";
/* An array describing valid long options.  */
const struct option long_options[] = {
    {"help", 0, NULL, 'h'},
    {"action", 1, NULL, 'a'},
    {"channel", 1, NULL, 'c'},
    {"device", 1, NULL, 'd'},
    {NULL, 0, NULL, 0} /* Required at end of array.  */
};

int execute_command(int num_items, char *cmd_line_items[])
{
    int opt;
    char serial_device_string[100];
    char action[20];
    int channel = 0;

    memset(action, 0, 20);
    memset(serial_device_string, 0, 100);

    while ((opt = getopt_long(num_items, cmd_line_items, short_options, long_options, NULL)) != EOF)
        switch (opt)
        {
        case 'c': /* -c or --channel */
            printf("Channel is %s\n", optarg);
            if (optarg)
                channel = atoi(optarg);
            break;
        case 'd': /* -c or --device */
            printf("Device is %s\n", optarg);
            if (optarg && strlen(optarg) < 99)
                strcpy(serial_device_string, optarg);
            if (open_serial_connection(serial_device_string) == 0)
            {
                printf("Serial device open successfully\n");
            }
            break;
        case 'a': /* -a or --action */
            if (optarg && strlen(optarg) < 19)
                strcpy(action, optarg);
            printf("Action is %s\n", optarg);
            if (strcmp(action, "reset") == 0)
            {
                reset();
                exit(0);
            }
            if (strcmp(action, "tests") == 0)
            {
                test_all();
                exit(0);
            }
            break;
        case 'h': /* -h or --help */
            usage();
            break;

        default:
            usage();
            break;
        }

    if (strlen(serial_device_string) == 0)
    {
        printf("No serial device is specified\n");
        usage();
        return -1;
    }
    else if (strlen(action) == 0)
    {
        printf("No action is specified\n");
        usage();
        return -1;
    }
    else if (channel == 0)
    {
        printf("No channel is specified\n");
        usage();
        return -1;
    }
    else
        do_action(channel, action);

    return 0;
}

int do_action(int channel, char *action)
{
    if (strlen(action) > 0 && channel > 0)
    {
        if (strcmp(action, "on") == 0)
        {
            if (channel == 1)
                write_command(CMD_ON_CH1);
            if (channel == 2)
                write_command(CMD_ON_CH2);
            if (channel == 3)
                write_command(CMD_ON_CH3);
            if (channel == 4)
                write_command(CMD_ON_CH4);
        }
        else if (strcmp(action, "off") == 0)
        {
            if (channel == 1)
                write_command(CMD_OFF_CH1);
            if (channel == 2)
                write_command(CMD_OFF_CH2);
            if (channel == 3)
                write_command(CMD_OFF_CH3);
            if (channel == 4)
                write_command(CMD_OFF_CH4);
        }
        else if (strcmp(action, "toggle") == 0)
        {
            if (channel == 1)
                write_command(CMD_TOGGLE_CH1);
            if (channel == 2)
                write_command(CMD_TOGGLE_CH2);
            if (channel == 3)
                write_command(CMD_TOGGLE_CH3);
            if (channel == 4)
                write_command(CMD_TOGGLE_CH4);
        }
        else if (strcmp(action, "pulse") == 0)
        {
            if (channel == 1)
                write_command(CMD_PULSE_CH1);
            if (channel == 2)
                write_command(CMD_PULSE_CH2);
            if (channel == 3)
                write_command(CMD_PULSE_CH3);
            if (channel == 4)
                write_command(CMD_PULSE_CH4);
        }
        else
            printf("Wrong action. Action <%s> doesn't exists\n", action);
    }
}

int usage()
{
    printf("USAGE\n");
    printf("serialSwitch --d <serial device> --c <relais channel> --a <action>\n");
    printf("<device> depends on RS232 port (i.e /dev/ttyUSB0) \n");
    printf("<channel> depends on board (generally integer number between 1 and 4) \n");
    printf("<action> can be on, off, toggle, pulse\n");
    return 0;
}

int reset()
{
    printf("Set all relais to OFF\n");
    write_command(CMD_OFF_CH1);
    write_command(CMD_OFF_CH2);
    write_command(CMD_OFF_CH3);
    write_command(CMD_OFF_CH4);
}