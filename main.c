#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define dim 10

typedef enum {
    false, true
} bool;

typedef char name[40];
typedef name *splitFrom; // puntatore  a nome di un membro


typedef struct member {
    name memberID;
    splitFrom *split;//array di puntatore a nome di membri
    int splitSize;
};

char addMember(char fromUsr) {


}

void addsplit(struct member currentMember) {

}

struct member *addPairs(int numberPairs) {
    char line[100];
    char memberOne[40], memberTwo[40];
    bool insertOne, insertTwo;
    int currentPos = 0;
    struct member *testMembers = malloc(numberPairs * 2 *
                                        sizeof(struct member));//al messimo ho il numero di membri pari al doppio del numeor di coppie

    for (int i = 0; i < numberPairs ; ++i) {
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
            currentPos++;

            //member two
            strcpy(testMembers[currentPos].memberID, memberTwo);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[currentPos - 1].memberID;
            testMembers[currentPos].splitSize = 1;
            currentPos++;

        }
        //aggiugere primo membro,secondo gia presente
        if (insertOne == true && insertTwo == false) {
            //member one
            strcpy(testMembers[currentPos].memberID, memberOne);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[posTwo].memberID;
            testMembers[currentPos].splitSize = 1;
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
        printf("primo membro: %s split from: ", &currentCaseMembers[0].memberID);
        for (int i = 0; i < currentCaseMembers[0].splitSize; ++i) {
            printf("%s\t", currentCaseMembers[0].split[i]);
        }
        printf("\n secondo membro: %s split from ", &currentCaseMembers[1].memberID);
        for (int i = 0; i < currentCaseMembers[1].splitSize; ++i) {
            printf("%s\t", currentCaseMembers[1].split[i]);
        }
    }
    return 0;
}