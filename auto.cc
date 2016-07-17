// file: auto.cc
// compile: g++ -std=c++11 -o auto auto.cc

#include <iostream>
#include <vector>
#include <string>
#include <map>

void test_map()
{
    std::map<std::string, std::string> mymap {{"abc", "123"}, {"apple", "10000"}};

    for (auto map_entry : mymap) {
        std::cout << map_entry.first << " <" <<
            map_entry.second << ">" << std::endl;
    }
}
void test_vector()
{
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);

    // read
    for (int i : vec) {
        std::cout << i << std::endl;
    }

    // update
    for (int& i : vec) {
        i++;
    }

    // read
    for (int i : vec) {
        std::cout << i << std::endl;
    }
}

int main(int argc, char* argv[])
{
    test_vector();
    test_map();

    return 0;
}
