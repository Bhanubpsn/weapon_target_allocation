/*
    A Static Approach for Weapon Target Allocation System.
    --By Bhanu / Akash /Praveen
    2021UG1020 / 2021UG1018 / 
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
    vector<Enemy_Resource> enemy_resources(number_of_enemy);
    vector<Allies_Resource> allies_resources(number_of_allies);

    input.read_enemy_resource("Resource_classification\enemy.txt", enemy_resources);
    input.read_allies_resource("Resource_classification\allies.txt",allies_resources);

    vector<vector<ll>> enemy_resource_under_allies_range = computation.enemy_under_attack_range(
        cordinates_enemey,
        cordinates_allies,
        enemy_resources,
        allies_resources
    );

    
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
