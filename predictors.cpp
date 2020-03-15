#include <iostream>
#include <string>
#include <fstream>
#include "predictors.h"

using namespace std;

int main(int argc, char** argv){ 
    if(argc<3){
        cout<< "Expected command format: ./predictors <inputfile> <outputfile>" <<endl;
        return 1;
    }

    // Temporary variables
    unsigned long long addr;
    string behavior;
    unsigned long long target;
    bool boolbehavior;
    // Open file for reading
    ifstream infile(argv[1]); 
    // //initialize predictors 
    predictor1* pred1= new predictor1();
    predictor2* pred2= new predictor2();
    predictor3* pred3= new predictor3();
    predictor4* pred4= new predictor4();
    predictor5* pred5= new predictor5();
    predictor6* pred6= new predictor6();
    predictor7* pred7= new predictor7();


    // The following loop will read a hexadecimal number and
    // a string each time and then output them
    while(infile >> std::hex >> addr >> behavior >> std::hex >> target) {
        //set behaviorbool
        if(behavior == "T") {
            boolbehavior= true; //cout << " -> taken, ";
        } else {
            boolbehavior=false; //cout << " -> not taken, ";
        }
        //predictor1 update
        pred1->predict1();
        pred1->update(boolbehavior);
        //predictor2 update
        pred2->predict2();
        pred2->update(boolbehavior);
        //predictor3 update
        pred3->predict3(addr);
        pred3->update(boolbehavior, addr);
        //predictor4 update
        pred4->predict4(addr);
        pred4->update(boolbehavior, addr);
        //predictor5 update
        pred5->predict5(addr);
        pred5->update(boolbehavior, addr);
        //predictor6 update
        pred6->predict6(addr);
        pred6->update(boolbehavior, addr);
        //predictor7 update
        pred7->predict7(addr);
        pred7->update(boolbehavior, addr, target);
        //cout << "target=" << target << endl;
    }
    //main output: print (each on new line) "#correct,#total; " . 

    //god bless you, lords of stack overflow 
    ofstream out(argv[2]);
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt
    pred1->printCorrect();
    pred2->printCorrect();
    pred3->printCorrect();
    pred4->printCorrect();
    pred5->printCorrect();
    pred6->printCorrect();
    pred7->printCorrect();
    //write these to a file specified by argv[2]
    
}
