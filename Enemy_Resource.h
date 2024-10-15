#ifndef ENEMEY_RESOURCE_H
#define ENEMEY_RESOURCE_H

// A Basic class for Enemy Resouces (For Now)

#include <bits/stdc++.h>
#define ll long long
using namespace std;

class Enemy_Resource{
    public:
        ll resource_value;
        string resource_type;
        ll defensive_value;

        Enemy_Resource(ll val,string type,ll defense){
            this->resource_value = val;
            this->resource_type = type;
            this->defensive_value = defense;
        }
    
};

#endif