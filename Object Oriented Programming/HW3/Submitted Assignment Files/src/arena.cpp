/* @author
* Student Name: Mehmet Ali Balıkçı 
* Student ID  : 150200059
*/


#include "arena.h"
#include <cstdlib>
#include <ctime>
#include <time.h>


using std::cout;
using std::endl;

void Arena::addPokemon(const char type, const string name, const int hp, const int damage){
    // adding two pokemon, one of them must be electric and the other one must be psychic

    if( (type == 'e' || type == 'p') && number_of_pokemon_ < 2){
        if(type == 'e' && m_electricPokemon == nullptr){
            m_electricPokemon = new electricPokemon(name, hp, damage);
            number_of_pokemon_++;
        }
        else if(type == 'p' && m_psychicPokemon == nullptr){ 
            m_psychicPokemon  = new psychicPokemon(name, hp, damage);
            number_of_pokemon_++;
        }
        restartTerrain();
    } 
    else{
        cout<<"Wrong character or excessive number of data entries "<<endl;
    }
    
}
void Arena::spawnTerrain(){
    int random_number = rand() % 100 + 1;        // Generate a random value between 1 and 100
    
    if(random_number <= 20 ){
        type_of_terrain_ = "psychic";            // assign "psychic" value with the possibility of %20
    }
    else if(random_number <= 40 ){
        type_of_terrain_ = "electric";           // assign "electric" value with the possibility of %20
    }
    else if(random_number <= 100 ){
        type_of_terrain_ = "none";               // assign "none" value with the possibility of %60
    }
}
void Arena::restartTerrain(){
    type_of_terrain_ = "none";
}
void Arena::printRoundStats(const int round, const int heads) const{
    
    cout<<"Round: "<<round<<endl;
    cout<<"Current Terrain: "<<type_of_terrain_<<endl;
    
    // Printing which pokemon will go first
    if(heads<51){
        cout<<""<<m_electricPokemon->getPokemonName()<<" goes first."<<endl; 
    }
    else{
        cout<<""<<m_psychicPokemon->getPokemonName()<<" goes first."<<endl; 
    }
    
    // Printing if any pokemon will powerUP

    if(m_electricPokemon->getStateOfPowerUP() ){
        cout<<""<<m_electricPokemon->getPokemonName()<<" has initiated a powerUP."<<endl;
    }
    if(m_psychicPokemon->getStateOfPowerUP() ){
        cout<<""<<m_psychicPokemon->getPokemonName()<<" has initiated a powerUP."<<endl;
    }

    // Printing how much hp pokemons have

    cout<<""<<m_electricPokemon->getPokemonName()<<" HP: "<<m_electricPokemon->getHP()<<endl;
    cout<<""<<m_psychicPokemon->getPokemonName()<<" HP: "<<m_psychicPokemon->getHP()<<endl;
    
    // Printing which pokemon is in the lead or the drawing situation

    if(m_electricPokemon->getHP() > m_psychicPokemon->getHP()) cout<<""<<m_electricPokemon->getPokemonName()<<" is in the lead!"<<endl;
    else if(m_psychicPokemon->getHP() > m_electricPokemon->getHP()) cout<<""<<m_psychicPokemon->getPokemonName()<<" is in the lead!"<<endl;
    else cout<<"Exciting moments match draw!"<<endl;
}
void Arena::printMatchResults() const{
    cout<<"Match Results: "<<endl;

    // Printing which pokemon has won the match

    if(m_electricPokemon->getFainted()) cout<<""<<m_psychicPokemon->getPokemonName()<<" has won the match!"<<endl;
    else cout<<""<<m_electricPokemon->getPokemonName()<<" has won the match!"<<endl;
}
void Arena::determinePokemonsPowerUP(){  

    // Deciding whether pokemons can initiate PowerUP or not

    if( m_electricPokemon->getCanPowerUP() ){
        int chance = rand() % 100 + 1;
        if( chance <= m_electricPokemon->getPossibilityOfPowerUP()){  
            m_electricPokemon->setStateOfPowerUP(true);
        }
    }
    if( m_psychicPokemon->getCanPowerUP() ){
        int chance = rand() % 100 + 1;

        if( chance <= m_psychicPokemon->getPossibilityOfPowerUP()){
            m_psychicPokemon->setStateOfPowerUP(true);
        }
    }
}
void Arena::simulateBattle(){

    int sim_heads; // Using in deciding which pokemon will be first
    int number_of_round = 1; // Using to keep what round pokemons are in
    int terrain_counter = 0; // Using to enable psychic and electric terrains remain for 5 rounds
    int e_pokemon_powerUp_counter=0; // Using to count the time of recharge of pokemons
    int p_pokemon_powerUp_counter=0; // Using to count the time of recharge of pokemons
    int e_pokemon_damage_counter=0;  // Using to count the number of rounds in which the electric pokemon is confused
    
    // Keep going unless some pokemon has fainted 
    while(!m_electricPokemon->getFainted() && !m_psychicPokemon->getFainted()){
        cout<<"\n\n";
        
        if(type_of_terrain_ == "none" ){
            spawnTerrain();
        }

        // Do not spawn terrain if the terrain is electric or psychic for 5 rounds
        else{
            terrain_counter++;
            if(terrain_counter == 5){
                spawnTerrain();
                terrain_counter = 0;
            }
        }

        // Use a random value to choose which pokemon will be first 
        sim_heads = rand() % 100 + 1; 
        
        m_electricPokemon->setIsFirst(false); // In every round, reseting the information of being first
        m_psychicPokemon->setIsFirst(false);  // In every round, reseting the information of being first
        
        if(sim_heads<51) m_electricPokemon->setIsFirst(true); // To set being first
        else m_psychicPokemon->setIsFirst(true);        // To set being first
        
        determinePokemonsPowerUP(); // Setting whether or not pokemons will powerUP

        int amount_of_damage_of_electric;
        int amount_of_damage_of_psychic;  
        
        // Setting the power of electric pokemon triple because of powerUP if it is available
        if(m_electricPokemon->getStateOfPowerUP()) amount_of_damage_of_electric=3;
        else amount_of_damage_of_electric = 1;

        // Setting the power of psychic pokemon double if it is in its own terrain
        if( m_psychicPokemon->isOwnTerrain(type_of_terrain_) ) amount_of_damage_of_psychic = 2;
        else amount_of_damage_of_psychic = 1;

        // Performing the fight according to the damaging pokemon first
        if(m_electricPokemon->getIsFirst()){  // Electric pokemon goes first
            if(e_pokemon_can_damage_){         // Electric pokemon hits if it isn't confused
                m_psychicPokemon->setHP(amount_of_damage_of_electric * m_electricPokemon->getDamage()); 
            }
            if(!m_psychicPokemon->getFainted()){       // Psychic pokemon hits if it has not fainted
                m_electricPokemon->setHP(amount_of_damage_of_psychic * m_psychicPokemon->getDamage());
            }
        }
        else{  // Psychic pokemon goes first
            m_electricPokemon->setHP(amount_of_damage_of_psychic * m_psychicPokemon->getDamage());                       
            
            if(e_pokemon_can_damage_ && !m_electricPokemon->getFainted()){ // Electric pokemon hits if it isn't confused and it hasn't fainted
                m_psychicPokemon->setHP(amount_of_damage_of_electric * m_electricPokemon->getDamage());
            }
                            
        }

        // Electric pokemon will be confused if psychic pokemon initiated a powerUP because the terrain is not electric
        if( m_psychicPokemon->getStateOfPowerUP() && !m_electricPokemon->isOwnTerrain(type_of_terrain_) ) e_pokemon_can_damage_ = false;

        // Setting the pokemons' hp to zero if their hp dropped below zero not to show their hp as negative
        if(m_psychicPokemon ->getHP() < 0 ) m_psychicPokemon->setHP( m_psychicPokemon ->getHP() );
        if(m_electricPokemon ->getHP() < 0 ) m_electricPokemon->setHP( m_electricPokemon ->getHP() );

        // Printing round statistics 
        printRoundStats(number_of_round,sim_heads);
        
        // Counting the time of recharching of pokemons
        if( m_electricPokemon->getStateOfPowerUP() ){
            
            m_electricPokemon->setStateOfPowerUP(false);
            m_electricPokemon->setCanPowerUP(false);
            e_pokemon_powerUp_counter++;
            
            if( e_pokemon_powerUp_counter == m_electricPokemon->getRecharge() ){
                m_electricPokemon->setCanPowerUP(true);
                e_pokemon_powerUp_counter = 0;
            }
        }
        if (m_psychicPokemon->getStateOfPowerUP( )){
            
            m_psychicPokemon->setStateOfPowerUP(false);
            m_psychicPokemon->setCanPowerUP(false);
            p_pokemon_powerUp_counter++;

            if( p_pokemon_powerUp_counter == m_psychicPokemon->getRecharge() ){
                p_pokemon_powerUp_counter = 0;
                m_psychicPokemon->setCanPowerUP(true);
            }
        }
        
        // Counting the time of the confusion of electric pokemon 
        if(!e_pokemon_can_damage_){
            e_pokemon_damage_counter++;
            if(e_pokemon_damage_counter == 4) e_pokemon_can_damage_ = true;
        }
        number_of_round++;    
    }
    cout<<"\n\n";
    printMatchResults();  // Printing match results  
    deletePokemons();     // Deleting fighting pokemons so that new pokemons can enter
}
void Arena::deletePokemons(){
    // Equalizing the pokemon pointers to NULL to get new pokemons and reseting the number of pokemons existing in the arena
    m_electricPokemon = nullptr;
    m_psychicPokemon  = nullptr;
    number_of_pokemon_ = 0;
}
Arena::~Arena(){
    // Deleting the pokemon pointers to prevent memory leak
    delete m_electricPokemon;
    delete m_psychicPokemon;
}