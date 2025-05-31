#include "scenario_2.h"
int main() {
    // Create an Intel computer
    Intel *intelComputer = new Intel;
    Lenvon lenvonComputer;
    
    // Process, render, and store using Intel components
    string cpuName = intelComputer->process();
    string gpuName = intelComputer->render();
    string memoryName = intelComputer->store();
    
    // Create a Computer object with the names of the components
    Computer myComputer_1(cpuName, gpuName, memoryName);
    
    // Display the computer specs
    myComputer_1.displaySpecs();

    // Process, render, and store using Lenovo components
    cpuName = lenvonComputer.process();
    gpuName = lenvonComputer.render();
    memoryName = lenvonComputer.store();
    // Create a Computer object with the names of the components
    Computer myComputer_2(cpuName, gpuName, memoryName);
    // Display the computer specs
    myComputer_2.displaySpecs();
    

    cpuName = intelComputer->process();
    gpuName = lenvonComputer.render();
    memoryName = intelComputer->store();
    // Create a Computer object with the names of the components
    Computer myComputer_3(cpuName, gpuName, memoryName);
    // Display the computer specs
    myComputer_3.displaySpecs();
    
    // Clean up
    delete intelComputer;
    return 0;
}