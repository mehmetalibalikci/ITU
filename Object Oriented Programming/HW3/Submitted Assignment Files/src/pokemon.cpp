/* @author
* Student Name: Mehmet Ali Balıkçı 
* Student ID  : 150200059
*/

#include "pokemon.h"

Pokemon::Pokemon(const string name, const int hp, const int damage, const int possibility_of_powerUP, const int recharge) 
:name_ (name), hp_(hp), damage_ (damage), possibility_of_powerUP_(possibility_of_powerUP), recharge_(recharge) 
{}
string Pokemon::getPokemonName() const{
    return name_;
}
int Pokemon::getHP() const{
    return hp_;
}
void Pokemon::setHP(const int damage_taken){
    hp_ -= damage_taken;
}
int Pokemon::getDamage() const{
    return damage_;
}
int Pokemon::getPossibilityOfPowerUP() const{
    return possibility_of_powerUP_;
}
bool Pokemon::getCanPowerUP() const{
    return availability_of_powerUP_;
}
void Pokemon::setCanPowerUP(const bool availability_of_powerUP ){
    availability_of_powerUP_ = availability_of_powerUP;
}
bool Pokemon::getStateOfPowerUP() const{
    return state_of_powerUP_;
}
void Pokemon::setStateOfPowerUP(const bool state_of_powerUP){
    state_of_powerUP_ = state_of_powerUP;
}
bool Pokemon::getIsFirst() const{
    return is_first_;
}
void Pokemon::setIsFirst(const bool is_first){
    is_first_ = is_first;
}
bool Pokemon::getFainted() const{
    if(hp_ <= 0) return true;
    return false;
}
void Pokemon::printProperties() const{
    cout<<"\tName: "<<name_<<endl;
    cout<<"\tHP: "<<hp_<<endl;
    cout<<"\tDamage: "<<damage_<<endl;
}
