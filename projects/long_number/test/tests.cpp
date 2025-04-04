#include "long_number.hpp"
#include <iostream>
#include <cassert>

using namespace vitashaa;

void test_constructors() {
    LongNumber num1("1234567890123456789");
    LongNumber num2("-9876543210987654321");

    assert(num1.get_digits_number() == 19);
    assert(num2.get_digits_number() == 19);
    assert(num1.is_negative() == false);
    assert(num2.is_negative() == true);
}

void test_arithmetic_operators() {
    LongNumber num1("12345");
    LongNumber num2("6789");

    // Проверка сложения
    LongNumber sum = num1 + num2;
    assert(sum == LongNumber("19134"));

    // Проверка вычитания
    LongNumber diff = num1 - num2;
    assert(diff == LongNumber("5556"));

    // Проверка умножения
    LongNumber product = num1 * num2;
    assert(product == LongNumber("83810205"));

    // Проверка деления
    LongNumber quotient = num1 / num2;
    assert(quotient == LongNumber("1"));

    // Проверка остатка от деления
    LongNumber remainder = num1 % num2;
    assert(remainder == LongNumber("5556"));
}

void test_comparison_operators() {
    LongNumber num1("12345");
    LongNumber num2("6789");
    LongNumber num3("12345");

    // Проверка равенства
    assert(num1 == num3);
    assert(!(num1 == num2));

    // Проверка неравенства
    assert(num1 != num2);
    assert(!(num1 != num3));

    // Проверка меньше
    assert(num2 < num1);
    assert(!(num1 < num2));

    // Проверка больше
    assert(num1 > num2);
    assert(!(num2 > num1));
}

void test_methods() {
    LongNumber num("123456789");

    assert(num.get_digits_number() == 9);
    assert(num.get_rank_number(0) == 9); // Последняя цифра числа
    assert(num.get_rank_number(8) == 1); // Первая цифра числа
    assert(num.is_negative() == false);

    LongNumber negative_num("-98765");
    assert(negative_num.is_negative() == true);
}

int main() {
    try {
        test_constructors();
        test_arithmetic_operators();
        test_comparison_operators();
        test_methods();

        std::cout << "All tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        return 1;
    }

    return 0;
}