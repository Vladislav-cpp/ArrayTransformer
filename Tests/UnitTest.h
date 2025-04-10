#pragma once
#include <functional>
#include <string>
#include <vector>

namespace UnitTest {

using TestFunc = std::function<std::string()>;

struct TestData {
	std::string testName;
	std::string expectedResult;
	TestFunc func;
};

class UnitTest {
public:
	UnitTest()=default;
	~UnitTest()=default;

public:
	void RunTests();
	void AddTest(const std::string& testName, const std::string& expectedResult, TestFunc func);
	void ClearTests();

private:
	std::vector<TestData> m_vTests;
};

}
