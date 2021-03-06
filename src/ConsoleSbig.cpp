#include <iostream>
#include "csbigcam.h"
#include "csbigimg.h"
#include <vector>
#include <ctime>
#include <string>
#include <cmath>
#include <pthread.h>
#include "getImage.h"
#include "splash.h"
using namespace std;

int main(){
    
	splash();
	double ccdTemp, setpointTemp, percentTE;
	OpenDeviceParams odp;
	string yes_temp;
	odp.deviceType = DEV_USB1;
	MY_LOGICAL enabled;

	pthread_t Temp_thread, GImg_thread;


	//ctor CSBIGCam(OpenDeviceParams) do--> operDriver and OpenDevice
	CSBIGCam *camera;
	camera = new CSBIGCam(odp);
	if((camera->EstablishLink()) != CE_NO_ERROR){
		cout << "Link error please check USB cable status" << endl;
		return 1;
	}
	camera->QueryTemperatureStatus(enabled, ccdTemp, setpointTemp, percentTE);

	cout << "Link established to =" << camera->GetCameraTypeString() << endl;
	if(enabled){
		cout << "Temperature control is on" <<endl;
		cout << "Temperature = "  << ccdTemp << endl;
		cout << "SetPoint    = " << setpointTemp << endl;
        	cout << "Percent     = " << (percentTE*100) << endl;
		cout << endl;
		cout << "Starting Temperature Control Thread..." << endl;
		cout << endl;
		pthread_create(&Temp_thread, NULL, checkTemp, camera);
	}else{
		 cout << "Temperature Control is off" << endl;
LOOP:do{
	cout << "Switch on Temperature Regulation? (yes/no): " ;
	cin >> yes_temp;
        if(yes_temp=="yes"){
		cout << "Create checkTemp thread..." << endl;
		pthread_create(&Temp_thread, NULL, checkTemp, camera);
		sleep(1);
		goto stop;
	}
	if(yes_temp=="no") {cout << "Temperature regulation is off" << endl; goto stop;}
	if(yes_temp != "yes" && yes_temp != "no") {
		cout << "Error! write \"yes\" or \"no\" " <<endl;
	}
	goto LOOP;
     }while(true);
stop:{}
	}
	pthread_create(&GImg_thread, NULL, grabImage, camera);
	pthread_join(GImg_thread, NULL);
	
	camera->~CSBIGCam();
	
	return 0;
}
