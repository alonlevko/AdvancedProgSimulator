#ifndef ADVANCEDPROG_EXPRESSION_H
#define ADVANCEDPROG_EXPRESSION_H
// we need to be able to calculate all exprressions.
class expression {
public:
    virtual double calculate() = 0;
    //virtual ~expression() = 0;
};
#endif //ADVANCEDPROG_EXPRESSION_H
