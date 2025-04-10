#include "UnitTest.h"
#include <iostream>

namespace UnitTest {

void UnitTest::RunTests() {
	for(const auto& test : m_vTests) {
		std::string result = test.func();
	
		if(result == test.expectedResult)	std::cout << "Test \"" << test.testName << "\" passed." << std::endl;
		else					std::cout << "Test \"" << test.testName << "\" failed. Expected: \"" << test.expectedResult << "\", got: \"" << result << "\"." << std::endl;
	}
}

void UnitTest::AddTest(const std::string& testName, const std::string& expectedResult, TestFunc func) {
	m_vTests.emplace_back( TestData{testName, expectedResult, func} );
}

void UnitTest::ClearTests() {
	m_vTests.clear();
}

}	
