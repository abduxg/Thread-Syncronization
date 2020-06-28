//Abdüssamed Güzey - 160316042
//Hasan Bekir Doğan - 190315077
//Please compile with pthread parameter on gcc

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *guest(void *arg);
void *waiter(void *arg);
int getId(char *);
int BOREK = 25;
int KEK = 10;
int DRINK = 25;
int TRAY_BOREK = 5;
int TRAY_KEK = 5;
int TRAY_DRINK = 5;
int g0=0,g1 = 0,g2 = 0 ,g3 = 0,g4 = 0 ,g5 = 0 ,g6 = 0,g7 = 0,g8 = 0,g9 = 0;

pthread_mutex_t mutex_kek = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_borek = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_drink = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t priv_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_kek_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_borek_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_drink_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_kek_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_borek_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_drink_empty = PTHREAD_COND_INITIALIZER;



int main(){


    pthread_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,w1;
    pthread_create(&w1,NULL,waiter,NULL);
    pthread_create(&t1,NULL,guest,"Guest0");
    pthread_create(&t2,NULL,guest,"Guest1");
    pthread_create(&t3,NULL,guest,"Guest2");
    pthread_create(&t4,NULL,guest,"Guest3");
    pthread_create(&t5,NULL,guest,"Guest4");
    pthread_create(&t6,NULL,guest,"Guest5");
    pthread_create(&t7,NULL,guest,"Guest6");
    pthread_create(&t8,NULL,guest,"Guest7");
    pthread_create(&t9,NULL,guest,"Guest8");
    pthread_create(&t10,NULL,guest,"Guest9");



    pthread_join(w1,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    pthread_join(t6,NULL);
    pthread_join(t7,NULL);
    pthread_join(t8,NULL);
    pthread_join(t9,NULL);
    pthread_join(t10,NULL);


    return 0;
}

void *guest(void *arg){

int limit_kek = 2;
int limit_drink = 5;
int limit_borek = 5;
char *who = (char* )arg;

int id = getId(who);

int k_flag = 0;
int b_flag = 0;
int d_flag = 0;



////FIRST BEGIN

    ///DRINK FIRST
    pthread_mutex_lock(&mutex_drink);

        while (TRAY_DRINK == 0 || TRAY_DRINK == 1)
            pthread_cond_wait(&cond_drink_full, &mutex_drink);
        TRAY_DRINK--;
        limit_drink--;
        printf("%s DRANK A GLASS \t\t DRINK ON TRAY= %d DRINK IN KITCHEN = %d TOTAL DRINK = %d\n",who,TRAY_DRINK,DRINK,TRAY_DRINK+DRINK);
        pthread_cond_signal(&cond_drink_empty);


   pthread_mutex_unlock(&mutex_drink);
    ///DRINK FIRST END

    ///BOREK FIRST
  pthread_mutex_lock(&mutex_borek);

        while (TRAY_BOREK == 0 || TRAY_BOREK == 1)
            pthread_cond_wait(&cond_borek_full, &mutex_borek);
        TRAY_BOREK--;
        limit_borek--;
    printf("%s ATE BOREK \t\t BOREK ON TRAY = %d BOREK IN KITCHEN = %d TOTAL BOREK = %d\n",who,TRAY_BOREK,BOREK,TRAY_BOREK+BOREK);
        pthread_cond_signal(&cond_borek_empty);

    pthread_mutex_unlock(&mutex_borek);
    ///BOREK FIRST END

    ///KEK FIRST

   pthread_mutex_lock(&mutex_kek);

        while (TRAY_KEK == 0 || TRAY_KEK == 1)
            pthread_cond_wait(&cond_kek_full, &mutex_kek);
        TRAY_KEK--;
        limit_kek--;
        printf("%s ATE CAKE \t\t CAKE ON TRAY = %d CAKE IN KITCHEN = %d TOTAL CAKE = %d\n",who,TRAY_KEK,KEK,TRAY_KEK+KEK);
        pthread_cond_signal(&cond_kek_empty);

   pthread_mutex_unlock(&mutex_kek);

//////KEK FIRST END


////FIRST END

///////////////////////////////////////BLOCK WHILE BEGIN//////////////////////////
// used to check that each guest have to eat one food from the each item this while loop. So, each guest have to least 1 borek, 1 cake and 1 drink

while (1){

    pthread_mutex_lock(&priv_mutex);

    switch (id){
        case 0:
            g0 = 1;
            break;

        case 1:
            g1 = 1;
            break;

        case 2:
            g2 = 1;
            break;

        case 3:
            g3 = 1;
            break;

        case 4:
            g4 = 1;
            break;

        case 5:
            g5 = 1;
            break;

        case 6:
            g6 = 1;
            break;

        case 7:
            g7 = 1;
            break;

        case 8:
            g8 = 1;
            break;
        case 9:
            g9 = 1;
            break;

    }///SWITCH END

        int isAllFirst = (g0 == 1 & g1 == 1 & g2 == 1 & g3 == 1 & g4  == 1 & g5 == 1 & g6  == 1 & g7 == 1 & g8  == 1 & g9 == 1);

        pthread_mutex_unlock(&priv_mutex);

        if(isAllFirst)
            break;////WHILE BREAK

}

///////////////////////////////////////////BLOCK WHILE END //////////////////////////////////////////////////////

//////TIME TO FIGHT :)
while (k_flag == 0 || d_flag == 0 || b_flag == 0) {

//////
usleep(rand()%100000);
///////

/////////////   DRINK BEGIN
            if (limit_drink > 0) {

                pthread_mutex_lock(&mutex_drink);

                if (DRINK > 0 ) {

                    while (TRAY_DRINK == 0 || TRAY_DRINK == 1)
                        pthread_cond_wait(&cond_drink_full, &mutex_drink);

                    TRAY_DRINK--;
                    limit_drink--;
                    printf("%s DRANK A GLASS \t\t DRINK ON TRAY= %d DRINK IN KITCHEN = %d TOTAL DRINK = %d\n",who,TRAY_DRINK,DRINK,TRAY_DRINK+DRINK);

                    pthread_cond_signal(&cond_drink_empty);

                } else if (TRAY_DRINK > 0) {

                    TRAY_DRINK--;
                    limit_drink--;
                    printf("%s DRANK A GLASS \t\t DRINK ON TRAY= %d DRINK IN KITCHEN = %d TOTAL DRINK = %d\n",who,TRAY_DRINK,DRINK,TRAY_DRINK+DRINK);

                } else { d_flag = 1;  }

                pthread_mutex_unlock(&mutex_drink);

            } else { d_flag = 1; }

            ///DRINK  END

            ///BOREK BEGIN
            if (limit_borek > 0) {

                pthread_mutex_lock(&mutex_borek);
                if (BOREK > 0 ) {

                    while (TRAY_BOREK == 0 || TRAY_BOREK == 1)
                        pthread_cond_wait(&cond_borek_full, &mutex_borek);

                    TRAY_BOREK--;
                    limit_borek--;
                    printf("%s ATE BOREK \t\t BOREK ON TRAY = %d BOREK IN KITCHEN = %d TOTAL BOREK = %d\n",who,TRAY_BOREK,BOREK,TRAY_BOREK+BOREK);

                    pthread_cond_signal(&cond_borek_empty);

                } else if (TRAY_BOREK > 0) {

                    TRAY_BOREK--;
                    limit_borek--;
                    printf("%s ATE BOREK \t\t BOREK ON TRAY = %d BOREK IN KITCHEN = %d TOTAL BOREK = %d\n",who,TRAY_BOREK,BOREK,TRAY_BOREK+BOREK);

                } else { b_flag = 1; }

                pthread_mutex_unlock(&mutex_borek);

            } else { b_flag = 1; }
            ///BOREK END

            ///KEK BEGIN
            if (limit_kek > 0) {


                pthread_mutex_lock(&mutex_kek);
                if (KEK > 0) {

                    while (TRAY_KEK == 0 || TRAY_KEK == 1)
                        pthread_cond_wait(&cond_kek_full, &mutex_kek);

                    TRAY_KEK--;
                    limit_kek--;
                    printf("%s ATE CAKE \t\t CAKE ON TRAY = %d CAKE IN KITCHEN = %d TOTAL CAKE = %d\n",who,TRAY_KEK,KEK,TRAY_KEK+KEK);

                    pthread_cond_signal(&cond_kek_empty);
                } else if (TRAY_KEK > 0) {

                    TRAY_KEK--;
                    limit_kek--;
                    printf("%s ATE CAKE \t\t CAKE ON TRAY = %d CAKE IN KITCHEN = %d TOTAL CAKE = %d\n",who,TRAY_KEK,KEK,TRAY_KEK+KEK);
                } else{ k_flag = 1 ; }
                pthread_mutex_unlock(&mutex_kek);

            } else { k_flag = 1;}
            ///KEK  END


        } /////END FIGHT


printf("\t\t\t\t\t\t\t\t\t\t%s EXITED\n",who);


pthread_exit(0);
}



///////////////////////////////////////////////////////////WAITER THREAD////////////////////////////////////////////////////////////////////////////

void *waiter(void *arg){
    int k_flag = 0;
    int d_flag = 0;
    int b_flag = 0;


    ////SERVE BEGIN
    while(k_flag == 0 || d_flag == 0 || b_flag == 0){


        ///KEK SERVE BEGIN
        pthread_mutex_lock(&mutex_kek);
        if(KEK > 0) {
            while (TRAY_KEK == 5)
                pthread_cond_wait(&cond_kek_empty, &mutex_kek);

            if (KEK >= 4 & TRAY_KEK == 1) {

                TRAY_KEK = 5;
                KEK = KEK - 4;
                printf("WAITER PUT 4 CAKE \t\t CAKE ON TRAY = %d\n",TRAY_KEK);

            }
            if (KEK == 4 & TRAY_KEK == 0) {
                TRAY_KEK = 4;
                KEK = 0;
                printf("WAITER PUT 4 CAKE \t\t CAKE ON TRAY = %d\n",TRAY_KEK);
            }

            if (KEK < 4 & KEK != 0) {
                switch (TRAY_KEK) {
                    case 1:
                        TRAY_KEK = TRAY_KEK + KEK;
                        printf("WAITER PUT %d CAKE \t\t CAKE ON TRAY = %d \n", KEK,TRAY_KEK);
                        KEK = 0;
                        break;
                    case 2:
                        TRAY_KEK = TRAY_KEK + KEK;
                        printf("WAITER PUT %d CAKE \t\t CAKE ON TRAY = %d\n", KEK,TRAY_KEK);
                        KEK = 0;
                        break;
                    case 3:
                        if (KEK == 2) {
                            TRAY_KEK = 5;
                            printf("WAITER PUT 2 CAKE \t\t CAKE ON TRAY = %d\n", TRAY_KEK);
                            KEK = 0;
                        }
                        if (KEK == 3) {
                            TRAY_KEK = 5;
                            KEK = KEK - 2;
                            printf("WAITER PUT 2 CAKE \t\t CAKE ON TRAY = %d\n", TRAY_KEK);
                        }
                        break;
                }


            }

            if (KEK >= 5 & TRAY_KEK == 0) {
                TRAY_KEK = 5;
                KEK = KEK - 5;
                printf("WAITER PUT 5 CAKE\n");

            }


            pthread_cond_signal(&cond_kek_full);


        }
        else{
            k_flag = 1;

        }
        pthread_mutex_unlock(&mutex_kek);

        ///CAKE SERVE END


        //////DRINK SERVE BEGIN

        pthread_mutex_lock(&mutex_drink);

        if(DRINK>0) {
            while (TRAY_DRINK == 5)
                pthread_cond_wait(&cond_drink_empty, &mutex_drink);

            if (DRINK >= 4 & TRAY_DRINK == 1) {
                TRAY_DRINK = 5;
                DRINK = DRINK - 4;
                printf("WAITER PUT 4 DRINK \t\t DRINK ON TRAY = %d \n",TRAY_DRINK);
            }
            if (DRINK == 4 & TRAY_DRINK == 0) {
                TRAY_DRINK = 4;
                DRINK = 0;
                printf("WAITER PUT 4 DRINK \t\t DRINK ON TRAY = %d \n",TRAY_DRINK);
            }
            if (DRINK < 4 & DRINK != 0) {
                switch (TRAY_DRINK) {
                    case 1:
                        TRAY_DRINK = TRAY_DRINK + DRINK;
                        printf("WAITER PUT %d DRINK \t\t DRINK ON TRAY = %d \n",DRINK,TRAY_DRINK);
                        DRINK = 0;
                        break;
                    case 2:
                        TRAY_DRINK = TRAY_DRINK + DRINK;
                        printf("WAITER PUT %d DRINK \t\t DRINK ON TRAY = %d \n",DRINK,TRAY_DRINK);
                        DRINK = 0;
                        break;
                    case 3:
                        if (DRINK == 2) {
                            TRAY_DRINK = 5;
                            printf("WAITER PUT 2 DRINK \t\t DRINK ON TRAY = %d \n",TRAY_DRINK);
                            DRINK = 0;
                        }
                        if (DRINK == 3) {
                            TRAY_DRINK = 5;
                            DRINK = DRINK - 2;
                            printf("WAITER PUT 2 DRINK \t\t DRINK ON TRAY = %d \n",TRAY_DRINK);
                        }
                        break;
                }///SWITCH END

            }

            if (DRINK >= 5 & TRAY_DRINK == 0) {
                TRAY_DRINK = 5;
                DRINK = DRINK - 5;
                printf("WAITER PUT 5 DRINK\n");

            }

            pthread_cond_signal(&cond_drink_full);
        }
        else{
            d_flag = 1;

        }
        pthread_mutex_unlock(&mutex_drink);

        ///DRINK END



        ///BOREK BEGIN
        pthread_mutex_lock(&mutex_borek);
        if(BOREK > 0) {
            while (TRAY_BOREK == 5)
                pthread_cond_wait(&cond_borek_empty, &mutex_borek);

            if (BOREK >= 4 & TRAY_BOREK == 1) {
                TRAY_BOREK = 5;
                BOREK = BOREK - 4;
                printf("WAITER PUT 4 BOREK \t\t BOREK ON TRAY = %d\n",TRAY_BOREK);
            }
            if (BOREK == 4 & TRAY_BOREK == 0) {
                TRAY_BOREK = 4;
                BOREK = 0;
                printf("WAITER PUT 4 BOREK \t\t BOREK ON TRAY = %d\n",TRAY_BOREK);
            }
            if (BOREK < 4 & BOREK != 0) {
                switch (TRAY_BOREK) {
                    case 1:
                        TRAY_BOREK = TRAY_BOREK + BOREK;
                        printf("WAITER PUT %d BOREK \t\t BOREK ON TRAY = %d\n",BOREK,TRAY_BOREK);
                        BOREK = 0;
                        break;
                    case 2:
                        TRAY_BOREK = TRAY_BOREK + BOREK;
                        printf("WAITER PUT %d BOREK \t\t BOREK ON TRAY = %d\n",BOREK,TRAY_BOREK);
                        BOREK = 0;
                        break;
                    case 3:
                        if (BOREK == 2) {
                            TRAY_BOREK = 5;
                            printf("WAITER PUT 2 \t\t BOREK ON TRAY = %d\n",TRAY_BOREK);
                            BOREK = 0;
                        }
                        if (BOREK == 3) {
                            TRAY_BOREK = 5;
                            BOREK = BOREK - 2;
                            printf("WAITER PUT 2 \t\t BOREK ON TRAY = %d\n",TRAY_BOREK);
                        }
                        break;
                }

            }
            if (BOREK >= 5 & TRAY_BOREK == 0) {
                TRAY_BOREK = 5;
                BOREK = BOREK - 5;
                printf("WAITER PUT 5 BOREK\n");

            }


            pthread_cond_signal(&cond_borek_full);
        }
        else{
            b_flag = 1;

        }
       pthread_mutex_unlock(&mutex_borek);

        ///BOREK END
    }///END SERVE

    printf("\t\t\t\t\t\t\t\t\t\tWAITER EXITED\n");

    pthread_cond_destroy(&cond_kek_full);
    pthread_cond_destroy(&cond_kek_empty);
    pthread_cond_destroy(&cond_borek_empty);
    pthread_cond_destroy(&cond_borek_full);
    pthread_cond_destroy(&cond_drink_empty);
    pthread_cond_destroy(&cond_drink_full);

    pthread_exit(0);


}

int getId(char *ch){


    char *tmp = ch;
    for(int i =0;i<5;i++)
        *tmp++;
    char *ptr = tmp;

    int id = atoi(ptr);
    return id;

}
