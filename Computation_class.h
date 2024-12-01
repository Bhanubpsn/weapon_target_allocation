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
            vector<pair<ll,ll>>& enemy_cord,
            vector<pair<ll,ll>>& allies_cord,
            vector<Enemy_Resource>& enemy_resoruce,
            vector<Allies_Resource>& allies_resource
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
                    if(distance < allies_resource[i].attack_range && allies_resource[i].damage_value > enemy_resoruce[j].defensive_value){
                        targets[i].push_back(j);
                    }
                }
            }

            return targets;
        }

        // Function to get the probabilitiy of the enemy resources to be targetted by the allies resources depeding on factors
        vector<vector<pair<ll,long double>>> compute_probabilities(
            vector<vector<ll>>& enemy_resource_under_allies_range,
            vector<Enemy_Resource>& enemy_resoruce,
            vector<Allies_Resource>& allies_resource,
            vector<pair<ll,ll>>& enemy_cord,
            vector<pair<ll,ll>>& allies_cord
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
                else{
                    attack_probabilities[i] = {};
                }
            }

            return attack_probabilities;
        }

        vector<vector<ll>> map_enemy_targets_closest(
            vector<vector<pair<ll,long double>>>& attack_probabilities,
            vector<pair<ll,ll>>& enemy_cord,
            vector<pair<ll,ll>>& allies_cord,
            vector<Allies_Resource> allies_resource
        ){
            ll n_allies = attack_probabilities.size();
            ll n_enemy = enemy_cord.size();
            vector<pair<ll,vector<pair<ll,long double>>>> allies_enemy_pair(n_allies);
            for(int i=0;i<n_allies; i++){
                allies_enemy_pair[i] = {i,attack_probabilities[i]};
            } 

            auto compute_total_distance = [&](pair<ll,vector<pair<ll,long double>>>& a)-> ll {
                vector<ll> enemies;
                for(auto& it : a.second){
                    enemies.push_back(it.first);
                }
                if(enemies.size() == 0) return 1e18;
                int allies_index = a.first;
                ll total_distance = 0;
                for(auto& ind : enemies){
                    ll curr_distance = pow((allies_cord[allies_index].first - enemy_cord[ind].first),2) + pow((allies_cord[allies_index].second - enemy_cord[ind].second),2);
                    curr_distance = pow(curr_distance,0.5);
                    total_distance += curr_distance;
                }
                return total_distance;
            };

            sort(allies_enemy_pair.begin(),allies_enemy_pair.end(),[&](pair<ll,vector<pair<ll,long double>>> a,pair<ll,vector<pair<ll,long double>>> b){
                ll dist_a = compute_total_distance(a);
                ll dist_b = compute_total_distance(b); 
                return dist_a < dist_b;
            });

            ll index =0;
            unordered_set<ll> enemy_set;
            vector<vector<ll>> map(n_allies);
            while (enemy_set.size() < n_enemy) {
                index = (index % n_allies);
                ll curr_allies = allies_enemy_pair[index].first;
                vector<pair<ll, long double>> enemy_targets = allies_enemy_pair[index].second;
                
                if(enemy_targets.size() == 0){
                    index++; continue;
                }

                for(auto& it : enemy_targets) {
                    if(enemy_set.find(it.first) == enemy_set.end() && allies_resource[curr_allies].resource_instances > 0){
                        map[curr_allies].push_back(it.first);
                        enemy_set.insert(it.first);
                        allies_resource[curr_allies].resource_instances--;
                        break;
                    }
                }
                index++;
            }
            
            return map;
        }

        vector<vector<ll>> map_enemy_targets_farthest(
            vector<vector<pair<ll,long double>>>& attack_probabilities,
            vector<pair<ll,ll>>& enemy_cord,
            vector<pair<ll,ll>>& allies_cord,
            vector<Allies_Resource> allies_resource
        ){
            ll n_allies = attack_probabilities.size();
            ll n_enemy = enemy_cord.size();
            vector<pair<ll,vector<pair<ll,long double>>>> allies_enemy_pair(n_allies);
            for(int i=0;i<n_allies; i++){
                allies_enemy_pair[i] = {i,attack_probabilities[i]};
            } 

            auto compute_total_distance = [&](pair<ll,vector<pair<ll,long double>>>& a)-> ll {
                vector<ll> enemies;
                for(auto& it : a.second){
                    enemies.push_back(it.first);
                }
                if(enemies.size() == 0) return -1e18;
                int allies_index = a.first;
                ll total_distance = 0;
                for(auto& ind : enemies){
                    ll curr_distance = pow((allies_cord[allies_index].first - enemy_cord[ind].first),2) + pow((allies_cord[allies_index].second - enemy_cord[ind].second),2);
                    curr_distance = pow(curr_distance,0.5);
                    total_distance += curr_distance;
                }
                return total_distance;
            };

            sort(allies_enemy_pair.begin(),allies_enemy_pair.end(),[&](pair<ll,vector<pair<ll,long double>>> a,pair<ll,vector<pair<ll,long double>>> b){
                ll dist_a = compute_total_distance(a);
                ll dist_b = compute_total_distance(b); 
                return dist_a > dist_b;
            });

            ll index =0;
            unordered_set<ll> enemy_set;
            vector<vector<ll>> map(n_allies);
            while (enemy_set.size() < n_enemy) {
                index = (index % n_allies);
                ll curr_allies = allies_enemy_pair[index].first;
                vector<pair<ll, long double>> enemy_targets = allies_enemy_pair[index].second;
                
                if(enemy_targets.size() == 0){
                    index++; continue;
                }

                for(auto& it : enemy_targets) {
                    if(enemy_set.find(it.first) == enemy_set.end() && allies_resource[curr_allies].resource_instances > 0){
                        map[curr_allies].push_back(it.first);
                        enemy_set.insert(it.first);
                        allies_resource[curr_allies].resource_instances--;
                        break;
                    }
                }
                index++;
            }
            
            return map;
        }

        vector<vector<ll>> map_enemy_targets_powerful(
            vector<vector<pair<ll,long double>>>& attack_probabilities,
            vector<pair<ll,ll>>& enemy_cord,
            vector<Allies_Resource> allies_resource
        ){
            ll n_allies = attack_probabilities.size();
            ll n_enemy = enemy_cord.size();
            vector<pair<ll,vector<pair<ll,long double>>>> allies_enemy_pair(n_allies);
            for(int i=0;i<n_allies; i++){
                allies_enemy_pair[i] = {i,attack_probabilities[i]};
            } 

            sort(allies_enemy_pair.begin(),allies_enemy_pair.end(),[&](pair<ll,vector<pair<ll,long double>>> a,pair<ll,vector<pair<ll,long double>>> b){
                return allies_resource[a.first].damage_value > allies_resource[b.first].damage_value;
            });

            ll index =0;
            unordered_set<ll> enemy_set;
            vector<vector<ll>> map(n_allies);
            while (enemy_set.size() < n_enemy) {
                index = (index % n_allies);
                ll curr_allies = allies_enemy_pair[index].first;
                vector<pair<ll, long double>> enemy_targets = allies_enemy_pair[index].second;
                
                if(enemy_targets.size() == 0){
                    index++; continue;
                }

                for(auto& it : enemy_targets) {
                    if(enemy_set.find(it.first) == enemy_set.end() && allies_resource[curr_allies].resource_instances > 0){
                        map[curr_allies].push_back(it.first);
                        enemy_set.insert(it.first);
                        allies_resource[curr_allies].resource_instances--;
                        break;
                    }
                }
                index++;
            }
            
            return map;
        }

        // Function to calculate the effectiveness of the mapping
        pair<ll,ll> compute_effectiveness(
            vector<vector<ll>>& map,
            vector<Enemy_Resource>& enemy_resoruce,
            vector<Allies_Resource>& allies_resource
        ){
            ll resource_used = 0, damage_done = 0;
            for(int i=0; i<map.size(); i++){
                resource_used += (allies_resource[i].resource_value * (ll)map[i].size());
                for(auto& ind : map[i]){
                    damage_done += (enemy_resoruce[ind].resource_value);
                }
            }
            return {resource_used, damage_done};
        }

};

#endif