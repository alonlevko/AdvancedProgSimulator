#include "expressionFactory.h"
#include "list"
#include "stack"
#include <algorithm>
#include <ctype.h>
// get a list of tokens and return its value.
double expressionFactory::parse(vector<string> vec, symbolTable* table) {
    vec = removeUnaryMinus(vec);
    list<string> tokens = shuntingYard(vec, table);
    return RPNCalc(tokens, table);
}
// calculate the value of a list of tokens that are orderd in reversed polish notation.
double expressionFactory::RPNCalc(list<string> tokens, symbolTable* table) {
    stack<double> temp;
    while(!tokens.empty()) {
        // load the first token.
        string first = tokens.front();
        tokens.pop_front();
        // check if the toekn is an operator
        if (is_operator(first)) {
            // if it is a unary minus
            if (first.compare("$") == 0) {
                // pop it operands then do the operation.
                double operand = -(temp.top());
                temp.pop();
                temp.push(operand);
            } else { // it is a binary operator
                double operand1 = temp.top();
                temp.pop();
                double operand2 = temp.top();
                temp.pop();
                // calculate the expression and push it
                temp.push(calc(operand1, first, operand2));
            }
            // if it is a number we check the value and push it
        } else if (is_number(first)) {
            double num = stod(first);
            temp.push(num);
            // if it is a variable we get its value and them push it
        } else if (table->isVariable(first)) {
            variable* v = table->getVariable(first);
            double num = v->calculate();
            temp.push(num);
        }
    }
    // at the end the top of the stack will be out value.
    return temp.top();
}
// replace all of the unary minuses with the dollar sign.
vector<string> expressionFactory::removeUnaryMinus(vector<string> vec) {
    vector<string> result;
    string prev = *(vec.begin());
    // check if the first operator is a unary minus and replace it.
    if(prev.compare("-") == 0) {
        result.push_back("$");
    } else {
        result.push_back(prev);
    }
    string current;
    // loop over all of the strings and replace the unary minuses
    for(vector<string>::iterator it = (vec.begin() + 1); it != vec.end(); it++){
        // make sure out current has somthing before we use it
        if(current.size() > 0) {
            prev = current;
        }
        current = (*it);
        // if we have 2 operators in a row the second is a unary minus.
        if((prev != ")") && (is_operator(prev)) && (current.compare("-") == 0)) { // this is a unary minus
            result.push_back("$"); // push back only the dollar and ignore the -
        } else {
            result.push_back(current);
        }
    }
    // return the string after manipulation.
    return result;
}
// take an expression in infix notation and turn it into reversed polish notation.
list<string> expressionFactory::shuntingYard(vector<string> vec, symbolTable* table) {
    list<string> output;
    stack<opertor> operators;
    // we will define unary negation as $
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); it++) {
        // if the token is a number push it into the ouput, variables also.
        if (is_number(*it)) {
            output.push_back(*it);
        } else if (table->isVariable(*it)) {
            output.push_back(*it);
            // we want to turn ( into operator and push it
        } else if ((*it).compare("(") == 0) {
            opertor ope;
            ope.rep = *it;
            ope.precedence = 1;
            operators.push(ope);
            // if we have ) we need to push all other operators untill its (
        } else if ((*it).compare(")") == 0) {
            while (!(operators.top().rep.compare("(") == 0)) {
                opertor tem = operators.top();
                operators.pop();
                output.push_back(tem.rep);
            }
            operators.pop();
            // if we have an operator
        } else if (is_operator(*it)) {
            // create the struct from it
            opertor ope = makeOpertor(*it);
            // use precedence and the size of the stack to choose if push or not
            while ((operators.size() > 0) && ((operators.top()).precedence >= ope.precedence)
                   && !(operators.top().rep.compare("(") == 0)) {
                opertor tem = operators.top();
                operators.pop();
                output.push_back(tem.rep);
            }
            operators.push(ope);
        }
    }
    // at the end push all of the operators into the output
    while (!operators.empty()) {
        opertor tem = operators.top();
        operators.pop();
        output.push_back(tem.rep);
    }
    return output;
}
// check if a string is a number by checking if all of its chers are digits
bool expressionFactory::is_number(string& s) {
    bool temp = true;
    for(string::iterator it  = s.begin(); it != s.end(); it++) {
        if(!(isdigit(*it) || *it == '.')) {
            temp = false;
        }
    }
    return temp;
}
// check if a strings is an operator by cehcking each options
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
// give every operator a precedence.
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
// calculate the value of the expression using the right command in the string.
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
