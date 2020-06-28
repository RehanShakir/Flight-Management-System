#include <iostream>
#include <string>
#include <stdlib.h>
struct arival{
    int flightId,fuel,runwayId;
    char destination;

    struct time{
        int arivalDate,arivalTime,waitingTime,landingTime;
    };
};


struct queueOne{
    int front=0,tail=0,counter=0;
    int queues[5];
}landingQueue1,landingQueue2,takeoffQueue1,takeoffQueue2;

int size = 5;

bool enqueueFlights(int number);
int dequeueFlights();
bool isEmpty ();
bool isFull();
void displayReports();







int main() {
    char ch;

    a:
    printf("\nPress 1 for Arival\nPress 2 For Departure\nPress 3 For Emergency\nPress 4 to Display Reports\n");
    scanf("%ch",&ch);

    switch(ch){
        case '1': {
            system("CLS");
            int flightId;
            printf("\nPlease Enter Flight ID: ");
            scanf("%d",&flightId);
            enqueueFlights(flightId);
            break;
        }
        case '2':{
            printf("\nPlease Enter Flight ID: ");
            scanf("%d",&flightId);
            enqueueFlights(flightId,"departure");
            break;
        case '4':{
            displayReports();
            //exit(0);
            break;
        }
        case '\n': break;
        default:
            printf("\nWrong Press!");
    }
    goto a;

}
bool enqueueFlights(int number) {


    if(isFull()){
        return false;
    }
    if(landingQueue1.counter <= landingQueue2.counter){
        printf("\nlandingQueue1.counter <= landingQueue2.counter");
        landingQueue1.queues[landingQueue1.tail++] = number;
        landingQueue1.counter++;
    }else if(landingQueue1.counter > landingQueue2.counter){
        printf("\nlandingQueue1.counter > landingQueue2.counter");
        landingQueue2.queues[landingQueue2.tail++] = number;
        landingQueue2.counter++;
    }
    printf("\nlandingQueue1: %d",landingQueue1.counter);
    printf("\nlandingQueue2: %d",landingQueue2.counter);
    printf("\nlandingQueue1Tail: %d",landingQueue1.tail);
    printf("\nlandingQueue2Tail: %d",landingQueue2.tail);
    return true;
}
void displayReports() {
    printf("\n---Landing Queue 1---\n");

    for(int i=0; i<=landingQueue1.counter-1; i++){
        printf(" %d ",landingQueue1.queues[i]);
    }
    printf("\n---Landing Queue 2---\n");
    for(int i=0; i<=landingQueue2.counter-1; i++){
        printf(" %d ",landingQueue2.queues[i]);
    }
}
bool isFull() {
    if(landingQueue1.counter || landingQueue2.counter >= size){
        return true;
    }
    return false;
}

bool isEmpty() {
    if(landingQueue1.counter || landingQueue2.counter >= 0){
        return true;
    }
    return false;
}

