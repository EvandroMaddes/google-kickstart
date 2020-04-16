#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define dim 10

typedef enum {
    false, true
} bool;

typedef enum {
    red, blue, white
} type;

//name of each member
typedef char name[40];

// puntatore  a nome di un membro
typedef name *splitFrom;

//each member has a name, a list of "enemy" members and the size of this last list 
typedef struct member {
    name memberID;
    splitFrom *split;//array di puntatore a nome di membri
    int splitSize;
    type color;
};

//Following is a simple algorithm to find out whether a given graph is Birpartite or not using Breadth First Search (BFS).
//1. Assign RED color to the source vertex (putting into set U).
//2. Color all the neighbors with BLUE color (putting into set V).
//3. Color all neighbor’s neighbor with RED color (putting into set U).
//4. This way, assign color to all vertices such that it satisfies all the constraints of m way coloring problem where m = 2.
//5. While assigning colors, if we find a neighbor which is colored with same color as current vertex, then the graph cannot be colored with 2 vertices (or graph is not Bipartite)
bool isBipartite() {
    int c = 0;
    return true;
}

//for each test this function adds the members and thier relations to the data structure
struct member *addPairs(int numberPairs) {
    char line[100];
    char memberOne[40], memberTwo[40];
    bool insertOne, insertTwo;
    int currentPos = 0;
    struct member *testMembers = malloc(numberPairs * 2 *
                                        sizeof(struct member));//al messimo ho il numero di membri pari al doppio del numeor di coppie

    for (int i = 0; i < numberPairs; ++i) {
        insertOne = true;
        insertTwo = true;
        int posOne = 0, posTwo = posOne + 1;
        fgets(line, 90, stdin);
        sscanf(line, "%s %s", &memberOne, &memberTwo);
        //Cerco se i membri della riga ccorrente sono gia presenti nell'array
        for (int j = 0; j < currentPos; ++j) {
            if (strcmp(testMembers[j].memberID, memberOne) == 0) { //Se è gia presente nell'array
                insertOne = false;
                posOne = j;
            }
            if (strcmp(testMembers[j].memberID, memberTwo) == 0) { //Se è gia presente nell'array
                insertTwo = false;
                posTwo = j;
            }
        }

        //4 possibili casi
        //aggiungere entrambi
        if (insertOne == true && insertTwo == true) {
            //member one
            strcpy(testMembers[currentPos].memberID, memberOne);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[currentPos + 1].memberID;
            testMembers[currentPos].splitSize = 1;
            testMembers[currentPos].color = white;
            currentPos++;

            //member two
            strcpy(testMembers[currentPos].memberID, memberTwo);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[currentPos - 1].memberID;
            testMembers[currentPos].splitSize = 1;
            testMembers[currentPos].color = white;
            currentPos++;

        }
        //aggiugere primo membro,secondo gia presente
        if (insertOne == true && insertTwo == false) {
            //member one
            strcpy(testMembers[currentPos].memberID, memberOne);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[posTwo].memberID;
            testMembers[currentPos].splitSize = 1;
            testMembers[currentPos].color = white;
            currentPos++;
            //member two
            testMembers[posTwo].split[testMembers[posTwo].splitSize] = &testMembers[currentPos - 1].memberID;
            testMembers[posTwo].splitSize++;
        }
        //aggiungere secondo membro
        if (insertOne == false && insertTwo == true) {
            //member one
            testMembers[posOne].split[testMembers[posOne].splitSize] = &testMembers[currentPos].memberID;
            testMembers[posOne].splitSize++;
            //member two
            strcpy(testMembers[currentPos].memberID, memberTwo);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[posOne].memberID;
            testMembers[currentPos].splitSize = 1;
            testMembers[currentPos].color = white;
            currentPos++;
        }
        //aggiungere solo relazione
        if (insertOne == false && insertTwo == false) {
            //member one
            testMembers[posOne].split[testMembers[posOne].splitSize] = &testMembers[posTwo].memberID;
            testMembers[posOne].splitSize++;
            //member two
            testMembers[posTwo].split[testMembers[posTwo].splitSize] = &testMembers[posOne].memberID;
            testMembers[posTwo].splitSize++;
        }
    }

    return testMembers;
}

int main() {
    struct member *currentCaseMembers; //array contenente i membri de test case corrente
    int numberTest = 0;
    char line[100] = "init";
    while (line != EOF) {
        fgets(line, 90, stdin);
        sscanf(line, "%d", &numberTest);
        currentCaseMembers = addPairs(numberTest);
        printf("primo membro: %s; color: %d split from: ", &currentCaseMembers[0].memberID,
               currentCaseMembers[0].color);
        for (int i = 0; i < currentCaseMembers[0].splitSize; ++i) {
            printf("%s\t", currentCaseMembers[0].split[i]);
        }
        printf("\n secondo membro: %s split from ", &currentCaseMembers[1].memberID);
        for (int i = 0; i < currentCaseMembers[1].splitSize; ++i) {
            printf("%s %d\t", currentCaseMembers[1].split[i], currentCaseMembers[1].split[i]);
        }
    }
    return 0;
}
