#ifndef ____SWITCH_COMMANDS_H_
#define ____SWITCH_COMMANDS_H_
int execute_command(int num_items, char *cmd_line_items[]);
int do_action(int channel, char *action);
int reset();
#endif