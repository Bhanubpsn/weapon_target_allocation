// A class that houses all the functions that takes in any kind of inputs :) Keeping the code base readable. 

#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
#include "Enemy_Resource.h"
#include "Allies_Resource.h"
#define ll long long
using namespace std;

class Input{
    public:

        void read_coordinates(const string &filename, vector<pair<ll, ll>> &coordinates) {
            ifstream infile(filename);
            ll x, y;
            if (!infile.is_open()) {
                cerr<<"Error: Could not open file "<<filename<<endl;
                return;
            }

            // Read each pair of coordinates from the input file
            while (infile>>x>>y) {
                coordinates.push_back({x, y});
            }
            infile.close();
        }

        void read_enemy_resource(const string &filename, vector<Enemy_Resource>& resouce) {
            ifstream infile(filename);
            
            ll resouce_value,defense_value;
            string type;

            if (!infile.is_open()) {
                cerr<<"Error: Could not open file "<<filename<<endl;
                return;
            }

            while (infile>>resouce_value>>type>>defense_value) {
                Enemy_Resource enemy(resouce_value,type,defense_value);
                resouce.push_back(enemy);
            }
            infile.close();
        }

        void read_allies_resource(const string &filename, vector<Allies_Resource> &resouce) {
            ifstream infile(filename);
            
            ll damage,range,resource_value,instances;
            string type;

            if (!infile.is_open()) {
                cerr<<"Error: Could not open file "<<filename<<endl;
                return;
            }

            while (infile>>damage>>type>>range>>resource_value>>instances) {
                Allies_Resource allies(damage,type,range,resource_value,instances);
                resouce.push_back(allies);
            }
            infile.close();
        }
};

#endif