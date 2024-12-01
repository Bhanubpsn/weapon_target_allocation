/*
    A Static Approach for Weapon Target Allocation System.
    --By Bhanu / Akash /Praveen
    2021UG1020 / 2021UG1018 / 2021UG1049
*/

// Including the classes for Enemy Resources and Allies Resources
#include "Enemy_Resource.h"
#include "Allies_Resource.h"
#include "Computation_class.h"
#include "Input_class.h"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
 

void solve() {
    // For any kind of input taking
    Input input;
    Computation computation;

    // For storing Coordinates for the Enemy and Allies resources.
    vector<pair<ll, ll>> cordinates_enemey,cordinates_allies;

    // Reading coordinates from files that will be given to us (at least in static case).
    input.read_coordinates("Co-ordinates/enemy_coordinates.txt", cordinates_enemey);
    input.read_coordinates("Co-ordinates/allies_coordinates.txt", cordinates_allies);

    int number_of_enemy = cordinates_enemey.size();
    int number_of_allies = cordinates_allies.size();

    // Getting the info about the enemy and allies resources
    vector<Enemy_Resource> enemy_resources;
    vector<Allies_Resource> allies_resources;

    input.read_enemy_resource("Resource_classification/enemy.txt", enemy_resources);
    input.read_allies_resource("Resource_classification/allies.txt",allies_resources);

    vector<vector<ll>> enemy_resource_under_allies_range = computation.enemy_under_attack_range(
        cordinates_enemey,
        cordinates_allies,
        enemy_resources,
        allies_resources
    );

    vector<vector<pair<ll,long double>>> probabilities_of_attack = computation.compute_probabilities(
        enemy_resource_under_allies_range,
        enemy_resources,
        allies_resources,
        cordinates_enemey,
        cordinates_allies
    );

    
    for(auto& it : probabilities_of_attack){
        sort(it.begin(),it.end(),[&](pair<ll,long double> a,pair<ll,long double> b){
            return a.second > b.second;
        });
    }

    // Map enemy targets using 3 ways :
    // 1. Nearest Allies First
    // 2. Farthest Allies First
    // 3. Powerful Allies First
    
    vector<vector<ll>> map_enemy_targets_1 = computation.map_enemy_targets_closest(
        probabilities_of_attack,
        cordinates_enemey,
        cordinates_allies,
        allies_resources
    );

    vector<vector<ll>> map_enemy_targets_2 = computation.map_enemy_targets_farthest(
        probabilities_of_attack,
        cordinates_enemey,
        cordinates_allies,
        allies_resources
    );

    vector<vector<ll>> map_enemy_targets_3 = computation.map_enemy_targets_powerful(
        probabilities_of_attack,
        cordinates_enemey,
        allies_resources
    );

    //Computing effectiveness of each mapping
    pair<ll,ll> map1 = computation.compute_effectiveness(map_enemy_targets_1,enemy_resources,allies_resources);
    pair<ll,ll> map2 = computation.compute_effectiveness(map_enemy_targets_2,enemy_resources,allies_resources);
    pair<ll,ll> map3 = computation.compute_effectiveness(map_enemy_targets_3,enemy_resources,allies_resources);

    for(int i=0; i<map_enemy_targets_1.size(); i++){
        cout<<i<<" : ";
        for(auto& it : map_enemy_targets_1[i]) cout<<it<<" ";
        cout<<endl;
    }
    cout<<"Resource Used : "<<map1.first<<endl;
    cout<<"Damage : "<<map1.second<<endl;
    cout<<"\n\n";

    for(int i=0; i<map_enemy_targets_2.size(); i++){
        cout<<i<<" : ";
        for(auto& it : map_enemy_targets_2[i]) cout<<it<<" ";
        cout<<endl;
    }
    cout<<"Resource Used : "<<map2.first<<endl;
    cout<<"Damage : "<<map2.second<<endl;
    cout<<"\n\n";

    for(int i=0; i<map_enemy_targets_3.size(); i++){
        cout<<i<<" : ";
        for(auto& it : map_enemy_targets_3[i]) cout<<it<<" ";
        cout<<endl;
    }
    cout<<"Resource Used : "<<map3.first<<endl;
    cout<<"Damage : "<<map3.second<<endl;
    cout<<"\n\n";

    auto save_output_to_file = [&]()->void{
        std::ofstream output_file("output.txt");
        for (int i = 0; i < map_enemy_targets_1.size(); i++) {
            output_file << i << " : ";
            for (auto& it : map_enemy_targets_1[i]) output_file << it << " ";
            output_file << std::endl;
        }
        output_file << "Resource Used : " << map1.first << std::endl;
        output_file << "Damage : " << map1.second << std::endl;
        output_file << "\n\n";

        for (int i = 0; i < map_enemy_targets_2.size(); i++) {
            output_file << i << " : ";
            for (auto& it : map_enemy_targets_2[i]) output_file << it << " ";
            output_file << std::endl;
        }
        output_file << "Resource Used : " << map2.first << std::endl;
        output_file << "Damage : " << map2.second << std::endl;
        output_file << "\n\n";

        for (int i = 0; i < map_enemy_targets_3.size(); i++) {
            output_file << i << " : ";
            for (auto& it : map_enemy_targets_3[i]) output_file << it << " ";
            output_file << std::endl;
        }
        output_file << "Resource Used : " << map3.first << std::endl;
        output_file << "Damage : " << map3.second << std::endl;
        output_file << "\n\n";
        output_file.close();
    };

    auto save_probabilities_to_file = [&]()->void{
        std::ofstream output_file("probabilities.txt");
        for (int i = 0; i < probabilities_of_attack.size(); i++) {
            output_file << i << " -> " << std::endl;
            for (auto& it : probabilities_of_attack[i]) {
                output_file << it.first << " , " << it.second << std::endl;
            }
            output_file << std::endl;
        }

        output_file.close();
    };
    save_probabilities_to_file();
    save_output_to_file();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
