#include <iostream>
#include <random>
using namespace std;

default_random_engine generator;
uniform_real_distribution<double> mbps(0,10); //
uniform_real_distribution<double> ten_secs(0,10);

class Link
{
   // double bandwidth;
    //double delay;
    public:
        //constructor intializes with 0's

    Link()
    {
     //   cout<<"constructor" <<endl;
        setBD(0,0);
        
    }
    void setBD(double band, double del) {
   //   cout << band << del << "-----" << endl;
        if(band==0|| del == 0){ //lmao i had this as (band || del == 0) 
            bandwidth = 0;   //mbps(generator);  //= 0;
            delay = 0;       //ten_secs(generator); // =0;
        }
        else if(band==1||del == 1){
            bandwidth = mbps(generator);
            delay = ten_secs(generator);
        }
        else {
cout << "setting bandwitdth" <<band <<" ";
            bandwidth = band;
cout << "setting delay" << del;
            delay = del;
        }
    }
    
    double getBandwidth(){
        return bandwidth;
    }
    double getDelay(){
        return delay;
    }
    // generate outside    
    private:
        
        double delay;
        double bandwidth;
};



