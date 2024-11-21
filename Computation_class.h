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
 
        // Function to get the enemy resource that can be targetted via a given allies resource
        vector<vector<ll>> enemy_under_attack_range(
            vector<pair<ll,ll>> &enemy_cord,
            vector<pair<ll,ll>> &allies_cord,
            vector<Enemy_Resource> &enemy_resoruce,
            vector<Allies_Resource> &allies_resource
            ){
            
            int n_enemy = enemy_cord.size();
            int n_allies = allies_cord.size();

            vector<vector<ll>> targets(n_allies);

            for(ll i = 0; i < n_allies; i++){
                pair<ll,ll> curr_allies_cord = allies_cord[i];

                for(ll j = 0; j < n_enemy; j++){
                    pair<ll,ll> curr_enemy_cord = enemy_cord[j];
                    long double distance = (curr_enemy_cord.first - curr_allies_cord.first)*(curr_enemy_cord.first - curr_allies_cord.first) + 
                                           (curr_enemy_cord.second - curr_allies_cord.second)*(curr_enemy_cord.second - curr_allies_cord.second);
                    
                    distance = pow(distance,0.5);
                    if(distance < allies_resource[i].attack_range && allies_resource[i].damage_value >= enemy_resoruce[j].defensive_value){
                        targets[i].push_back(j);
                    }
                }
            }

            return targets;
        }

        // Function to get the probabilitiy of the enemy resources to be targetted by the allies resources depeding on factors
        vector<vector<pair<ll,long double>>> compute_probabilities(
            vector<vector<ll>>& enemy_resource_under_allies_range,
            vector<Enemy_Resource> &enemy_resoruce,
            vector<Allies_Resource> &allies_resource,
            vector<pair<ll,ll>> &enemy_cord,
            vector<pair<ll,ll>> &allies_cord
        ){
            // Formula used : (resource of enemy)^2 * root(distance) * (damage - defense)
            int n_allies = enemy_resource_under_allies_range.size();
            vector<vector<pair<ll,long double>>> attack_probabilities(n_allies);
            auto probability = [&](vector<ll>& targets,int index)-> vector<pair<ll,long double>>{
                vector<long double> curr_score;
                long double total_score = 0;
                for(auto& it : targets){
                    long double distance = (enemy_cord[it].first - allies_cord[index].first)*(enemy_cord[it].first - allies_cord[index].first) + 
                                           (enemy_cord[it].second - allies_cord[index].second)*(enemy_cord[it].second - allies_cord[index].second);
                    distance = pow(distance,0.5);
                    long double score = pow(enemy_resoruce[it].resource_value,2) * pow(distance,0.5) * (allies_resource[index].damage_value - enemy_resoruce[it].defensive_value);
                    total_score += score;
                    curr_score.push_back(score);
                }

                vector<pair<ll,long double>> curr_probabilities;
                for(int i=0; i<targets.size(); i++){
                    curr_probabilities.push_back({targets[i],curr_score[i]/total_score});
                }
                return curr_probabilities;
            };

            for(int i=0; i<n_allies; i++){
                vector<ll> curr_targets = enemy_resource_under_allies_range[i];
                if((int)curr_targets.size()){
                    attack_probabilities[i] = probability(curr_targets,i);
                }
            }

            return attack_probabilities;
        }

};

#endif