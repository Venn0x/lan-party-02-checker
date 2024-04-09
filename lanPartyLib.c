#include <stdio.h>
#include <stdlib.h>

#include "lanPartyLib.h"

void readTasks(char cerinte[], char date[], char out[]){
    //printf("%s", cerinte);
    FILE* tasksFile = fopen(cerinte, "r");
    if(tasksFile == NULL) {
        printf("Could not open file %s", cerinte);
        exit(1);
    }

    //Create list
    Node *head = (Node*) malloc(sizeof(Node));
    Node *z= malloc(sizeof(Node));
    z -> next = z;
    head -> next = z;


    for(int i = 1; i <= 5; i++) {
        int useTask;
        fscanf(tasksFile, "%d", &useTask);

        if(!useTask) continue;

        switch(i) {
            case 1: {
                processTask1(date, head, z);
                break;
            }
        }
    }

    printTeams(head);
    
    fclose(tasksFile);
}

void processTask1(char pathDate[], Node *head, Node *z) {

    FILE* readFile = fopen(pathDate, "r");
    if(readFile == NULL) {
        printf("Could not open file %s", pathDate);
        exit(1);
    }

    int nrEchipe;
    fscanf(readFile, "%d", &nrEchipe);
    printf("Nr echipe %d\n\n", nrEchipe);
    Node *iter;
    iter = head;

    for(int i = 0; i < nrEchipe; i++) {
        Node *nextElem = malloc(sizeof(Node));

        int nrMembrii;
        fscanf(readFile, "%d", &nrMembrii);

        char bufferNumeEchipa[30];
        fgets(bufferNumeEchipa, sizeof(bufferNumeEchipa), readFile);
        //printf(" %d ", strlen(bufferNumeEchipa));
        //if(bufferNumeEchipa[strlen(bufferNumeEchipa) - 2] == "\n") bufferNumeEchipa[strlen(bufferNumeEchipa) - 2] = "\0";
        trimNewline(bufferNumeEchipa);
        removeFirstAndLast(bufferNumeEchipa);
        char *numeEchipa = malloc(strlen(bufferNumeEchipa) * sizeof(char));
        if (numeEchipa != NULL) {
            strcpy(numeEchipa, bufferNumeEchipa);
        }
        Player *players = malloc(nrMembrii * sizeof(Player));

        for(int u = 0; u < nrMembrii; u++) {
            char bufferFirstName[30], bufferLastName[30];
            int score;
            fscanf(readFile, "%s %s %d", bufferFirstName, bufferLastName, &score);

            players[u].firstName = malloc(strlen(bufferFirstName) + 1);
            if (players[u].firstName != NULL) {
                strcpy(players[u].firstName, bufferFirstName);
            }

            players[u].secondName = malloc(strlen(bufferLastName) + 1);
            if (players[u].secondName != NULL) {
                strcpy(players[u].secondName, bufferLastName);
            }

            players[u].points = score;
        }

        nextElem->val.nume = numeEchipa;
        nextElem->val.nrMembrii = nrMembrii;
        nextElem->val.players = players;
        nextElem -> next = iter -> next;
        iter->next = nextElem;
        iter = nextElem;
    }
            
    iter->next = z;

}

void printTeams (Node *head) {
    head=head->next;
    while (head->next != head) {
        for(int i = 0; i < strlen(head->val.nume); i++) {
            printf("|%c| ", head->val.nume[i]);
        }
        printf("\n");
        ///printf( "%s cu %d membrii\n" , head->val.nume, head->val.nrMembrii );
        head=head->next;
    }
}

void removeFirstAndLast(char *str) {
    int len = strlen(str);
    
    // Check if the string has at least two characters
    if (len >= 2) {
        // Shift characters to the left to remove the first character
        for (int i = 0; i < len - 1; i++) {
            str[i] = str[i + 1];
        }
        
        // Replace the last character with null terminator to effectively remove it
        str[len - 1] = '\0';
    }
}

void trimNewline(char* str) {
    int len = strlen(str);
    if(len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0'; // Replace the newline with a null terminator
    }
}