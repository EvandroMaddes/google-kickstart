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
typedef struct member *splitFrom;

//each member has a name, a list of "enemy" members and the size of this last list
typedef struct member {
    name memberID;
    splitFrom *split;//array di puntatore a nome di membri
    int splitSize;
    type color;
};
/*+++++++++++++++++++++++++++++++++++ FUNCTION +++++++++++++++++++++++++++++++++++++++++++*/
/**
 * Push into the heap policy FIFO
 */
splitFrom *push(splitFrom *heap, struct member *member, int size) {
    heap[size] = member;
    return heap;
}

/**
 * Pop from the heap policy FIFO
 */
splitFrom *pop(splitFrom *heap, int size) {
    heap[size] = NULL;
    return heap[size];
}

//Following is a simple algorithm to find out whether a given graph is Birpartite or not using Breadth First Search (BFS).
//1. Assign RED color to the source vertex (putting into set U).
//2. Color all the neighbors with BLUE color (putting into set V).
//3. Color all neighbor’s neighbor with RED color (putting into set U).
//4. This way, assign color to all vertices such that it satisfies all the constraints of m way coloring problem where m = 2.
//5. While assigning colors, if we find a neighbor which is colored with same color as current vertex, then the graph cannot be colored with 2 vertices (or graph is not Bipartite)
//todo push primo elemento
//todo while heap vuoto
//todo pop
//todo per ogni split del membro corrente
//todo controlli su self loop o loop infiniti
//todo if stesso colore del padre uscire
//todo else assegnare il colore opposto a qeullo del padre
//todo push memmbro
//todo fine for
//todo fine while
//todo return true

bool isBipartite(struct member *members, int size) {
    splitFrom *heap = malloc(dim * dim * sizeof(splitFrom));
    int heapSize = 0;
    struct member *curMember;
    bool selfLoop = false;

    //push first member
    members[0].color = red;
    //push primo elemento
    heap[heapSize] = &members[0];
    heapSize++;
    do {
        //pop member form the heap
        curMember = ((struct member *) heap[heapSize - 1]);
        heapSize--;

        for (int i = 0; i < curMember->splitSize; i++) {
            struct member *curChildMember = ((struct member *) curMember->split[i]);
            bool toPush = true;
            //se stesso colore del padre allora i grafo non puo essere bipartito
            //todo esaminare caso di loop a->b->a->b ... usare il colore bianco: WHITE

            if (curMember->color == curChildMember->color) {
                free(heap);
                return false;
            } else {
                if (curChildMember->color == white) {
                    switch (curMember->color) {
                        case blue:
                            curChildMember->color = red;
                            break;
                        case red:
                            curChildMember->color = blue;
                            break;
                    }

                } else { // gia stato visitato almeno una volta
                    toPush = false;
                }
            }
            //iNSERIMENTO IN TESTA
            if (toPush) {
                for (int j = heapSize; j > 0; j--) {
                    heap[j] = heap[j - 1];
                }
                //push del membro corrente
                heap[0] = curChildMember;
                heapSize++;
            }

        }

    } while (heapSize != 0);
    free(heap);
    return true;

}

/**
 * For each test this function adds the members and their relations to the data structure
 */
bool addPairs(int numberPairs) {
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
            if (strcmp(testMembers[j].memberID, memberOne) == 0) { //Se gia presente nell'array
                insertOne = false;
                posOne = j;
            }
            if (strcmp(testMembers[j].memberID, memberTwo) == 0) { //Se gia presente nell'array
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
            testMembers[currentPos].split[0] = &testMembers[currentPos + 1];
            testMembers[currentPos].splitSize = 1;
            testMembers[currentPos].color = white;
            currentPos++;

            //member two
            strcpy(testMembers[currentPos].memberID, memberTwo);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[currentPos - 1];
            testMembers[currentPos].splitSize = 1;
            testMembers[currentPos].color = white;
            currentPos++;

        }
        //aggiugere primo membro,secondo gia presente
        if (insertOne == true && insertTwo == false) {
            //member one
            strcpy(testMembers[currentPos].memberID, memberOne);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[posTwo];
            testMembers[currentPos].splitSize = 1;
            testMembers[currentPos].color = white;
            currentPos++;
            //member two
            testMembers[posTwo].split[testMembers[posTwo].splitSize] = &testMembers[currentPos - 1];
            testMembers[posTwo].splitSize++;
        }

        //aggiungere secondo membro
        if (insertOne == false && insertTwo == true) {
            //member one
            testMembers[posOne].split[testMembers[posOne].splitSize] = &testMembers[currentPos];
            testMembers[posOne].splitSize++;
            //member two
            strcpy(testMembers[currentPos].memberID, memberTwo);
            testMembers[currentPos].split = malloc(dim * sizeof(splitFrom));
            testMembers[currentPos].split[0] = &testMembers[posOne];
            testMembers[currentPos].splitSize = 1;
            testMembers[currentPos].color = white;
            currentPos++;
        }
//aggiungere solo relazione
        if (insertOne == false && insertTwo == false) {
            //member one
            testMembers[posOne].split[testMembers[posOne].splitSize] = &testMembers[posTwo];
            testMembers[posOne].splitSize++;
            //member two
            testMembers[posTwo].split[testMembers[posTwo].splitSize] = &testMembers[posOne];
            testMembers[posTwo].splitSize++;
        }
    }
    bool result = isBipartite(testMembers, currentPos);
    free(testMembers);
    return result;
}

void printResult(bool result, int caseNumber) {
    printf("Case #%d: %s", caseNumber, result ? "Yes" : "No");
}

int main() {
    int pairNumber = 0, testNumber = 0, count = 0;
    char line[100] = "init";
    fgets(line, 90, stdin); //number of tests
    sscanf(line, "%d", &testNumber);
    while (testNumber != count) {
        count++;
        fgets(line, 90, stdin);
        sscanf(line, "%d", &pairNumber);
        bool result = addPairs(pairNumber);
        printResult(result, count);
        if (testNumber != count ){
            fputs("\n",stdout);
        }
    }
    return 0;
}
