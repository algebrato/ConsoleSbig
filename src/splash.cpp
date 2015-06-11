#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void splash(){
	cout <<endl;
	printf("\
++++++ Seveso Astronomical Observatory - MPCcode: C24  ++++++\n\
+ ConsoleSbig - Control tools for USB-SBIG devices          +\n\
+ Version    : 0                                            +\n\
+ Devel      : Stefano Mandelli                             +\n\
+ License    : GPLv2					    +\n\
+ Help	     : To set the grabbing parameters you can modify+\n\
+              the file .parameters in your working path    +\n\
+              (where the program was run at his the firs   +\n\
+              time). In this way you can jump the boring   +\n\
+	       parameters configuration of the program.	    +\n\
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"\
);
	cout << endl; 
	cout << "Tryng to load driver and establish a connection..." << endl;
	cout << endl;

}
