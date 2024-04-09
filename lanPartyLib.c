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

    printTeams(head, out);
    
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

    for(int i = 0; i < nrEchipe; i++) {
        Node *newElem = malloc(sizeof(Node));

        int nrMembrii;
        fscanf(readFile, "%d", &nrMembrii);

        char bufferNumeEchipa[30];
        fgets(bufferNumeEchipa, sizeof(bufferNumeEchipa), readFile);
        processFGETS(bufferNumeEchipa);
        char *numeEchipa = malloc(strlen(bufferNumeEchipa) + 1);
        strcpy(numeEchipa, bufferNumeEchipa);

        Player *players = malloc(nrMembrii * sizeof(Player));

        for(int u = 0; u < nrMembrii; u++) {
            char bufferFirstName[30], bufferLastName[30];
            int score;
            fscanf(readFile, "%s %s %d", bufferFirstName, bufferLastName, &score);

            players[u].firstName = malloc(strlen(bufferFirstName) + 1);
            strcpy(players[u].firstName, bufferFirstName);

            players[u].secondName = malloc(strlen(bufferLastName) + 1);
            strcpy(players[u].secondName, bufferLastName);

            players[u].points = score;
        }

        newElem->val.nume = numeEchipa;
        newElem->val.nrMembrii = nrMembrii;
        newElem->val.players = players;
        newElem->next = head->next;
        head->next = newElem;
    }

    fclose(readFile);
}


void printTeams (Node *head, char out[]) {
    FILE* writeFile = fopen(out, "w");
    if(writeFile == NULL) {
        printf("Could not open file %s", writeFile);
        exit(1);
    }
    head=head->next;
    while (head->next != head) {
       
        //fprintf(writeFile, "%s cu %d membrii\n" , head->val.nume, head->val.nrMembrii );
        fprintf(writeFile, "%s\n" , head->val.nume);
        head=head->next;
    }

    fclose(writeFile);
}

void processFGETS(char *str) {

    trimNewline(str);

    int len = strlen(str);
    
    if (len >= 2) {
        for (int i = 0; i < len - 1; i++) {
            str[i] = str[i + 1];
        }
        
        str[len - 1] = '\0';
    }
}

void trimNewline(char* str) {
    int len = strlen(str);
    if(len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0'; // Replace the newline with a null terminator
    }
}