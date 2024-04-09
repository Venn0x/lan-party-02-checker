typedef struct {
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct {
    char *nume;
    int nrMembrii;
    Player *players;
} Echipa;

struct Elem {
    Echipa val;
    struct Elem *next;
};

typedef struct Elem Node;

void readTasks(char cerinte[], char date[], char out[]);