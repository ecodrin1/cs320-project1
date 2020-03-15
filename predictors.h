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
        bool predict1(){
            return true;
        }
        void update(bool result){
            if(result==predict1()){
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
        bool predict2(){
            return false;
        }
        void update(bool result){
            if(result==predict2()){
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
            for(unsigned int i=0; i<predictor3_PT16.size(); i++){
                predictor3_PT16[i]=true;
            }
            for(unsigned int i=0; i<predictor3_PT32.size(); i++){
                predictor3_PT32[i]=true;
            }
            for(unsigned int i=0; i<predictor3_PT128.size(); i++){
                predictor3_PT128[i]=true;
            }
            for(unsigned int i=0; i<predictor3_PT256.size(); i++){
                predictor3_PT256[i]=true;
            }
            for(unsigned int i=0; i<predictor3_PT512.size(); i++){
                predictor3_PT512[i]=true;
            }
            for(unsigned int i=0; i<predictor3_PT1024.size(); i++){
                predictor3_PT1024[i]=true;
            }
            for(unsigned int i=0; i<predictor3_PT2048.size(); i++){
                predictor3_PT2048[i]=true;
            }
        }
        bool getPrediction(int index){
            return predictList[index];
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
        void update(bool result, unsigned long long addr){
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
            for(unsigned int i=0; i<predictor4_PT16.size(); i++){
                predictor4_PT16[i]=3;
            }
            for(unsigned int i=0; i<predictor4_PT32.size(); i++){
                predictor4_PT32[i]=3;
            }
            for(unsigned int i=0; i<predictor4_PT128.size(); i++){
                predictor4_PT128[i]=3;
            }
            for(unsigned int i=0; i<predictor4_PT256.size(); i++){
                predictor4_PT256[i]=3;
            }
            for(unsigned int i=0; i<predictor4_PT512.size(); i++){
                predictor4_PT512[i]=3;
            }
            for(unsigned int i=0; i<predictor4_PT1024.size(); i++){
                predictor4_PT1024[i]=3;
            }
            for(unsigned int i=0; i<predictor4_PT2048.size(); i++){
                predictor4_PT2048[i]=3;
            }
        }
        bool getPrediction(int index){
            return predictList[index];
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
        void update(bool result, unsigned long long addr){
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
        std::array<int, 2048> predictor5_PT;
        bool predictList[9];
        unsigned int correct3b,total3b, correct4b,total4b, correct5b, total5b, correct6b, total6b, correct7b, total7b, correct8b, total8b, correct9b,total9b, correct10b, total10b, correct11b, total11b= 0;
        unsigned int GHR3, GHR4, GHR5, GHR6, GHR7, GHR8, GHR9, GHR10, GHR11=0;
        //predictor4* ghr_PT;
    public:
        predictor5(){
            for(unsigned int i=0; i<predictor5_PT.size(); i++){
                predictor5_PT[i]=3; //initialize PT to TT/0b11/3
            }
        }
        bool getPrediction(int index){
            return predictList[index];
        }
        void predict5(unsigned long long addr){
            //Mask GHRs with modulo
            GHR3= GHR3%8; //ensures GHR-X is X-bits
            GHR4= GHR4%16;
            GHR5= GHR5%32;
            GHR6= GHR6%64;
            GHR7= GHR7%128;
            GHR8= GHR8%256;
            GHR9= GHR9%512;
            GHR10= GHR10%1024;
            GHR11= GHR11%2048;
            //index= addr xor GHR (from 3-bit to 11-bit sized GHRs)
            //guess with PT[index]
            predictList[0]= predictor5_PT[(GHR3^(addr%2048))]>1? true:false;
            predictList[1]= predictor5_PT[(GHR4^(addr%2048))]>1? true:false;
            predictList[2]= predictor5_PT[(GHR5^(addr%2048))]>1? true:false;
            predictList[3]= predictor5_PT[(GHR6^(addr%2048))]>1? true:false;
            predictList[4]= predictor5_PT[(GHR7^(addr%2048))]>1? true:false;
            predictList[5]= predictor5_PT[(GHR8^(addr%2048))]>1? true:false;
            predictList[6]= predictor5_PT[(GHR9^(addr%2048))]>1? true:false;
            predictList[7]= predictor5_PT[(GHR10^(addr%2048))]>1? true:false;
            predictList[8]= predictor5_PT[(GHR11^(addr%2048))]>1? true:false;
        }
        void update(bool result, unsigned long long addr){
            //for each GHR size:
                //use bimodal update on PC[index] (if right or wrong)
            if(predictList[0]!= result){
                total3b++;//wrong. increment total only
                if(predictList[0]==true){
                    predictor5_PT[(GHR3^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR3^(addr%2048))]<0){
                        predictor5_PT[(GHR3^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[0]==false){
                    predictor5_PT[(GHR3^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR3^(addr%2048))]>3){
                        predictor5_PT[(GHR3^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[0]==result){
                total3b++; correct3b++; //correct. increment total and correct
                if(predictList[0]==true){
                    predictor5_PT[(GHR3^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR3^(addr%2048))]>3){
                        predictor5_PT[(GHR3^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[0]==false){
                    predictor5_PT[(GHR3^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR3^(addr%2048))]<0){
                        predictor5_PT[(GHR3^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }

            if(predictList[1]!= result){
                total4b++;//wrong. increment total only
                if(predictList[1]==true){
                    predictor5_PT[(GHR4^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR4^(addr%2048))]<0){
                        predictor5_PT[(GHR4^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[1]==false){
                    predictor5_PT[(GHR4^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR4^(addr%2048))]>3){
                        predictor5_PT[(GHR4^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[1]==result){
                total4b++; correct4b++; //correct. increment total and correct
                if(predictList[1]==true){
                    predictor5_PT[(GHR4^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR4^(addr%2048))]>3){
                        predictor5_PT[(GHR4^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[1]==false){
                    predictor5_PT[(GHR4^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR4^(addr%2048))]<0){
                        predictor5_PT[(GHR4^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }

            if(predictList[2]!= result){
                total5b++;//wrong. increment total only
                if(predictList[2]==true){
                    predictor5_PT[(GHR5^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR5^(addr%2048))]<0){
                        predictor5_PT[(GHR5^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[2]==false){
                    predictor5_PT[(GHR5^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR5^(addr%2048))]>3){
                        predictor5_PT[(GHR5^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[2]==result){
                total5b++; correct5b++; //correct. increment total and correct
                if(predictList[2]==true){
                    predictor5_PT[(GHR5^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR5^(addr%2048))]>3){
                        predictor5_PT[(GHR5^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[2]==false){
                    predictor5_PT[(GHR5^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR5^(addr%2048))]<0){
                        predictor5_PT[(GHR5^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }

            if(predictList[3]!= result){
                total6b++;//wrong. increment total only
                if(predictList[3]==true){
                    predictor5_PT[(GHR6^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR6^(addr%2048))]<0){
                        predictor5_PT[(GHR6^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[3]==false){
                    predictor5_PT[(GHR6^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR6^(addr%2048))]>3){
                        predictor5_PT[(GHR6^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[3]==result){
                total6b++; correct6b++; //correct. increment total and correct
                if(predictList[3]==true){
                    predictor5_PT[(GHR6^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR6^(addr%2048))]>3){
                        predictor5_PT[(GHR6^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[3]==false){
                    predictor5_PT[(GHR6^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR6^(addr%2048))]<0){
                        predictor5_PT[(GHR6^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }

            if(predictList[4]!= result){
                total7b++;//wrong. increment total only
                if(predictList[4]==true){
                    predictor5_PT[(GHR7^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR7^(addr%2048))]<0){
                        predictor5_PT[(GHR7^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[4]==false){
                    predictor5_PT[(GHR7^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR7^(addr%2048))]>3){
                        predictor5_PT[(GHR7^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[4]==result){
                total7b++; correct7b++; //correct. increment total and correct
                if(predictList[4]==true){
                    predictor5_PT[(GHR7^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR7^(addr%2048))]>3){
                        predictor5_PT[(GHR7^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[4]==false){
                    predictor5_PT[(GHR7^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR7^(addr%2048))]<0){
                        predictor5_PT[(GHR7^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }
            if(predictList[5]!= result){
                total8b++;//wrong. increment total only
                if(predictList[5]==true){
                    predictor5_PT[(GHR8^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR8^(addr%2048))]<0){
                        predictor5_PT[(GHR8^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[5]==false){
                    predictor5_PT[(GHR8^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR8^(addr%2048))]>3){
                        predictor5_PT[(GHR8^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[5]==result){
                total8b++; correct8b++; //correct. increment total and correct
                if(predictList[5]==true){
                    predictor5_PT[(GHR8^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR8^(addr%2048))]>3){
                        predictor5_PT[(GHR8^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[5]==false){
                    predictor5_PT[(GHR8^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR8^(addr%2048))]<0){
                        predictor5_PT[(GHR8^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }

            if(predictList[6]!= result){
                total9b++;//wrong. increment total only
                if(predictList[6]==true){
                    predictor5_PT[(GHR9^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR9^(addr%2048))]<0){
                        predictor5_PT[(GHR9^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[6]==false){
                    predictor5_PT[(GHR9^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR9^(addr%2048))]>3){
                        predictor5_PT[(GHR9^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[6]==result){
                total9b++; correct9b++; //correct. increment total and correct
                if(predictList[6]==true){
                    predictor5_PT[(GHR9^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR9^(addr%2048))]>3){
                        predictor5_PT[(GHR9^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[6]==false){
                    predictor5_PT[(GHR9^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR9^(addr%2048))]<0){
                        predictor5_PT[(GHR9^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }

            if(predictList[7]!= result){
                total10b++;//wrong. increment total only
                if(predictList[7]==true){
                    predictor5_PT[(GHR10^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR10^(addr%2048))]<0){
                        predictor5_PT[(GHR10^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[7]==false){
                    predictor5_PT[(GHR10^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR10^(addr%2048))]>3){
                        predictor5_PT[(GHR10^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[7]==result){
                total10b++; correct10b++; //correct. increment total and correct
                if(predictList[7]==true){
                    predictor5_PT[(GHR10^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR10^(addr%2048))]>3){
                        predictor5_PT[(GHR10^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[7]==false){
                    predictor5_PT[(GHR10^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR10^(addr%2048))]<0){
                        predictor5_PT[(GHR10^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }

            if(predictList[8]!= result){
                total11b++;//wrong. increment total only
                if(predictList[8]==true){
                    predictor5_PT[(GHR11^(addr%2048))]-=1;//if T is wrong, subtract 1 from PT used
                    if(predictor5_PT[(GHR11^(addr%2048))]<0){
                        predictor5_PT[(GHR11^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }    
                }
                else if(predictList[8]==false){
                    predictor5_PT[(GHR11^(addr%2048))]+=1;//if NT is wrong, add 1 to PT
                    if(predictor5_PT[(GHR11^(addr%2048))]>3){
                        predictor5_PT[(GHR11^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                }
            } else if(predictList[8]==result){
                total11b++; correct11b++; //correct. increment total and correct
                if(predictList[8]==true){
                    predictor5_PT[(GHR11^(addr%2048))]+=1;//if T is right, add 1 to PT
                    if(predictor5_PT[(GHR11^(addr%2048))]>3){
                        predictor5_PT[(GHR11^(addr%2048))]=3;//if adding 1 goes above 3, set PT to 3
                    }
                } else if(predictList[8]==false){
                    predictor5_PT[(GHR11^(addr%2048))]-=1;//if NT is right, subtract 1 from PT
                    if(predictor5_PT[(GHR11^(addr%2048))]<0){
                        predictor5_PT[(GHR11^(addr%2048))]=0;//if subtracting 1 goes below 0, set PT to 0
                    }
                }
            }
            //update each GHR
            if(result==true){
                //shift bits left by 1 and add 1 (T)
                GHR3= (GHR3<<1) +1;
                GHR4= (GHR4<<1) +1;
                GHR5= (GHR5<<1) +1;
                GHR6= (GHR6<<1) +1;
                GHR7= (GHR7<<1) +1;
                GHR8= (GHR8<<1) +1;
                GHR9= (GHR9<<1) +1;
                GHR10= (GHR10<<1) +1;
                GHR11= (GHR11<<1) +1;
            }
            else {
                //shift bits left by 1 and add 0 (NT)
                GHR3= GHR3<<1;
                GHR4= GHR4<<1;
                GHR5= GHR5<<1;
                GHR6= GHR6<<1;
                GHR7= GHR7<<1;
                GHR8= GHR8<<1;
                GHR9= GHR9<<1;
                GHR10= GHR10<<1;
                GHR11= GHR11<<1;
            }
        }
        void printCorrect(){
            std::cout<< correct3b <<","<< total3b<<"; ";
            std::cout<< correct4b <<","<< total4b<<"; ";
            std::cout<< correct5b <<","<< total5b<<"; ";
            std::cout<< correct6b <<","<< total6b<<"; ";
            std::cout<< correct7b <<","<< total7b<<"; ";
            std::cout<< correct8b <<","<< total8b<<"; ";
            std::cout<< correct9b <<","<< total9b<<"; ";
            std::cout<< correct10b <<","<< total10b<<"; ";
            std::cout<< correct11b <<","<< total11b<<"; " <<std::endl;



        }

};
//tournament predictor (Gshare + 2-bit bimodal)
class predictor6{
    private:
        std::array<int, 2048> predictor6_ST; //instead of a predictor table, we have a selector table now
        predictor4* bimodal; //only use 2048 entry
        predictor5* gshare; //only use 2048 entry
        bool prediction;
        bool bimodal_prediction;
        bool gshare_prediction;
        int correct, total=0;
    public:
        predictor6(){
            for(unsigned int i=0; i<predictor6_ST.size(); i++){
                predictor6_ST[i]=0; //set ST to 00/strong Gshare
            }
            bimodal= new predictor4();
            gshare= new predictor5();
        }
        ~predictor6(){
            delete bimodal;
            delete gshare;
        }
        void predict6(unsigned long long addr){
            bimodal->predict4(addr);
            gshare->predict5(addr);
            bimodal_prediction= bimodal->getPrediction(6); //prediction from 2048 entry
            gshare_prediction= gshare->getPrediction(8); //prediction from 2048 entry table
            prediction= predictor6_ST[addr%2048]>1? bimodal_prediction:gshare_prediction; //10/11 for bimodal, 00,01 for gshare
        }
        void update(bool result, unsigned long long addr){
            gshare->update(result, addr);
            bimodal->update(result, addr);
            if(result==prediction){
                correct++; total++;
            } else {
                total++;
            }
            if(bimodal_prediction==gshare_prediction){
                return;// do nothing, they both are really good.. or really dumb
            } else if(result==bimodal_prediction){
                predictor6_ST[addr%2048]+=1;// ST++ to favor bimodal, since it was right
                if(predictor6_ST[addr%2048]>3){
                    predictor6_ST[addr%2048]=3;//if over 3, set to 3
                }
            } else if(result==gshare_prediction){
                predictor6_ST[addr%2048]-=1; //ST-- to favor gshare, since it was right
                if(predictor6_ST[addr%2048]<0){
                    predictor6_ST[addr%2048]=0;
                }
            }
        }
        void printCorrect(){
            std::cout<< correct<< ","<<total<< "; "<< std::endl;
        }  
};    
//Branch Target Buffer
class predictor7{
    private:
        predictor3* bimodal; //use 512 only
        std::array<unsigned long long, 512> buffer; //buffer of.. addresses?
        int correct, attempted=0;
        bool bimodal_prediction;
        unsigned long long prediction;
    public:
        predictor7(){
            bimodal= new predictor3();
            for(unsigned int i=0; i<buffer.size(); i++){
                buffer[i]=0;
            }
        }
        ~predictor7(){
            delete bimodal;
        }
        void predict7(unsigned long long addr){
            bimodal->predict3(addr);
            bimodal_prediction= bimodal->getPrediction(4);
            if(bimodal_prediction==true){
                attempted++;
                prediction= buffer[addr%512]; //we access buffer if bimodal predicts T
            } else {
                prediction= addr+4;
            }
            
        }
        void update(bool result, unsigned long long addr, unsigned long long target){
            //if result is true, set buffer[] to target
            bimodal->update(result, addr);
            if(result==true){
                buffer[addr%512]= target;
            }
            if((prediction==target)&& (bimodal_prediction==true)){
                correct++;
            }
        }
        void printCorrect(){
            std::cout<< correct<< ","<< attempted<< "; "<< std::endl;
        }
};

#endif