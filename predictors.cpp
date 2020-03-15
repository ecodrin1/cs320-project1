#include <iostream>
#include <string>
#include <fstream>
#include "predictors.h"

using namespace std;

int main(int argc, char** argv){ 

    // Temporary variables
    unsigned long long addr;
    string behavior;
    unsigned long long target;
    bool boolbehavior;
    int correct1,total1,correct2,total2,correct3,total3,correct4,total4,correct5,total5,correct6,total6=0;
    int correct7,attempted7=0;
    // Open file for reading
    ifstream infile("./examples/test_input.txt"); //TODO edit to take from commandline
    // //initialize bimodal predictors 
    predictor3* pred3= new predictor3();
    // for(int i=0; i<predictor3_PT16.size;i++) predictor3_PT16[i]=true;
    // for(int i=0; i<predictor3_PT32.size;i++) predictor3_PT32[i]=true;
    // for(int i=0; i<predictor3_PT128.size;i++) predictor3_PT128[i]=true;
    // for(int i=0; i<predictor3_PT256.size;i++) predictor3_PT256[i]=true;
    // for(int i=0; i<predictor3_PT512.size;i++) predictor3_PT512[i]=true;
    // for(int i=0; i<predictor3_PT1024.size;i++) predictor3_PT1024[i]=true;
    // for(int i=0; i<predictor3_PT2048.size;i++) predictor3_PT2048[i]=true;

    // The following loop will read a hexadecimal number and
    // a string each time and then output them
    while(infile >> std::hex >> addr >> behavior >> std::hex >> target) {
        /* in main, call:
            predictors1(addr)
            predictors2(addr)
            predictors3(addr)...to predictors7(addr)
            set boolbehavior to true/false (T==true; else false)
            if boolbehavior == predictor then increment correct and total; else only increment total
        */
        //cout << addr;
        //set behaviorbool
        if(behavior == "T") {
            boolbehavior= true; //cout << " -> taken, ";
        } else {
            boolbehavior=false; //cout << " -> not taken, ";
        }
        //predictor1 update
        if(boolbehavior==predictor1(addr)){
            //increment correct1 AND total1
            correct1++; total1++;
        } else total1++;
        //predictor2 update
        if(boolbehavior==predictor2(addr)){
            correct2++;total2++;
        } else total2++;
        //predictor3 update
        bool* list3= pred3->predict3(addr);
        pred3->updatePT(boolbehavior, addr);
        //predictor4 update
        
        //cout << "target=" << target << endl;
    }
    //main output: print (each on new line) "#correct,#total; " . 
    std::cout<< correct1<< ","<< total1 <<"; "<< endl;
    std::cout<< correct2<< ","<< total2 <<"; "<< endl;
    pred3->printCorrect();
    
}

/*
Types of predictors needed:
1. Always Taken (prediction is simple: T)
2. Always Not Taken (prediction is simple: N)
3. Bimodal, 1 bit history 
4. Bimodal, 2 bit history
4a. Exactly what we did in class with the finite state machine.
5. Gshare predictor
5a. 2048 bit size table 
5b. last 4 bits of program counter (PC & 0b1111) XOR (^) Global History Register 
6. Tournament predictor
7. Branch Target Buffer 


Base predictor logic:
1. parse file (try to use what he provides?)
2. function(inputaddress) yields T or NT (based on function logic)
3. if Guess==actual mark correct? If not, increment total but not correct
4. update given predictors with required logic
*/