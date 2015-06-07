#include <iostream>
#include "csbigcam.h"
#include "csbigimg.h"
#include <vector>
#include <ctime>
#include <string>
#include <cmath>
#include <pthread.h>
#include <fstream>
#include <list>

//#define TEST

using namespace std;

pthread_cond_t      cond  = PTHREAD_COND_INITIALIZER;
pthread_cond_t      cond2  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;

class ExposureData {
	private:
		bool is_valid;
	public:
		int *ret;
		int fullHeight;
	        int fullWidth;
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

    while(true){//aggiustare un po' le cifre significative del STP
        camera->SetTemperatureRegulation(enabled, setpointTemp);
        camera->QueryTemperatureStatus(isenable, ccdTemp, setpointTemp, percentTE);
	setpointTemp-=0.19;
	camera->SetTemperatureRegulation(enabled, setpointTemp);
        printf("\n\033[F\033[J");
        cout << "Temp control: CCDTemp=" << ccdTemp << " STP="<<setpointTemp << " Power=" <<percentTE*100 << "%";

        if(count%20==0 && setpointTemp > endpointTemp && reverse==false){
            setpointTemp -= delta;
	    if(setpointTemp < endpointTemp) setpointTemp = endpointTemp;
        }

	if(count%20==0 && setpointTemp < endpointTemp && reverse==true){
            setpointTemp += delta;
	    if(setpointTemp > endpointTemp) setpointTemp = endpointTemp;
	}

        if(termalized==1 && abs(endpointTemp-ccdTemp) < 0.4){
            cout << endl << "Start termalizzation..." << endl;


            while(true){
		    ++counter;
		    camera->QueryTemperatureStatus(isenable, ccdTemp, setpointTemp, percentTE);
		    printf("\n\033[F\033[J");
		    cout << "Temp control: CCDTemp=" << ccdTemp << " STP="<<setpointTemp << " Power=" <<percentTE*100 << "%" << " Iterator = (" << counter <<"/36)"; //33--> 35 (colpa del revert line!) 
		    if(counter%36==0){
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
	if((string)(&path_save->at(len-1)) != "/") path_save->append("/"); //Da testare, potrebbe non funzionare.


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
	}else{
		*rm=2;
	}

	string read;
	cout << "Fast readout (1/0): ";
	cin >> read;
	if(read == "1") *bFastReadout = true;

	string channel;
	cout << "Dual channel mode (1/0): ";
	cin >> channel;
	if(channel == "1") *bDualChannelMode=true;
	
	//only fits
	*bFitsType = 1;


}

void printparameter(int *num_img, string *name_img, string *path_save,
                    bool *bFitsType, bool *bLightFrame, double *exptime, 
		    int *rm, bool *bFastReadout, bool *bDualChannelMode){
	fstream file_save;
	file_save.open(".parameters", ios::out);
	cout << "Num Image  = " << *num_img          << endl
	     << "Nome Img   = " << *name_img         << endl
	     << "Path save  = " << *path_save        << endl
	     << "Fits type  = " << *bFitsType        << endl
	     << "LightFrame = " << *bLightFrame      << endl
	     << "Exp Time   = " << *exptime          << endl
	     << "RM         = " << *rm               << endl
	     << "Fast RO    = " << *bFastReadout     << endl
	     << "DualChannel= " << *bDualChannelMode << endl;
	
	file_save << "Num_Image__= " << *num_img          << endl
	          << "Nome_Img___= " << *name_img         << endl
	          << "Path_save__= " << *path_save        << endl
	          << "Fits_type__= " << *bFitsType        << endl
	          << "LightFrame_= " << *bLightFrame      << endl
	          << "Exp_Time___= " << *exptime          << endl
	          << "RM_________= " << *rm               << endl
	          << "Fast_RO____= " << *bFastReadout     << endl
	          << "DualChannel= " << *bDualChannelMode << endl;

}

bool exists_file (const std::string& name) {
	if (FILE *file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	} else {
		return false;
	}   
}


void check_all(){
	
	fstream input;
	list<string> l;
	string a, b;
	int k=0;
	if(exists_file(".parameters")){
		input.open(".parameters", ios::in);
		cout << "esiste" << endl;
		while(!input.eof()){
			input>>a>>b;
			l.push_back(b);
			k++;
		}
	} else {
		cout << "non esiste" << endl;
	}
	for(auto elem : l)
		cout << elem << endl;
}





void *grabImage(void *cam){
	pthread_mutex_lock(&mutex);
	ExposureData ed;
	CSBIGCam *camera = (CSBIGCam *)cam;
	CSBIGImg *ImgSbi = new CSBIGImg;	
	
	string name_TOT="";

	SBIG_FILE_ERROR ferr;
	PAR_ERROR err=CE_NO_ERROR;
	
	fstream input;
	list<string> l;
	string a, b, loadfile;
	int k=0;
	if(exists_file(".parameters")){
		cout << "A parameters file has been found. Load it or modify? (load/modify): ";
		cin  >> loadfile;
		if(loadfile == "load"){
			input.open(".parameters", ios::in);
			while(!input.eof()){
				input>>a>>b;
				l.push_back(b);
				k++;
			}
			ed.num_img = (int)l[0];
		}
	} else {
		cout << "Not found" << endl;
	}

/* Esempio che si può seguire per caricare i dati da file
int main(){
	list<string> l;
	std::list<string>::iterator it;
	l = {"1","2","3","4","5","6","7"};
	it = l.begin();

	advance(it,2);
	
	string prova = *it;

	int a = atoi(prova.c_str());
	cout << a << endl;



	return 0;
}
*/
	setparameter(&(ed.num_img), &(ed.name_img), &(ed.path_save), 
		     &(ed.bFitsType),  &(ed.bLightFrame), &(ed.exptime),
		     &(ed.rm), &(ed.bFastReadout), &(ed.bDualChannelMode));

	printparameter(&(ed.num_img), &(ed.name_img), &(ed.path_save), 
		       &(ed.bFitsType),  &(ed.bLightFrame), &(ed.exptime), 
		       &(ed.rm), &(ed.bFastReadout), &(ed.bDualChannelMode));

	cout << "Sensor termalization...";
	
	pthread_cond_signal(&cond);
	pthread_cond_wait(&cond2,&mutex);

	
	camera->SetActiveCCD(CCD_IMAGING);
	camera->SetExposureTime(ed.exptime);
	camera->SetReadoutMode(ed.rm);
	camera->SetABGState(ABG_LOW7);
	camera->SetFastReadout(ed.bFastReadout);
	camera->SetDualChannelMode(ed.bDualChannelMode);
	camera->GetFullFrame(ed.fullWidth, ed.fullHeight);
	
	ImgSbi->AllocateImageBuffer(ed.fullHeight, ed.fullWidth);
	
	for(int i=1; i<=ed.num_img; ++i){
		name_TOT = ed.path_save; 
		name_TOT += ed.name_img;
		if(ed.bLightFrame){
			cout << "Taking light frame n. = " << i << endl;
			if ((err = camera->GrabImage(ImgSbi, SBDF_LIGHT_ONLY)) != CE_NO_ERROR){
				 cout << "CSBIGCam error        : " << camera->GetErrorString(err) << endl;
				 break;
			}
			name_TOT += "_LF_" ;
		}else{
			cout << "Taking dark frame n. = " << i << endl;
			if ((err = camera->GrabImage(ImgSbi, SBDF_DARK_ONLY)) != CE_NO_ERROR){
				cout << "CSBIGCam error        : " << camera->GetErrorString(err) << endl;
				break;
			}
			name_TOT += "_DF_";
		}
		char timeBuf[128];
		struct tm* pTm;
		struct timeval tv;
		struct timezone tz;
		gettimeofday(&tv, &tz);
		pTm = localtime(&(tv.tv_sec));
		sprintf(timeBuf, "%04d-%02d-%02dT%02d:%02d:%02d.%03ld",
			       	pTm->tm_year + 1900, 
				pTm->tm_mon + 1, 
				pTm->tm_mday,
				pTm->tm_hour,
				pTm->tm_min,
			    	pTm->tm_sec,
			       	(tv.tv_usec/1000));
		
		name_TOT += timeBuf;

		if(ed.bFitsType){
			name_TOT += ".fits";
			if( (ferr = ImgSbi->SaveImage((name_TOT).c_str(), SBIF_FITS)) != SBFE_NO_ERROR){
				cout << " FITS_FORMAT_SAVE error        : " << ferr << endl;
				break;
			}
		}else{
			name_TOT += ".sbig";
			if( (ferr = ImgSbi->SaveImage((name_TOT).c_str(), SBIF_COMPRESSED)) != SBFE_NO_ERROR){
				cout << " SBIG_FORMAT_SAVE error        : " << ferr << endl;
				break;
			}
		}

		cout << "Image save as : " << name_TOT << endl;
		name_TOT = "";

	} //qui si chiude il for

	//Chiudo connessione,driver, distruggo divece ed immagine. 
	if((err = camera->CloseDevice()) != CE_NO_ERROR) {cout << "ERROR in CloseDevice" << endl;}
	if((err = camera->CloseDriver()) != CE_NO_ERROR) {cout << "ERROR in CloseDriver" << endl;}

	if(ImgSbi) delete ImgSbi;
	if(camera) delete camera;

		
	#ifdef TEST
		for(int i=0; i < 10; ++i){
			cout << "Grabbing image number " << i << "..." << endl;
			sleep(5);
		}
	#endif
	
	pthread_exit(ed.ret);
	return NULL;
}
