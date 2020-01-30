# tek4010-pidp8i
Using the Tektronix 4010 emulator tek4010 on the PiDP-8


**Pascal directory**

The Pascal directory contains Pascal programs for the OS/8 Pascal compiler.
The Pascal compiler can be obtained from

https://www.pdp8.net/pdp8cgi/os8_html?act=dir;fn=images/os8/pascal1.rx01;sort=name

The README.1 file there describes the installation of Pascal.

Compile these programs with

	.R P,PASCAL,name.PS

where name is the file name of the Pascal program you want to compile.

Execute it with

	.R P,name.PB

Source files in this directory:

	- graph1.ps	parametric plot, x=sin(3t), y=sin(4t)
	- graph2.ps	3D plot, sin(x+y)
	- graph3.ps	3D plot, sin(r+d)
	- typep8.ps	type Tektronix 4010/4014 plot files .p8

Usage of typep8 (use only if you are connected to tek4010 or a real Tektronix terminal)

	.R P,TYPEP8,name.P8


**OS8-plotfiles directory**

These are OS/8 compatible plot files for the Tektronix 4010, 4014. They have been converted
using tektoOS8. To display them, use TYPEP8 (see above).

**tektoOS8 directory**

tektoOS8 is a small conversion program to convert normal Tektronix 4010/4014 plot files
to a format compatible with OS/8. They can only be displayed using TYPEP8 (see above).

**Floppy_images directory**

This directory contains the following floppy disk images:

	- pascal1.rx01	Pascal installation disk with Pascal compiler and runtime (from pdp8.net)
	- pascal2.rx01	Pascal source programs (from pdp8.net)
	- pascal3.rx01	Tektronix graphics programs written in Pascal
	- tekplot1.rx01	Tektronix plot files (to be used with TYPEP8)
	- tekplot2.rx01	Tektronix plot files (to be used with TYPEP8)

**using tek4010 with the PiDP-8**

You can download tek4010 from https://github.com/rricharz/Tek4010

This is ongoing work. I hope that we will be able to make this much easier. You cannot use
tek4010 in the standard pidp8i setup, which uses screen, because screen does not work
with dump graphics terminals such as the Tektronix 4010. If tek4010 is on the
same Raspberry Pi as pidp8i, use the method described in the tek410 repo under
"Log into PiDP-11 running on the same Raspberry Pi, using the console" to log into Raspbian
with tek4010. Then type

	pidp8i stop
	cd pidp8i
	make run

Note, that you are now running OS/8 with the RK05 image in /home/pi/pidp8i/bin.
Don't forget to use one of the keys to erase the screen very frequently.

