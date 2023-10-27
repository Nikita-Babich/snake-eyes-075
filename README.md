# Snake-Eyes simulations
Context: https://manifold.markets/dreev/is-the-probability-of-dying-in-the 

 For the purpose of making simultions not overflow population and be completed in short time, the 1/36 chance of deathroll is replaced with 0.75. That is done because 1/36 is an arbitrary number, which does not affect how the problem is solved. For the probability of deathroll equal to 0.75 NO solution predicts 0.91 chance of death, and YES party predicts 0.75 chance of death, some participants of the market predict 0.5.

 This program shows, that all 3 answers mentioned in the Snake-Eyes market discussions can be achieved with different simulations. I made the setting of each simulation correspond to how the party sees the question. Because of the fact, that predicted values were achieved by simulations, it is likely that neither party did a mathematical mistake (or did self-annihilating couples/sets of mistakes).

 ## Simulation 1
 Instead of making random drafts from the pool between rounds, the population is shuffled. Euclid is assigned a random integer, representing his position in the queue. (The problem with this approch is that we know his potential round even before the game begins. We know the future: that he will not be drafted in the first several rounds whose index is smaller thn his potential round.)
 
 Game starts. When/if Euclid round comes, we immeditely zoom into, increment *chosen* and if deathroll happens, increment *dead*.
 This simulation gives an answer = 0.75 .

 ## Simulation 2
 Game is completed first. Then we acquire infromation, that Euclid was part of the game. We assume he is equiprobable to be any person (live or dead participant or not chosen). If he is not chosen, disqulify the run.
 This version outputs 0.5.
 *Fun fact*: this is the simulation which was actively pushed by YES community. How could they use something that outputs 0.5? They were making the simulation for 1/36 chance and thus were running out of pool, which immediately truncted insanely huge amounts of dead people, and they used "bounded-escape" principle to prevent disqualification of the run. Any kind of truncation leads to the answer immediately to snap towards p(deathroll). That can be esily illusrated if you imagine the point of truncation immediately after the first roll. Or by using python and raising the pool to 10^400 or higher - the answer snaps from p(deathroll) to 0.5 when pool is huge enough, so none of your millions of simulations hits the cap. The answer is also 0.5 if you just disqualify those out-of-people runs.

 ## Simulation 3
 This is my attempt to get rid of simulation 1 problem. 
 We do not know when Euclid will be chosen. The random draft happens only when it is needed by the game to continue. Every time people are taken from the pool, the pool is reduced.
Mathematiclly there is no difference between shuffle in advance an shuffling what is left before each draft: probability of Euclid being on any place is the same. But this version is closer to the game setting and to common sense of the order of getting information.
 
 This simultion outputs 0.75, but does not assume, that we know when Euclid will be chosen; no information from the future.

 ## Simulation 4
 Game is completed first. Then we acquire infromation, that Euclid was part of the chosen people in that run.
 Outputs 0.91.

 # My conclusions
 I've got all 3 answers, which hints, that all 3 groups have not made mathematical mistakes and were solving correctly according to their interpretation of the market question.
 1. 0.5 - The game is complete. Euclid being chosen is a given fact. From the point of algorithm it simulates general "Euclid is chosen", without specification to which round he was chosen.
 2. 0.75 - The game has not started yet. Euclid might be or not be chosen. Prediction conditioned on a not guaranteed event. From the point of algorithm it simulates "Euclid is chosen into the current round". Current relative to the point of time when the question was asked. 
 3. 0.91 - The game has not started yet. But we know due to some reasons he will be chosen, ie Euclid being chosen is a given fact. Prediction conditioned upon a guaranteed event. Simulates "game is rigged to guarantee, that Euclid is chosen every game".

    I suspect that the difference in interpretations between 0.75 and 0.91 is the pair: "given", "conditioned upon". In american interpretation those have identical meaning, while in european use of "given" some fact is mentioned.

How can participation be a guaranteed event? Throw the dice first until snake eyes and look how many people you will need. Take Euclid and other people in the amount to fill the rounds. Randomly distribute them into round-groups and declare which group is dead. It is easily organisable, but does not match the order of drafts and throws given in the game algorithm.
 
# My current position
My opinion changed from 0.91 to 0.5.
I still think that YES calculations are incorrect and recommend reading Fintan's paper.
