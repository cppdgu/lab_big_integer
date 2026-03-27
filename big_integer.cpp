// =============================================================
//  big_integer.cpp -- BigInteger class implementation
//
//  TASK: Implement all methods declared in big_integer.h
//  This stub file exists only so the project structure is clear.
//  Replace its contents with your implementation.
// =============================================================

#include "big_integer.h"

// TODO: your code here
#include "big_integer.h"
#include <iostream>

// ---------------- Конструкторы ----------------

BigInteger::BigInteger() {
    digits_.push_back(0);
    negative_ = false;
}

BigInteger::BigInteger(int value) {
    if (value < 0) {
        negative_ = true;
        value = -value;
    } else {
        negative_ = false;
    }

    if (value == 0) digits_.push_back(0);

    while (value > 0) {
        digits_.push_back(value % 10);
        value /= 10;
    }
}

BigInteger::BigInteger(long long value) : BigInteger((int)value) {}

BigInteger::BigInteger(const std::string& str) {
    negative_ = false;

    int start = 0;
    if (str[0] == '-') {
        negative_ = true;
        start = 1;
    }

    for (int i = str.size() - 1; i >= start; i--) {
        digits_.push_back(str[i] - '0');
    }
}

// ---------------- Простые функции ----------------

bool BigInteger::is_zero() const {
    return digits_.size() == 1 && digits_[0] == 0;
}

bool BigInteger::is_negative() const {
    return negative_;
}

std::string BigInteger::to_string() const {
    std::string s;

    if (negative_) s += "-";

    for (int i = digits_.size() - 1; i >= 0; i--) {
        s += char('0' + digits_[i]);
    }

    return s;
}

// ---------------- Сравнение ----------------

bool BigInteger::operator==(const BigInteger& rhs) const {
    return digits_ == rhs.digits_;
}

bool BigInteger::operator<(const BigInteger& rhs) const {
    if (digits_.size() != rhs.digits_.size())
        return digits_.size() < rhs.digits_.size();

    for (int i = digits_.size() - 1; i >= 0; i--) {
        if (digits_[i] != rhs.digits_[i])
            return digits_[i] < rhs.digits_[i];
    }

    return false;
}

bool BigInteger::operator!=(const BigInteger& rhs) const { return !(*this == rhs); }
bool BigInteger::operator>(const BigInteger& rhs) const { return rhs < *this; }
bool BigInteger::operator<=(const BigInteger& rhs) const { return !(*this > rhs); }
bool BigInteger::operator>=(const BigInteger& rhs) const { return !(*this < rhs); }

// ---------------- Сложение ----------------

BigInteger BigInteger::operator+(const BigInteger& rhs) const {
    BigInteger res;
    res.digits_.clear();

    int carry = 0;

    for (int i = 0; i < digits_.size() || i < rhs.digits_.size(); i++) {
        int a = (i < digits_.size()) ? digits_[i] : 0;
        int b = (i < rhs.digits_.size()) ? rhs.digits_[i] : 0;

        int sum = a + b + carry;

        res.digits_.push_back(sum % 10);
        carry = sum / 10;
    }

    if (carry) res.digits_.push_back(carry);

    return res;
}

// ---------------- Вычитание ----------------

BigInteger BigInteger::operator-(const BigInteger& rhs) const {
    BigInteger res;
    res.digits_.clear();

    int carry = 0;

    for (int i = 0; i < digits_.size(); i++) {
        int a = digits_[i];
        int b = (i < rhs.digits_.size()) ? rhs.digits_[i] : 0;

        int sub = a - b - carry;

        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        res.digits_.push_back(sub);
    }

    return res;
}

// ---------------- Умножение ----------------

BigInteger BigInteger::operator*(const BigInteger& rhs) const {
    BigInteger res;
    res.digits_ = std::vector<int>(digits_.size() + rhs.digits_.size(), 0);

    for (int i = 0; i < digits_.size(); i++) {
        for (int j = 0; j < rhs.digits_.size(); j++) {
            res.digits_[i + j] += digits_[i] * rhs.digits_[j];
        }
    }

    return res;
}

// ---------------- Деление (очень простое) ----------------

BigInteger BigInteger::operator/(const BigInteger& rhs) const {
    BigInteger res(0);
    BigInteger temp = *this;

    while (temp >= rhs) {
        temp = temp - rhs;
        res = res + BigInteger(1);
    }

    return res;
}

BigInteger BigInteger::operator%(const BigInteger& rhs) const {
    BigInteger temp = *this;

    while (temp >= rhs) {
        temp = temp - rhs;
    }

    return temp;
}

// ---------------- Инкременты ----------------

BigInteger& BigInteger::operator++() {
    *this = *this + BigInteger(1);
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    *this = *this + BigInteger(1);
    return temp;
}

BigInteger& BigInteger::operator--() {
    *this = *this - BigInteger(1);
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger temp = *this;
    *this = *this - BigInteger(1);
    return temp;
}

// ---------------- Минус ----------------

BigInteger BigInteger::operator-() const {
    BigInteger res = *this;
    res.negative_ = !negative_;
    return res;
}

// ---------------- Ввод/вывод ----------------

std::ostream& operator<<(std::ostream& os, const BigInteger& value) {
    os << value.to_string();
    return os;
}

std::istream& operator>>(std::istream& is, BigInteger& value) {
    std::string s;
    is >> s;
    value = BigInteger(s);
    return is;
}
