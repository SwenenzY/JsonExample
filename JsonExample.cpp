#pragma comment(lib, "urlmon.lib")

#include <urlmon.h>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp> // Install with nuget
using json = nlohmann::json;
using namespace std;

int main() {

    IStream* stream;
    HRESULT result = URLOpenBlockingStream(0, L"https://swenenzy.com/test.json", &stream, 0, 0); // Any Url
    /*
    {
      "array": [
        1,
        2,
        3
      ],
      "boolean": true,
      "color": "gold",
      "null": null,
      "number": 123,
      "object": {
        "a": "b",
        "c": "d"
      },
      "string": "Hello World"
    }
    */
    if (result != 0)
    {
        return 1;
    }
    char buffer[100];
    unsigned long bytesRead;
    stringstream ss;
    stream->Read(buffer, 100, &bytesRead);
    while (bytesRead > 0U)
    {
        ss.write(buffer, (long long)bytesRead);
        stream->Read(buffer, 100, &bytesRead);
    }
    string resultString = ss.str();
    std::cout << "Data : \n" << resultString << "\n" << std::endl;
    auto j3 = json::parse(resultString);
    std::cout << "'String' from webrequest " << j3["string"] << std::endl;
    std::cout << "'Array' from webrequest " << j3["array"] << std::endl;
    for (const auto& element : j3["array"])
    {
        std::cout << "'Element' from array " << element << std::endl;
    }

    system("pause");



}