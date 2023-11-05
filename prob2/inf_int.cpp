#include "inf_int.h"

inf_int::inf_int(){
    //기본값으로 0을 할당
    length = 1; 
    thesign = true;
    digits = new char[length + 1]; // /0를 위해 +1
    strcpy(digits, "0"); //0으로 초기화
}

inf_int::inf_int(int value){
    //부호 확인
    if(value >= 0){
        thesign = true;
    } else {
        thesign = false;
        value = -value; //절대값으로 일단 변환시켜 놓음
    }

    //정수를 문자열로 변환하고 임시 버퍼를 할당
    char buffer[100];
    sprintf(buffer, "%d", value);

    //digits에 복사
    length = strlen(buffer);
    digits = new char[length + 1];
    strcpy(digits, buffer);
}

//문자열을 매개변수로 받는 객체
inf_int::inf_int(const char* value){
    //null값일때
    if(value == NULL){
        length = 1;
        thesign = true;
        digits = new char[length + 1];
        strcpy(digits, "0");
        return;
    }
    //부호확인
    if (value[0] == '-') {
        thesign = false;
        value++; // -다음 부분으로 이동시킴
    } else {
        thesign = true;
    }

    length = strlen(value);

    digits = new char[length + 1];
    strcpy(digits, value);

    //앞쪽의 불필요한 0을 제거해야 하는 것 필요할지도
}

//복사 생성자
inf_int::inf_int(const inf_int& other){
    length = other.length;
    thesign = other.thesign;

    digits = new char[length+1];
    strcpy(digits, other.digits);
}

//소멸자
inf_int::~inf_int(){
    //동적 할당된 메모리 해제
    delete[] digits;
}

inf_int& inf_int::operator=(const inf_int& other){
    //자기자신을 대입했으면
    if(this == &other){
        return *this;
    }
    //기존 digits메모리 해제
    delete[] digits;

    //다른 객체의 멤버변수 복사
    length = other.length;
    thesign = other.thesign;

    digits = new char[length + 1]; 
    strcpy(digits, other.digits);

    //현재 객체의 참조를 반환
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
    //부호가 다르면
    if (a.thesign && !b.thesign){
        return true; //a양수,b음수
    } 
    else if(!a.thesign && b.thesign){
        return false; //a음수, b양수
    }

    //부호 같으면
    if(a.length > b.length){
        return a.thesign; //길이 긴 쪽의 thesign 따라감
    } 
    else if(a.length < b.length){
       return !a.thesign;
    }
    else{
        //길이가 같으면, 숫자를 하나하나 비교
        for(unsigned int i = 0; i < a.length; i++){
            if(a.digits[i] > b.digits[i]){
                return a.thesign;
            }
            else if(a.digits[i] < b.digits[i]){
                return !a.thesign;
            }
        }
    }

    //두 숫자가 같으면
    return false;

}

//위에 >를 반전시킴
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

    //두 숫자의 부호가 다른 경우
    if(!a.thesign || !b.thesign){
       //음수 혼합된 '+'는 뺄셈으로 대체하는 걸로
       //일단 지금은 구현 안함
       return inf_int(); // 일시적으로 0 반환
    }
    //결과 저장할 임시 문자열
    char temp[10000];

    int carry = 0; //십진수 계산 올림용도
    int i = a.length - 1;
    int j = b.length - 1;
    int k = 0;

    //두 숫자를 뒤에서부터 더해줌
    while(i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if(i>=0){
            sum += a.digits[i--] - '0'; //sum에 한자리 숫자씩 넣기
        }
        if(j>=0){
            sum += b.digits[j--] - '0';
        }
        temp[k++] = (sum % 10) + '0'; //문자로 변환해서 임시 문자열에 저장
        carry = sum / 10; //올림수 올려놓음
    }

    //결과 문자열을 뒤집기
    for (int l = 0; l < k / 2; l++) {
        char t = temp[l];
        temp[l] = temp[k - l - 1];
        temp[k - l - 1] = t;
    }
    temp[k] = '\0'; // 문자열 종료

    return inf_int(temp); //임시 문자열로 객체 생성
}

inf_int operator-(const inf_int& a, const inf_int& b) {
    
    //두 숫자의 부호가 다른 경우
    if (!a.thesign || !b.thesign) {
        //일단 0 반환
        //구현 안함
        return inf_int(); 
    }

    // 두 수의 크기를 비교하여 a가 b보다 작은지 확인
    bool aIsSmaller = false;
    if (a.length < b.length) {
        aIsSmaller = true;
    } else if (a.length == b.length) {
        for (int i = 0; i < a.length; i++) {
            if (a.digits[i] < b.digits[i]) {
                aIsSmaller = true;
                break;
            } else if (a.digits[i] > b.digits[i]) {
                break;
            }
        }
    }

    // 결과를 저장할 임시 배열
    char temp[10000];
    memset(temp, 0, sizeof(temp)); // 배열을 0으로 초기화

    int borrow = 0; // 빌리는 수
    int i = a.length - 1, j = b.length - 1, k = 0;

    // a가 b보다 작으면, b - a를 계산하고 결과의 부호를 음수로 설정
    if (aIsSmaller) {
        // i, j 바꾸기
        i = b.length - 1;
        j = a.length - 1;
    }

    while (i >= 0 || j >= 0) {
        int a_digit = i >= 0 ? (aIsSmaller ? b.digits[i--] - '0' : a.digits[i--] - '0') : 0;
        int b_digit = j >= 0 ? (aIsSmaller ? a.digits[j--] - '0' : b.digits[j--] - '0') : 0;

        int diff = a_digit - b_digit - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        temp[k++] = diff + '0';
    }

    // 결과 배열의 순서를 뒤집음
    for (int l = 0; l < k / 2; l++) {
        char t = temp[l];
        temp[l] = temp[k - l - 1];
        temp[k - l - 1] = t;
    }

    // 결과 문자열에서 앞쪽의 불필요한 0 제거
    int start = 0;
    while (start < k - 1 && temp[start] == '0') start++;
    int newSize = k - start;
    char* result = new char[newSize + 1 + (aIsSmaller ? 1 : 0)]; // '-'를 위한 공간 추가

    if (aIsSmaller) {
        result[0] = '-';
        memcpy(result + 1, temp + start, newSize);
    } else {
        memcpy(result, temp + start, newSize);
    }
    result[newSize + (aIsSmaller ? 1 : 0)] = '\0';

    inf_int resultObj(result);
    delete[] result; // 동적 할당된 메모리 해제
    return resultObj;
}

inf_int operator*(const inf_int& a, const inf_int& b) {
    if (!a.thesign || !b.thesign) {
        return inf_int(); 
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

    int k = a.length + b.length;
    while (k > 0 && temp[k - 1] == 0) k--; 

    if (k == 0) return inf_int("0"); 

    char result[20000];
    for (int i = 0; i < k; i++) {
        result[i] = temp[k - i - 1] + '0';
    }
    result[k] = '\0'; 

    return inf_int(result); 
}

std::ostream& operator<<(std::ostream& os, const inf_int& obj) {
     if (!obj.thesign) {
        os << '-';  //음수일때 - 출력해야지
    }
    for (int i = 0; i < obj.length; i++) {
        os << obj.digits[i]; 
    }
    return os;
}
std::istream& operator>>(std::istream& is, inf_int& obj) {
    std::string input;
    is >> input;
    obj = inf_int(input.c_str());
    return is;
}
