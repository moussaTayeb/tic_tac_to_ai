#include <stdio.h>
#include <stdbool.h>
#define HUMAN 'X'
#define AI 'O'



void board(char *pos)
{
    system("clear");
    printf("\tTic-Tac-Toe\n\n");
        printf("\n\n");
    printf("\n\n");
      
    printf("\t\t\t  %c | %c  | %c  \n", pos[0],
                             pos[1], pos[2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n", pos[3],
                             pos[4], pos[5]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n\n", pos[6],
                             pos[7], pos[8]);
    
}

void playerDecision(char *pos){
    int position;
    printf("enter a position from 1 to 9: ");
    scanf("%d", &position);
    if (position >= 9){
        printf("the position is out of range :/\n");
        playerDecision(pos);
    }
    if (pos[position] == NULL){
        pos[position] = HUMAN;
        board(pos);
    }
    else{
        printf("this place is allready taken, choose another position\n");
        playerDecision(pos);
    }
}



bool checkGamePlayer(char *pos){
    //Horizental check

    if(pos[0] != NULL && pos[0] != 0 && pos[0] == pos[1] && pos[1] == pos[2] && pos[0] == HUMAN){
        return true;
    }else if(pos[3] != NULL && pos[3] != 0 && pos[3] == pos[4] && pos[4] == pos[5] && pos[3] == HUMAN){
        return true;
    }
    else if(pos[6] != NULL && pos[6] != 0 && pos[6] == pos[7] && pos[7] == pos[8] && pos[6] == HUMAN){
        return true;
    }

    //Vertical check

    else if(pos[0] != NULL && pos[0] != 0 && pos[0] == pos[3] && pos[3] == pos[6] && pos[0] == HUMAN){
        return true;
    }else if(pos[1] != NULL && pos[1] != 0 && pos[1] == pos[4] && pos[4] == pos[7] && pos[1] == HUMAN){
        return true;
    }
    else if(pos[2] != NULL && pos[2] != 0 && pos[2] == pos[5] && pos[5] == pos[8] && pos[2] == HUMAN){
        return true;
    }

    //diagonal check

    else if(pos[0] != NULL && pos[0] != 0 && pos[0] == pos[4] && pos[4] == pos[8] && pos[0] == HUMAN){
        return true;
    }else if(pos[2] != NULL && pos[2] != 0 && pos[2] == pos[4] && pos[4] == pos[6] && pos[2] == HUMAN){
        return true;
    }
}

bool checkGameAI(char *pos){
    if(pos[0] != NULL && pos[0] != 0 && pos[0] == pos[1] && pos[1] == pos[2] && pos[0] == AI){
        return true;
    }else if(pos[3] != NULL && pos[3] != 0 && pos[3] == pos[4] && pos[4] == pos[5] && pos[3] == AI){
        return true;
    }
    else if(pos[6] != NULL && pos[6] != 0 && pos[6] == pos[7] && pos[7] == pos[8] && pos[6] == AI){
        return true;
    }

    //Vertical check

    else if(pos[0] != NULL && pos[0] != 0 && pos[0] == pos[3] && pos[3] == pos[6] && pos[0] == AI){
        return true;
    }else if(pos[1] != NULL && pos[1] != 0 && pos[1] == pos[4] && pos[4] == pos[7] && pos[1] == AI){
        return true;
    }
    else if(pos[2] != NULL && pos[2] != 0 && pos[2] == pos[5] && pos[5] == pos[8] && pos[2] == AI){
        return true;
    }

    //diagonal check

    else if(pos[0] != NULL && pos[0] != 0 && pos[0] == pos[4] && pos[4] == pos[8] && pos[0] == AI){
        return true;
    }else if(pos[2] != NULL && pos[2] != 0 && pos[2] == pos[4] && pos[4] == pos[6] && pos[2] == AI){
        return true;
    }
}

bool checkGame(char *pos, bool *draw){
    bool ai = checkGameAI(pos);
    bool human = checkGamePlayer(pos);
    if(ai){
        return false;
    }else if(human){
        return false;
    }
     else if(!ai && !human){
        for (int i =0 ; i< 9; i++){
            if(pos[i] == NULL){
                *draw = false;
            }
        }
    }else{
        return true;
    }

}

int minimax(char *pos, int depth, bool isMaximazing, bool *draw){
    if (!checkGameAI(pos)){
        return -1;
    }
    if (!checkGamePlayer(pos)){
        return 1;
    } else if(*draw){
        return 0;
    }
    if(isMaximazing){
        int bestScore = -1000;
        for(int i = 0; i<9; i++){
            if(pos[i] == NULL){
                pos[i] = AI;
                int score = minimax(pos, depth +1, false, draw);
                pos[i] = NULL;
                if(score > bestScore){
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }
    else{
        int bestScore = 1000;
        for(int i = 0; i<9; i++){
            if(pos[i] == NULL){
                pos[i] = HUMAN;
                int score = minimax(pos, depth +1, true, draw);
                pos[i] = NULL;
                if(score > bestScore){
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }


}

void whoWon(char *pos){
    bool ai = checkGameAI(pos);
    bool human = checkGamePlayer(pos);
    if(ai && !human){
        printf("AI has won :) \n");
    }else if(human && !ai){
        printf("HUMAN has won :) \n");
    }
}

void machineDecision(char *pos, bool *draw){
    int bestScore = -1000;
    int bestMove;
    for(int i = 0; i<9; i++){
        if(pos[i] == NULL){
            pos[i] = AI;
            int score = minimax(pos, 0, false, draw);
            pos[i] = NULL;
            if(score > bestScore){
                bestScore = score;
                bestMove = i;
            }
        }
    }
    if (pos[bestMove] == NULL){
        pos[bestMove] = AI;
        board(pos);
    }
    else{
        machineDecision(pos, &draw);
    }

}



int main(){
    bool draw = false;
    char winner[20];
    char pos[9];
    for(int i =0; i<9; i++){
        pos[i] = NULL;
    }
    bool game = true;
    while (game && !draw){
        playerDecision(pos);
        game = checkGame(pos, &draw);
        machineDecision(pos, &draw);
        game = checkGame(pos, &draw);
        printf("\n%d \n%d", game, draw);
        board(pos);
    }
    printf("game ended");
    
    
    return 0;
}