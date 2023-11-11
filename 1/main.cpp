#include <iostream>
#include <string>
#include <map>
#include <random>
#include <vector>
#include "HW2_Visualizer.h"

using namespace std;

class HW2_VIZ;
class Plane;
class Airliner;
class GeneralAviation;
class ATC;

// Question 1
struct Flight { // container storing information of the airport distances from statecollege
    string destination;
    int distance;
    Flight(const string& dest, int dist) : destination(dest), distance(dist) {}
};

using Flights = vector<Flight>;
using AirportMap = map<string, Flights>;

int main() {
    AirportMap airportMap;

    airportMap["SCE"].push_back(Flight("PHL", 160));
    airportMap["SCE"].push_back(Flight("ORD", 640));
    airportMap["SCE"].push_back(Flight("EWR", 220));


    return 0;
}
// Question 2
class Plane { // class named Plane
protected:
    double wait_time;

private:
    double pos;
    double vel;
    double distance;
    double loiter_time;
    bool at_SCE;
    string origin, destination;

public:
    Plane(string from, string to);
    virtual ~Plane();
    void operate(double dt);
    double getpos();
    double getvel();
    double getloiter_time();
    string getorigin();
    string getdestination();
    bool getat_SCE();
    void setvel(double vel);
    void setloiter_time(double loiter_time);
    double distance_to_SCE();
    virtual double time_on_ground() = 0;
    virtual string plane_type();
};

// Question 3
Plane::Plane(string from, string to) { //origin and destination
    origin = from;
    destination = to;
    distance = 0.0;
    pos = 0.0;
    vel = 0.0;
    wait_time = 0.0;
    loiter_time = 0.0;
    at_SCE = false;
}

Plane::~Plane() {}

void Plane::operate(double dt) {
    if (loiter_time != 0) {
        loiter_time -= dt;
    }
    else if (destination == "SCE") {
        at_SCE = true;
    }
}

// Question 4
class Airliner : public Plane { //Airliner Class
private:
    string Airline;

public:
    Airliner(string Airline, string from, string to);
    ~Airliner();
    string plane_type();
    double time_on_ground();
    double draw_from_normal_dist(double m, double sd)
    {
        random_device rd{};
        mt19937 gen{ rd() };
        normal_distribution<> d{1800,600 };
        return d(gen);
    }
};

class GeneralAviation : public Plane { // General Aviation Class
public:
    GeneralAviation(string from, string to);
    ~GeneralAviation();
    double time_on_ground();
    double draw_from_normal_dist(double m, double sd)
    {
        random_device rd{};
        mt19937 gen{ rd() };
        normal_distribution<> d{ 600, 60 };
        return d(gen);
    }
};

// Question 6
class ATC { //ATC Class
private:
    vector<Plane*> registered_planes;
    int MAX_LANDED_PLANE_NUM = 2;
    int AIRSPACE_DISTANCE = 50;

public:
    ATC();
    ~ATC();
    void register_plane(Plane* plane);
    void control_traffic();
};
char AA5915, & UA5236, & UA4465, & AA6240, & GeneralAviationA, & GeneralAviationB, & GeneralAviationC;
    // Question 7 
    double dt = 100; //timestep
    int main(){
    while (true) {
        vector<Plane*> planes = { AA5915, UA5236, UA4465, AA6240, GeneralAviationA, GeneralAviationB, GeneralAviationC };

        for (auto& plane : planes) {
            plane->operate(dt);
            ATC control_traffic();
        }
    }

    return 0;
 }
   