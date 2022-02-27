//Sai Kasam, Sxk200161
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

int getRows(ifstream &input){
    string temp;
    int row = 0;
    while(!input.eof()){
        if(input.peek() != -1){
            getline(input,temp);
            row += 1;
        }
    }
    input.clear();
    return row;
}

void loadCoefficient(ifstream &input, char temp,double&x,double&y,double&z, bool negative){
    int num;
    if(isdigit(temp)){
            input >> num;
            if (negative){num *= -1;}
            input >> temp; //gets the variable
            switch(temp) {
                case 'x':
                    x = num;
                    break;
                case 'y':
                    y = num;
                    break;
                case 'z':
                    z = num;
                    break;
            }
        }
    else{
        switch(temp) {
            case 'x'  :
                if(negative){x = -1;}
                else{x = 1;}
                break;
            case 'y'  :
                if(negative){y = -1;}
                else{y = 1;}
                break;
            case 'z'  :
                if(negative){z = -1;}
                else{z = 1;}
                break;
        }
    }
}
void getData(double *arr,ifstream &input, int rows){
    char temp;
    double x,y,z,c;
    double *ptr;
    bool negative = false;
    while(rows>0){
        if(char(input.peek()) == '-'){
            negative = true;
            input >> temp;
        }
        temp = char(input.peek());
        loadCoefficient(input, temp,x,y,z,negative);
        negative = false;;
        while(temp != '+' && temp != '-'){
            input >> temp;
        }
        if(temp == '-'){ negative = true;}
        //got first coefficient
        temp = char(input.peek());
        loadCoefficient(input, temp,x,y,z,negative);
        negative = false;
        //got second coefficient
        while(temp != '+' && temp != '-'){
            input >> temp;
        }
        if(temp == '-'){ negative = true;}
        temp = char(input.peek());
        loadCoefficient(input, temp,x,y,z,negative);
        negative = false;
        while(temp != '='){
            input >> temp;
        }
        //got third coefficient
        if(char(input.peek()) == '-'){
            negative = true;
            input >> temp;
        }
        temp = char(input.peek());
        if(isdigit(temp)){
            input >> c;
            input.get(temp);
        }
        else{
            c = 1;
            input.get(temp);
        }
        if (negative){
            c *= -1;
        }
        negative = false;
        
        ptr = arr;
        *arr = x;
        arr += 1;
        *arr = y;
        arr += 1;
        *arr = z;
        arr += 1;
        *arr = c;
        arr += 1;
        // for(int i = 0; i < 4; i++){
        //     cout << fixed << setprecision(2) << *ptr << " ";
        //     ptr += 1;
        // }
        rows -= 1;
        cout << endl;
    }
}

void multiplyRow(double *arr, int row, double num){
    double *ptr = arr;
    row --;
    ptr += (row*4);
    for(int i = 0; i < 4; i++){
        *ptr *= num;
        ptr++;
    }
    ptr -= 4;
    // cout << "new row" << endl;
    ptr = arr;
}

int main()
{
    double *arr;
    int command;
    string filename;
    int multiplyIn1;
    double multiplyIn2;
    double *tempPtr;
    cout << "Please enter the input file name:" << endl;
    cin >> filename;
    // filename = "sample.txt";
    ifstream input(filename);
    if (!input){
        cout << "File could not be opened";
        return 1;
    }
    int rows = getRows(input);
    arr = new double [4*rows];
    input.seekg(0L);
    getData(arr,input,rows);
    input.close();
    tempPtr = arr;
    for(int j = 0; j<rows; j++){
        for(int i = 0; i < 4; i++){
            cout << fixed << setprecision(2) << *tempPtr << " ";
            tempPtr += 1;
        }
        cout << endl;
    }
    while (true){
        cout << "Enter command" << endl;
        cin >> command;
        switch(command){
            case 2:
                cin >> multiplyIn1 >> multiplyIn2;
                multiplyRow(arr,multiplyIn1,multiplyIn2);
                break;
            case 4:
                for(int j = 0; j<rows; j++){
                    for(int i = 0; i < 4; i++){
                        cout << fixed << setprecision(2) << *arr << " ";
                        arr += 1;
                    }
                    cout << endl;
                }
                return 0;
        }
    }
    return 0;
}





















