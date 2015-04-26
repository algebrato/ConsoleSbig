#include <iostream>
#include "csbigcam.h"
#include "csbigimg.h"
#include <vector>
#include <ctime>
#include <string>

using namespace std;



void *checkTemp(void *cam){
    CSBIGCam *camera = (CSBIGCam *)cam;
    double ccdTemp = (double)rand()/((double)RAND_MAX);
    double percentTE = (double)rand()/((double)RAND_MAX);
    double setpointTemp;
    int count=0;

    MY_LOGICAL enabled=true;

    cout << "Set point temperature = ";
    cin >> setpointTemp;


    while(true){
        /*camera->SetTemperatureRegulation(enabled2, setpointTemp);
        camera->QueryTemperatureStatus(enabled, ccdTemp, setpointTemp, percentTE);*/
        ccdTemp = (double)rand()/((double)RAND_MAX);
        percentTE = (double)rand()/((double)RAND_MAX);
        cout << "Temp control: CCDTemp=" << ccdTemp << " STP="<<setpointTemp << " Power=" <<percentTE*100 << "%";
        printf("\n\033[F\033[J");
        ++count;

        sleep(1);
    }
pthread_exit(cam);

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


    pthread_create(&Temp_thread, NULL, checkTemp, camera);
    double ap;

    sleep(10);

    camera->~CSBIGCam();

	return 0;
}





