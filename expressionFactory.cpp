//
// Created by alon on 12/20/18.
//

#include "expressionFactory.h"
#include "list"
#include "stack"
#include <algorithm>
#include <ctype.h>

double expressionFactory::parse(vector<string> vec, symbolTable* table) {
    vec = removeUnaryMinus(vec);
    list<string> tokens = shuntingYard(vec, table);
    return RPNCalc(tokens, table);
}

double expressionFactory::RPNCalc(list<string> tokens, symbolTable* table) {
    stack<double> temp;
    while(!tokens.empty()) {
        string first = tokens.front();
        tokens.pop_front();
        if (is_operator(first)) {
            if (first.compare("$") == 0) {
                double operand = -(temp.top());
                temp.pop();
                temp.push(operand);
            } else {
                double operand1 = temp.top();
                temp.pop();
                double operand2 = temp.top();
                temp.pop();
                temp.push(calc(operand1, first, operand2));
            }
        } else if (is_number(first)) {
            double num = stod(first);
            temp.push(num);
        } else if (table->isVariable(first)) {
            variable* v = table->getVariable(first);
            double num = v->calculate();
            temp.push(num);
        }
    }
    return temp.top();
}
vector<string> expressionFactory::removeUnaryMinus(vector<string> vec) {
    vector<string> result;
    string prev = *(vec.begin());
    if(prev.compare("-") == 0) {
        result.push_back("$");
    } else {
        result.push_back(prev);
    }
    string current;
    for(vector<string>::iterator it = (vec.begin() + 1); it != vec.end(); it++){
        if(current.size() > 0) {
            prev = current;
        }
        current = (*it);
        if((prev != ")") && (is_operator(prev)) && (current.compare("-") == 0)) { // this is a unary minus
            result.push_back("$");
        } else {
            result.push_back(current);
        }
    }
    return result;
}

list<string> expressionFactory::shuntingYard(vector<string> vec, symbolTable* table) {
    list<string> output;
    stack<opertor> operators;
    // we will define unary negation as $
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); it++) {
        if (is_number(*it)) {
            output.push_back(*it);
        } else if (table->isVariable(*it)) {
            output.push_back(*it);
        } else if ((*it).compare("(") == 0) {
            opertor ope;
            ope.rep = *it;
            ope.precedence = 1;
            operators.push(ope);
        } else if ((*it).compare(")") == 0) {
            while (!(operators.top().rep.compare("(") == 0)) {
                opertor tem = operators.top();
                operators.pop();
                output.push_back(tem.rep);
            }
            operators.pop();
        } else if (is_operator(*it)) {
            opertor ope = makeOpertor(*it);
            //if(is_operator(output.back())){}
            while ((operators.size() > 0) && ((operators.top()).precedence >= ope.precedence)
                   && !(operators.top().rep.compare("(") == 0)) {
                opertor tem = operators.top();
                operators.pop();
                output.push_back(tem.rep);
            }
            operators.push(ope);
        }
    }
    while (!operators.empty()) {
        opertor tem = operators.top();
        operators.pop();
        output.push_back(tem.rep);
    }
    return output;
}
bool expressionFactory::is_number(string& s) {
    bool temp = true;
    for(string::iterator it  = s.begin(); it != s.end(); it++) {
        if(!(isdigit(*it) || *it == '.')) {
            temp = false;
        }
    }
    return temp;
}

bool expressionFactory::is_operator(string& s) {
    if (s.compare("+") == 0) {
        return true;
    } else if (s.compare("-") == 0) {
        return true;
    } else if (s.compare("*") == 0) {
        return true;
    } else if (s.compare("/") == 0) {
        return true;
    } else if (s.compare("(") == 0) {
        return true;
    } else if (s.compare(")") == 0) {
        return true;
    } else if (s.compare("$") == 0) {
        return true;
    } else {
        return false;
    }
}

opertor expressionFactory::makeOpertor(string& s) {
    opertor temp;
    temp.rep = s;
    if (s.compare("+") == 0) {
        temp.precedence = 2;
    } else if (s.compare("-") == 0) {
        temp.precedence = 2;
    } else if (s.compare("*") == 0) {
        temp.precedence = 3;
    } else if (s.compare("$") == 0) {
        temp.precedence = 4;
    } else if (s.compare("/") == 0) {
        temp.precedence = 3;
    } else if (s.compare("(") == 0) {
        temp.precedence = 1;
    } else if (s.compare(")") == 0) {
        temp.precedence = 1;
    } else {
        temp.precedence = 0;
    }
    return temp;
}

bool expressionFactory::is_variable(string& s) {
    bool temp = true;
    for(string::iterator it  = s.begin(); it != s.end(); it++) {
        if(isalpha(*it) == 0) {
            temp = false;
        }
    }
    return temp;
}

double expressionFactory::calc(double first, string s, double second) {
    if (s.compare("+") == 0) {
        return first + second;
    } else if (s.compare("-") == 0) {
        return second - first;
    } else if (s.compare("*") == 0) {
        return first * second;
    } else if (s.compare("/") == 0) {
        return second / first;
    } else {
        return 0;
    }
}
