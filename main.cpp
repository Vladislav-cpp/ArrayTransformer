#include "Source/TMiscUtils.h"
#include "Source/ArrayTransformer.h"
#include "Tests/UtilityTests.h"
#include <functional>


const static std::string s_sInputFileName = "input.txt";

int main() {
	// Test
	UnitTest::RunTests();

	std::cout << "=============================================" << std::endl << std::endl;

	//● зчитувати масиви з файлу
	auto arrays = miscUtils::ReadArraysFromFile(s_sInputFileName);

	//● друкувати вміст масивів
	std::cout << "PrintArrays" << std::endl;
	miscUtils::PrintArrays(arrays);
	std::cout << std::endl;

	//● сортувати масиви без допомоги вбудованих функцій
	auto transformer = TransformerFactory::Create(Transformation::sort);
	transformer->Transform(arrays);

	//● знаходити перетин всіх трьох масивів
	transformer = TransformerFactory::Create(Transformation::intersect);
	transformer->Transform(arrays);

	miscUtils::QuickSort(arrays.begin(), arrays.end(), 
			std::function<bool(const std::vector<int>& a,const std::vector<int>& b)>{[](const auto& a, const auto& b) {
				 return a.size() > b.size();
			}});

	//● знаходити перетин двох масивів з найбільшою найбільжиною
	auto twoLongestArray = std::vector<std::vector<int>>{ arrays[0], arrays[1] };
	transformer = TransformerFactory::Create(Transformation::intersect);
	transformer->Transform(twoLongestArray);

	//● створювати відсортований у зворотному порядку масив, що містить лише унікальні елементи з трьох представлених масивів
	transformer = TransformerFactory::Create(Transformation::uniqueReverseSorted);
	transformer->Transform(arrays);

   	return 0;
}
