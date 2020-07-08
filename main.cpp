#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int size = 5; //size of queue, globally declared to access it anywhere in the program.
int k=0,l=0,m=0,n=0;  //counters for storing information of arrival & departure of flight

//Struct for flight arrival information
struct arrivalDeparture{
    int flightId,fuel,runwayId,flightStatus;
    char destination[10];
    struct Time{
        int hours,min;
    }arrivalTime,landingTime,waitingTime,scheduleTime,actualTime;
    struct Date{
        int day,mon;
    }arrivalDate,scheduleDate,actualDate;
}arrivalFlightDetails[5],departureFlightDetails[5];

//Stack for implementing Emergency queue(priority queue)
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
void departureFlightsDetails();
bool isEmpty ();
bool isFull();
void displayReports();
void fuelCheck();
void timeArrivalDeparture(int status);

void fuelCheck(){                        //Checking Fuel
    if(k > 0) {
        for (int i = 0; i < k; i++) {
            arrivalFlightDetails[i].fuel = arrivalFlightDetails[i].fuel - 10;               //Decreasing the fuel of plane every time by 10
                    if (arrivalFlightDetails[i].fuel < 40){          //if fuel is less than 40, flight is in emergency
                        enqueueFlights(arrivalFlightDetails[i].flightId,3);
                    }
        }
    }
}

void arrivalFlightsDetails(){             //Set Reports for Arrival Flights

    printf("\nPlease Enter the Following details of Arrival Flight\n");

    printf("\nFuel: ");
    scanf("%d",&arrivalFlightDetails[k].fuel);

    /*printf("\nDestination: ");
    scanf("%s",&arrivalFlightDetails[k].destination);

    b:
    printf("\nArrival Date (Format D/M): ");
    scanf("%d/%d",&arrivalFlightDetails[k].arrivalDate.day,&arrivalFlightDetails[k].arrivalDate.mon);
    if(arrivalFlightDetails[k].arrivalDate.day > 31 || arrivalFlightDetails[k].arrivalDate.mon > 12 ){
        printf("\nYou entered wrong date! please enter correct date");
        goto b;
    }

    a:
    printf("\nArrival Time (Format H:M (24 Hours)): ");
    scanf("%d:%d",&arrivalFlightDetails[k].arrivalTime.hours,&arrivalFlightDetails[k].arrivalTime.min);
    if(arrivalFlightDetails[k].arrivalTime.hours > 24 || arrivalFlightDetails[k].arrivalTime.min > 60){           //Checking time
        printf("\nYou entered wrong time!, please enter time in the provided format (Format H:M (24 Hours))");
        goto a;
    }*/
}

void departureFlightsDetails(){                      //Set Reports for Departure Flights
    printf("\nPlease Enter the Following details for Takeoff Flight\n");

    printf("\nFuel: ");
    scanf("%d",&departureFlightDetails[n].fuel);

    printf("\nDestination: ");
    scanf("%s",&departureFlightDetails[n].destination);

    printf("\nFlight Status: ");
    scanf("%s",&departureFlightDetails[n].flightStatus);

    c:
    printf("\nScheduled Date (Format D/M): ");
    scanf("%d/%d",&departureFlightDetails[n].arrivalDate.day, &departureFlightDetails[n].arrivalDate.mon);
    if(departureFlightDetails[n].scheduleDate.day > 31 || departureFlightDetails[n].scheduleDate.mon > 12 ){            //checking date
        printf("\nYou entered wrong date! please enter correct date");
        goto c;
    }
    b:
    printf("\nScheduled Time (Format H:M):");
    scanf("%d:%d",&departureFlightDetails[m].scheduleTime.hours, &departureFlightDetails[m].scheduleTime.min);
    if(arrivalFlightDetails[k].scheduleTime.hours > 24 || arrivalFlightDetails[k].scheduleTime.min > 60){           //Checking time
        printf("\nYou entered wrong time!, please enter time in the provided format (Format H:M (24 Hours))");
        goto b;
    }

}
void timeArrivalDeparture(int status){                           //Set Report for landing and Waiting time for arrival flight
    if(status == 1) {
        a:
        printf("\nEnter Landing Time(Format H:M:S):");
        scanf("%d:%d:%d", &arrivalFlightDetails[l].landingTime.hours, &arrivalFlightDetails[l].landingTime.min);
        if(arrivalFlightDetails[k].landingTime.hours > 24 || arrivalFlightDetails[k].landingTime.min > 60){           //Checking time
            printf("\nYou entered wrong time!, please enter time in the provided format (Format H:M (24 Hours))");
            goto a;
        }

        arrivalFlightDetails[l].waitingTime.hours =
                arrivalFlightDetails[l].arrivalTime.hours - arrivalFlightDetails[l].arrivalTime.hours;       //waiting time for arrival of flight
        arrivalFlightDetails[l].waitingTime.hours =
                arrivalFlightDetails[l].arrivalTime.min - arrivalFlightDetails[l].arrivalTime.min;
        l++;
    }else if(status == 2){
        b:
        printf("\nEnter Actual Time of Departure(Format H:M):");
        scanf("%d:%d", departureFlightDetails[m].actualTime.hours, &departureFlightDetails[m].actualTime.min);
        if(arrivalFlightDetails[k].actualTime.hours > 24 || arrivalFlightDetails[k].actualTime.min > 60){           //Checking time(is correct or not)
            printf("\nYou entered wrong time!, please enter time in the provided format (Format H:M (24 Hours))");
            goto a;
        }

        departureFlightDetails[m].waitingTime.hours =
                departureFlightDetails[m].scheduleTime.hours - departureFlightDetails[m].scheduleTime.hours;      //waiting time for departure of flights
        departureFlightDetails[m].waitingTime.hours =
                departureFlightDetails[m].scheduleTime.min - departureFlightDetails[m].scheduleTime.min;
        m++;
    }
}
bool enqueueFlights(int number,int status) {           //Making queues of flights
    if(isFull()){
        printf("\nQueue is FULL!\n");
        return false;
    }
    if(status == 1) {
        if (landingQueue1.counter <= landingQueue2.counter) {           //Landing Queue 1
            arrivalFlightDetails[k].runwayId = 1;
            landingQueue1.queues[landingQueue1.tail++] = number;
            landingQueue1.counter++;
        } else if (landingQueue1.counter > landingQueue2.counter) {     //Landing Queue 2
            arrivalFlightDetails[k].runwayId = 2;
            landingQueue2.queues[landingQueue2.tail++] = number;
            landingQueue2.counter++;
        }
    }else if(status == 2){
        if (takeoffQueue1.counter <= takeoffQueue2.counter) {          //Takeoff Queue 1
            departureFlightDetails[n].runwayId = 1;
            takeoffQueue1.queues[takeoffQueue1.tail++] = number;
            takeoffQueue1.counter++;
        } else if (takeoffQueue1.counter > takeoffQueue2.counter) {    //Takeoff Queue 2
            departureFlightDetails[n].runwayId = 2;
            takeoffQueue2.queues[takeoffQueue2.tail++] = number;
            takeoffQueue2.counter++;
        }
    }else if (status == 3){                                          //Handling Emergency Queue(Priority Queue)
        int index;
        for(int j=0; j<5; j++) {
            if (landingQueue1.queues[j] == number || landingQueue2.queues[j] == number) {
                emergencyQueue.queues[emergencyQueue.tail++] = number;
                emergencyQueue.counter++;
                index = j;
                break;
            }else{
                int c1,c2;
                c1 = landingQueue1.counter - 1;
                c2 = landingQueue2.counter - 1;
                if(c1 > 0){
                    stack.queue1[stack.top1++] = landingQueue1.queues[j];
                    landingQueue1.front++;
                    c1--;
                } else if (c2 > 0) {
                    stack.queue2[stack.top2++] = landingQueue2.queues[j];
                    landingQueue2.front++;
                    c2--;
                }
            }
        }
        if(landingQueue1.queues[index] == number){
            for(int i = index; i<landingQueue1.counter; i++){
                landingQueue1.queues[i] = landingQueue1.queues[i+1];
            }
            landingQueue1.tail--;
            landingQueue1.counter--;
        }else if(landingQueue2.queues[index] == number){
            for(int i = index; i<landingQueue2.counter; i++){
                landingQueue2.queues[i] = landingQueue2.queues[i+1];
            }
            landingQueue1.tail--;
            landingQueue2.counter--;
        }
        landingQueue1.front = landingQueue1.front - 1;
        landingQueue2.front = landingQueue2.front - 1;
        while (stack.top1 >=0 && stack.top2 >=0){
            landingQueue1.queues[landingQueue1.front--] = stack.queue1[stack.top1--];
            landingQueue1.counter++;
            landingQueue2.queues[landingQueue2.front--] = stack.queue2[stack.top2--];
            landingQueue2.counter++;
            }
        }
    k++;   //Arrival Flight Details counter
    n++;   //Departure Flight Details counter
    return true;
}
// for landing and takeoff flight and removing flights from queue
int dequeueFlights(){
    int emergencyFlight,regularFlight1,regularFlight2,fl=0;
    if(isEmpty()){
        printf("\nNo Flight left\n");
        return -99999;
    }
    printf("\nEmergency Flight Counter = %d\n",emergencyQueue.counter);
    if(emergencyQueue.counter >0){
        emergencyFlight = emergencyQueue.queues[emergencyQueue.front];
        for(int i=0; i<emergencyQueue.tail; i++){
            emergencyQueue.queues[i] = emergencyQueue.queues[i + 1];
            emergencyQueue.tail--;
        }
        printf("\nEmergency Flight No %d is Landed Successfully",emergencyFlight);
        timeArrivalDeparture(1);
    }else {

        regularFlight1 = landingQueue1.queues[landingQueue1.front];
        for (int i = 0; i <= landingQueue1.tail; i++) {
            landingQueue1.queues[i] = landingQueue1.queues[i + 1];
            landingQueue1.tail--;
        }
        printf("\nFlight No %d is Landed Successfully on Runway Id %d\n", regularFlight1,
               arrivalFlightDetails[fl++].runwayId);
        timeArrivalDeparture(1);

        regularFlight2 = landingQueue2.queues[landingQueue2.front];
        for (int i = 0; i <= landingQueue2.tail; i++) {
            landingQueue2.queues[i] = landingQueue2.queues[i + 1];
            landingQueue2.tail--;
        }
        printf("\nFlight No %d is Landed Successfully on Runway Id %d\n", regularFlight2,
               arrivalFlightDetails[fl].runwayId);
        timeArrivalDeparture(1);
    }


}
void displayReports() {                             //Displaying all the Reports
    char option,option1;
    printf("\nGenerate Reports for \nPress 1 For Landing Queue Reports\nPress 2 for Takeoff Queues Reports\nPress 3 for Emergency Queue Report\nPress 4 all Arrival Flights Information\nPress 5 for Departure Flights Information\n");
    option = getche();
    if (option == '1') {
        printf("\n---Landing Queue 1---\n");
        for (int i = 0;i < landingQueue1.counter; i++) {                //Reports of Flights that are in Landing Queue 1
            printf(" %d ", landingQueue1.queues[i]);
        }
        printf("\n---Landing Queue 2---\n");                    //Reports of Flights that are in Landing Queue 2
        for (int i = 0; i < landingQueue2.counter; i++) {
            printf(" %d ", landingQueue2.queues[i]);
        }
    }else if (option == '2'){
        printf("\n---Takeoff Queue 1---\n");
        for (int i = 0;i < takeoffQueue1.counter; i++) {                 //Reports of Flights that are in Takeoff Queue 1
            printf(" %d ", takeoffQueue1.queues[i]);
        }
        printf("\n---Takeoff Queue 2---\n");                    //Reports of Flights that are in Takeoff Queue 2
        for (int i = 0; i < takeoffQueue2.counter; i++) {
            printf(" %d ", takeoffQueue2.queues[i]);
        }
    }else if(option == '3'){
        printf("\n---!EMERGENCY Queue!---\n");                     //Reports of Flights that are in Emergency
        for(int i=0; i<emergencyQueue.counter; i++) {
            printf(" %d ", emergencyQueue.queues[i]);
        }
    }else if(option == '4') {
        printf("\n---Arrival Flights Details---\n");

        for (int i = 0;i < k; i++) {                                   //For displaying all details of arrival information

            printf("\nFlight ID=%d\n", arrivalFlightDetails[i].flightId);
            printf("Fuel=%d\n", arrivalFlightDetails[i].fuel);
            printf("Destination=%s\n", arrivalFlightDetails[i].destination);
            printf("Flight Status\n");
            printf("Arrival Date=%02d-%02d\n", arrivalFlightDetails[i].arrivalDate.day,
                   arrivalFlightDetails[i].arrivalDate.mon);
            printf("Arrival Time=%02d:%02d\n", arrivalFlightDetails[i].arrivalTime.hours,
                   arrivalFlightDetails[i].arrivalTime.min);
            if (arrivalFlightDetails[i].landingTime.hours != 0) {
                printf("Landing Time=%02d:%02d\n", arrivalFlightDetails[i].landingTime.hours,
                       arrivalFlightDetails[i].landingTime.min);
            }
            if (arrivalFlightDetails[i].waitingTime.min != 0) {
                printf("Waiting Time=%02d:%02d\n", arrivalFlightDetails[i].waitingTime.hours,
                       arrivalFlightDetails[i].waitingTime.min);
            }
            printf("Runway Id=%d\n", arrivalFlightDetails[i].runwayId);
            printf("\n---------------------\n");
        }
    } else if (option == '5') {

        printf("\n---Departure Flights Details---\n");

        for (int i = 0;
             i < n; i++) {                                   //For displaying all details of Departure information

            printf("\nFlight ID=%d\n", departureFlightDetails[i].flightId);
            printf("Fuel=%d\n", departureFlightDetails[i].fuel);
            printf("Destination=%s\n", departureFlightDetails[i].destination);
            printf("Flight Status\n", departureFlightDetails[i].flightStatus);
            printf("Schedule Date=%02d-%02d\n", departureFlightDetails[i].scheduleDate.day,
                   departureFlightDetails[i].scheduleDate.mon);
            printf("Schedule Time=%02d:%02d\n", departureFlightDetails[i].scheduleTime.hours,
                   departureFlightDetails[i].scheduleTime.min);
            if (departureFlightDetails[i].actualTime.hours != 0) {
                printf("Actual Time=%02d:%02d\n", departureFlightDetails[i].actualTime.hours,
                       departureFlightDetails[i].actualTime.min);
            }
            if (departureFlightDetails[i].waitingTime.min != 0) {
                printf("Waiting Time=%02d:%02d\n", departureFlightDetails[i].waitingTime.hours,
                       departureFlightDetails[i].waitingTime.min);
            }
            printf("Runway Id=%d\n", departureFlightDetails[i].runwayId);
            printf("\n---------------------\n");
        }
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
    if(landingQueue1.counter < 0 && landingQueue2.counter < 0 || takeoffQueue1.counter < 0 && takeoffQueue2.counter <0){
        return true;
    }
    return false;
}

// Main
int main() {
    char ch;
    int flightId;
    a:
    system("CLS");
    printf("-FLIGHT MANAGEMENT SYSTEM-\n");
    printf("\nPress 1 for Arrival\nPress 2 For Departure\nPress 3 For Emergency\nPress 4 to Display Reports\n");  //Menu
    ch = getche();
    switch(ch){
        case '1': {
            system("CLS");
            printf("\nPlease Enter Arrival Flight ID: ");
            scanf("%d",&flightId);
            arrivalFlightDetails[k].flightId = flightId;
            arrivalFlightsDetails();
            enqueueFlights(flightId,1);
            fuelCheck();
            break;
        }
        case '2':{
            printf("\nPlease Enter Departure Flight ID: ");
            scanf("%d",&flightId);
            departureFlightsDetails();
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
    printf("\nFlights are ready for Landing, Press Y "
           "for confirmation for landing on runway 1 and 2 or N to go to Menu\n");
    ch = getche();
    if(ch == 'y' || ch == 'Y'){
        dequeueFlights();
    }else{
        goto a;
    }
    goto a;
}
