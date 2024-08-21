#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

// 计算器函数，根据操作类型对输入参数列表进行计算
double cal(const std::string& fun, const std::vector<double>& numbers) {
    if (fun == "add") {
        double sum = 0;
        for (double num : numbers) {
            sum += num;
        }
        return sum;
    }
    else if (fun == "minus") {
        double result = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            result -= numbers[i];
        }
        return result;
    }
    else if (fun == "multiply") {
        double product = 1;
        for (double num : numbers) {
            product *= num;
        }
        return product;
    }
    else if (fun == "divide") {
        if (numbers.size() < 2) throw std::invalid_argument("Not enough numbers for division.");
        double result = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            if (numbers[i] == 0) throw std::invalid_argument("Division by zero is not allowed.");
            result /= numbers[i];
        }
        return result;
    }
    else {
        throw std::invalid_argument("Invalid operation.");
    }
}

// 从文件中读取数字
std::vector<double> read_numbers_from_file(const std::string& filename) {
    std::vector<double> numbers;
    std::ifstream file(filename);
    double num;
    while (file >> num) {
        numbers.push_back(num);
    }
    file.close();
    return numbers;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <operation> <filename>" << std::endl;
        return 1;
    }

    std::string operation = argv[1];
    std::string filename = argv[2];

    try {
        std::vector<double> numbers = read_numbers_from_file(filename);
        double result = cal(operation, numbers);
        std::cout << "The result of " << operation << " is: " << result << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}
