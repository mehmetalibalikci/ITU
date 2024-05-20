/* @author
* Student Name: Mehmet Ali Balıkçı 
* Student ID  : 150200059
*/

#include "pokemon.h"

// This class inherited from the class Pokemon provides creating an psychic Pokemon.

class psychicPokemon : public Pokemon{
    public:
        psychicPokemon(const string name, const int hp, const int damage); // constructor
        bool isOwnTerrain(const string type_of_terrain) const; // It returns whether or not the pokemon is in its own terrain.
        int getRecharge() const; // It returns the number of rounds needed to recharge.        
};
