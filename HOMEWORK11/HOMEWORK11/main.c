

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/* MARK: - part1  */


int find_factor(int n){
    if (n == 0 || n == 1){
        return 1;
    }else
        return n * find_factor(n - 1);
}

int numPathsHome(int street, int avenue, int fact, int street2, int avenue2) {
//    int fact = find_factor(street + avenue);
    if (street == 0 && avenue == 0) {
        return fact/ (find_factor(street2) * find_factor(avenue2));
    }else  if( street != 0){
        return numPathsHome(street - 1, avenue,fact,street2 ,avenue2);
    }else {
        return numPathsHome(street, avenue - 1,fact,street2,avenue2 );
    }
}
/*MARK: - PART 2 */

typedef struct
{
char* name;
char citiesServed[3];
}Hospital;

/*MARK: - PART 3 */

typedef struct{
    const char *face;
    const char *suit;
} Card;

const char *faces[13] = {
    "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
    "Nine", "Ten", "Jack", "Queen", "King"
};
const char *suits[4] = {
    "Hearts", "Diamonds", "Clubs", "Spades"
};

void init_cards(Card deck[52]){
    int i, j , k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            deck[k].face = faces[j];
            deck[k].suit = suits[i];
            k++;
        }
        
    }
}
void shuffle_deck(Card deck[52]){
    int i = 0;
    Card temp;
    for (i = 0; i < 52; i++) {
        int rand_number = rand() % 52;
        temp = deck[i];
        deck[i] = deck[rand_number];
        deck[rand_number] = temp;
    }
}

void printDeck(Card deck[]) {
    int i;
    for ( i = 0; i < 52; i++) {
        printf("%5s of %-8s\n", deck[i].face, deck[i].suit);
    }
}


int main(int argc, const char * argv[]) {
    /* part 1*/
    int street_number, avenue_number;
    srand(time(0));
    printf("Enter the street number");
    scanf("%d",&street_number);
    printf("Enter the avenue number");
    scanf("%d",&avenue_number);
    int number_path = numPathsHome(street_number - 1, avenue_number - 1, find_factor(street_number + avenue_number - 2), street_number - 1, avenue_number - 1);
    printf("number of optimal paths to take back home %d\n", number_path);
    /* part 2 */
    char cities[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    char *locationss[][4] = {{"A", "B", "C", "\n"}, {"A", "C", "D", "\n"}, {"B", "F", "\n", "\0"}, {"C", "E", "F", "\n"}};

    char locations[][4] = {
        {'A', 'B', 'C', '\0'},
        {'A', 'C', 'D', '\0'},
        {'B', 'F', '\0'},
        {'C', 'E', 'F', '\0'}
      };
    /* part 3 */
    Card deck[52];
    init_cards(deck);
    printDeck(deck);
    printf("-----shufffffliiinggg----\n");
    shuffle_deck(deck);
    printDeck(deck);
    return 0;

}

