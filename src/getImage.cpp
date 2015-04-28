#include <iostream>
#include "csbigcam.h"
#include "csbigimg.h"
#include <vector>
#include <ctime>
#include <string>
#include <cmath>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;



void *checkTemp(void *cam){
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex2);
    int *ret;
    CSBIGCam *camera = (CSBIGCam *)cam;
    double ccdTemp = (double)rand()/((double)RAND_MAX);
    double percentTE = (double)rand()/((double)RAND_MAX);
    double setpointTemp;
    double endpointTemp;
    int count=0;

    MY_LOGICAL enabled=true;
    MY_LOGICAL isenable;

    cout << "Set start point temperature = ";
    cin >> setpointTemp;
    cout << "Set end point temperature   = ";
    cin >> endpointTemp;

    pthread_cond_wait( &cond, &mutex );


    while(true){
        //camera->SetTemperatureRegulation(enabled, setpointTemp);
        //camera->QueryTemperatureStatus(isenable, ccdTemp, setpointTemp, percentTE);
        printf("\n\033[F\033[J");
        ccdTemp = (double)rand()/((double)RAND_MAX);
        percentTE = (double)rand()/((double)RAND_MAX);
        cout << "Temp control: CCDTemp=" << ccdTemp << " STP="<<setpointTemp << " Power=" <<percentTE*100 << "%";

        if(count%30==0 && setpointTemp > endpointTemp){
            setpointTemp -= 3.00;
            if(setpointTemp<endpointTemp) setpointTemp = endpointTemp;
        }


        if(abs(endpointTemp-ccdTemp) < 0.05){
            pthread_mutex_unlock(&mutex2);
        }
        ++count;
        sleep(1);
    }
pthread_exit(ret);

    return NULL;
}



void *grabImage(void *cam){
    pthread_mutex_lock(&mutex);

    int *ret;
    int num_img;
    string name_img;
    string path_save;
    cout << endl;
    cout << "Number of images in the sequence = ";
    cin >> num_img;
    cout << "Name of the image = ";
    cin >> name_img;
    cout << "Path to save = ";
    cin >> path_save;
    cout << "Sensor termalization..."<<endl;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&mutex2);


    cout << endl <<"Termalized!"<< endl << "Grabbing ...." << endl;
    for(int i=0; i<num_img; ++i){
        sleep(5);
        cout << endl << "Image "<< i+1 << " grabbed" << endl;
    }



    pthread_exit(ret);

}
