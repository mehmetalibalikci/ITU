/* @author
* Student Name: Mehmet Ali Balıkçı 
* Student ID  : 150200059
*/

#include "electricPokemon.h"


electricPokemon::electricPokemon(const string name, const int hp, const int damage) 
:Pokemon(name, hp, damage, 20, 3) // 20 for the possibility of that an electric pokemon will powerUp, and 3 for the time of recharge
{   cout<<"\n\n";
    cout<<"Electric Pokemon "<<name<<" has entered the arena."<<endl;
    cout<<"Class: Electric"<<endl;
    printProperties();
}

bool electricPokemon::isOwnTerrain (const string type_of_terrain) const{
    if(type_of_terrain == "electric") return true;
    return false;
}

int electricPokemon::getRecharge() const{
    return recharge_;
}