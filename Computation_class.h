#ifndef COMPUTATION_H
#define COMPUTATION_H

// A class to perform all the necessary compution for tha algorithm

#include <bits/stdc++.h>
#include "Enemy_Resource.h"
#include "Allies_Resource.h"
#define ll long long
using namespace std;

class Computation{
    public:

        // Function to get the allies resource that can target a given enemy resource
        vector<vector<ll>> enemy_under_attack_range(
            vector<pair<ll,ll>> &enemy_cord,
            vector<pair<ll,ll>> &allies_cord,
            vector<Enemy_Resource> &enemy_resoruce,
            vector<Allies_Resource> &allies_resource
            ){
            
            int n_enemy = enemy_cord.size();
            int n_allies = allies_cord.size();

            vector<vector<ll>> targets(n_enemy);

            for(ll i = 0; i < n_enemy; i++){
                pair<ll,ll> curr_enemy_cord = enemy_cord[i];

                for(ll j = 0; j < n_allies; j++){
                    pair<ll,ll> curr_allies_cord = allies_cord[j];

                    long double distance = (curr_enemy_cord.first - curr_allies_cord.first)*(curr_enemy_cord.first - curr_allies_cord.first) + 
                                           (curr_enemy_cord.second - curr_allies_cord.second)*(curr_enemy_cord.second - curr_allies_cord.second);
                    
                    distance = pow(distance,0.5);

                    if(distance < allies_resource[j].attack_range){
                        targets[i].push_back(j);
                    }
                }
            }

            return targets;
        }
};

#endif