#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Ride { //Class to define the base ride
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;
public:
    Ride(int id, const string& pickup, const string& dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual ~Ride() {} 

    virtual double fare() const { // For the base ride I'll just use a 1 factor
        return distance * 1.0;
    }

    virtual void rideDetails() const { // Method to display details
        cout << "Ride ID: " << rideID << "\nPickup Location: " << pickupLocation 
             << "\nDropoff: " << dropoffLocation << "\nDistance: " << distance 
             << " miles\nCost: $" << fare() << "\n==================================\n";
    }
};

class StandardRide : public Ride {
public:
    StandardRide(int id, const string& pickup, const string& dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override { // For the standard ride I am multiplying by 1.2 the distance
        return distance * 1.2;
    }
};

class PremiumRide : public Ride {
public:
    PremiumRide(int id, const string& pickup, const string& dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override { // For premium rides, I am setting it to 2 dollars per mile
        return distance * 2.0;
    }
};

class Rider {
    private:
        int riderID;
        string name;
        vector<Ride*> requestedRides; // Store the history of requested rides for the rider
    public:
        Rider(int id, const string& nm) : riderID(id), name(nm) {}
    
        void requestRide(Ride* ride) { // adds ride to requested history
            requestedRides.push_back(ride);
        }
    
        // Display all ride history
        void viewRides() const {
            cout << "\n" << name << "'s Ride History:\n";
            for (const auto& ride : requestedRides) // iterate through ride history
                ride->rideDetails();
        }
};

class Driver {
    private:
        int driverID;
        string name;
        double rating;
        vector<Ride*> assignedRides;  // Store the history of completed rides
    public:
        Driver(int id, const string& nm, double rate) : driverID(id), name(nm), rating(rate) {}
    
        void addRide(Ride* ride) { // adds ride to requested history
            assignedRides.push_back(ride);
        }
    
        void getDriverInfo() const { //show driver information to rider
            cout << "\nDriver ID: " << driverID << "\nName: " << name 
                 << "\nRating: " << rating << "\nCompleted Rides: " << assignedRides.size() 
                 << "\n";
        }
};

int main() {
    Ride* ride1 = new StandardRide(001, "410 Meijer Drive, Florence, KY", "2939 Terminal Drive, Hebron, KY", 10.0);
    Ride* ride2 = new PremiumRide(002, "6178 College Station Drive, Williamsburg, KY", "994 Aviation Boulevard, Williamsburg KY", 25.0);

    vector<Ride*> rideList = { ride1, ride2 }; // Using the same Vector to store the different types of rides for polymorphism

    Driver driver1(1408, "Nicolas", 4.9); // creating driver
    driver1.addRide(ride1);
    driver1.addRide(ride2);
    cout << "===========DRIVER DETAILS=============";
    driver1.getDriverInfo();

    Rider rider1(632, "Dax"); // Ceate Rider and assign the created rides
    rider1.requestRide(ride1);
    rider1.requestRide(ride2);
    cout << "============RIDER RIDES===============";
    rider1.viewRides();

    for (auto& ride : rideList) { // Clean up mem
        delete ride;
    }

    return 0;
}
