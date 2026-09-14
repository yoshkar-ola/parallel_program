#include <charconv>
#include <exception>
#include <iostream>
#include <string_view>
#include <syncstream>
#include <thread>
#include <vector>
#include <windows.h>

void Worker(int index)
{
    std::osyncstream(std::cout)
        << "Поток № " << index << " выполняет свою работу\n";
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    if (argc != 2)
    {
        std::cerr << "Использование: " << argv[0] << " <N>\n";
        return 1;
    }

    std::string_view arg{ argv[1] };
    int n = 0;
    auto [ptr, ec] = std::from_chars(arg.data(), arg.data() + arg.size(), n);

    if (ec != std::errc{} || ptr != arg.data() + arg.size() || n <= 0)
    {
        std::cerr << "N должно быть положительным целым числом\n";
        return 2;
    }

    try
    {
        std::vector<std::jthread> threads;
        for (int i = 1; i <= n; ++i)
            threads.emplace_back(Worker, i);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 3;
    }
}