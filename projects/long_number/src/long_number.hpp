#pragma once

#include <iostream>

namespace vitashaa {
	class LongNumber {
	private:
		int* numbers;
		int length;
		int sign;

	public:
		LongNumber();
		LongNumber(const char* const str);
		LongNumber(const std::string& str) : LongNumber(str.c_str()) {} // Added assignment operator
		LongNumber(const LongNumber& x);
		LongNumber(LongNumber&& x);

		~LongNumber();

		LongNumber& operator = (const char* const str);
		LongNumber& operator = (const std::string& str); // Added assignment operator
		LongNumber& operator = (const LongNumber& x);
		LongNumber& operator = (LongNumber&& x);

		bool operator == (const LongNumber& x) const;
		bool operator != (const LongNumber& x) const;
		bool operator > (const LongNumber& x) const;
		bool operator < (const LongNumber& x) const;
		bool operator>=(const LongNumber& x) const;
		LongNumber operator-() const;
		LongNumber operator + (const LongNumber& x) const;
		LongNumber operator - (const LongNumber& x) const;
		LongNumber operator * (const LongNumber& x) const;
		LongNumber operator / (const LongNumber& x) const;
		LongNumber operator % (const LongNumber& x) const;

		int get_digits_number() const noexcept;
		int get_rank_number(const int rank) const;
		bool is_negative() const noexcept;

		friend std::ostream& operator<<(std::ostream &os, const LongNumber& x);

	private:
		int get_length(const char* const str) const noexcept;
		void remove_leading_zeros();
	};
}