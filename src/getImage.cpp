#include <iostream>
#include "csbigcam.h"
#include "csbigimg.h"
#include <vector>
#include <ctime>
#include <string>
#include <cmath>
#include <pthread.h>

using namespace std;

pthread_cond_t      cond  = PTHREAD_COND_INITIALIZER;
pthread_cond_t      cond2  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;



void *checkTemp(void *cam){
    pthread_mutex_lock(&mutex);

    int *ret;
    ret= new int();
    CSBIGCam *camera = (CSBIGCam *)cam;
    double ccdTemp = (double)rand()/((double)RAND_MAX);
    double percentTE = (double)rand()/((double)RAND_MAX);
    double setpointTemp;
    double endpointTemp;
    int termalized=1;
    int count=0;
    int counter=0;
    double delta=3.00;
    bool reverse;
    string yes_grab;

    MY_LOGICAL enabled=true;
    MY_LOGICAL isenable;

    cout << "Set start point temperature = ";
    cin >> setpointTemp;
    cout << "Set end point temperature   = ";
    cin >> endpointTemp;
    if(setpointTemp > endpointTemp){
	    reverse = false;
    }else{
	    reverse = true;
    }

    pthread_cond_wait(&cond,&mutex);

    while(true){
        camera->SetTemperatureRegulation(enabled, setpointTemp);
        camera->QueryTemperatureStatus(isenable, ccdTemp, setpointTemp, percentTE);
	setpointTemp-=0.19;
	camera->SetTemperatureRegulation(enabled, setpointTemp);
        printf("\n\033[F\033[J");
        cout << "Temp control: CCDTemp=" << ccdTemp << " STP="<<setpointTemp << " Power=" <<percentTE*100 << "%";

        if(count%4==0 && setpointTemp > endpointTemp && reverse==false){
            setpointTemp -= delta;
	    if(setpointTemp < endpointTemp) setpointTemp = endpointTemp;
        }

	if(count%4==0 && setpointTemp < endpointTemp && reverse==true){
            setpointTemp += delta;
	    if(setpointTemp > endpointTemp) setpointTemp = endpointTemp;
	}

        if(termalized==1 && abs(endpointTemp-ccdTemp) < 0.4){
            cout << endl << "Start termalizzation..." << endl;


            while(true){
		    ++counter;
		    camera->QueryTemperatureStatus(isenable, ccdTemp, setpointTemp, percentTE);
		    printf("\n\033[F\033[J");
		    cout << "Temp control: CCDTemp=" << ccdTemp << " STP="<<setpointTemp << " Power=" <<percentTE*100 << "%" << " Iterator = (" << counter <<"/35)";
		    if(counter%35==0){
			    cout <<endl;
			    cout << "Start image grab? (yes/no): ";
			    cin >> yes_grab;
			    if(yes_grab=="yes"){
				 break;
			    }else{
				    counter=0;
			    }
		    }
		    sleep(1);
	    }
	    
	    
	    cout << endl << "Termalized!" << endl;
	    termalized=0;
            pthread_cond_signal(&cond2);
            pthread_mutex_unlock(&mutex);
        }
        ++count;
        sleep(1);
    }
    pthread_exit(ret);

    return NULL;
}



void *grabImage(void *cam){

    pthread_mutex_lock(&mutex);

    int *rit;
    rit= new int();
    rit[1]=1;
    cout << "rit = " << rit[1] << endl;
    int num_img;
    string name_img;
    string path_save("/home/algebrato/");
    cout << endl;
    cout << "Number of images in the sequence = ";
    cin >> num_img;
    cout << "Name of the image = ";
    cin >> name_img;
    cout << "Path to save = ";
    cin >> path_save;
    cout << "Sensor termalization..."<<endl;

    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond2,&mutex);



    cout << endl << "Grabbing ...." << endl;
    for(int i=0; i<num_img; ++i){
        sleep(5);
        cout << endl << "Image "<< i+1 << " grabbed" << endl;
    }
    pthread_exit(rit);
    cout << "rit = " << rit[1] << endl;
    return NULL;
}
