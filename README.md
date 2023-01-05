# gnuSerialSwitch

Little program that allow to pilot switch board by RS232
simply specifing channel (i.e. relais number) and action.

Actions allowed are
on/off (switch on or off the channel)
toggle (alternative change status of the channel)
pulse (relais give a pulse of about 200ms)

Examples

Switch on and off the first relais.
./serialSwitch --d /dev/ttysUSB0 --c 1 --a on
./serialSwitch --d /dev/ttysUSB0 --c 1 --a off

Switch on and leave the second relais.
./serialSwitch --d /dev/ttysUSB0 --c 2 --a toggle

Give a 200ms pulse on fourth relais.
./serialSwitch --d /dev/ttysUSB0 --c 4 --a pulse
