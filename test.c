#include "serialSwitch.h"

int test_all()
{
    printf("MAKE ALL TESTS (duration 45secs)\n");
    test_on_off();
    test_toggle();
    test_pulse();
}

int test_on_off()
{
    printf("TESTING ON-OFF \n");

    write_command(CMD_OFF_CH1);
    write_command(CMD_OFF_CH2);
    write_command(CMD_OFF_CH3);
    write_command(CMD_OFF_CH4);

    printf("ON Ch1--> ");
    write_command(CMD_ON_CH1);
    read_response();
    sleep(2);
    printf("Off Ch1--> ");
    write_command(CMD_OFF_CH1);
    read_response();
    sleep(3);
    printf("\n\n");

    printf("ON Ch2--> ");
    write_command(CMD_ON_CH2);
    read_response();
    sleep(2);
    printf("Off Ch2--> ");
    write_command(CMD_OFF_CH2);
    read_response();
    sleep(3);
    printf("\n\n");

    printf("ON Ch3--> ");
    write_command(CMD_ON_CH3);
    read_response();
    sleep(2);
    printf("Off Ch3--> ");
    write_command(CMD_OFF_CH3);
    read_response();
    sleep(3);
    printf("\n\n");

    printf("ON Ch4--> ");
    write_command(CMD_ON_CH4);
    read_response();
    sleep(2);
    printf("Off Ch4--> ");
    write_command(CMD_OFF_CH4);
    read_response();
    printf("\n\n");

    return 0;
}

int test_toggle()
{
    printf("TESTING TOGGLE\n");
    write_command(CMD_OFF_CH1);
    write_command(CMD_OFF_CH2);
    write_command(CMD_OFF_CH3);
    write_command(CMD_OFF_CH4);

    printf("Toggle ON Ch1--> ");
    write_command(CMD_TOGGLE_CH1);
    read_response();
    sleep(1);
    printf("Toggle Off Ch1--> ");
    write_command(CMD_TOGGLE_CH1);
    read_response();
    printf("\n\n");
    sleep(3);

    printf("Toggle ON Ch2--> ");
    write_command(CMD_TOGGLE_CH2);
    read_response();
    sleep(1);
    printf("Toggle Off Ch2--> ");
    write_command(CMD_TOGGLE_CH2);
    read_response();
    printf("\n\n");
    sleep(3);

    printf("Toggle ON Ch3--> ");
    write_command(CMD_TOGGLE_CH3);
    read_response();
    sleep(1);
    printf("Toggle Off Ch3--> ");
    write_command(CMD_TOGGLE_CH3);
    read_response();
    printf("\n\n");
    sleep(3);

    printf("Toggle ON Ch4--> ");
    write_command(CMD_TOGGLE_CH4);
    read_response();
    sleep(1);
    printf("Toggle Off Ch4--> ");
    write_command(CMD_TOGGLE_CH4);
    read_response();
    printf("\n\n");

    return 0;
}

int test_pulse()
{
    printf("TESTING PULSE (200ms) \n");
    write_command(CMD_OFF_CH1);
    write_command(CMD_OFF_CH2);
    write_command(CMD_OFF_CH3);
    write_command(CMD_OFF_CH4);

    printf("Pulse ON Ch1--> ");
    write_command(CMD_PULSE_CH1);
    read_response();
    printf("\n\n");
    sleep(3);

    printf("Pulse ON Ch2--> ");
    write_command(CMD_PULSE_CH2);
    read_response();
    printf("\n\n");
    sleep(3);

    printf("Pulse ON Ch3--> ");
    write_command(CMD_PULSE_CH3);
    read_response();
    printf("\n\n");
    sleep(3);

    printf("Pulse ON Ch4--> ");
    write_command(CMD_PULSE_CH4);
    read_response();
    printf("\n\n");
    sleep(3);

    return 0;
}