###There native gate controller with async mode commander unit via UDP Socket###

compilation tested on Win10x64@qt-6.7

unit commands type:

	0xfa - command to set the mode;
	0xfb - command to ask the current mode;

unit commands special variables:

	0xcc - open the gate
	0xdd - close the gate

inut command overal appear:

	<0xff - constant><unit_commands_type><commands_special_variable><0xff - constant>
if unit_commands_type = 0xfb then commands_special_variable is ignored by the gates.

unit get request from gates only by command with 0xfb - type:

	<0xff - constant><0xff - constant><commands_special_variable><0xff - constant>
