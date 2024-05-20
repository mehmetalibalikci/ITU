/* @author
* Student Name: Mehmet Ali Balıkçı 
* Student ID  : 150200059
*/

#pragma once

#include<iostream>

using std::string;
using std::cout;
using std::endl;

class Pokemon{
    public:
        Pokemon(const string name, const int hp, const int damage, const int power_up, const int recharge); // constructor
        string getPokemonName() const; // It returns the name of pokemon.
        int getHP() const;             // It returns the hp of pokemon.
        void setHP(const int damage_taken); // It changes the hp of pokemon according to the damage pokemon take.
        int getDamage() const;         // It returns the amount of damage a pokemon causes.
        int getPossibilityOfPowerUP() const; // It returns the possibility of PowerUp a Pokemon will.
        bool getCanPowerUP() const;  // It returns whether or not a pokemon can powerUP.
        void setCanPowerUP(const bool availability_of_powerUP); // It sets whether a pokemon can powerUP or not.
        bool getStateOfPowerUP() const;       // It returns whether a pokemon will powerUP or not.
        void setStateOfPowerUP(const bool state_of_powerUP);   // It sets whether a pokemon will powerUP or not.
        bool getIsFirst() const;            // It returns whether a pokemon will fight first or not.
        void setIsFirst(const bool is_first); // It sets whether a pokemon will fight first or not.
        bool getFainted() const;         // It turns whether or not the pokemon has fainted.
        void printProperties() const;    // It prints the properties of a pokemon such as name, hp and damage it can cause.

    protected:
        const string name_;           // name of a pokemon
        int hp_;                // Hit Points: Indicates how much damage a pokemon can receive before fainting.
        const int damage_;      // indicates how much damage a pokemon will cause.
        const int possibility_of_powerUP_;  // PowerUp possiblity: Indicates the chance that it will powerUp on a given round of the battle.
        bool availability_of_powerUP_ = true;    // It controls whether a pokemon can powerUP or not.
        bool state_of_powerUP_ = false;           // It shows whether a pokemon will powerUP or not.     
        bool is_first_ = false;      // It controls whether a pokemon will fight first or not.
        const int recharge_; // It shows the number of rounds that must pass until a pokemon has the chance of having powerUP.   
};