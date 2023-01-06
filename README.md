# gnuSerialSwitch

Little program that allow to pilot switch board by RS232
simply specifing channel (i.e. relais number) and action.

Actions allowed are
on/off (switch on or off the channel)
toggle (alternative change status of the channel)
pulse (relais give a pulse of about 200ms)

<p>To build executable simply doing</p>
<code>make</code>

<p>To install in /usr/local/bin (root privileges required)</p>
<code>make install</code>

<p>To uninstall (root privileges required)</p>
<code>make uninstall</code>

Examples

Switch on and off the first relais.
<br>
./serialSwitch --d /dev/ttysUSB0 --c 1 --a on
<br>
./serialSwitch --d /dev/ttysUSB0 --c 1 --a off

Switch on and leave the second relais.
<br>
./serialSwitch --d /dev/ttysUSB0 --c 2 --a toggle

Give a 200ms pulse on fourth relais.
<br>
./serialSwitch --d /dev/ttysUSB0 --c 4 --a pulse

<strong>BOARD TYPES EXAMPLE</strong>
![Board sample](https://ae01.alicdn.com/kf/HLB1kTXhNXYqK1RjSZLeq6zXppXao/1-pz-DC12V-4-canali-RS232-scheda-rel-PC-USB-UART-DB9-interruttore-di-controllo-remoto.jpg_Q90.jpg_.webp "Working board examples")

<p>
Others board can be supported changing switch_codes.h that contains exadecimal strings for relais board command.
</p>
