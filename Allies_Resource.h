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
        ll resource_instances;
        Allies_Resource() : damage_value(0), resource_type(""), attack_range(0), resource_value(0), resource_instances(0) {}
        Allies_Resource(ll damage,string type,ll range,ll resource,ll instances){
            this->damage_value = damage;
            this->resource_type = type;
            this->attack_range = range;
            this->resource_value = resource;
            this->resource_instances = instances;
        }
};

#endif