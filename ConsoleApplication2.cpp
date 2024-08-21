
/*增加对文件不存在的处理：在尝试打开文件之前，检查文件是否存在。
改进异常信息：提供更详细的异常信息，帮助用户更好地理解错误。
使用std::stof替代std::atof：std::stof是C++11中推荐的函数，用于将字符串转换为浮点数，因为它可以抛出异常，处理非法输入。
使用std::to_string格式化输出结果：提高输出的可读性。
优化内存使用：在cal函数中，使用迭代器而不是索引来遍历向量，避免不必要的类型转换。
增加对除法操作的优化：如果除法操作只有一个数字，直接返回该数字，避免不必要的操作。*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <sstream>

// 计算器函数，根据操作类型对输入参数列表进行计算
double cal(const std::string& fun, const std::vector<double>& numbers) {
    if (fun == "add") {
        double sum = 0;
        for (const auto& num : numbers) {
            sum += num;
        }
        return sum;
    }
    else if (fun == "minus") {
        if (numbers.size() == 1) return numbers[0]; // 优化：只有一个数字时直接返回
        double result = 0;
        for (const auto& num : numbers) {
            result -= num;
        }
        return result;
    }
    else if (fun == "multiply") {
        double product = 1;
        for (const auto& num : numbers) {
            product *= num;
        }
        return product;
    }
    else if (fun == "divide") {
        if (numbers.size() < 2) throw std::invalid_argument("Division requires at least two numbers.");
        if (numbers[0] == 0) throw std::invalid_argument("Division by zero is not allowed.");
        double result = numbers[1];
        for (size_t i = 2; i < numbers.size(); ++i) {
            if (numbers[i] == 0) throw std::invalid_argument("Division by zero is not allowed.");
            result /= numbers[i];
        }
        return result;
    }
    else {
        throw std::invalid_argument("Invalid operation: '" + fun + "' is not supported.");
    }
}

// 从文件中读取数字
std::vector<double> read_numbers_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename); // 增加文件不存在的处理
    }
    std::vector<double> numbers;
    std::string line;
    while (getline(file, line)) {
        try {
            numbers.push_back(std::stof(line)); // 使用std::stof替代std::atof
        }
        catch (const std::invalid_argument& e) {
            throw std::runtime_error("Invalid number format in file: " + filename);
        }
    }
    file.close();
    return numbers;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <operation> <filename> <numbers per line>" << std::endl;
        return 1;
    }

    std::string operation = argv[1];
    std::string filename = argv[2];
    int numbers_per_line = std::stoi(argv[3]); // 增加每行数字数量的参数

    try {
        std::vector<double> numbers = read_numbers_from_file(filename);
        if (numbers.size() % numbers_per_line != 0) {
            throw std::runtime_error("The number of numbers read does not match the expected per line count.");
        }
        double result = cal(operation, numbers);
        std::cout << "The result of " << operation << " is: " << std::to_string(result) << std::endl; // 使用std::to_string格式化输出
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}