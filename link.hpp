#include <iostream>
#include <random>
using namespace std;

default_random_engine generator;
uniform_real_distribution<double> mbps(0,1000000);
uniform_real_distribution<double> ten_secs(0,10);

class Link
{
   // double bandwidth;
    //double delay;
    public:
        //constructor intializes with 0's

    Link()
    {
        cout<<"constructor" <<endl;
        setBD(0,0);
        
    }
    void setBD(double band, double del) {
      cout << band << del << "-----" << endl;
        if(band==0|| del == 0){ //lmao i had this as (band || del == 0) 
 cout <<"yo" <<endl; //test
            bandwidth = 0;   //mbps(generator);  //= 0;
            delay = 0;       //ten_secs(generator); // =0;
        }
        else{
cout <<"sup"<<endl; //test
            bandwidth = mbps(generator);
            delay = ten_secs(generator);
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



