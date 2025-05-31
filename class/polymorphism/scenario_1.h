#include <iostream>
#include <string>
using namespace std;
class AbstractCalculator {
    public:
    virtual float calculate () {
        return 0;
    }
    float m_a;
    float m_b;
};

class AddCalculator : public AbstractCalculator {
    public:
    float calculate () {
        return m_a + m_b;
    }
};

class MinusCalculator : public AbstractCalculator {
    public:
    float calculate () {
        return m_a - m_b;
    }
};

class ProductCalculator : public AbstractCalculator {
    public:
    float calculate () {
        return m_a * m_b;
    }
};

class SubstractCalculator : public AbstractCalculator {
    public:
    float calculate () {
        return m_a / m_b;
    }
};
