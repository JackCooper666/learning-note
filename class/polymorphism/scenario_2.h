#include <iostream>
#include <string>
using namespace std;

class CPU {
public:
    virtual string process() = 0;
    virtual ~CPU() {
        ;
    }
};
class GPU {
public:
    virtual string render() = 0;
    virtual ~GPU() {
        ;
    }
};
class Memory {
public:
    virtual string store() = 0;
    virtual ~Memory() {
        ;
    }
};

class Computer {
    public:
    string cpuname;
    string gpuname;
    string memoryname;

    // Constructor to initialize names (optional but good practice)
    Computer(const string& cpu, const string& gpu, const string& mem)
        : cpuname(cpu), gpuname(gpu), memoryname(mem) {}

    // Optional: Method to display computer specs
    void displaySpecs() {
        cout << "CPU: " << cpuname << endl;
        cout << "GPU: " << gpuname << endl;
        cout << "Memory: " << memoryname << endl;
    }
};

class Intel: public CPU,
             public GPU,
             public Memory {
public:
    virtual string process() {
        cout << "Intel CPU processing..." << endl;
        intelcpu = "Intel Core i7";
        return intelcpu;
    }
    virtual string render() {
        cout << "Intel GPU rendering..." << endl;
        intelgpu = "Intel Iris Xe";
        return intelgpu;
    }
    virtual string store() {
        cout << "Intel Memory storing..." << endl;
        intelmemory = "Intel Optane";
        return intelmemory;
    }
    private:
    string intelcpu;
    string intelgpu;
    string intelmemory;
};

class Lenvon: public CPU,
             public GPU,
             public Memory {
public:
    virtual string process() {
        cout << "Lenovo CPU processing..." << endl;
        lenovocpu = "Lenovo Ryzen 7";
        return lenovocpu;
    }
    virtual string render() {
        cout << "Lenovo GPU rendering..." << endl;
        lenovogpu = "Lenovo Radeon RX 5600M";
        return lenovogpu;
    }
    virtual string store() {
        cout << "Lenovo Memory storing..." << endl;
        lenovomemory = "Lenovo SSD";
        return lenovomemory;
    }
    private:
    string lenovocpu;
    string lenovogpu;
    string lenovomemory;
};