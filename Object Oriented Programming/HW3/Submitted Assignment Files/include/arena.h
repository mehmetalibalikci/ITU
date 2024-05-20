/* @author
* Student Name: Mehmet Ali Balıkçı 
* Student ID  : 150200059
*/

#include<iostream>
#include "electricPokemon.h"
#include "psychicPokemon.h"

class Arena{
    public:
        void addPokemon(const char type, const string name, const int hp, const int damage); // To add pokemon to the arena 
        void spawnTerrain(); // To spawn terrain 
        void restartTerrain(); // To reset the type of terrain
        void printRoundStats(const int round, const int heads) const; // To print round informations
        void printMatchResults() const; // To print match results
        void determinePokemonsPowerUP(); // This determines which pokemons will powerUp.
        void fightOnElectricTerrain(); // To simulate the fight taking place on electric terrain 
        void fightOnPsychicTerrain();  // To simulate the fight taking place on psychic terrain 
        void fightOnNoneTerrain();     // To simulate the fight taking place on none terrain 
        void simulateBattle();         // To organize the fight in general
        void deletePokemons();         // To delete the old pokemons for new pokemons to enter the fight
        ~Arena();  // destructor
    private:
        electricPokemon* m_electricPokemon = nullptr; // pointer to pokemon in a composition relationship
        psychicPokemon*  m_psychicPokemon = nullptr;  // pointer to pokemon in a composition relationship
        string type_of_terrain_;
        int number_of_pokemon_{};
        bool e_pokemon_can_damage_ = true; // To control whether a pokemon is confused or not, that is, it can cause damage or not.
};