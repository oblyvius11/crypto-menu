//
// Created by aegra on 11/22/2023.
//

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

#ifndef CANYOUHACKUS_TOKEN_H
#define CANYOUHACKUS_TOKEN_H

class token {
private:
    int size, capacity;
    char* data;
    double score;
public:
    token() {
        size = 0;
        capacity = 5;
        data = new char[capacity];
        score = 0;
    }

    token(int capacity) {
        size = 0;
        this->capacity = capacity;
        data = new char[this->capacity];
        score = 0;
    }

    token(const token& other) {
        size = other.size;
        capacity = other.capacity;
        data = new char[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        data[size] = '\0';
        score = other.score;
    }

    token& operator=(const token& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new char[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
            data[size] = '\0';
            score = other.score;
        }
        return *this;
    }

    ~token() {
        delete[] data;
    }

    void pushback(char ch) {
        if (size == capacity) {
            capacity += 5;
            char* tmp = new char[capacity];

            for (int i = 0; i < size; i++) {
                tmp[i] = data[i];
            }

            delete[] data;
            data = tmp;
        }
        data[size] = ch;
        size++;
    }

    token& operator+(string str) {
        for (size_t i = 0; i < str.size(); i++) {
            pushback(str.at(i));
        }
        data[size] = '\0';
        return *this;
    }

    token& operator=(const string& str) {
        delete[] data;
        size = str.size();
        capacity = str.size() + 1;
        while (capacity % 5 != 0) {
            capacity++;
        }
        data = new char[capacity];
        for (size_t i = 0; i < str.size(); i++) {
            data[i] = str.at(i);
        }
        data[size] = '\0';
        setScore();
        return *this;
    }

    double calculateScore() {
        const double expectedFrequency[] = {
                8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
                0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
                2.758, 0.978, 2.361, 0.150, 1.974, 0.074
        };
        score = 0;
        char ch;
        for (int i = 0; i < size; i++) {
            ch = data[i];
            if (isalpha(ch)) {
                // Convert to uppercase for simplicity
                ch = toupper(ch);
                int index = ch - 'A';

                score += log(expectedFrequency[index]);
            }
        }

        return score;
    }

    void printData() const {
        for (int i = 0; i < size; i++) {
            cout << data[i];
        }
        cout << endl;
    }

    void printDataRev() const {
        for (int i = size - 1; i >= 0; i--) {
            cout << data[i];
        }
        cout << endl;
    }

    void printAlpha() const {
        for (int i = 0; i < size; i++) {
            if (isalpha(data[i])) {
                cout << data[i];
            }
        }
        cout << endl;
    }

    void printNum() const {
        for (int i = 0; i < size; i++) {
            if(isdigit(data[i])) {
                cout << data[i];
            }
        }
        cout << endl;
    }

    void printScore() const {
        cout << "LETTER SCORE: " << score << endl;
    }

    void printDetails() const {
        cout << "Size: " << size << endl;
        cout << "Capacity: " << capacity << endl;
    }

    char getCh(int ndx) {
        if (ndx >= size) {
            return -1;
        }
        else {
            return data[ndx];
        }
    }

    string getData() const {
        return string(data);
    }

    void setScore() {
        score = calculateScore();
    }

    double getScore() {
        return score;
    }
};

struct key {
    int keySize;
    double distance;
};

string intToString (int val) {
    string result, temp;
    while (val != 0) {
        temp.push_back((val % 10) + 48);
        val /= 10;
    }
    for (int i = temp.size() - 1; i >= 0; i--) {
        result.push_back(temp.at(i));
    }
    return result;
}

long long int stringToInt(string in) {
    long long int num = 0;
    for (int i = 0; i < in.size(); i++) {
        num *= 10;
        num += (in.at(i) - 48);
    }
    return num;
}

string decToBinary(int num, int bit = 8) {
    int temp = 0;
    string result;
    while (num != 0) {
        temp = num % 2;
        num /= 2;
        result.push_back(temp + 48);
    }
    while (result.size() != bit) {
        if (result.size() > 8) {
            break;
        }
        result.push_back('0');
    }
    string tmp = result;
    int j = 0;
    for (int i = result.size() - 1; i >= 0; i--) {
        tmp.at(i) = result.at(j);
        j++;
    }
    result = tmp;
    return result;
}

int binaryToDec(string str) {
    int num = 0, j = 0;
    for (int i = str.size() - 1; i >= 0; i--) {
        num += (str.at(j) - 48) * (pow(2, i));
        j++;
    }
    return num;
}

char intTo64(int ndx) {
    string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (ndx < 0 || ndx > 63) {
        return -1;
    }
    else {
        return str.at(ndx);
    }

}

int base64CharToIndex(char base64Char) {
    const char base64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for (int i = 0; i < 64; ++i) {
        if (base64Char == base64Chars[i]) {
            return i;
        }
    }

    return -1;
}

string addStrings(const string& num1, const string& num2) {
    string result;
    int carry = 0;

    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digit1;
        if (i >= 0) {
            digit1 = num1[i] - '0';
        } else {
            digit1 = 0;
        }

        int digit2;
        if (j >= 0) {
            digit2 = num2[j] - '0';
        } else {
            digit2 = 0;
        }

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;

        result.insert(result.begin(), '0' + sum % 10);

        if (i >= 0) {
            i--;
        }
        if (j >= 0) {
            j--;
        }
    }

    return result;
}

int hexCharToDecimal(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else {
        cerr << "Invalid hex character: " << c << endl;
        return -1; // Invalid character
    }
}

string hexToDec(const string str) {
    int cap = str.size() / 8;
    if (cap % 8 != 0 || cap == 0) {
        cap++;
    }

    int iter = 0;
    string* chunks = new string[cap];
    for (size_t i = 0; i < str.size(); i++) {
        if (i % 8 == 0 && i != 0) {
            iter++;
        }
        chunks[iter].push_back(str.at(i));
    }
    while(chunks[cap - 1].size() != 8) {
        chunks[cap - 1].insert(0, "0");
    }

    int num;
    string result;
    for (int i = 0; i < cap; i++) {
        num = stoi(chunks[i], nullptr, 16);
        for (size_t j = 8; j < str.size(); j+=8) {
            result.push_back('0');
        }
        result = addStrings(result, intToString(num));
    }

    delete[] chunks;

    return result;

}

string hexToBinary(string in) {
    int temp;
    string result;
    in = hexToDec(in);
    temp = stringToInt(in);

    result = decToBinary(temp, 4);

    return result;
}

string hexToBinary(char in) {
    int temp;
    string result;
    string ch(1, in);
    ch = hexToDec(ch);
    temp = stringToInt(ch);

    result = decToBinary(temp, 4);

    return result;
}

string hexStringToBytes(const string& str) {
    string byteString;
    for (size_t i = 0; i < str.size(); i+=2) {
        string byte = str.substr(i, 2);
        char ch = static_cast<char>(stoul(byte, nullptr, 16));
        byteString.push_back(ch);
    }
    return byteString;
}

string bytesToHexString(const string& str) {
    stringstream hexStream;
    hexStream << hex << setfill('0');

    for (char byte : str) {
        hexStream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(byte));
    }

    return hexStream.str();
}

string encode64(string in) {
    int* asci = new int[in.size()];
    string* asciStr = new string[in.size()];
    for (int i = 0; i < in.size(); i++) {
        asci[i] = static_cast<int>(in.at(i));
        asciStr[i] = decToBinary(asci[i]);
    }

    string str;

    for (int i = 0; i < in.size(); i++) {
        str += asciStr[i];
    }

    delete[] asci;
    delete[] asciStr;

    int cap = str.size() / 6;
    bool six = true;

    if (str.size() % 6 != 0) {
        cap++;
        six = false;
    }
    asciStr = new string[cap];

    int iter = 0;
    for (int i = 0; i < str.size(); i++) {
        if (i % 6 == 0 && i != 0) {
            iter++;
        }
        asciStr[iter].push_back(str.at(i));
    }
    if (!six) {
        while (asciStr[cap-1].size() != 6) {
            asciStr[cap - 1].push_back('0');
        }
    }

    for (int i = 0; i < cap; i++) {
        asciStr[i].insert(0, "0");
        asciStr[i].insert(0, "0");
    }

    asci = new int[cap];
    string result;
    for (int i = 0; i < cap; i++) {
        asci[i] = binaryToDec(asciStr[i]);
        result.push_back(intTo64(asci[i]));
    }

    while (result.size() % 4 != 0) {
        result.push_back('=');
    }
    delete[] asciStr;

    return result;
}

string decode64(const string& str) {
    string temp = str;

    for (size_t i = 0; i < str.size(); i++) {
        if (temp[i] == '=') {
            temp.erase(i);
            break;
        }
    }


    int base;
    int cap = str.size();
    string concat;
    string* arr = new string[cap];
    for (size_t i = 0; i < temp.size(); i++) {
        base = base64CharToIndex(temp[i]);
        //cout << base << endl;
        arr[i] = decToBinary(base);
        //cout << arr[i] << endl;
        arr[i].erase(0, 2);
        //cout << arr[i] << endl;
        concat += arr[i];
    }
    //cout << concat << endl;

    delete[] arr;

    cap = concat.size()/8;
    arr = new string[cap];
    int iter = 0;
    for (size_t i = 0; i < cap * 8; i++) {
        if (i % 8 == 0 && i != 0) {
            iter++;
        }
        arr[iter].push_back(concat[i]);
        //cout << arr[iter] << endl;
    }

    int asci;
    string result;
    for (int i = 0; i < cap; i++) {
        asci = binaryToDec(arr[i]);
        result.push_back(static_cast<char>(asci));
    }
    result = bytesToHexString(result);
    return result;
}

string hexTo64(string in) {
    string concat;

    for(int i = 0; i < in.size(); i++) {
        concat += hexToBinary(in.at(i));
    }

    int iter = 0, cap = 0;
    bool six = true;

    cap = concat.size() / 6;

    if(concat.size() % 6 != 0) {
        cap++;
        six = false;
    }

    string* binArr = new string[cap];
    for (int i = 0; i < concat.size(); i++) {
        if (i % 6 == 0 && i != 0) {
            iter++;
        }
        binArr[iter].push_back(concat.at(i));
    }
    if (!six) {
        while (binArr[cap-1].size() != 6) {
            binArr[cap - 1].push_back('0');
        }
    }

    int* numArr = new int[cap];
    string result;
    for (int i = 0; i < cap; i++) {
        numArr[i] = binaryToDec(binArr[i]);
        result.push_back(intTo64(numArr[i]));
    }
    delete[] numArr;
    delete[] binArr;

    while (result.size() % 4 != 0) {
        result.push_back('=');
    }

    return result;
}

string fixedXOR(const string hex1, const string hex2) {
    if (hex1.size() != hex2.size()) {
        cout << "[ERROR] Strings differ in length." << endl;
        return "";
    }
    int cap = hex1.size() / 8;
    if (hex1.size() % 8 != 0) {
        cap++;
    }

    string* chunks = new string[cap];
    string* chunks2 = new string [cap];
    int iter = 0;
    for (int i = 0; i < hex1.size(); i++) {
        if (i % 8 == 0 && i != 0) {
            iter++;
        }
        chunks[iter].push_back(hex1.at(i));
        chunks2[iter].push_back(hex2.at(i));
    }

    string temp, result;
    int dec, dec2;

    for (int i = 0; i < cap; i++) {
        temp = hexToDec(chunks[i]);
        dec = stringToInt(temp);
        temp = hexToDec(chunks2[i]);
        dec2 = stringToInt(temp);

        if (dec <= -1 || dec2 <= -1) {
            cout << "[ERROR] Invalid hex values." << endl;
            cout << dec << endl;
            cout << dec2 << endl;
            return "";
        }

        int xorResult = dec ^ dec2;
        stringstream ss;
        ss << hex << xorResult;
        result += ss.str();
    }

    delete[] chunks;
    delete[] chunks2;
    return result;
}

string xorSingleByte(string str, char key) {
    string result;
    for (char byte : str) {
        result.push_back(key ^ byte);
    }
    result.push_back('\0');
    return result;
}

string xorBreakSingleKey (token* arr, int cap) {
    char ch;
    char key;
    token result;
    string tmp1 = xorSingleByte(hexStringToBytes(arr[0].getData()), 'a');
    result = tmp1;
    for (int i = 0; i < 256; i++) {
        ch = static_cast<char>(i);
        for (int j = 0; j < cap; j++) {
            token tmp;
            tmp1 = arr[j].getData();
            tmp1 = hexStringToBytes(tmp1);
            tmp1 = xorSingleByte(tmp1, ch);
            tmp = tmp1;
            if (result.getScore() < tmp.getScore()) {
                tmp1 = tmp.getData();
                result = tmp1;
                key = ch;
            }
        }
    }
    cout << "KEY: " << key << endl;
    return result.getData();
}

char xorBreakSingleKey (const string &str) {
    char ch;
    char key;
    token result;
    string tmp1 = str;
    string debug;
    result = tmp1;
    for (int i = 0; i < 256; i++) {
        ch = static_cast<char>(i);
        token tmp;
        tmp1 = str;
        tmp1 = hexStringToBytes(tmp1);
        tmp1 = xorSingleByte(tmp1, ch);
        tmp = tmp1;
        if (result.getScore() < tmp.getScore()) {
            tmp1 = tmp.getData();
            result = tmp1;
            key = ch;
            debug = tmp1;
        }

    }
    return key;
}

string xorRepeat(string str, string key) {
    stringstream result;
    string temp;
    int j = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (j == key.size() && j != 0) {
            j = 0;
        }
        char ch = key.at(j);
        char resultXOR = ch ^ str.at(i);
        result << hex << setw(2) << setfill('0') << static_cast<int>(resultXOR);
        j++;
    }
    return result.str();
}

string xorRepeatDecrypt(string str, string key) {
    string result;
    int j = 0;
    for (size_t i = 0; i < str.length(); i += 2) {
        if (j == key.length() && j != 0) {
            j = 0;
        }
        char ch = key.at(j);
        char resultXOR = static_cast<char>(stoi(str.substr(i, 2), nullptr, 16) ^ ch);
        result += resultXOR;
        j += 1;
    }
    return result;
}



int partition(token* arr, int low, int high) {
    double pivot = arr[high].getScore();
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].getScore() >= pivot) {
            i++;
            token temp(arr[i]);
            arr[i] = arr[j];
            arr[j] = temp;
            //swap(arr[i], arr[j]);
        }
    }

    //swap(arr[i + 1], arr[high]);
    token temp(arr[i + 1]);
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void sortByScore (token* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        sortByScore(arr, low, pivotIndex - 1);
        sortByScore(arr, pivotIndex + 1, high);
    }
}

int partition(key* arr, int low, int high) {
    double pivot = arr[high].distance;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].distance <= pivot) {
            i++;
            key temp(arr[i]);
            arr[i] = arr[j];
            arr[j] = temp;
            //swap(arr[i], arr[j]);
        }
    }

    //swap(arr[i + 1], arr[high]);
    key temp(arr[i + 1]);
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void sortByDistance (key* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        sortByDistance(arr, low, pivotIndex - 1);
        sortByDistance(arr, pivotIndex + 1, high);
    }
}

int hammingDistance(const std::string& str1, const std::string& str2) {
    int distance = 0;

    if (str1.size() != str2.size()) {
        cerr << "[ERROR]: Strings must have the same size." << std::endl;
        return -1;
    }

    for (size_t i = 0; i < str1.size(); i++) {
        char char1 = str1[i];
        char char2 = str2[i];

        char xorResult = char1 ^ char2;

        while (xorResult != 0) {
            distance += xorResult & 1;
            xorResult >>= 1;
        }
    }

    return distance;
}

string breakRepeatingKey(const string &str) {
    int KEYSIZE = 2;
    int keyNum = 40;


    //Guessing Key Size
    if (str.size() / 4 < 40) {
        keyNum = str.size() / 4;
    }

    cout << "NUMBER OF TESTED KEYS: " << keyNum << endl;

    key* keys = new key[keyNum];

    for (; KEYSIZE < keyNum + 2; KEYSIZE++) {
        int numBlocks = str.size()/KEYSIZE;
        if (numBlocks > 200) {
            numBlocks = 200;
        }
        //cout << "NUMBLOCKS: " << numBlocks << endl;
        string* blocks = new string[numBlocks];
        int ctr = 0;
        for (size_t i = 0; i < KEYSIZE * numBlocks; i++) {
            if (i % KEYSIZE == 0 && i != 0) {
                ctr++;
            }
            blocks[ctr].push_back(str[i]);
        }

        keys[KEYSIZE - 2].keySize = KEYSIZE;
        double avgDistance = 0;
        //cout << "GUESSED KEYSIZE: " << KEYSIZE << endl;
        for (int i = 0; i < numBlocks - 1; i+= 2) {
            //cout << blocks[i] << endl;
            //cout << "HAMMING DISTANCE OF: " << blocks[i] << " AND " << blocks[i + 1] << ": " << hammingDistance(blocks[i],blocks[i + 1]) << endl;
            avgDistance += hammingDistance(blocks[i], blocks[i + 1]);
        }
        avgDistance = (avgDistance/ ((numBlocks)/2)) / KEYSIZE;
        keys[KEYSIZE - 2].distance = avgDistance;
        //cout << "AVERAGE DISTANCE: " << avgDistance << endl << endl;
        delete[] blocks;
    }

    sortByDistance(keys,0, keyNum - 1);
    //cout << endl << "SORTED KEYNUM GUESSES: " << endl;
    /*for (int i = 2; i < keyNum + 2; i++) {
        cout << "KEYSIZE: " << keys[i - 2].keySize << " DISTANCE: "<< keys[i - 2].distance << endl;
    }*/

    //Forming key
    KEYSIZE = keys[0].keySize;
    cout << "GUESSED KEY SIZE: " << KEYSIZE << endl;
    int cap = str.size() / KEYSIZE;
    if (str.size() % KEYSIZE != 0) {
        cap++;
    }

    string *chunks = new string[cap];
    int iter = 0;

    for (size_t i = 0; i < str.size(); i++) {
        if (i % KEYSIZE == 0 && i != 0) {
            iter++;
        }
        chunks[iter].push_back(str[i]);
    }

    string *transpose = new string[KEYSIZE];

    //Transposing string chunks
    for (int j = 0; j < KEYSIZE; j++) {
        iter = 0;
        while (iter != cap) {
            if (iter != cap - 1) {
                transpose[j].push_back(chunks[iter].at(j));
            }
            iter++;
        }

    }

    //Adding last chunk
    for (size_t i = 0; i < chunks[cap - 1].size(); i++) {
        transpose[i].push_back(chunks[cap - 1].at(i));
    }

    string result;
    for (int i = 0; i < KEYSIZE; i++) {
        string temp = bytesToHexString(transpose[i]);
        result.push_back(xorBreakSingleKey(temp));
    }
    
    delete[] transpose;
    delete[] chunks;
    delete[] keys;
    return result;

}

string transpose(string* str, int ndx, int size) {
    string result;
    for (int i = 0; i < size; i++) {
        result.push_back(str[i].at(ndx));
    }
    return result;
}







#endif //CANYOUHACKUS_TOKEN_H
