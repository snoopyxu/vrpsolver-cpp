#include <iostream>

#include "SavingsList.h"

extern "C"
{
#include "vrp_macros.h"
}

Savings::Savings(void)
{
    value = 0;
    edge  = EDGE(UNKNOWN, UNKNOWN);
}

Savings::Savings(const Savings& savings)
{
    value = savings.value;
    edge.first  = savings.edge.first;
    edge.second = savings.edge.second;
}

Savings::~Savings(void)
{
}

static int computeValue(const vrp_problem *vrp, int first, int second)
{
    return vrp->dist.cost[INDEX(0, first)] + vrp->dist.cost[INDEX(0, second)] -
           vrp->dist.cost[INDEX(first, second)];
}

void Savings::set(const vrp_problem *vrp, int first, int second)
{
    value = computeValue(vrp, first, second);
    edge  = EDGE(first, second);
}

int Savings::getValue(void) const
{
    return value;
}

EDGE Savings::getEdge(void) const
{
    return edge;
}

bool Savings::operator<(const Savings& s) const
{
    return value < s.value;
}

bool Savings::operator>(const Savings& s) const
{
    return value > s.value;
}

bool Savings::operator<=(const Savings& s) const
{
    return value <= s.value;
}

bool Savings::operator>=(const Savings& s) const
{
    return value >= s.value;
}

/***************************************************/
/***************************************************/


SavingsList::SavingsList(const vrp_problem *vrp)
{
    if (vrp == NULL)
    {
        return;
    }

    for (int i=1; i < vrp->vertnum; i++)
    {
        for (int j=1; j < i; j++)
        {
            Savings s;
            s.set(vrp, j, i);
            savings.push(s);
        }
    }
}

SavingsList::~SavingsList(void)
{
}

int SavingsList::getSize(void) const
{
    return savings.size();
}

EDGE SavingsList::getEdge(void)
{
    EDGE edge = savings.top().getEdge();
    savings.pop();
    return edge;
}
