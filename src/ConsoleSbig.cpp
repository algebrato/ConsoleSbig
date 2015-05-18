#include <iostream>
#include "csbigcam.h"
#include "csbigimg.h"
#include <vector>
#include <ctime>
#include <string>
#include <cmath>
#include <pthread.h>
#include "getImage.h"

using namespace std;

int main(){
    double ccdTemp, setpointTemp, percentTE;
    OpenDeviceParams odp;
    string yes_temp;
    odp.deviceType = DEV_USB1;
    MY_LOGICAL enabled;

    pthread_t Temp_thread, GImg_thread;


    //il costruttore CSBIGCam(OpenDeviceParams) fa operDriver e OpenDevice
    CSBIGCam *camera;
    camera = new CSBIGCam(odp);
/*    if((camera->EstablishLink()) != CE_NO_ERROR){
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
            cout << "Create checkTemp thread...";
            pthread_create(&Temp_thread, NULL, checkTemp, camera);
            cout << "done!"<<endl;
            goto stop;
        }
        if(yes_temp=="no") {cout << "lascio spendo" << endl; goto stop;}
        if(yes_temp != "yes" && yes_temp != "no") {
            cout << "Error! write \"yes\" or \"no\" " <<endl;

        }
        goto LOOP;
        }while(true);
stop:{}

    }*/
    pthread_create(&Temp_thread, NULL, checkTemp, camera);
    sleep(1);
    pthread_create(&GImg_thread, NULL, grabImage, camera);
    pthread_join(GImg_thread, NULL);



    camera->~CSBIGCam();

	return 0;
}
