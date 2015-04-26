#include <iostream>
#include "csbigcam.h"
#include "csbigimg.h"
#include <vector>
#include <ctime>
#include <string>

using namespace std;



void *checkTemp(void *cam){
    CSBIGCam *camera = (CSBIGCam *)cam;
    double ccdTemp, setpointTemp, percentTE;

    MY_LOGICAL enabled=true;

    while(true){
        cout << "Sto regolando ..." << endl;
        sleep(1);
    }
    /*camera->SetTemperatureRegulation(enabled2, setpointTemp);*/

    return NULL;
}








int main(){
    double ccdTemp, setpointTemp, percentTE;
    OpenDeviceParams odp;
    string yes_temp;
    odp.deviceType = DEV_USB1;
    MY_LOGICAL enabled;

    pthread_t Temp_thread;


    //il costruttore CSBIGCam(OpenDeviceParams) fa operDriver e OpenDevice
    CSBIGCam *camera;
    camera = new CSBIGCam(odp);
    if((camera->EstablishLink()) != CE_NO_ERROR){
        cout << "Link error please check USB cable status" << endl;
        return 1;
    }
    camera->QueryTemperatureStatus(enabled, ccdTemp, setpointTemp, percentTE);

    cout << "Model = " << camera->GetCameraTypeString() << "\tLink status:UP" << endl;
    if(enabled){
        cout << "Temperature control is on" <<endl;
        cout << "Temperature ="  << ccdTemp << endl;
        cout <<" setPoint    = " << setpointTemp << endl;
        cout << "percent     = " << percentTE << endl;
    }else{
        cout << "Temperature control is off" << endl;

LOOP:do{
        cout << "Switch on Temperature Regulation? (yes/no): " ;
        cin >> yes_temp;
        if(yes_temp=="yes"){
            cout << "accendo!" << endl;
            pthread_create(&Temp_thread, NULL, checkTemp, camera);
            goto stop;
        }
        if(yes_temp=="no") {cout << "lascio spendo" << endl; goto stop;}
        if(yes_temp != "yes" && yes_temp != "no") {
            cout << "Error! write \"yes\" or \"no\" " <<endl;

        }
        goto LOOP;
        }while(true);
stop:{}
    }

    sleep(50);

    camera->~CSBIGCam();

	return 0;
}





