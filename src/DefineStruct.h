//
// Created by rasmk on 28-11-2025.
//

#ifndef TRUCKINGNAVIGATION_DEFINESTRUCTS_H
#define TRUCKINGNAVIGATION_DEFINESTRUCTS_H

typedef struct {
    int Type;
    int Toilet;
    int Fuel;
    int Hotel;
    int Food;
    int Parking;
} StopType ;

typedef struct {
    StopType Type;
    unsigned int locationX;
    unsigned int locationY;
} Stops ;

typedef struct {
    int startX, startY, endX, endY;
} InterStateRoad;

typedef struct {
    int type;
    int locationX, locationY;
} TruckStopInterstate;


#endif //TRUCKINGNAVIGATION_DEFINESTRUCTS_H