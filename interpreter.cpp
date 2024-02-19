#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#define MEMSIZE 512

using namespace std;

class CPU{
    public:
    int Memory[MEMSIZE];
    int accumulator;
    char UC[20];
    char ICR[20];
    char MAR[5];
    int MDR;
    bool is_paused;

    void SET(char *address, char *num) {
        // Move the pointer of the string to the next char ('Dn' -> 'D', n).
        int convertedaddress = stoi(address+1);
        this->Memory[convertedaddress-1] = stoi(num);
        return;
    }

    void LDR(char *address){
        // Move the pointer of the string to the next char ('Dn' -> 'D', n).
        int convertedaddress = stoi(address+1);
        this->accumulator = this->Memory[convertedaddress-1];
        strcpy(this->MAR, address);
        this->MDR = this->Memory[convertedaddress-1];
    }

    void STR(char *address){
        // Move the pointer of the string to the next char ('Dn' -> 'D', n).
        int convertedaddress = stoi(address+1);
        this->Memory[convertedaddress-1] = this->accumulator;
        strcpy(this->MAR, address);
        this->MDR = this->Memory[convertedaddress-1];
        return;
    }

    void ADD(char *address1, char *address2, char *address3){
        // Move the pointer of the string to the next char ('Dn' -> 'D', n).
        int convertedaddress1 = stoi(address1+1);
        int convertedaddress2 = stoi(address2+1);
        int convertedaddress3 = stoi(address3+1);

        // OPTION 1: ADD ADDR NULL NULL.
        if (strcmp(address1, "NULL") != 0 && strcmp(address2, "NULL") == 0 && strcmp(address3, "NULL") == 0) {
            this->accumulator = this->accumulator + this->Memory[convertedaddress1-1];
            strcpy(this->MAR, address1); // Copy the address to the MAR.
            this->MDR = this->Memory[convertedaddress1-1];
        }
        // OPTION 2: ADD ADDR1 ADDR2 NULL.
        else if (strcmp(address1, "NULL") != 0 && strcmp(address2, "NULL") != 0 && strcmp(address3, "NULL") == 0) {
            this->accumulator = this->Memory[convertedaddress1-1] + this->Memory[convertedaddress2-1];
            strcpy(this->MAR, address2);
            this->MDR = this->Memory[convertedaddress2-1];
        }
        // OPTION 3: ADD ADDR1 ADDR2 ADDR3.
        else {
            this->accumulator = this->Memory[convertedaddress1-1] + this->Memory[convertedaddress2-1];
            this->Memory[convertedaddress3-1] = this->accumulator;
            strcpy(this->MAR, address3);
            this->MDR = this->Memory[convertedaddress3-1];
        }
        return;
    }

    void INC(char *address){
        this->LDR(address);
        this->accumulator++;
        this->STR(address);
        return;
    }

    void DEC(char *address){
        this->LDR(address);
        this->accumulator--;
        this->STR(address);
        return;
    }

    void SHW(char *address){
        if (address[0] == 'D'){
            // Move the pointer of the string to the next char ('Dn' -> 'D', n).
            int convertedaddress = stoi(address+1);
            printf("%d\n", this->Memory[convertedaddress-1]);
        }
        else{
            if (!this->is_paused){
                if (strcmp(address, "ACC")==0){
                    printf("%d\n", this->accumulator);
                }
                else if (strcmp(address, "MAR")==0){
                    printf("%d\n", this->MAR);
                }
                else if (strcmp(address, "MDR")==0){
                    printf("%d\n", this->MDR);
                }
                else if (strcmp(address, "ICR")==0){
                    printf("%d\n", this->ICR);
                }
                else if (strcmp(address, "UC")==0){
                    printf("%d\n", this->UC);
                }
            }
        }        

        return;
    }

    void PAUSE(){
        if (this->is_paused){
            this->is_paused = false;
        }
        else{
            this->is_paused = true;
        }
    }
};