// =============================================================
//  big_integer.cpp -- BigInteger class implementation
//
//  TASK: Implement all methods declared in big_integer.h
//  This stub file exists only so the project structure is clear.
//  Replace its contents with your implementation.
// =============================================================

#include "big_integer.h"

// TODO: your code here

// конструкторы
BigInteger::BigInteger() {
    value = "0";
}

BigInteger::BigInteger(string s) {
    value = s;
}

// сложение
BigInteger BigInteger::add(const BigInteger& other) {
    string a = value;
    string b = other.value;

    string result = "";
    int carry = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0  j >= 0  carry) {
        int sum = carry;

        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';

        result = char(sum % 10 + '0') + result;
        carry = sum / 10;
    }

    return BigInteger(result);
}

// вычитание (предполагаем a >= b)
BigInteger BigInteger::sub(const BigInteger& other) {
    string a = value;
    string b = other.value;

    string result = "";
    int borrow = 0;

    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0) {
        int diff = (a[i] - '0') - borrow;

        if (j >= 0) diff -= (b[j] - '0');

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = char(diff + '0') + result;

        i--;
        j--;
    }

    // убираем ведущие нули
    while (result.size() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }

    return BigInteger(result);
}

// вывод
string BigInteger::toString() const {
    return value;
}
