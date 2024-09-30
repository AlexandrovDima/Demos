###There native gate controller with async mode commander unit via UDP Socket###

Compilation tested on Win10x64@qt-6.7

Unit commands type:

	0xfa - command to set the mode
	0xfb - command to ask the current mode

Unit commands special variables:

	0xcc - open the gate
	0xdd - close the gate

Inut command overal appear:

	<0xff - constant><unit_commands_type><commands_special_variable><0xff - constant>
if unit_commands_type = 0xfb then commands_special_variable is ignored by the gates

Unit get request from gates only by command with 0xfb - type:

	<0xff - constant><0xff - constant><commands_special_variable><0xff - constant>
