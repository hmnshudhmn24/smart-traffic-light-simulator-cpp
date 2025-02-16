#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

class TrafficLight {
public:
    string color;
    int duration;

    TrafficLight(string col, int dur) : color(col), duration(dur) {}
};

class SmartTrafficSystem {
private:
    vector<int> trafficDensity;
    vector<TrafficLight> lights;

public:
    SmartTrafficSystem() {
        trafficDensity = {rand() % 100, rand() % 100, rand() % 100, rand() % 100};
        lights = {TrafficLight("Red", 30), TrafficLight("Green", 30), TrafficLight("Yellow", 5)};
    }

    void adjustTimings() {
        int totalDensity = 0;
        for (int d : trafficDensity) totalDensity += d;

        for (int i = 0; i < 4; ++i) {
            int proportion = (trafficDensity[i] * 100) / totalDensity;
            lights[1].duration = 30 + (proportion / 2);
            lights[0].duration = 30 - (proportion / 3);
        }
    }

    void displayStatus() {
        cout << "Traffic Density: ";
        for (int i = 0; i < 4; ++i)
            cout << "Lane " << i + 1 << ": " << trafficDensity[i] << "%  ";
        cout << endl;

        cout << "Signal Timings: " << endl;
        cout << "Green: " << lights[1].duration << " sec, "
             << "Red: " << lights[0].duration << " sec, "
             << "Yellow: " << lights[2].duration << " sec" << endl;
    }

    void simulateTraffic() {
        while (true) {
            system("clear");
            adjustTimings();
            displayStatus();
            this_thread::sleep_for(chrono::seconds(5));
            for (int &d : trafficDensity) d = rand() % 100;
        }
    }
};

int main() {
    srand(time(0));
    SmartTrafficSystem system;
    system.simulateTraffic();
    return 0;
}
