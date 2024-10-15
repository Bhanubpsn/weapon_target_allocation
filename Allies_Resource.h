#ifndef ALLIES_RESOURCE_H
#define ALLIES_RESOURCE_H

// A Basic class for Allies Resouces (For Now)
 
#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Allies_Resource{
    public:
        ll damage_value;
        string resource_type;
        ll attack_range;
        ll resource_value;

        Allies_Resource(ll damage,string type,ll range,ll resource){
            this->damage_value = damage;
            this->resource_type = type;
            this->attack_range = range;
            this->resource_value = resource;
        }
};

#endif