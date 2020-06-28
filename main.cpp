#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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

int size = 5; //size of queue, globally declared to access it anywhere in the program.
bool enqueueFlights(int number,int status);  //Function for making queues of flights
int dequeueFlights();
bool isEmpty ();
bool isFull();
void displayReports();

int main() {
    char ch;
    int flightId;
    a:
    printf("\nPress 1 for Arival\nPress 2 For Departure\nPress 3 For Emergency\nPress 4 to Display Reports\n");
    ch = getche();
    switch(ch){
        case '1': {
        	//system("CLS");
            printf("\nPlease Enter Arival Flight ID: ");
            scanf("%d",&flightId);
            enqueueFlights(flightId,1);
            break;
        }
        case '2':{
            printf("\nPlease Enter Departure Flight ID: ");
            scanf("%d",&flightId);
            enqueueFlights(flightId,2);
            break;
        }
        case '4':{
            displayReports();
            //exit(0);
            break;
        }
        default:
            printf("\nWrong Press!");
    }
    goto a;

}
bool enqueueFlights(int number,int status) {
    if(isFull() == true){
    	printf("\nQueue is FULL!\n");
        return false;
    }
    if(status == 1) {
        if (landingQueue1.counter <= landingQueue2.counter) {
            printf("\nlandingQueue1.counter <= landingQueue2.counter");
            landingQueue1.queues[landingQueue1.tail++] = number;
            landingQueue1.counter++;
        } else if (landingQueue1.counter > landingQueue2.counter) {
            printf("\nlandingQueue1.counter > landingQueue2.counter");
            landingQueue2.queues[landingQueue2.tail++] = number;
            landingQueue2.counter++;
        }
        printf("\nlandingQueue1: %d", landingQueue1.counter);
        printf("\nlandingQueue2: %d", landingQueue2.counter);
        printf("\nlandingQueue1Tail: %d", landingQueue1.tail);
        printf("\nlandingQueue2Tail: %d", landingQueue2.tail);
    }
    else if(status == 2){
        if (takeoffQueue1.counter <= takeoffQueue2.counter) {
            printf("\ntakeOffQueue1.counter <= takeOffQueue2.counter");
            takeoffQueue1.queues[takeoffQueue1.tail++] = number;
            takeoffQueue1.counter++;
        } else if (takeoffQueue1.counter > takeoffQueue2.counter) {
            printf("\ntakeOffQueue1.counter > takeOffQueue2.counter");
            takeoffQueue2.queues[takeoffQueue2.tail++] = number;
            takeoffQueue2.counter++;
        }
    }
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
    printf("\nlandingQueue1: %d", landingQueue1.counter);
    printf("\nlandingQueue2: %d", landingQueue2.counter);

    if((landingQueue1.counter || landingQueue2.counter || takeoffQueue1.counter || takeoffQueue2.counter) >= size ){
        return true;
    }
    return false;
}

bool isEmpty() {
    if((landingQueue1.counter || landingQueue2.counter || takeoffQueue1.counter || takeoffQueue2.counter) >= 0){
        return true;
    }
    return false;
}

