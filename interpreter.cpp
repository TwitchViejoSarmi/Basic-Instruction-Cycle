#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#define MEMSIZE 512

using namespace std;

class CPU{
    private:
    int Memory[MEMSIZE];
    int accumulator;
    char ICR[20];
    char MAR[5];
    int MDR;
    bool is_paused;
    public:
    char UC[20];

    CPU(){
        this->accumulator = 0;
        this->UC[0] = '\0';
        this->ICR[0] = '\0';
        this->MAR[0] = '\0';
        this->MDR = 0;
        this->is_paused = false;
    }

    // Destructor.
    ~CPU(){}

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
        cout << this->Memory[convertedaddress-1] << endl;
    }
    else{
        if (!this->is_paused){
            if (strcmp(address, "ACC")==0){
                cout << this->accumulator << endl;
            }
            else if (strcmp(address, "MAR")==0){
                cout << this->MAR << endl;
            }
            else if (strcmp(address, "MDR")==0){
                cout << this->MDR << endl;
            }
            else if (strcmp(address, "ICR")==0){
                cout << this->ICR << endl;
            }
            else if (strcmp(address, "UC")==0){
                cout << this->UC << endl;
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
        return;
    }
};


// Function extracted from internet to simulate the split function of Python.
vector<char*> split(const char* s, char delimiter) {
    vector<char*> tokens;
    char* token = strtok(const_cast<char*>(s), &delimiter);
    
    while (token != nullptr) {
        tokens.push_back(token);
        token = strtok(nullptr, &delimiter);
    }
    
    return tokens;
}

int main() {
    // Program 1:
    cout << "PROGRAM 1:" << endl;
    ifstream file1("input/programa1.txt"); // Abre el primer archivo.
    char* line; // Tamaño de la línea

    if (file1.is_open()) { // Verifica si el archivo se abrió correctamente
        while (file1.getline(line, sizeof(line))) { // Lee cada línea del archivo
            cout << line << endl; // Imprime la línea en la consola
        }
        file1.close(); // Cierra el archivo después de leerlo
    } else {
        cerr << "Unable to open file 1." << endl; // Mensaje de error si no se puede abrir el archivo
    }
    return 0;
}

main();