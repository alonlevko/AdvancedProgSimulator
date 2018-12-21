//
// Created by alon on 12/20/18.
//

#ifndef ADVANCEDPROG_PLUS_H
#define ADVANCEDPROG_PLUS_H

#include "expression.h"
class binaryExpression: public expression {
protected:
    expression* left;
    expression* right;
};

class plus: public binaryExpression {
public:
    double calculate() {
        double valL;
        double valR;
        if(left == nullptr) {
            valL = 0;
        } else {
            valL = left->calculate();
        }
        if(right == nullptr) {
            valR = 0;
        } else {
            valR = right->calculate();
        }
        return valL + valR;
    }
};

class minus: public binaryExpression {
public:
    double calculate() {
        double valL;
        double valR;
        if(left == nullptr) {
            valL = 0;
        } else {
            valL = left->calculate();
        }
        if(right == nullptr) {
            valR = 0;
        } else {
            valR = right->calculate();
        }
        return valL - valR;
    }
};

class multiply: public binaryExpression {
public:
    double calculate() {
        double valL;
        double valR;
        if(left == nullptr) {
            valL = 0;
        } else {
            valL = left->calculate();
        }
        if(right == nullptr) {
            valR = 0;
        } else {
            valR = right->calculate();
        }
        return valL * valR;
    }
};

class divide: public binaryExpression {
public:
    double calculate() {
        double valL;
        double valR;
        if(left == nullptr) {
            valL = 0;
        } else {
            valL = left->calculate();
        }
        if(right == nullptr) {
            valR = 0;
        } else {
            valR = right->calculate();
        }
        return valL / valR;
    }
};

class unminus: public expression {
private:
    expression* unary;
public:
    double calculate() {
        if(unary == nullptr) {
            return 0;
        } else {
            return -(unary->calculate());
        }
    }
};

class number: public expression {
private:
    double value;
public:
    double calculate() {
        return value;
    }
};
#endif //ADVANCEDPROG_PLUS_H
