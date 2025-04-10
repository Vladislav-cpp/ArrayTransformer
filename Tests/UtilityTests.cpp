#include "..\\Source/TMiscUtils.h"
#include "..\\Source/ArrayTransformer.h"
#include "UtilityTests.h"
#include <string>
#include <vector>
#include <memory>


namespace UnitTest {

#define ADD_TEST(unitTest, name, expected, codeBlock) \
	unitTest.AddTest(name, expected, [=]() mutable -> std::string { \
		return miscUtils::CustomFormat(codeBlock); \
	});

#define ADD_TEST_Not_Return_Result(unitTest, name, expected, codeBlock, result) \
	unitTest.AddTest(name, expected, [=]() mutable -> std::string { \
		codeBlock; \
		return miscUtils::CustomFormat(result); \
	});

void TestMiscUtils(UnitTest& unitTest) {

	// Test QuickSort
	std::vector<int> testQuickSortArray {9, 7, 4, 0, -1};
	ADD_TEST_Not_Return_Result( unitTest, "Test QuickSort", "-1 0 4 7 9", 
		miscUtils::QuickSort(testQuickSortArray.begin(), testQuickSortArray.end(), miscUtils::LessThanComparator), testQuickSortArray);


	// Test ParseLineToNumbers
	std::vector<int> testDuplicatesArray {9, 7, 4, 0, -1, 4, 9, 15, 0};

	ADD_TEST_Not_Return_Result(unitTest, "Test RemoveDuplicates", "7 -1 15",
		miscUtils::RemoveDuplicates(testDuplicatesArray), testDuplicatesArray);


	// Test Intersection
	std::vector<std::vector<int>> testIntersectionArrays { {5, 4, 4, 2, -1, 0}, {10, 15, -1, +0} };

	ADD_TEST( unitTest, "Test Intersection", "-1 0", miscUtils::Intersection(testIntersectionArrays) );


	// Test UniqueElementsFromArrays
	std::vector<std::vector<int>> testUniqueArrays { {5, 4, 4, 2, -1, 0}, {10, 15, -1, +0, 4, 5, 100} };

	ADD_TEST( unitTest, "Test UniqueElementsFromArrays", "2 10 15 100", miscUtils::UniqueElementsFromArrays(testUniqueArrays) );


	// Test UniqueElementsFromArrays
	std::vector<std::vector<int>> testCountElementsArray { {5, 4, 4, 2, -1, 0, 0} };

	ADD_TEST(unitTest, "Test CountElements", "-1 1 0 2 2 1 4 2 5 1", miscUtils::CountElements(testCountElementsArray));

}

#define ADD_TRANSFORMATION_TEST(unitTest, transformation, expected, arrays, ResultType) \
	unitTest.AddTest( #transformation, expected, \
	[=]() mutable -> std::string { \
	    auto transformer = TransformerFactory::Create(transformation); \
	    transformer->Transform(arrays, false); \
	    auto result = std::dynamic_pointer_cast<ResultType>(transformer->GetResult()); \
	    return miscUtils::CustomFormat(result->m_vData); \
	});

void TestArrayTransformer(UnitTest& unitTest) {
	std::vector<std::vector<int>> arrays = {
		{5, 4, 4, 2, -1, 0},
		{10, 15, -1, +0},
		{5, 4, 15, 2, 3, 0}
	};

	//● тест сортувати масиви без допомоги вбудованих функцій
	ADD_TRANSFORMATION_TEST(unitTest, Transformation::sort, "-1 0 2 4 4 5 -1 0 10 15 0 2 3 4 5 15", arrays, ArrayOfIntegerArraysResult);

	//● тест знаходити перетин всіх трьох масивів
	ADD_TRANSFORMATION_TEST(unitTest, Transformation::intersect, "0", arrays, IntegerArrayResult);

	miscUtils::QuickSort(arrays.begin(), arrays.end(), 
						std::function<bool(const std::vector<int>& a,const std::vector<int>& b)>{[](const auto& a, const auto& b) {
							 return a.size() > b.size();
						}});

	//● тест знаходити перетин двох масивів з найбільжиною довгою
	auto twoLongestArray = std::vector<std::vector<int>>{ arrays[0], arrays[1] };
	ADD_TRANSFORMATION_TEST(unitTest, Transformation::intersect, "0 2 5", twoLongestArray, IntegerArrayResult);

	//● тест створювати відсортований у зворотному порядку масив, що містить лише унікальні елементи з трьох представлених масивів
	ADD_TRANSFORMATION_TEST(unitTest, Transformation::uniqueReverseSorted, "15 3 -1", twoLongestArray, IntegerArrayResult);
}

#define RunTest(NameFun, unitTest)  \
	NameFun(unitTest); \
	unitTest.RunTests();\
	unitTest.ClearTests();


void RunTests() {
	UnitTest unitTest;

	RunTest(TestMiscUtils, unitTest)
	RunTest(TestArrayTransformer, unitTest)

}

}
