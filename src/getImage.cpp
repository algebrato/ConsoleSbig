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

class ExposureData {
	private:
		bool is_valid;
	public:
		int *ret;
		string name_img;
		string path_save;
		int num_img;
		bool bFitsType;
		bool bLightFrame;
		double exptime;
		int rm;
		bool bFastReadout;
		bool bDualChannelMode;
		
		ExposureData() {
			is_valid=true;
			ret = new int();
			ret[0]=1;
		};

		~ExposureData() {
			is_valid=false;
			ret[0]=0;
		};
};










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
        printf("\n\033[F\033[J");
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
		    counter++;
		    camera->QueryTemperatureStatus(isenable, ccdTemp, setpointTemp, percentTE);
		    printf("\n\033[F\033[J");
		    cout << "Temp control: CCDTemp=" << ccdTemp << " STP="<<setpointTemp << " Power=" <<percentTE*100 << "%" << " Iterator = (" << counter <<"/35)"; //33-->35 ???
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


void setparameter(int *num_img, string *name_img, string *path_save,
					bool *bFitsType, bool *bLightFrame, double *exptime,
					int *rm, bool *bFastReadout, bool *bDualChannelMode){
	cout << endl;
	cout << "Number of images in the sequence = ";
	cin >> *num_img;

	cout << "Name of the image = ";
	cin >> *name_img;

	cout << "Path to save = ";
	cin >> *path_save;
	int len = path_save->length();
	if((string)(&prova->at(len-1)) != "/") path_save->append("/"); //Da testare, potrebbe non funzionare.


	string lightframe;
	cout << "Light Frame or Dark Frame (DF/LF): ";
	cin >> lightframe;
	if(lightframe == "LF" ) *bLightFrame = true;

	cout << "Exposure time = ";
	cin >> *exptime;

	string binning;
	cout << "Bin (1x1/2x2/3x3): ";
	cin >> binning;
	if(binning == "1x1" ){
		*rm=0;
	}else if(binning == "2x2"){
		*rm=1;
	}

	string read;
	cout << "Fast readout (1/0): ";
	cin >> read;
	if(read == "1") *bFastReadout = true;

	string channel;
	cout << "Dual channel mode (1/0): ";
	cin >> channel;
	if(channel == "1") *bDualChannelMode=true;
}


void *grabImage(void *cam){
	pthread_mutex_lock(&mutex);
	ExposureData ed;
	SBIG_FILE_ERROR ferr;
	PAR_ERROR err=CE_NO_ERROR;

	setparameter(&(ed.num_img), &(ed.name_img), &(ed.path_save), &(ed.bFitsType),  &(ed.bLightFrame), &(ed.exptime), &(ed.rm), &(ed.bFastReadout), &(ed.bDualChannelMode));
	cout << "Sensor termalization..."<<endl;

	pthread_cond_signal(&cond);
	pthread_cond_wait(&cond2,&mutex);



	cout << endl << "Grabbing ...." << endl;
	for(int i=0; i<ed.num_img; ++i){
		sleep(5);
		cout << endl << "Image "<< i+1 << " grabbed" << endl;
	}
    
	return NULL;


	pthread_exit(ed.ret);
	return NULL;
}
