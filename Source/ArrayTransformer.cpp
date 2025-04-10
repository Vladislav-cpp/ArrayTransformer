#include "ArrayTransformer.h"
#include "TMiscUtils.h"
#include <iterator>
#include <stdexcept>

#define PRINT_IF_NEED_AND_COPY(source, destination, print, additionalInfo) \
    if (print) { \
	std::cout << additionalInfo << std::endl; \
        miscUtils::PrintArrays(source); \
	std::cout << std::endl; \
    } \
    std::copy(source.begin(), source.end(), std::back_inserter(destination.m_vData))


void ManualSortTransformer::Transform(std::vector<std::vector<int>>& arrays, bool printResult) {
	for(auto& vec : arrays) miscUtils::QuickSort(vec.begin(), vec.end(), miscUtils::LessThanComparator);

	PRINT_IF_NEED_AND_COPY(arrays, m_vResult, printResult, "ManualSortTransformer result");
}

std::shared_ptr<Result> ManualSortTransformer::GetResult() const {
	return std::make_unique<ArrayOfIntegerArraysResult>(m_vResult);
}

void IntersectionTransformer::Transform(std::vector<std::vector<int>>& arrays, bool printResult) {
	const auto& result = miscUtils::Intersection(arrays);

	PRINT_IF_NEED_AND_COPY(result, m_vResult, printResult, "IntersectionTransformer result");
}

std::shared_ptr<Result> IntersectionTransformer::GetResult() const {
	return std::make_unique<IntegerArrayResult>(m_vResult);
}

void UniqueReverseSortedTransformer::Transform(std::vector<std::vector<int>>& arrays, bool printResult) {
	auto uniqueArray = miscUtils::UniqueElementsFromArrays(arrays);
	miscUtils::QuickSort(uniqueArray.begin(), uniqueArray.end(), miscUtils::GreaterThanComparator);

	PRINT_IF_NEED_AND_COPY(uniqueArray, m_vResult, printResult, "UniqueReverseSortedTransformer result");
}

std::shared_ptr<Result> UniqueReverseSortedTransformer::GetResult() const {
	return std::make_unique<IntegerArrayResult>(m_vResult);
}

std::unique_ptr<ArrayTransformer> TransformerFactory::Create(enum Transformation type) {
	if	(type == Transformation::sort)			return std::unique_ptr<ArrayTransformer>(new ManualSortTransformer());
	else if (type == Transformation::intersect)		return std::unique_ptr<ArrayTransformer>(new IntersectionTransformer());
	else if (type == Transformation::uniqueReverseSorted)	return std::unique_ptr<ArrayTransformer>(new UniqueReverseSortedTransformer());
	else							throw std::invalid_argument("Невідомий тип трансформації:  " + int(type));
}
