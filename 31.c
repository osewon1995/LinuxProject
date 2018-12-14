#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <time.h>

int game_num = 0; // 1~31
static int semid;

// start using semaphore
void p(){
    struct sembuf pbuf;

    pbuf.sem_num = 0;
    pbuf.sem_op = -1;
    pbuf.sem_flg = SEM_UNDO;

    if (-1 == semop(semid, &pbuf, 1))
        printf("p() error\n");
}

// stop using semaphore
void v(){
    struct sembuf vbuf;

    vbuf.sem_num = 0;
    vbuf.sem_op = 1;
    vbuf.sem_flg = SEM_UNDO;

    if(-1 == semop(semid, &vbuf, 1))
        printf("v() error\n");
}

void *gamer1(void *arg){
    p(); // start using semaphore
    int limit=0; // increase limit 3
    char us; // up or stop
    printf("\n\n\nUser1's turn\n");
    printf("GAME NUM = %d\n\n", game_num);
    while(1){
        printf("Press U to increase number\n");
        printf("Press P to turn end\n");
        scanf("%c", &us);
        getchar();
        if(us == 'U'){
            limit++;
            if(limit == 4){
                printf("\n\nToo much! Turn end\n");
                return NULL;
            } // stop when user trying to increase more than 4 times
            game_num++;
            printf("\nGAME NUM =  %d\n", game_num);
            if(game_num == 31){
                printf("User1 is Lose!\n");
                return NULL;
            }
        }
        else if(us == 'P')
            break;
    }
    v();
    return NULL;
}

void *gamer2(void *arg){
    p(); // start using semaphore
    int limit=0; // increase limit 3
    char us; // up or stop
    printf("\n\n\nUser2's turn\n");
    printf("GAME NUM = %d\n\n", game_num);
    while(1){
        printf("Press U to increase number\n");
        printf("Press P to turn end\n");
        scanf("%c", &us);
        getchar();
        if(us == 'U'){
            limit++;
            if(limit == 4){
                printf("\n\nToo much! Turn end\n");
                return NULL;
            } // stop when user trying to increase more than 4 times
            game_num++;
            printf("\nGAME NUM = %d\n", game_num);
            if(game_num == 31){
                printf("User2 is Lose!\n");
                return NULL;
            }
        }
        else if(us == 'P')
            break;
    }
    v();
    return NULL;
}

void *gamer3(void *arg){
    p(); // start using semaphore
    int limit=0; // increase limit 3
    char us; // up or stop
    printf("\n\n\nUser3's turn\n");
    printf("GAME NUM = %d\n\n", game_num);
    while(1){
        printf("Press U to increase number\n");
        printf("Press P to turn end\n");
        scanf("%c", &us);
        getchar();
        if(us == 'U'){
            limit++;
            if(limit == 4){
                printf("\n\nToo much! Turn end\n");
                return NULL;
            } // stop when user trying to increase more than 4 times
            game_num++;
            printf("\nGAME NUM = %d\n", game_num);
            if(game_num == 31){
                printf("User3 is Lose!\n");
                return NULL;
            }
        }
        else if(us == 'P')
            break;
    }
    v();
    return NULL;
}

void *gamer4(void *arg){
    p(); // start using semaphore
    int limit=0; // can increase to 4
    char us; // up or stop
    printf("\n\n\nUser4's turn\n");
    printf("GAME NUM = %d\n\n", game_num);
    while(1){
        printf("Press U to increase number\n");
        printf("Press P to turn end\n");
        scanf("%c", &us);
        getchar();
        if(us == 'U'){
            limit++;
            if(limit == 4){
                printf("Too much! Turn end\n");
                return NULL;
            } // stop when user trying to increase more than 4 times
            game_num++;
            printf("\nGAME NUM = %d\n", game_num);
            if(game_num == 31){
                printf("User4 is Lose!\n");
                return NULL;
            }
        }
        else if(us == 'P')
            break;
    }
    v();
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t user[3];
    int usr1, usr2, usr3, usr4;

    union semun{
        int val;
        struct semid_ds *buf;
        unsigned short int *array;
    } arg;

    if (-1 == (semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666))){
        printf("semget() error\n");
        return -1;
    }

    arg.val = 1; // set semaphore value to 1

    if (-1 == semctl(semid, 0, SETVAL, arg)){
        printf("set semctl() error\n");
        return -1;
    }

    int u_num;
    printf("\n\n**ë² ìŠ¤í‚¨ë\n\n\n");
    char choice;
    printf("\n\n\nìˆœì„œë¥¼ ì •í•©ë‹ˆë‹¤\n");
    printf("ë‚œìˆ˜ê°€ ê°™ì
    while(1){
        srand((unsigned)time(NULL));
        usr1 = (rand()%4)+1;
        usr2 = (rand()%4)+1;
        usr3 = (rand()%4)+1;
        usr4 = (rand()%4)+1;
        printf("\nuser1: %d\nuser2: %d\nuser3: %d\nuser4: %d\n\n", usr1, usr2, usr3, usr4);
        printf("ë‹¤ì‹œêµ´ë¦¬ê¸° - R , ì‹œìž‘í•˜ê¸° - G\n");
        scanf("%c", &choice);
        getchar();
        if(choice == 'G')
            break;
        if(choice == 'R')
            continue;
    }
    
    while(1){
        if(usr1 == 1){
            pthread_create(&user[0], NULL, gamer1, NULL);
            pthread_join(user[0], NULL);}
        if(usr2 == 1){
            pthread_create(&user[1], NULL, gamer2, NULL);
            pthread_join(user[1], NULL);}
        if(usr3 == 1){
            pthread_create(&user[2], NULL, gamer3, NULL);
            pthread_join(user[2], NULL);}
        if(usr4 == 1){
            pthread_create(&user[3], NULL, gamer4, NULL);
            pthread_join(user[3], NULL);}

        if(game_num == 31)
            return -1;

        arg.val = 1;
        if(-1 == semctl(semid, 0, SETVAL, arg)){
            printf("semctl num_1 error\n");
            return -1;}

        if(usr1 == 2){
            pthread_create(&user[0], NULL, gamer1, NULL);
            pthread_join(user[0], NULL);}
        if(usr2 == 2){
            pthread_create(&user[1], NULL, gamer2, NULL);
            pthread_join(user[1], NULL);}
        if(usr3 == 2){
            pthread_create(&user[2], NULL, gamer3, NULL);
            pthread_join(user[2], NULL);}
        if(usr4 == 2){
            pthread_create(&user[3], NULL, gamer4, NULL);
            pthread_join(user[3], NULL);}

        if(game_num == 31)
            return -1;

        arg.val = 1;
        if(-1 == semctl(semid, 0, SETVAL, arg)){
            printf("semctl num_2 error\n");
            return -1;}

        if(usr1 == 3){
            pthread_create(&user[0], NULL, gamer1, NULL);
            pthread_join(user[0], NULL);}
        if(usr2 == 3){
            pthread_create(&user[1], NULL, gamer2, NULL);
            pthread_join(user[1], NULL);}
        if(usr3 == 3){
            pthread_create(&user[2], NULL, gamer3, NULL);
            pthread_join(user[2], NULL);}
        if(usr4 == 3){
            pthread_create(&user[3], NULL, gamer4, NULL);
            pthread_join(user[3], NULL);}

        if(game_num == 31)
            return -1;
        
        arg.val = 1;
        if(-1 == semctl(semid, 0, SETVAL, arg)){
            printf("semctl num_3 error\n");
            return -1;}

        if(usr1 == 4){
            pthread_create(&user[0], NULL, gamer1, NULL);
            pthread_join(user[0], NULL);}
        if(usr2 == 4){
            pthread_create(&user[1], NULL, gamer2, NULL);
            pthread_join(user[1], NULL);}
        if(usr3 == 4){
            pthread_create(&user[2], NULL, gamer3, NULL);
            pthread_join(user[2], NULL);}
        if(usr4 == 4){
            pthread_create(&user[3], NULL, gamer4, NULL);
            pthread_join(user[3], NULL);}

        if(game_num == 31)
            return -1;

        arg.val = 1;
        if(-1 == semctl(semid, 0, SETVAL, arg)){
            printf("semctl num_4 error\n");
            return -1;}
    }
    return 0;
}
