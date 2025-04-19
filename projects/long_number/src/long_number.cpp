#include "long_number.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace vitashaa;

// Конструктор по умолчанию
LongNumber::LongNumber() : numbers(nullptr), length(0), sign(1) {}

// Вспомогательный метод для получения длины строки
int LongNumber::get_length(const char* const str) const noexcept {
    return strlen(str);
}

// Конструктор из строки
LongNumber::LongNumber(const char* const str) {
    if (str == nullptr || str[0] == '\0') {
        throw std::invalid_argument("Invalid number string");
    }

    // Определяем знак
    sign = (str[0] == '-') ? -1 : 1;
    int start = (sign == -1) ? 1 : 0; // Пропускаем '-' для отрицательных чисел
    length = get_length(str) - start;

    // Выделяем память и сохраняем цифры
    numbers = new int[length];
    for (int i = 0; i < length; ++i) {
        if (str[start + i] < '0' || str[start + i] > '9') {
            throw std::invalid_argument("Invalid character in number string");
        }
        numbers[i] = str[start + i] - '0';
    }

    remove_leading_zeros();
}

// Конструктор копирования
LongNumber::LongNumber(const LongNumber& x) : length(x.length), sign(x.sign) {
    numbers = new int[length];
    memcpy(numbers, x.numbers, length * sizeof(int));
}

// Конструктор перемещения
LongNumber::LongNumber(LongNumber&& x) : numbers(x.numbers), length(x.length), sign(x.sign) {
    x.numbers = nullptr;
    x.length = 0;
}

// Деструктор
LongNumber::~LongNumber() {
    delete[] numbers;
}

// Оператор присваивания из строки
LongNumber& LongNumber::operator=(const char* const str) {
    LongNumber tmp(str);
    *this = tmp;
    return *this;
}

// Оператор копирующего присваивания
LongNumber& LongNumber::operator=(const LongNumber& x) {
    if (this != &x) {
        delete[] numbers;
        length = x.length;
        sign = x.sign;
        numbers = new int[length];
        memcpy(numbers, x.numbers, length * sizeof(int));
    }
    return *this;
}

// Оператор перемещающего присваивания
LongNumber& LongNumber::operator=(LongNumber&& x) {
    if (this != &x) {
        delete[] numbers;
        numbers = x.numbers;
        length = x.length;
        sign = x.sign;
        x.numbers = nullptr;
        x.length = 0;
    }
    return *this;
}

// Удаление ведущих нулей
void LongNumber::remove_leading_zeros() {
    int zeros = 0;
    while (zeros < length - 1 && numbers[zeros] == 0) {
        ++zeros;
    }

    if (zeros > 0) {
        int new_length = length - zeros;
        int* new_numbers = new int[new_length];
        memcpy(new_numbers, numbers + zeros, new_length * sizeof(int));
        delete[] numbers;
        numbers = new_numbers;
        length = new_length;
    }

    // Если число равно 0, то знак всегда будет положительным
    if (length == 1 && numbers[0] == 0) {
        sign = 1;
    }
}

// Оператор ==
bool LongNumber::operator==(const LongNumber& x) const {
    if (length != x.length || sign != x.sign) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        if (numbers[i] != x.numbers[i]) {
            return false;
        }
    }
    return true;
}

// Оператор !=
bool LongNumber::operator!=(const LongNumber& x) const {
    return !(*this == x);
}

// Оператор <
bool LongNumber::operator<(const LongNumber& x) const {
    if (sign != x.sign) {
        return sign < x.sign;
    }
    if (length != x.length) {
        return (sign == 1) ? (length < x.length) : (length > x.length);
    }
    for (int i = 0; i < length; ++i) {
        if (numbers[i] != x.numbers[i]) {
            return (sign == 1) ? (numbers[i] < x.numbers[i]) : (numbers[i] > x.numbers[i]);
        }
    }
    return false;
}

// Оператор >
bool LongNumber::operator>(const LongNumber& x) const {
    return !(*this < x) && *this != x;
}

// Арифметические операторы (+)
LongNumber LongNumber::operator+(const LongNumber& x) const {
    if (sign != x.sign) {
        if (sign == -1) {
            LongNumber tmp = *this;
            tmp.sign = 1;
            return x - tmp; // x - abs(this)
        } else {
            LongNumber tmp = x;
            tmp.sign = 1;
            return *this - tmp; // this - abs(x)
        }
    }

    // Сложение чисел с одинаковыми знаками (уже было выше)
    int max_len = std::max(length, x.length);
    int* result = new int[max_len + 1]();

    int carry = 0;
    int i = length - 1, j = x.length - 1, k = max_len;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? numbers[i] : 0;
        int digit2 = (j >= 0) ? x.numbers[j] : 0;

        int sum = digit1 + digit2 + carry;
        result[k] = sum % 10;
        carry = sum / 10;

        --i; --j; --k;
    }

    LongNumber res;
    res.length = max_len + 1 - (k + 1);
    res.numbers = new int[res.length];
    memcpy(res.numbers, result + k + 1, res.length * sizeof(int));
    res.sign = sign;

    delete[] result;
    res.remove_leading_zeros();
    return res;
}

// Оператор -

LongNumber LongNumber::operator-(const LongNumber& x) const
{
    /* ---------- 1. разные знаки  →  превращаем в сложение ---------- */
    if (sign != x.sign)
    {
        LongNumber tmp = x;
        tmp.sign *= -1;
        return *this + tmp;
    }

    /* ---------- 2. знаки одинаковые – сравниваем модули ------------ */
    auto abs_less = [](const LongNumber& a, const LongNumber& b) -> bool
    {
        if (a.length != b.length) return a.length < b.length;
        for (int i = 0; i < a.length; ++i)
            if (a.numbers[i] != b.numbers[i])
                return a.numbers[i] < b.numbers[i];
        return false;                       // |a| == |b|
    };

    /* число с бо́льшим модулем ставим первым в операции вычитания     */
    const LongNumber *big, *small;
    int resultSign;

    if (abs_less(*this, x))
    {               // |*this| < |x|
        big  = &x;
        small = this;
        resultSign = -sign;                 // знак меняется
    }
    else
    {               // |*this| ≥ |x|
        big  = this;
        small = &x;
        resultSign =  sign;                 // знак сохраняется
    }

    /* ---------- 3. собственно вычитание «большое  –  маленькое» ---- */
    int newLen = big->length;
    int* result = new int[newLen]();        // zero‑fill
    int borrow = 0;

    for (int ib = big->length - 1,
             is = small->length - 1,
             k  = newLen - 1;
         k >= 0;
         --ib, --is, --k)
    {
        int d1 = big->numbers[ib];
        int d2 = (is >= 0) ? small->numbers[is] : 0;

        int diff = d1 - d2 - borrow;
        if (diff < 0)
        {
            diff  += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        result[k] = diff;
    }

    /* ---------- 4. формируем объект‑результат ---------------------- */
    LongNumber res;
    res.length  = newLen;
    res.numbers = result;
    res.sign    = resultSign;
    res.remove_leading_zeros();             // убираем ведущие нули,
                                            // поправляем знак для нуля
    return res;
}

// Оператор *
LongNumber LongNumber::operator*(const LongNumber& x) const {
    int new_length = length + x.length;
    int* result = new int[new_length]();
    
    for (int i = length - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = x.length - 1; j >= 0; --j) {
            int temp = numbers[i] * x.numbers[j] + result[i + j + 1] + carry;
            result[i + j + 1] = temp % 10;
            carry = temp / 10;
        }
        result[i] += carry;
    }

    LongNumber res;
    res.length = new_length;
    res.numbers = result;
    res.sign = sign * x.sign;
    res.remove_leading_zeros();
    return res;
}

// Оператор /
LongNumber LongNumber::operator/(const LongNumber& x) const
{
    if (x == LongNumber("0"))
        throw std::invalid_argument("Division by zero");

    /* --- работаем с копиями, чтобы не трогать исходные объекты --- */
    LongNumber dividend = *this;   // a
    LongNumber divisor  =  x;      // b

    const int dividendSign = dividend.sign;
    const int divisorSign  = divisor .sign;

    dividend.sign = divisor.sign = 1;   // берём модули

    /* --- обычное «долгое» деление для |a| / |b| ------------------ */
    LongNumber quotient("0"), current("0");
    quotient.length  = dividend.length;
    quotient.numbers = new int[quotient.length]();   // zero‑fill

    for (int i = 0; i < dividend.length; ++i)
    {
        current = current * LongNumber("10")
                + LongNumber(std::to_string(dividend.numbers[i]));

        int digit = 0;
        while (current >= divisor)
        {
            current = current - divisor;
            ++digit;
        }
        quotient.numbers[i] = digit;
    }
    quotient.remove_leading_zeros();

    /* ----------- ВАЖНО: порядок следующих двух шагов! ------------- */

    /* 1. сначала ставим правильный знак частному                    */
    quotient.sign = (dividendSign == divisorSign) ? 1 : -1;

    /* 2. затем, если делимое было <0 и остаток ≠0,                   */
    /*    сдвигаем частное ещё на 1 в сторону –∞ (евклидово деление)  */
    if (dividendSign == -1 && !(current == LongNumber("0")))
    {
        if (divisorSign == 1)          // a<0, b>0  → q = -q - 1
            quotient = quotient - LongNumber("1");
        else                           // a<0, b<0  → q = -q + 1
            quotient = quotient + LongNumber("1");
    }

    quotient.remove_leading_zeros();
    return quotient;
}

bool LongNumber::operator>=(const LongNumber& x) const {
    return !(*this < x);
}
// Оператор %
LongNumber LongNumber::operator%(const LongNumber& x) const
{
    LongNumber mod = *this - ((*this / x) * x);
    mod.remove_leading_zeros();    // <<— на случай, если остаток 0
    return mod;
}

LongNumber LongNumber::operator-() const {
    LongNumber result(*this);
    if (!(result == LongNumber("0"))) {
        result.sign *= -1;
    }
    return result;
}

// Оператор << (дружественная функция)
namespace vitashaa {
    std::ostream& operator<<(std::ostream &os, const LongNumber& x) {
        if (x.sign == -1) os << '-';
        for (int i = 0; i < x.length; ++i) {
            os << x.numbers[i];
        }
        return os;
    }
}

int LongNumber::get_digits_number() const noexcept {
    return length;
}

int LongNumber::get_rank_number(const int rank) const {
    if (rank < 0 || rank >= length) {
        throw std::out_of_range("Rank is out of bounds");
    }
    return numbers[length - rank - 1];
}

bool LongNumber::is_negative() const noexcept {
    return sign == -1;
}