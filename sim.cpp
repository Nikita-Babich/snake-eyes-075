#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

//Round indexing goes from 0, so amount of people in  round N is 2^N.

//#define SPELL_OUT

const int population = 1048575; //2^20-1
const int wait_for_Euclids = 800;

int random_position(){
	//equivalent to assigning some index to each person in the pool 
	return rand() % population;
}

int deathroll(){ 
	//returns 1 with 75% chance, otherwise returns 0
	if(rand() % 4 < 3){
		return 1;
	} else {
		return 0;
	}
}

int general_deathroll(int a, int b){ // a/b chance
	if(rand() % b < a){
		return 1;
	} else {
		return 0;
	}
}

int is_Euclid_assigned_in_group_N(int N, int Euclid_index){ //N = round index
	// 1 23 4567 
	int lower_index = pow(2,N);
	int higher_index = pow(2,N+1)-1;
	return (lower_index <= Euclid_index & Euclid_index <= higher_index);
}

int is_Euclid_assigned_before_N(int N, int Euclid_index){ //N = round index
	int lower_index = pow(2,N);
	return (Euclid_index < lower_index);
}

void method1(){
	std::cout << "Method 1 starts. \n Generate an index for Euclid before the game. \n Look at Euclid immediately when his round if drafted.\n When the game starts we know exact round Euclid could be drafted into. \n";
	int pool_exhausted_counter = 0;
	int games_hosted = 0;
	int Euclid_chosen_counter = 0;
	int Euclid_dead_counter = 0;
	
	while (Euclid_chosen_counter < wait_for_Euclids){
		games_hosted++;
		int Euclid_index = random_position();
		
		int game_continues = 1;
		int round = -1;
		while(game_continues > 0){
			round++;
			if(round>19){
				pool_exhausted_counter++;
				game_continues = 0;
			}
			if ( is_Euclid_assigned_in_group_N(round, Euclid_index) ){
				Euclid_chosen_counter++;
				if(deathroll()){
					Euclid_dead_counter++;
					game_continues = 0;
				}
			} else {
				if(deathroll()){
					game_continues = 0;
				}
			}
		}
		#ifdef SPELL_OUT
		if(rand() == 0){
			std::cout << "Games hosted: " << games_hosted << "\t\t "<< Euclid_chosen_counter << "\n";
		}
		#endif
	}
	
	double result = Euclid_dead_counter / (double) Euclid_chosen_counter;
	std::cout << "Games hosted: " << games_hosted << ".\n";
	std::cout << "Games which exhausted the pool: " << pool_exhausted_counter << ".\n";
	std::cout << "Euclid was chosen " << Euclid_chosen_counter << " times.\n";
	std::cout << "Euclid ended up being dead " << Euclid_dead_counter << " times.\n";
	std::cout << "That gives us the following dead/chosen: " << result << " \n\n\n";
}

void method2(){
	
	std::cout << "Method 2 starts. \n Generate an index for Euclid before the game. \n Game finishes first and then we get the knowledge, which index Euclid had. \n When the game starts we know exact round Euclid could be drafted into.\n";
	int pool_exhausted_counter = 0;
	int games_hosted = 0;
	int Euclid_chosen_counter = 0;
	int Euclid_dead_counter = 0;
	
	while (Euclid_chosen_counter < wait_for_Euclids){
		games_hosted++;
		int Euclid_index = random_position();
		
		int game_continues = 1;
		int round = -1;
		int dead_round = -1; 
		while(game_continues > 0){
			round++;
			if(round>19){
				pool_exhausted_counter++;
				game_continues = 0;
				break;
			}
			if(deathroll()){
				dead_round = round;
				game_continues = 0;
			}
		}
		if ( is_Euclid_assigned_in_group_N(dead_round, Euclid_index) ){
			Euclid_chosen_counter++;
			Euclid_dead_counter++;
		}
		if (is_Euclid_assigned_before_N(dead_round, Euclid_index)){
			Euclid_chosen_counter++;
		}
		#ifdef SPELL_OUT
		if(rand() == 0){
			std::cout << "Games hosted: " << games_hosted << "\t\t "<< Euclid_chosen_counter << "\n";
		}
		#endif
	}
	
	double result = Euclid_dead_counter / (double) Euclid_chosen_counter;
	std::cout << "Games hosted: " << games_hosted << ".\n";
	std::cout << "Games which exhausted the pool: " << pool_exhausted_counter << ".\n";
	std::cout << "Euler was chosen " << Euclid_chosen_counter << " times.\n";
	std::cout << "Euler ended up being dead " << Euclid_dead_counter << " times.\n\n";
	std::cout << "That gives us the following dead/chosen: " << result << " \n\n\n";
}

/////////

int Is_Euclid_chosen_in_N(int round){
	//equivalent to choosing randomly from the pool right before each draft
	return ( rand() % (int)(population - (pow(2,round)-1)) ) < pow(2, round);
}

void method3(){
	
	std::cout << "Method 3 starts. \n Do NOT generate Euclid position in advance. Every draft is random. \n When the game starts we do not know which round he could be drafted. \n";
	int pool_exhausted_counter = 0;
	int games_hosted = 0;
	int Euclid_chosen_counter = 0;
	int Euclid_dead_counter = 0;
	
	while (Euclid_chosen_counter < wait_for_Euclids){
		games_hosted++;
		
		int game_continues = 1;
		int round = -1;
		while(game_continues > 0){
			round++;
			if(round>19){
				pool_exhausted_counter++;
				game_continues = 0;
			}
			if ( Is_Euclid_chosen_in_N(round) ){
				Euclid_chosen_counter++;
				if(deathroll()){
					Euclid_dead_counter++;
					game_continues = 0;
				}
			} else {
				if(deathroll()){
					game_continues = 0;
				}
			}
		}
		#ifdef SPELL_OUT
		if(rand() == 0){
			std::cout << "Games hosted: " << games_hosted << "\t\t "<< Euclid_chosen_counter << "\n";
		}
		#endif
	}
	
	double result = Euclid_dead_counter / (double) Euclid_chosen_counter;
	std::cout << "Games hosted: " << games_hosted << ".\n";
	std::cout << "Games which exhausted the pool: " << pool_exhausted_counter << ".\n";
	std::cout << "Euclid was chosen " << Euclid_chosen_counter << " times.\n";
	std::cout << "Euclid ended up being dead " << Euclid_dead_counter << " times.\n\n";
	std::cout << "That gives us the following dead/chosen: " << result << " \n\n\n";
}

void method4(){
	std::cout << "Method 4 starts. \n Game finishes first, then we get the knowledge, that Euclid was chosen into that game. \n We do not know which round he could be in.\n";
	int pool_exhausted_counter = 0;
	int games_hosted = 0;
	int Euclid_chosen_counter = 0;
	int Euclid_dead_counter = 0;
	
	while (games_hosted < wait_for_Euclids){
		games_hosted++;
		
		int game_continues = 1;
		int round = -1;
		int dead_round = -1; 
		while(game_continues > 0){
			round++;
			//players += pow(2,round);
			if(deathroll()){
				dead_round = round;
				game_continues = 0;
				break;
			}
		}
		int Euclid_index = rand() % (int)(pow(2,dead_round+1)-1); //he is equiprobably any of the chosen
		Euclid_chosen_counter++;
		int is_Euclid_dead = Euclid_index < pow(2,dead_round); //is he in the last group
		if (is_Euclid_dead){
			Euclid_dead_counter++;
		}
	}
	double result = Euclid_dead_counter / (double) Euclid_chosen_counter;
	std::cout << "Games hosted: " << games_hosted << ".\n";
	std::cout << "Games which exhausted the pool: " << pool_exhausted_counter << ".\n";
	std::cout << "Euclid was chosen " << Euclid_chosen_counter << " times.\n";
	std::cout << "Euclid ended up being dead " << Euclid_dead_counter << " times.\n\n";
	std::cout << "That gives us the following dead/chosen: " << result << " \n\n\n";
}

int main(){
	srand(time(NULL));
	method1();
	method2();
	method3();
	method4();
	
	std::cout << "Method 1 is how YES party sees the question. Probability is calculted for the widest probability space, where 'Being chosen' might or might not happen, is not part of the setup, is an info conditioned upon.\n ";
	std::cout << "Method 2 is how some commenters on Snake Eyes market see the question.\n ";
	std::cout << "The methods 1 and 2 are not quite correct, because there we know the future by knowing Euclid index.\n\n ";
	std::cout << "Method 3 is mathematically equivalent to 1 (additional shuffles do not affect the result), \n but technically does not recieve information from the future.\n";
	std::cout << "Method 4 is how NO party sees the question. 'Being chosen' is part of the setup, is given information.";
}