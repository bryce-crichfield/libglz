#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <string>

namespace veracity {

    namespace log {
        void success(std::string message);
        void info(std::string message);
        void warn(std::string message);
        void error(std::string message);
    }
}


namespace test {
using std::cout;
using std::endl;
using std::function;
using std::map;
using std::string;

namespace Color {
const auto Red = "\033[0;31m";
const auto Green = "\033[0;32m";
const auto Yellow = "\033[0;33m";
const auto Blue = "\033[0;34m";
const auto Magenta = "\033[0;35m";
const auto Cyan = "\033[0;36m";
const auto White = "\033[0;37m";
const auto Reset = "\033[0m";
} // namespace Color
namespace log {
void success(string message) {
    cout << Color::Green << message << Color::Reset << endl;
}

void info(string message) {
    cout << Color::Cyan << message << Color::Reset << endl;
}

void warn(string message) {
    cout << Color::Yellow << message << Color::Reset << endl;
}

void error(string message) {
    cout << Color::Red << message << Color::Reset << endl;
}
} // namespace log

struct Attempt {
    std::string message;
    bool isSuccess;
};

Attempt Pass() {
    return Attempt{.isSuccess = true, .message = ""};
}

Attempt Fail(std::string message) {
    return Attempt{.isSuccess = false, .message = message};
}

struct Suite {
    string name;
    std::map<string, function<Attempt()>> cases;

    Suite(string name) : name(name) {
    }

    int run() {
        for (auto& pair : cases) {
            log::info("Running test: " + pair.first);
            auto attempt = pair.second();
            if (attempt.isSuccess) {
                log::success("Test passed: " + pair.first);
            } else {
                log::error("Test \"" + pair.first + "\" failed with: ");
                log::error(attempt.message);
                return 1;
            }
            std::cout << std::endl;
        }
        return 0;
    }

    void add(string name, function<Attempt()> test) {
        cases.insert(make_pair(name, test));
    }
};
} // namespace test

#define assert(condition)                                                                          \
    if (!(condition)) {                                                                            \
        return test::Attempt::Fail("Assertion failed: " #condition);                               \
    }

#define attempt(procedure) \
    try { \
        procedure; \
    } catch (std::exception& e) { \
        return test::Fail("Exception thrown: " + std::string(e.what())); \
    }

#define Suite(name)                                                                                \
    int main(void) {                                                                               \
        test::Suite suite(name);

#define Case(name)                                                                                 \
    suite.add(name, []() {
#define EndCase()                                                                                  \
    return test::Pass();                                                                           \
    });

#define EndSuite()                                                                                 \
    return suite.run();                                                                            \
    }

class TestSuite {
    std::vector<
}