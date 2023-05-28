#include <variant>
#include <iostream>

auto func = [] (int x) -> std::variant<int,std::string> {
    if (x > 0)
        return x * 1.5; // 返回值是int，可以隐式转换为std::variant<int, std::string>
    else
        return "error"; // 返回值是const char*，可以隐式转换为std::variant<int, std::string>
};

auto func2 = [](){std::cout<<"haha"<<std::endl;};

int main()
{
    auto result = func(-3); // 调用lambda
    if (std::holds_alternative<int>(result)) // 检查返回值是否是int类型
    {
        std::cout << "The result is " << std::get<int>(result) << "\n"; // 访问返回值
    }
    else if (std::holds_alternative<std::string>(result)) // 检查返回值是否是std::string类型
    {
        std::cout << "The result is " << std::get<std::string>(result) << "\n"; // 访问返回值
    }

    func2();
    return 0;
}
