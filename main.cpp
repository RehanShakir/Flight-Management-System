#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
int size = 5; //size of queue, globally declared to access it anywhere in the program.
int k=0;  //counter for storing information of arrival of flight

time_t t = time(NULL);
struct tm tm = *localtime(&t);

//Struct for flight arrival information
struct arrival{
    int flightId,fuel,runwayId;
    char destination[10];
    struct Time{
        int hours,min,sec;
    }arivalTime,landingTime,waitingTime;
    struct Date{
        int day,mon,year;
    }arivalDate;
}arrival[5];

//Stack for implementing Emergecny queue(priority queue)
struct stack{
    int queue1[5],queue2[5],top1,top2;
}stack;

// Queue for adding flights in queues
struct queue{
    int front,tail,counter;
    int queues[5];
}landingQueue1 = {0},landingQueue2 = {0},takeoffQueue1 = {0},takeoffQueue2 = {0},emergencyQueue = {0};

//Function Prototypes
bool enqueueFlights(int number,int status);
int dequeueFlights();
void arrivalFlightsDetails();
bool isEmpty ();
bool isFull();
void displayReports();

// Main
int main() {
    char ch;
    int flightId;
    a:
    printf("\nPress 1 for Arrival\nPress 2 For Departure\nPress 3 For Emergency\nPress 4 to Display Reports\n");  //Menu
    ch = getche();
    switch(ch){
        case '1': {
        	system("CLS");
            printf("\nPlease Enter Arrival Flight ID: ");
            scanf("%d",&flightId);
            arrival[k].flightId = flightId;
            arrivalFlightsDetails();
            enqueueFlights(flightId,1);
            break;
        }
        case '2':{
            printf("\nPlease Enter Departure Flight ID: ");
            scanf("%d",&flightId);
            enqueueFlights(flightId,2);
            break;
        }
        case '3':{
            printf("\nPlease Enter the Flight ID that is in Emergency: ");
            scanf("%d",&flightId);
            enqueueFlights(flightId,3);
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
    printf("\nFlight no %d is ready for Landing, Press Y for confirmation for landing\n",arrival[0].flightId);
    ch = getche();
    if(ch == 'y' || ch == 'Y'){
        dequeueFlights();
    }else{
        goto a;
    }
    goto a;
}
void arrivalFlightsDetails(){             //Setting all the flight details

    printf("\nPlease Enter the Following details of coming flight\n");

    printf("\nFuel: ");
    scanf("%d",&arrival[k].fuel);

    printf("\nDestination: ");
    scanf("%s",&arrival[k].destination);

    arrival[k].arivalTime.hours = tm.tm_hour;
    arrival[k].arivalTime.min = tm.tm_min;        //arrival Time
    arrival[k].arivalTime.sec = tm.tm_sec;

    arrival[k].arivalDate.day = tm.tm_mday;
    arrival[k].arivalDate.mon = tm.tm_mon;       //arrival Date
    arrival[k].arivalDate.year = tm.tm_year;

    arrival[k].waitingTime.hours = arrival[k].landingTime.hours - arrival[k].arivalTime.hours;
    arrival[k].waitingTime.min = arrival[k].landingTime.min - arrival[k].arivalTime.min;             //waiting time
    arrival[k].waitingTime.sec = arrival[k].landingTime.sec - arrival[k].arivalTime.sec;

    arrival[k].landingTime.hours  = tm.tm_hour;
    arrival[k].landingTime.min = tm.tm_min;      //Landing Time
    arrival[k].landingTime.sec = tm.tm_sec;


    k++;
}

bool enqueueFlights(int number,int status) {           //Making queues of flights
    if(isFull()){
    	printf("\nQueue is FULL!\n");
        return false;
    }
    if(status == 1) {
        if (landingQueue1.counter <= landingQueue2.counter) {           //Landing Queue 1
            arrival[k].runwayId = 1;
            landingQueue1.queues[landingQueue1.tail++] = number;
            landingQueue1.counter++;
        } else if (landingQueue1.counter > landingQueue2.counter) {     //Landing Queue 2
            arrival[k].runwayId = 2;
            landingQueue2.queues[landingQueue2.tail++] = number;
            landingQueue2.counter++;
        }
    }else if(status == 2){
        if (takeoffQueue1.counter <= takeoffQueue2.counter) {          //Takeoff Queue 1
            takeoffQueue1.queues[takeoffQueue1.tail++] = number;
            takeoffQueue1.counter++;
        } else if (takeoffQueue1.counter > takeoffQueue2.counter) {    //Takeoff Queue 2
            takeoffQueue2.queues[takeoffQueue2.tail++] = number;
            takeoffQueue2.counter++;
        }
    }else if (status == 3){                                          //Emergency Queue(Priority Queue)
        for(int j=0; j<5; j++) {
            if (landingQueue1.queues[j] == number || landingQueue2.queues[j] == number) {
                if(landingQueue1.queues[j] == number){
                } else if(landingQueue2.queues[j] == number){
                }
                emergencyQueue.queues[emergencyQueue.tail++] = number;
                emergencyQueue.counter++;
                break;
            }else{
                stack.queue1[stack.top1++] = landingQueue1.queues[landingQueue1.tail--];
                landingQueue1.counter--;

                stack.queue2[stack.top2++] = landingQueue2.queues[landingQueue2.tail--];
                landingQueue2.counter--;
            }
        }
        while (stack.top1 >=0 && stack.top2 >=0){
            if(stack.top1 >=0) {
                landingQueue1.queues[landingQueue1.tail++] = stack.queue1[stack.top1--];
                landingQueue1.counter++;
            }else if(stack.top2) {
                landingQueue2.queues[landingQueue2.tail++] = stack.queue2[stack.top2--];
                landingQueue2.counter++;
            }
        }
    }
    return true;
}
// for
int dequeueFlights(){
    int emergencyFlight,regularFlight1,regularFlight2;
    if(isEmpty()){
        printf("\nNo Flight left\n");
        return -99999;
    }
    if(emergencyQueue.counter >= 0){
        emergencyFlight = emergencyQueue.queues[emergencyQueue.front];
        for(int i=0; i<emergencyQueue.tail; i++){
            emergencyQueue.queues[i] = emergencyQueue.queues[i+1];
            emergencyQueue.tail--;
        }
        printf("\nEmergency Flight No %d is Landed Successfully",emergencyFlight);
    }else {
        regularFlight1 = landingQueue1.queues[landingQueue1.front];
        for (int i = 0; i <= landingQueue1.tail; i++) {
            landingQueue1.queues[i] = landingQueue1.queues[i + 1];
            landingQueue1.tail--;
        }
        printf("\nFlight No %d is Landed Successfully on Runway Id %d\n", regularFlight1,
               arrival[landingQueue1.counter].runwayId);


        regularFlight2 = landingQueue2.queues[landingQueue2.front];
        for (int i = 0; i <= landingQueue2.tail; i++) {
            landingQueue2.queues[i] = landingQueue2.queues[i + 1];
            landingQueue2.tail--;
        }
        printf("\nFlight No %d is Landed Successfully on Runway Id %d\n", regularFlight2,
               arrival[landingQueue2.counter].runwayId);
    }



}
void displayReports() {                                   //Displaying all the Reports
    printf("\n---Landing Queue 1---\n");

    for(int i=0; i<landingQueue1.counter; i++){
        printf(" %d ",landingQueue1.queues[i]);
    }
    printf("\n---Landing Queue 2---\n");
    for(int i=0; i<landingQueue2.counter; i++){
        printf(" %d ",landingQueue2.queues[i]);
    }
    printf("\n---!EMERGENCY Queue!---\n");
    for(int i=0; i<emergencyQueue.counter; i++) {
        printf(" %d ", emergencyQueue.queues[i]);
    }
    printf("\n---Flights Details---\n");

    for(int i=0; i<5; i++){                                         //For displaying all details of arrival information
        if(arrival[i].flightId == 0){ break;}
        printf("---------------");
        printf("\nFlight ID=%d |\n",arrival[i].flightId);
        printf("---------------\n");
        printf("Fuel=%d\n",arrival[i].fuel);
        printf("Destination=%s\n",arrival[i].destination);
        printf("Arrival Date=%02d-%02d-%d\n",arrival[i].arivalDate.day,arrival[i].arivalDate.mon,arrival[i].arivalDate.year+1900);
        printf("Arrival Time=%02d:%02d:%02d\n",arrival[i].arivalTime.hours,arrival[i].arivalTime.min,arrival[i].arivalTime.sec);
        printf("Landing Time=%02d:%02d:%02d\n",arrival[i].landingTime.hours,arrival[i].landingTime.min,arrival[i].landingTime.sec);
        printf("Waiting Time=%02d:%02d:%02d\n",arrival[i].waitingTime.hours,arrival[i].waitingTime.min,arrival[i].waitingTime.sec);
        printf("Runway Id=%d\n",arrival[i].runwayId);
        printf("\n\n---------------------------------------------------------------\n\n");
    }
}
bool isFull() {                                     //For Checking if the queues are full or not
    if(takeoffQueue1.counter >= size && takeoffQueue2.counter >= size && emergencyQueue.counter >= size ||
       landingQueue1.counter >= size && landingQueue2.counter >= size && emergencyQueue.counter >= size){
        return true;
    }
    return false;
}

bool isEmpty() {                              //For Checking if the queues are empty or not
    printf("\nLanding Queue one = %d",landingQueue1.counter);
    printf("\nLanding Queue two = %d",landingQueue2.counter);
    if(landingQueue1.counter < 0 && landingQueue2.counter < 0 || takeoffQueue1.counter <0 && takeoffQueue2.counter <0){
        return true;
    }
    return false;
}

