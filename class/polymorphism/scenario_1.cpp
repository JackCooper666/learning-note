#include "scenario_1.h"

int main() {
    AbstractCalculator *addCalc = new AddCalculator();
    addCalc->m_a = 5;
    addCalc->m_b = 3;
    cout << "Addition: " << addCalc->calculate() << endl;
    delete addCalc;

    AbstractCalculator *minusCalc = new MinusCalculator();
    minusCalc->m_a = 5;
    minusCalc->m_b = 3;
    cout << "Subtraction: " << minusCalc->calculate() << endl;
    delete minusCalc;

    AbstractCalculator *productCalc = new ProductCalculator();
    productCalc->m_a = 5;
    productCalc->m_b = 3;
    cout << "Multiplication: " << productCalc->calculate() << endl;
    delete productCalc;
    
    AbstractCalculator *substractCalc = new SubstractCalculator();
    substractCalc->m_a = 5;
    substractCalc->m_b = 3;
    cout << "Division: " << substractCalc->calculate() << endl;
    delete substractCalc;
    cout << "All calculations done." << endl;
    
    return 0;
}