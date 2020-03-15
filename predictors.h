#ifndef PREDICTORS_H
#define PREDICTORS_H
#include <array>
#include <iostream>
//#include <utility> //for std::pair

//always taken
class predictor1{
    private:
        int correct, total=0;
    public:
        bool predict1(unsigned long long addr){
            return true;
        }
        void updatePT(bool result, unsigned long long addr){
            if(result==predict1(addr)){
            //increment correct1 AND total1
            correct++; total++;
            } else total++;
        }
        void printCorrect(){
            std::cout<< correct<< "," <<total<< "; " <<std::endl;
        }
};


//always not taken
class predictor2{
    private:
        int correct, total=0;
    public:
        bool predict2(unsigned long long addr){
            return false;
        }
        void updatePT(bool result, unsigned long long addr){
            if(result==predict2(addr)){
            //increment correct1 AND total1
            correct++; total++;
            } else total++;
        }
        void printCorrect(){
            std::cout<< correct<< "," <<total<< "; " <<std::endl;
        }
};

//bimodal predictor: 1-bit history
class predictor3{
    private:
        bool predictList[7];
        std::array<bool,16> predictor3_PT16; 
        std::array<bool,32> predictor3_PT32;
        std::array<bool,128> predictor3_PT128;
        std::array<bool,256> predictor3_PT256;
        std::array<bool,512> predictor3_PT512;
        std::array<bool,1024> predictor3_PT1024;
        std::array<bool,2048> predictor3_PT2048;
        int correct16, total16, correct32, total32, correct128, total128, correct256, total256, correct512, total512, correct1024, total1024, correct2048, total2048=0;
    public:
        //constructor to set all predictor tables to 1 (taken)
        predictor3(){
            for(int i=0; i<predictor3_PT16.size(); i++){
                predictor3_PT16[i]=true;
            }
            for(int i=0; i<predictor3_PT32.size(); i++){
                predictor3_PT32[i]=true;
            }
            for(int i=0; i<predictor3_PT128.size(); i++){
                predictor3_PT128[i]=true;
            }
            for(int i=0; i<predictor3_PT256.size(); i++){
                predictor3_PT256[i]=true;
            }
            for(int i=0; i<predictor3_PT512.size(); i++){
                predictor3_PT512[i]=true;
            }
            for(int i=0; i<predictor3_PT1024.size(); i++){
                predictor3_PT1024[i]=true;
            }
            for(int i=0; i<predictor3_PT2048.size(); i++){
                predictor3_PT2048[i]=true;
            }
        }
        void predict3(unsigned long long addr){
            predictList[0]= predictor3_PT16[addr%16]; 
            predictList[1]= predictor3_PT32[addr%32];
            predictList[2]= predictor3_PT128[addr%128];
            predictList[3]= predictor3_PT256[addr%256];
            predictList[4]= predictor3_PT512[addr%512];
            predictList[5]= predictor3_PT1024[addr%1024];
            predictList[6]= predictor3_PT2048[addr%2048];
            //return predictList;
        }
        void updatePT(bool result, unsigned long long addr){
            if(predictList[0]!=result){
                predictor3_PT16[addr%16]= !predictor3_PT16[addr%16];
                total16++;
            } else {
                correct16++; total16++;
            }
            if(predictList[1]!=result){
                predictor3_PT32[addr%32]= !predictor3_PT32[addr%32];
                total32++;
            } else {
                correct32++; total32++;
            }
            if(predictList[2]!=result){
                predictor3_PT128[addr%128]= !predictor3_PT128[addr%128];
                total128++;
            } else {
                correct128++; total128++;
            }
            if(predictList[3]!=result){
                predictor3_PT256[addr%256]= !predictor3_PT256[addr%256];
                total256++;
            } else {
                correct256++; total256++;
            }
            if(predictList[4]!=result){
                predictor3_PT512[addr%512]= !predictor3_PT512[addr%512];
                total512++;
            } else {
                correct512++; total512++;
            }
            if(predictList[5]!=result){
                predictor3_PT1024[addr%1024]= !predictor3_PT1024[addr%1024];
                total1024++;
            } else {
                correct1024++; total1024++;
            }
            if(predictList[6]!=result){
                predictor3_PT2048[addr%2048]= !predictor3_PT2048[addr%2048];
                total2048++;
            } else {
                correct2048++; total2048++;
            }
        }
        void printCorrect(){
            std::cout<< correct16 <<"," <<total16 << "; ";
            std::cout<< correct32 <<"," <<total32 << "; ";
            std::cout<< correct128 << ","<<total128 << "; ";
            std::cout<< correct256<< ","<< total256<< "; ";
            std::cout<< correct512<< ","<< total512<< "; ";
            std::cout<< correct1024<< ","<< total1024<< "; ";
            std::cout<< correct2048<< ","<< total2048<< "; " <<std::endl;
        }
};
//bimodal predictor: 2-bit history
class predictor4{
    private:
        bool predictList[7];
        std::array<int,16> predictor4_PT16; 
        std::array<int,32> predictor4_PT32;
        std::array<int,128> predictor4_PT128;
        std::array<int,256> predictor4_PT256;
        std::array<int,512> predictor4_PT512;
        std::array<int,1024> predictor4_PT1024;
        std::array<int,2048> predictor4_PT2048;
        int correct16, total16, correct32, total32, correct128, total128, correct256, total256, correct512, total512, correct1024, total1024, correct2048, total2048=0;
    public:
        //constructor to set all predictor tables to 3 or 0b11 (Strongly taken)
        predictor4(){
            for(int i=0; i<predictor4_PT16.size(); i++){
                predictor4_PT16[i]=3;
            }
            for(int i=0; i<predictor4_PT32.size(); i++){
                predictor4_PT32[i]=3;
            }
            for(int i=0; i<predictor4_PT128.size(); i++){
                predictor4_PT128[i]=3;
            }
            for(int i=0; i<predictor4_PT256.size(); i++){
                predictor4_PT256[i]=3;
            }
            for(int i=0; i<predictor4_PT512.size(); i++){
                predictor4_PT512[i]=3;
            }
            for(int i=0; i<predictor4_PT1024.size(); i++){
                predictor4_PT1024[i]=3;
            }
            for(int i=0; i<predictor4_PT2048.size(); i++){
                predictor4_PT2048[i]=3;
            }
        }
        void predict4(unsigned long long addr){
            predictList[0]= predictor4_PT16[addr%16]>1? true:false; //if 0/1, NT; if 2/3, T
            predictList[1]= predictor4_PT32[addr%32]>1? true:false;
            predictList[2]= predictor4_PT128[addr%128]>1? true:false;
            predictList[3]= predictor4_PT256[addr%256]>1? true:false;
            predictList[4]= predictor4_PT512[addr%512]>1? true:false;
            predictList[5]= predictor4_PT1024[addr%1024]>1? true:false;
            predictList[6]= predictor4_PT2048[addr%2048]>1? true:false;
            //return predictList;
        }
        void updatePT(bool result, unsigned long long addr){
            if(predictList[0]!=result){
                //this prediction is wrong. increment total. more logic is needed to update PT
                total16++;
                if(predictList[0]==false) {
                    predictor4_PT16[addr%16]+=1;//if NT is wrong, add 1
                    if(predictor4_PT16[addr%16]>3){
                        predictor4_PT16[addr%16]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[0]==true){
                    predictor4_PT16[addr%16]-=1;//if T is wrong, subtract 1
                    if(predictor4_PT16[addr%16]<0){
                        predictor4_PT16[addr%16]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            } else {
                //this prediction is correct. increment correct and total. more logic is needed to update PT
                correct16++; total16++;
                if(predictList[0]==true){
                    predictor4_PT16[addr%16]+=1;//if T is right, add 1
                    if(predictor4_PT16[addr%16]>3){
                        predictor4_PT16[addr%16]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[0]==false){
                    predictor4_PT16[addr%16]-=1;//if NT is right, subtract 1 
                    if(predictor4_PT16[addr%16]<0){
                        predictor4_PT16[addr%16]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            }
            if(predictList[1]!=result){
                //this prediction is wrong. increment total. more logic is needed to update PT
                total32++;
                if(predictList[1]==false) {
                    predictor4_PT32[addr%32]+=1;//if NT is wrong, add 1
                    if(predictor4_PT32[addr%32]>3){
                        predictor4_PT32[addr%32]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[1]==true){
                    predictor4_PT32[addr%32]-=1;//if T is wrong, subtract 1
                    if(predictor4_PT32[addr%32]<0){
                        predictor4_PT32[addr%32]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            } else {
                //this prediction is correct. increment correct and total. more logic is needed to update PT
                correct32++; total32++;
                if(predictList[1]==true){
                    predictor4_PT32[addr%32]+=1;//if T is right, add 1
                    if(predictor4_PT32[addr%32]>3){
                        predictor4_PT32[addr%32]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[1]==false){
                    predictor4_PT32[addr%32]-=1;//if NT is right, subtract 1 
                    if(predictor4_PT32[addr%32]<0){
                        predictor4_PT32[addr%32]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            }

            if(predictList[2]!=result){
                //this prediction is wrong. increment total. more logic is needed to update PT
                total128++;
                if(predictList[2]==false) {
                    predictor4_PT128[addr%128]+=1;//if NT is wrong, add 1
                    if(predictor4_PT128[addr%128]>3){
                        predictor4_PT128[addr%128]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[2]==true){
                    predictor4_PT128[addr%128]-=1;//if T is wrong, subtract 1
                    if(predictor4_PT128[addr%128]<0){
                        predictor4_PT128[addr%128]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            } else {
                //this prediction is correct. increment correct and total. more logic is needed to update PT
                correct128++; total128++;
                if(predictList[2]==true){
                    predictor4_PT128[addr%128]+=1;//if T is right, add 1
                    if(predictor4_PT128[addr%128]>3){
                        predictor4_PT128[addr%128]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[2]==false){
                    predictor4_PT128[addr%128]-=1;//if NT is right, subtract 1 
                    if(predictor4_PT128[addr%128]<0){
                        predictor4_PT128[addr%128]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            }
            if(predictList[3]!=result){
                //this prediction is wrong. increment total. more logic is needed to update PT
                total256++;
                if(predictList[3]==false) {
                    predictor4_PT256[addr%256]+=1;//if NT is wrong, add 1
                    if(predictor4_PT256[addr%256]>3){
                        predictor4_PT256[addr%256]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[3]==true){
                    predictor4_PT256[addr%256]-=1;//if T is wrong, subtract 1
                    if(predictor4_PT256[addr%256]<0){
                        predictor4_PT256[addr%256]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            } else {
                //this prediction is correct. increment correct and total. more logic is needed to update PT
                correct256++; total256++;
                if(predictList[3]==true){
                    predictor4_PT256[addr%256]+=1;//if T is right, add 1
                    if(predictor4_PT256[addr%256]>3){
                        predictor4_PT256[addr%256]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[3]==false){
                    predictor4_PT256[addr%256]-=1;//if NT is right, subtract 1 
                    if(predictor4_PT256[addr%256]<0){
                        predictor4_PT256[addr%256]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            }
                    if(predictList[4]!=result){
                //this prediction is wrong. increment total. more logic is needed to update PT
                total512++;
                if(predictList[4]==false) {
                    predictor4_PT512[addr%512]+=1;//if NT is wrong, add 1
                    if(predictor4_PT512[addr%512]>3){
                        predictor4_PT512[addr%512]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[4]==true){
                    predictor4_PT512[addr%512]-=1;//if T is wrong, subtract 1
                    if(predictor4_PT512[addr%512]<0){
                        predictor4_PT512[addr%512]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            } else {
                //this prediction is correct. increment correct and total. more logic is needed to update PT
                correct512++; total512++;
                if(predictList[4]==true){
                    predictor4_PT512[addr%512]+=1;//if T is right, add 1
                    if(predictor4_PT512[addr%512]>3){
                        predictor4_PT512[addr%512]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[4]==false){
                    predictor4_PT512[addr%512]-=1;//if NT is right, subtract 1 
                    if(predictor4_PT512[addr%512]<0){
                        predictor4_PT512[addr%512]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            }
            if(predictList[5]!=result){
                //this prediction is wrong. increment total. more logic is needed to update PT
                total1024++;
                if(predictList[5]==false) {
                    predictor4_PT1024[addr%1024]+=1;//if NT is wrong, add 1
                    if(predictor4_PT1024[addr%1024]>3){
                        predictor4_PT1024[addr%1024]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[5]==true){
                    predictor4_PT1024[addr%1024]-=1;//if T is wrong, subtract 1
                    if(predictor4_PT1024[addr%1024]<0){
                        predictor4_PT1024[addr%1024]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            } else {
                //this prediction is correct. increment correct and total. more logic is needed to update PT
                correct1024++; total1024++;
                if(predictList[5]==true){
                    predictor4_PT1024[addr%1024]+=1;//if T is right, add 1
                    if(predictor4_PT1024[addr%1024]>3){
                        predictor4_PT1024[addr%1024]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[5]==false){
                    predictor4_PT1024[addr%1024]-=1;//if NT is right, subtract 1 
                    if(predictor4_PT1024[addr%1024]<0){
                        predictor4_PT1024[addr%1024]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            }
            if(predictList[6]!=result){
                //this prediction is wrong. increment total. more logic is needed to update PT
                total2048++;
                if(predictList[6]==false) {
                    predictor4_PT2048[addr%2048]+=1;//if NT is wrong, add 1
                    if(predictor4_PT2048[addr%2048]>3){
                        predictor4_PT2048[addr%2048]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[6]==true){
                    predictor4_PT2048[addr%2048]-=1;//if T is wrong, subtract 1
                    if(predictor4_PT2048[addr%2048]<0){
                        predictor4_PT2048[addr%2048]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            } else {
                //this prediction is correct. increment correct and total. more logic is needed to update PT
                correct2048++; total2048++;
                if(predictList[6]==true){
                    predictor4_PT2048[addr%2048]+=1;//if T is right, add 1
                    if(predictor4_PT2048[addr%2048]>3){
                        predictor4_PT2048[addr%2048]=3;//if adding 1 goes over 3, set to 3
                    }
                }
                else if(predictList[6]==false){
                    predictor4_PT2048[addr%2048]-=1;//if NT is right, subtract 1 
                    if(predictor4_PT2048[addr%2048]<0){
                        predictor4_PT2048[addr%2048]=0;//if subtracting 1 goes below 0, set to 0
                    }
                }
            }
            
        }
        void printCorrect(){
            std::cout<< correct16 <<"," <<total16 << "; ";
            std::cout<< correct32 <<"," <<total32 << "; ";
            std::cout<< correct128 << ","<<total128 << "; ";
            std::cout<< correct256<< ","<< total256<< "; ";
            std::cout<< correct512<< ","<< total512<< "; ";
            std::cout<< correct1024<< ","<< total1024<< "; ";
            std::cout<< correct2048<< ","<< total2048<< "; " <<std::endl;
        }
};
//Gshare predictor
class predictor5{
    private:
    public:
        bool predict5(unsigned long long addr){

        }

};
//tournament predictor (Gshare || 2-bit bimodal)
class predictor6{
    
};    
//Branch Target Buffer
class predictor7{

};

#endif