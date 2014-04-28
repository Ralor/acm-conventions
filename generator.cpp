#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <windows.h>

using namespace std;

const char TEMPLATE[ ] = "template.cpp";

int main() {
    char lastTask;
    do {
        cin >> lastTask;
        if (lastTask >= 'a' && lastTask <= 'z')
            lastTask = toupper(lastTask);
    } while (lastTask < 'A' || lastTask > 'Z');
    ifstream f(TEMPLATE, ios_base::binary);
    f.seekg(0, f.end);
    auto templateSize = f.tellg();
    f.seekg(0, f.beg);
    unique_ptr<char[ ]> templateCpp(new char[templateSize]);
    f.read(templateCpp.get(), templateSize);
    f.close();
    for (char task = 'A'; task <= lastTask; task++) {
        ostringstream ss;
        ss << task << task - 'A' + 1;
        string directoryName = ss.str();
        ::CreateDirectoryA(directoryName.c_str(), nullptr);
        ofstream f((directoryName + "\\input.txt").c_str());
        f << '\n';
        f.close();
        ss << '\\' << (char)tolower(task) << ".cpp";
        f.open(ss.str(), ios_base::binary);
        f.write(templateCpp.get(), templateSize);
        f.close();
    }
}
