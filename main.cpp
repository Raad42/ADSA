#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::string convertToDecimal(const std::string &number, int base) {
    long long decimalValue = 0;
    for (char digit : number) {
        decimalValue = decimalValue * base + (digit - '0');
    }
    return std::to_string(decimalValue);
}

std::string convertFromDecimal(long long decimalValue, int base) {
    if (decimalValue == 0) {
        return "0";
    }
    std::string result;
    while (decimalValue > 0) {
        result.push_back((decimalValue % base) + '0');
        decimalValue /= base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string addInBase(const std::string &num1, const std::string &num2, int base) {
    std::string result;
    int carry = 0;
    int len1 = num1.length();
    int len2 = num2.length();
    int maxLength = std::max(len1, len2);

    for (int i = 0; i < maxLength || carry; i++) {
        int digit1 = (i < len1) ? num1[len1 - 1 - i] - '0' : 0;
        int digit2 = (i < len2) ? num2[len2 - 1 - i] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        result.push_back((sum % base) + '0');
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string subtractInBase(const std::string &num1, const std::string &num2, int base) {
    std::string result;
    int borrow = 0;
    int len1 = num1.length();
    int len2 = num2.length();

    for (int i = 0; i < len1; ++i) {
        int digit1 = num1[len1 - 1 - i] - '0';
        int digit2 = (i < len2) ? num2[len2 - 1 - i] - '0' : 0;
        int difference = digit1 - digit2 - borrow;
        if (difference < 0) {
            difference += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(difference + '0');
    }
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string karatsubaMultiply(const std::string &num1, const std::string &num2, int base) {
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0) {
        return "0";
    }
    if (len1 == 1 && len2 == 1) {
        int digit1 = num1[0] - '0';
        int digit2 = num2[0] - '0';
        return convertFromDecimal(digit1 * digit2, base);
    }

    int maxLength = std::max(len1, len2);
    int halfLength = (maxLength + 1) / 2;

    std::string paddedNum1 = std::string(maxLength - len1, '0') + num1;
    std::string paddedNum2 = std::string(maxLength - len2, '0') + num2;

    std::string upper1 = paddedNum1.substr(0, maxLength - halfLength);
    std::string lower1 = paddedNum1.substr(maxLength - halfLength);
    std::string upper2 = paddedNum2.substr(0, maxLength - halfLength);
    std::string lower2 = paddedNum2.substr(maxLength - halfLength);

    std::string productLower = karatsubaMultiply(lower1, lower2, base);
    std::string productUpper = karatsubaMultiply(upper1, upper2, base);

    std::string sumLowerUpper1 = addInBase(upper1, lower1, base);
    std::string sumLowerUpper2 = addInBase(upper2, lower2, base);
    std::string productSumLowerUpper = karatsubaMultiply(sumLowerUpper1, sumLowerUpper2, base);

    std::string middleTerm = subtractInBase(subtractInBase(productSumLowerUpper, productLower, base), productUpper, base);

    std::string productUpperShifted = productUpper + std::string(2 * halfLength, '0');
    std::string middleTermShifted = middleTerm + std::string(halfLength, '0');

    std::string result = addInBase(addInBase(productUpperShifted, middleTermShifted, base), productLower, base);

    result.erase(0, result.find_first_not_of('0'));

    if (result.empty()) {
        return "0";
    } else {
        return result;
    }
}

int main() {
    std::string input1, input2;
    int base;

    std::cin >> input1 >> input2 >> base;

    std::string additionResult = addInBase(input1, input2, base);
    std::string multiplicationResult = karatsubaMultiply(input1, input2, base);

    std::cout << additionResult << " " << multiplicationResult << " 0" << std::endl;

    return 0;
}
