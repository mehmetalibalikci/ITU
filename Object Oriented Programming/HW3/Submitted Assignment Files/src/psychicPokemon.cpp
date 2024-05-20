/* @author
* Student Name: Mehmet Ali Balıkçı 
* Student ID  : 150200059
*/

#include "psychicPokemon.h"


psychicPokemon::psychicPokemon(const string name, const int hp, const int damage)
:Pokemon(name, hp, damage, 30, 5) // 30 for the possibility of that an psychic pokemon will powerUp, and 5 for the time of recharge
{   cout<<"\n\n";
    cout<<"Psychic Pokemon "<<name<<" has entered the arena."<<endl;
    cout<<"Class: Psychic"<<endl;
    printProperties();
}

bool psychicPokemon::isOwnTerrain(const string type_of_terrain) const{
    if(type_of_terrain == "psychic") return true;
    return false;
}

int psychicPokemon::getRecharge() const{
    return recharge_;
}