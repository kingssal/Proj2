#include "inf_int.h"

inf_int::inf_int(){
    length = 1;
    thesign = true;
    digits = new char[length+1];
    strcpy(digits, "0");
}

inf_int::inf_int(int value){
    if(value >= 0){
        thesign = true;
    } else {
        thesign = false;
        value= -value;
    }

    char buffer[50];
    sprintf(buffer, "%d", value);

    length = strlen(buffer);
    digits = new char[length +1];
    strcpy(digits, buffer);
}

inf_int::inf_int(const char* value){
    if(value == NULL) {
        length = 1;
        thesign = true;
        digits = new char[length+1];
        strcpy(digits, "0");
        return;
    }

    if(value[0]=='-'){
        thesign=false;
        value++;
    } else{
        thesign = true;
    }

    length = strlen(value);

    digits = new char[length + 1];
    strcpy(digits, value);
}

inf_int::inf_int(const inf_int& other){
    length = other.length;
    thesign = other.thesign;

    digits = new char[length +1];
    strcpy(digits, other.digits);
}

inf_int::~inf_int(){
    delete[] digits;
}

inf_int& inf_int::operator=(const inf_int& other){
    if(this == &other){
        return *this;
    }
    
    delete[] digits;
    length = other.length;
    thesign = other.thesign;

    digits = new char[length +1];
    strcpy(digits, other.digits);

    return *this;
}

bool operator==(const inf_int& a, const inf_int& b) {
   if((strcmp(a.digits, b.digits)==0) && a.thesign==b.thesign ){
    return true;
   }
   return false;
}

bool operator!=(const inf_int& a, const inf_int& b) {
    if((strcmp(a.digits, b.digits)==0) && a.thesign==b.thesign ){
    return false;
   }
   return true;
}

bool operator>(const inf_int& a, const inf_int& b) {
    if (a.thesign && !b.thesign){
        return true; //a is positive, b is negative
    } else if (!a.thesign && b.thesign) {
        return false;  // a is negative, b is positive
    }

    if (a.length > b. length){
        return a.thesign; 
    }
    else if(a.length < b.length){
        return !a.thesign;
    }
    else {
        for(unsigned int i = 0; i < a.length; i++){
            if(a.digits[i]>b.digits[i]){
                return a.thesign;
            }
            else if(a.digits[i]<b.digits[i]){
                return !a.thesign;
            }
        }
    }

    return false;

}

bool operator<(const inf_int& a, const inf_int& b) {
     if (a.thesign && !b.thesign){
        return false; 
    } else if (!a.thesign && b.thesign) {
        return true;  
    }

    if (a.length > b. length){
        return !b.thesign; 
    }
    else if(a.length < b.length){
        return b.thesign;
    }
    else {
        for(unsigned int i = 0; i < a.length; i++){
            if(a.digits[i]<b.digits[i]){
                return b.thesign;
            }
            else if(a.digits[i]>b.digits[i]){
                return !a.thesign;
            }
        }
    }

    return false;

}

inf_int operator+(const inf_int& a, const inf_int& b) {
    if(!a.thesign || !b.thesign){
        return inf_int();
    }

    char temp[10000];
    int carry = 0;
    int i = a.length - 1, j = b.length-1, k = 0;

      // 두 숫자를 뒤에서부터 더함
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a.digits[i--] - '0';
        if (j >= 0) sum += b.digits[j--] - '0';
        temp[k++] = (sum % 10) + '0'; // 한 자리 수를 문자로 변환하여 저장
        carry = sum / 10; // 다음 자리수로 올림수 계산
    }

    // 결과 문자열을 올바른 순서로 뒤집음
    for (int l = 0; l < k / 2; l++) {
        char t = temp[l];
        temp[l] = temp[k - l - 1];
        temp[k - l - 1] = t;
    }
    temp[k] = '\0'; // 문자열 종료

    return inf_int(temp); // 결과 문자열로 inf_int 객체 생성
}

inf_int operator-(const inf_int& a, const inf_int& b) {
// 두 숫자 모두 양수인 경우에만 유효
    if (!a.thesign || !b.thesign) {
        // 음수 또는 혼합된 부호에 대한 처리가 필요
        return inf_int(); // 임시적으로 0을 반환
    }

    // 결과를 저장할 임시 문자열
    char temp[10000]; // 충분히 큰 크기로 설정

    int borrow = 0; // 빌림수
    int i = a.length - 1, j = b.length - 1, k = 0;

    // 두 숫자를 뒤에서부터 빼면서 결과를 임시 문자열에 저장
    while (i >= 0 || j >= 0) {
        int diff = borrow;
        if (i >= 0) diff += a.digits[i--] - '0';
        if (j >= 0) diff -= b.digits[j--] - '0';
        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        temp[k++] = diff + '0'; // 한 자리 수를 문자로 변환하여 저장
    }

    // 결과 문자열을 올바른 순서로 뒤집음
    for (int l = 0; l < k / 2; l++) {
        char t = temp[l];
        temp[l] = temp[k - l - 1];
        temp[k - l - 1] = t;
    }
    temp[k] = '\0'; // 문자열 종료

    return inf_int(temp); // 결과 문자열로 inf_int 객체 생성
}

inf_int operator*(const inf_int& a, const inf_int& b) {
     // 두 숫자 모두 양수인 경우에만 유효
    if (!a.thesign || !b.thesign) {
        // 음수 또는 혼합된 부호에 대한 처리가 필요
        return inf_int(); // 임시적으로 0을 반환
    }

    // 결과를 저장할 임시 배열
    int temp[20000] = {0}; // 충분히 큰 크기로 초기화

    // 두 숫자를 곱함
    for (int i = 0; i < a.length; i++) {
        for (int j = 0; j < b.length; j++) {
            temp[i + j] += (a.digits[a.length - i - 1] - '0') * (b.digits[b.length - j - 1] - '0');
            temp[i + j + 1] += temp[i + j] / 10;
            temp[i + j] %= 10;
        }
    }

    // 결과를 문자열로 변환
    int k = a.length + b.length;
    while (k > 0 && temp[k - 1] == 0) k--; // 앞쪽의 0 제거

    if (k == 0) return inf_int("0"); // 결과가 0인 경우

    char result[20000];
    for (int i = 0; i < k; i++) {
        result[i] = temp[k - i - 1] + '0';
    }
    result[k] = '\0'; // 문자열 종료

    return inf_int(result); // 결과 문자열로 inf_int 객체 생성
}

std::ostream& operator<<(std::ostream& os, const inf_int& obj) {
     if (!obj.thesign) {
        os << '-'; // 음수인 경우 '-' 기호를 먼저 출력
    }
    for (int i = 0; i < obj.length; i++) {
        os << obj.digits[i]; // 각 자리의 숫자를 순서대로 출력
    }
    return os;
}
std::istream& operator>>(std::istream& is, inf_int& obj) {
    std::string input;
    is >> input;
    obj = inf_int(input.c_str());
    return is;
}
