#ifndef _INF_INT_H_ //중복방지
#define _INF_INT_H_

#include <iostream>

class inf_int {
private:
    char* digits; //pointer
    unsigned int length; //length of digits
    bool thesign; // positive->1, negative->0
public:
    inf_int(); 
    inf_int(int);
    inf_int(const char*);
    inf_int(const inf_int&); //copy constructor
    ~inf_int(); //destructor

    inf_int& operator=(const inf_int&);

    friend bool operator==(const inf_int&, const inf_int&);
    friend bool operator!=(const inf_int&, const inf_int&);
    friend bool operator>(const inf_int&, const inf_int&);
    friend bool operator<(const inf_int&, const inf_int&);

    friend inf_int operator+(const inf_int&, const inf_int&);
    friend inf_int operator-(const inf_int&, const inf_int&);
    friend inf_int operator*(const inf_int&, const inf_int&);
    // friend inf_int operator/(const inf_int&, const inf_int&);

    friend std::ostream& operator<<(std::ostream&  , const inf_int& );
    friend std::istream& operator>>(std::istream&, inf_int&);

};

#endif