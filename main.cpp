#include <iostream>
#include <fstream>
#include "token.h"


using namespace std;
int main() {

    //FILE PARSING
    ifstream inFile;

    inFile.open("tokens.txt");

    if(!inFile) {
        cout << "File failed to open." << endl;
    }
    else {
        cout << "File opened." << endl;
    }

    string temp;
    int count = 0;
    while (getline(inFile, temp)) {
        count++;
    }
    inFile.close();

    token* tArray = new token[count];

    inFile.open("tokens.txt");

    if (!inFile) {
        cout << "File failed to open" << endl;
    }
    count = 0;
    while (getline(inFile, temp)) {
        for (int j = 0; j < temp.size(); j++) {
            tArray[count].pushback(temp[j]);
        }
        tArray[count].pushback('\0');
        tArray[count].setScore();
        count++;
    }
    cout << "Data in File: " << endl;
    for (int i = 0; i < count; i++) {
        tArray[i].printData();
    }
    cout << endl;

    //DATA ANALYSIS

    token result;
    token letters, numbers;
    for (int i = 0; i < temp.size(); i++) {
        bool same = true;
        char compare = tArray[0].getCh(i);
        for (int j = 0; j < count - 1; j++) {
            if (compare != tArray[j + 1].getCh(i)) {
                same = false;
            }
        }
        if (same) {
            result.pushback(tArray[0].getCh(i));
        }
    }

    //PRINT REPORT
    cout << "Token pattern: " << endl;
    result.printData();
    cout << endl;

    cout << "Token pattern reversed: " << endl;
    result.printDataRev();
    cout << endl;

    /*cout << "Token pattern details: " << endl;
    result.printDetails();
    cout << endl;*/

    cout << "Token pattern letters:" << endl;
    result.printAlpha();
    cout << endl;

    cout << "Token pattern numbers: " << endl;
    result.printNum();
    cout << endl;


    //MENU
    string in;

    while (in != "EXIT") {
        cout << "Commands: " << endl;
        cout << "1: (Encrypt) Encode to Base64" << endl;
        cout << "2: (Encrypt) Hexadecimal to Base64" << endl;
        cout << "3: (Encrypt) String to Hexadecimal" << endl;
        cout << "4: (Encrypt) Hexadecimal to String" << endl;
        cout << "5: (Encrypt) HexString XOR Repeating Key" << endl;
        cout << "6: (Decrypt) Decode Base64" << endl;
        cout << "7: (Decrypt) String XOR Key" << endl;
        cout << "8: (Decrypt) HexString XOR Key" << endl;
        cout << "9: (Decrypt) Break Single XOR Key" << endl;
        cout << "10: (Decrypt) Break Repeating XOR Key" << endl;
        cout << "11: Letter Score" << endl;
        cout << "Enter \"EXIT\" to quit." << endl;

        cin >> in;

        if (in == "1") {
            cout << "DATA ENCODED TO BASE64: " << endl;

            token* t64 = new token[count];
            for (int i = 0; i < count; i++) {
                t64[i] = encode64(tArray[i].getData());
                t64[i].printData();
            }

            delete[] t64;
        }
        else if(in == "2") {
            cout << "HEXADECIMAL DATA ENCODED TO BASE64: " << endl;

            token* hex64 = new token[count];
            for (int i = 0; i < count; i++) {
                hex64[i] = hexTo64(tArray[i].getData());
                hex64[i].printData();
            }
            delete[] hex64;
        }
        else if (in == "3") {
            string hex;
            for (int i = 0; i < count; i++) {
                hex = bytesToHexString(tArray[i].getData());
                cout << hex << endl;
            }
        }
        else if (in == "4") {
            string plaintext;
            for (int i = 0; i < count; i++) {
                plaintext = hexStringToBytes(tArray[i].getData());
                cout << plaintext << endl;
            }
        }
        else if (in == "5"){
            string key;
            cout << "Enter Key:" << endl;
            cin >> key;

            cout << "Encrypted Data: " << endl;

            token* sort = new token[count];
            for (int i = 0; i < count; i++) {
                string tmp = tArray[i].getData();
                tmp = hexStringToBytes(tmp);
                tmp = xorRepeat(tmp, key);
                cout << tmp << endl;
            }
        }
        else if (in == "6") {
            string plaintext;
            for (int i = 0; i < count; i++) {
                plaintext = decode64(tArray[i].getData());
                cout << plaintext << endl;
            }
        }
        else if (in == "7") {
            char ch;
            cout << "ENTER KEY: ";
            cin >> ch;
            cout << endl;

            for (int i = 0; i < count; i++) {
                cout << xorSingleByte(tArray[i].getData(), ch) << endl;
            }
        }
        else if(in == "8") {
            token* sort = new token[count];
            char ch;
            cout << "ENTER KEY: ";
            cin >> ch;

            for (int i = 0; i < count; i++) {
                string tmp = tArray[i].getData();
                tmp = hexStringToBytes(tmp);
                tmp = xorSingleByte(tmp, ch);
                sort[i] = tmp;
            }

            sortByScore(sort, 0, count - 1);

            cout << endl << "BEST LETTER SCORES: " << endl << endl;

            for (int i = 0; i < 10; i++) {
                cout << "Data: ";
                sort[i].printData();
                sort[i].printScore();
                cout << endl;
            }
        }
        else if (in == "9") {
            string plaintext;
            plaintext = xorBreakSingleKey(tArray, count);
            cout << "PLAINTEXT: " << plaintext << endl;
        }
        else if (in == "10") {
            string ciphertext;
            for (int i = 0; i < count; i++) {
                ciphertext += tArray[i].getData();
            }

            ciphertext = decode64(ciphertext);
            ciphertext = hexStringToBytes(ciphertext);
            string guessKey = breakRepeatingKey(ciphertext);

            cout << "TESTING GUESSED KEY: " << guessKey << endl << endl;
            ciphertext = bytesToHexString(ciphertext);

            string plaintext;

            plaintext = xorRepeatDecrypt(ciphertext, guessKey);
            cout << plaintext << endl;
        }
        else if(in == "11") {
            token* sort = new token[count];
            for (int i = 0; i < count; i++) {
                sort[i] = tArray[i];
            }
            sortByScore(sort, 0, count - 1);
            for (int i = 0; i < count; i++) {
                cout << "Data: ";
                sort[i].printData();
                sort[i].printScore();
            }
        }
        else if (in != "EXIT"){
            cerr << "[ERROR] Command not recognized." << endl;
        }
        cout << endl;

    }



    delete[] tArray;
    inFile.close();

    return 0;
}