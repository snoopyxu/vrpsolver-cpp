#include <stdio.h>
#include <string.h>

#include "Vehicle.h"

extern "C"
{
#include "vrp_macros.h"
}


Vehicle::Vehicle(void)
{
    route_length_  = 0;
    capacity_      = 0;
}

Vehicle Vehicle::copy(void) const
{
    Vehicle v_copy;

    size_t route_byte = route_length_ * sizeof(int);
    memcpy(v_copy.route_, route_, route_byte);

    v_copy.route_length_ = route_length_;
    v_copy.capacity_     = capacity_;

    return v_copy;
}

int Vehicle::capacity(void) const
{
    return capacity_;
}

/* customerは０以上顧客数未満 */
bool Vehicle::visit(const vrp_problem *vrp, int customer)
{
    if (!(0 < customer && customer < vrp->vertnum))
        return false;

    route_[route_length_] = customer;
    route_length_++;
    capacity_ += vrp->demand[customer];
    return true;
}

int Vehicle::computeCost(const vrp_problem *vrp) const
{
    if (route_length_ == 0) return 0;

    int i;
    int cost = vrp->dist.cost[INDEX(0, route_[0])];
    for (i=1; i < route_length_; i++)
    {
        cost += vrp->dist.cost[INDEX(route_[i-1], route_[i])];
    }
    cost += vrp->dist.cost[INDEX(route_[i-1], 0)];

    return cost;
}

void Vehicle::print(void) const
{
    printf("[%6d] ", capacity_);
    for (int i=0; i < route_length_; i++)
        printf("%4d", route_[i]);
    printf("\n");
}
