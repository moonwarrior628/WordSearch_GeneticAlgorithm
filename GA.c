/*This GA code is based on the word search code posted by geeksforgeeks.
The inspired code was performed in the language of python which I'm not a Guru at.
Hence I translated or modified the code basics into my own simpler C language.
The code is highly modified and is quite different from what was used as inspiration.
There were many functions which python just breathed and it existed while the language
of C or any other language is far more intricate than just typing magic words to get work done.

The link form which this code was inspired from is given below:
https://www.geeksforgeeks.org/genetic-algorithms/

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//This is the size of the population. As in 100 genomes will be created every generation.
#define POPULATION_SIZE 100




/*This GLOBAL array consists of genes that make up a single
genome. All are lower case for simplicity and a space
character is added for a sentence*/
char GENES[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','\0'};
/*This the length of the above GENES array. This can be
modified depending on the above array*/
int length_GENES = 27;

//Target phrase that is of the user's choice
char targetPhrase[] = "easy as it seems";
//Length of the target phrase
int length_targetPhrase = 16;

    /*This function makes a single gene as in a single character
    and it is made random (taken from the GENES array, a single
    character will be made)It returns a single random character form the GENES array */
    char random_gene(){

        //Define randomNum variable to produce a random number
        int randomNum = (rand()% (length_GENES +1)) ;
        //Create a new variable gene that assigns the random number generated to a character in the GENES array.
        char gene = GENES[randomNum];
        //printf("%c", gene);

        return gene;
    }

    /*This void function that does not return any value and
    creates a phrase consisting of characters from the GENES
    array.The phrase created is stored in the function variable
    phrase.*/
    void create_phrase(char phrase[length_targetPhrase]){

        //Variable i is defined to be used in the for loop
        int i;
        /*This for loop is creating a single phrase which is
        the length of the target phrase. Each loop, a single
        random character is filled in the phrase array until
        it hits the target phrase length*/
        for (i = 0; i<length_targetPhrase; i++){

            phrase[i] = random_gene();
        }
    }

    /*This function is responsible for creating children out
    of the genomes. The parents variable will be used in
    other functions. While the child_phrase variable contains
    the mated child. This function also determines the mutation
    process.Currently the randomness of creating random child
    phrases is set to 3%. The parent 1 will have 45% chance
    of mating while parent 2 has 50% chance of mating.*/
    void mate(char parent1[length_targetPhrase], char parent2[length_targetPhrase], char child_phrase[length_targetPhrase]){

        int i;
        /*This for loop goes through the length of the target
        phrase filling each character in the phrase either from
        parent 1, parent 2 or random. */
        for (i=0; i<length_targetPhrase; i++){

            //Prob is a variable where a random number will be stored ranging from 0-99.
            int prob;
            prob = rand()% 100;

            //If probability is from 0% to 45%, child's gene will be made from parent 1
            if (prob < 45){
                child_phrase[i]= parent1[i];
            }
            //If probability is from 46% to 95%, child's  will be made from parent 2
            else if (prob < 95){
                child_phrase[i]= parent2[i];
            }
            //Otherwise the child's gene will be made through the random gene
            else{
                child_phrase[i]= random_gene();
            }
        }
    }

   /*This function calculates the fitness score of each phrase
   in the population. The fitness score in this program is calculated
   based on how not close is the phrase from the correct answer.
   Each letter if not equal to the target phrase contributes to
   addition of fitness score (+1). For example: the target phrase's
   fitness score will be 0. This function returns fitness score. When
   this function is called, the fitness score is calculated of the
   phrases from population. The chk_phrase array holds the phrase
   from the population that needs to be checked. */
   int calc_fitness(char chk_phrase[length_targetPhrase]){

        //The fitness score is initialized to be 0.
        int fitness = 0;
        int i;
        //If the target phrase's each letter or space is not equal to the chk_phrase, fitness score increases.
        for (i = 0; i<length_targetPhrase; i++){

            if (chk_phrase[i] != targetPhrase[i]){
                fitness = fitness + 1;
            }
        }

        return fitness;
   }

   /*This function sorts fitness score of the population. It deals
   with a 2D array that stores the index of the population and the
   score of the population. The for loop uses the technique of
   bubble sort to sort through the fitness score of population. The
   fitness_scores has the score of the population sorted in a
   increasing order of scores. The top being the best.*/
   void Sort_Fitness(int fitness_scores[POPULATION_SIZE][2]){

        int j;
        int i;
        int temp0;
        int temp1;
        /*The first loop runs through the size of population size
        which is 100 indexes of phrases. While the second loop
        runs through population_size -1 (99) times. This is because
        in the first loop the greatest number is already placed at
        the end.Its sorted in increasing order of fitness score.*/
        for (i = 0; i < POPULATION_SIZE - 1; i++){

            for (j = 0 ; j < POPULATION_SIZE  - i - 1; j++){

                if(fitness_scores[i][0] > fitness_scores[i+1][0]){

                    temp0 = fitness_scores[i][0];
                    temp1 = fitness_scores[i][1];

                    fitness_scores[i][0] = fitness_scores[i+1][0];
                    fitness_scores[i][1] = fitness_scores[i+1][1];

                    fitness_scores[i+1][0] = temp0;
                    fitness_scores[i+1][1] = temp1;
                }
            }
        }
   }


/*This is the main function where population is created over and over and other
functions are called to create phrases and sort them.*/
int main(){

    //This is a 2D int array that holds the fitness scores of the respective indexes of the phrases.
    int population_fitness_scores[POPULATION_SIZE][2];
    //This is a 2D char array that holds the phrases of the population.
    char population[POPULATION_SIZE][length_targetPhrase];
    //Uses current time for random number generator
    srand(time(0));


    //The current generation is initialized to 1.
    int generation = 1;
    //This value will be used to stop the program when the target phrase is found.
    int found_value = 0;

    //This is the phrase array that holds a single phrase.
    char phrase[length_targetPhrase+1];
    phrase[length_targetPhrase] = '\0';

    //Variable i and j are defined t be used in for loops
    int i;
    int j;
    //Variable m is defined as 10% of the population_size.
    int m;

    /*This for loop is creating 100 phrases thereby
    filling up the population array. The create_phrase
    function is called where a phrase is created and
    this phrase is then populated into the population
    array in the inner loop. The inner loop is
    populating each character by character of the
    current phrase.*/
    for(i=0; i < POPULATION_SIZE; i++){
        create_phrase(phrase);

        for(j=0; j< length_targetPhrase; j++){
            population[i][j] = phrase[j];
        }
    }

    //These are parent 1 and 2 char array variables that will be used to populate the population
    char parent1[length_targetPhrase];
    char parent2[length_targetPhrase];
    //These variables are created to create parent 1
    int random_Quart_Num_P1;
    int Select_phrase_index_P1;
    //These variables are created to create parent 2
    int random_Quart_Num_P2;
    int Select_phrase_index_P2;

    //Stores the index of a phrase that we will use later
    int Index_of_phrase;
    //Used to print the results
    int var;

    /*This while loop runs until the target phrase is found which
    means fitness score is 0. Meanwhile it creates new generation
    of population until the answer is found.*/
    while (found_value == 0){

       /*This for loop is populating the ith array with
       fitness score (along with the respective phrase).
       The population fitness score is being filled with
       the calculated fitness score which is done by
       calling the calc_fitness function. The second line
       indicates that while fitness scores are being
       assigned, the index of the respective phrases are
       assigned with the same fitness score. */
       for(i=0; i< POPULATION_SIZE;i++){
            population_fitness_scores[i][0]= calc_fitness(population[i]);
            population_fitness_scores[i][1] = i;
       }

       //This function is called to sort phrases (w.r.t index) based on their fitness score
       Sort_Fitness(population_fitness_scores);

        /*This if statement determines if the target phrase
        is found, if it is found then the while loop breaks
        as in stops the program. Before that a statement
        indicating the generation number and target phrase
        and its fitness score is printed.Also, if the
        condition of the if statement is not met then the
        program runs otherwise to recreate population.*/
        if (population_fitness_scores[0][0] == 0){

            found_value = 1;
            printf("it is DOOONe\n");

            printf("Gen is: %d\t",generation);
            var = population_fitness_scores[0][1];
            for(i = 0; i<length_targetPhrase; i++){

                printf("%c", population[var][i]);
            }

            printf("\tfitness: %d\n",population_fitness_scores[0][0]);

            break;
        }

        //This variable is used to store the child phrase
        char child[length_targetPhrase+1];
        child[length_targetPhrase] = '\0';

        //Variable m is 10% of population rounded up to a whole number.
        m = (int)(round(POPULATION_SIZE/10));

        /*This for loop runs only 90 times and only begins
        from 11-100, reserving the top ten as the elite
        population which is kept for greater efficiency
        and not repopulated with new population. */
        for(i=m; i<POPULATION_SIZE; i++){

            /*These random number variables  generate from
            0-24 which means they are operating only on the
            24% of the population which is still the top
            population with good solutions. These numbers
            help make parents from a good gene.*/
            random_Quart_Num_P1 = rand()% (int)(round(POPULATION_SIZE/4));
            random_Quart_Num_P2 = rand()% (int)(round(POPULATION_SIZE/4));
            /*These variables assign the random number
            generated from above to the index of the fitness
            score array, thereby choosing a random phrase index
            from 0-24.*/
            Select_phrase_index_P1 = population_fitness_scores[random_Quart_Num_P1][1];
            Select_phrase_index_P2 = population_fitness_scores[random_Quart_Num_P2][1];
            /*The selected phrase index from above is then
            transferred to the population array and that
            single array then populates a parent character by
            character.*/
            for(j=0;j<length_targetPhrase;j++){

                parent1[j] = population[Select_phrase_index_P1][j];
            }

            for(j=0;j<length_targetPhrase;j++){

                parent2[j] = population[Select_phrase_index_P2][j];
            }
            /*Taking the above parents, the function of mate
            is called to create a new child.*/
            mate(parent1, parent2, child);
            //This variable is assigned to the ith array of ith phrase index
            Index_of_phrase = population_fitness_scores[i][1];

            //This for loop repopulates the new population array by using the child array.
            for(j=0;j<length_targetPhrase;j++){

                population[Index_of_phrase][j] = child[j];
            }
        }
        //This section is for printing out the results.
        //var variable stores the index of the best fit solution which is on the first row.
        var = population_fitness_scores[0][1];
        //prints the generation number which is when every time a population is created.
        printf("Gen is: %d\t",generation);
        /*This for loop prints each character of the best
        solution which is the target phrase. The var
        variable contains the index of the target phrase
        and i is each character of the target_phrase.*/
        for(i = 0; i<length_targetPhrase; i++){

            printf("%c", population[var][i]);
        }
        //This prints the fitness score of the first element of fitness score array.
        printf("\tfitness: %d\n",population_fitness_scores[0][0]);
        //This adds one generation after each run.
        generation += 1;
    }


 return 0;
}



