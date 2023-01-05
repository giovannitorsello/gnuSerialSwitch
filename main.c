#include "commands.h"
#include "serialSwitch.h"

int main(int argc, char *argv[])
{
    execute_command(argc, argv);
    close_serial_connection();
    return 0;
};