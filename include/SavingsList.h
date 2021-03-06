#ifndef VRPSOLVER_CPP_SAVINGSLIST_H
#define VRPSOLVER_CPP_SAVINGSLIST_H

#include <queue>

extern "C"
{
#include "vrp_types.h"
}

typedef std::pair<int, int> EDGE;

class Savings
{
public:
    enum
    {
        UNKNOWN = -1
    };
private:
    int value;
    EDGE edge;

public:
    Savings(void);
    Savings(const Savings& savings);
    ~Savings(void);

    void set(const vrp_problem *vrp, int first, int second);
    int getValue(void) const;
    EDGE getEdge(void) const;

    bool operator<(const Savings& s) const;
    bool operator>(const Savings& s) const;
    bool operator<=(const Savings& s) const;
    bool operator>=(const Savings& s) const;
};

class SavingsList
{
private:
    std::priority_queue<Savings> savings;

public:
    SavingsList(const vrp_problem *vrp);
    ~SavingsList(void);

    int getSize(void) const;
    EDGE getEdge(void);
};

#endif /* VRPSOLVER_CPP_SAVINGSLIST_H */
