#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <iostream>

namespace miscUtils {

static auto LessThanComparator = std::function<bool(const int, const int)>{[](int a, int b) { return a < b; }};
static auto GreaterThanComparator = std::function<bool(const int, const int)>{[](int a, int b) { return a > b; }};

std::vector<int> ParseLineToNumbers(const std::string& line);

std::vector<std::vector<int>> ReadArraysFromFile(const std::string& filename);

template <typename T>
std::string CustomFormat(const std::vector<T>& array) {
	std::string output;
	for(const auto& i : array) output += std::to_string(i) + " ";
	if(!output.empty()) output.pop_back();
	return output;

}

template <typename T>
std::string CustomFormat(const std::vector<std::vector<T>>& arrays) {
	std::string output;
	for(const auto& array : arrays) for(const auto& i : array) output += std::to_string(i) + " ";
	if(!output.empty()) output.pop_back();
	return output;
}
	
template <typename T>
std::string CustomFormat(const std::map<int, T>& map) {
	std::string output;
	for(const auto& i : map) output += std::to_string(i.first) + " " + std::to_string(i.second) + " ";
	if(!output.empty()) output.pop_back();
	return output;
}

template <typename T>
void PrintArrays(const T& arrays) {
    for(size_t i = 0; i < arrays.size(); ++i) {

        std::cout << "Vector " << i + 1 << ": ";
        for(int num : arrays[i]) std::cout << num << " ";
        std::cout << std::endl;
    }
}

template <>
void inline PrintArrays<std::vector<int>>(const std::vector<int>& arrays) {

    for(int num : arrays) std::cout << num << " ";
    std::cout << std::endl;
}

template <typename T>
std::map<T, int> CountElements(const std::vector<std::vector<T>>& arrays) {
    std::map<T, int> counter;

    for(const auto& array : arrays)
        for(const T& item : array)
            ++counter[item];
    return counter;
}

template <typename T>
std::vector<int> UniqueElementsFromArrays(const std::vector<std::vector<T>>& arrays) {
	std::vector<T> result;

	auto counter = CountElements(arrays);
	for(auto& i: counter) if(i.second == 1) result.push_back(i.first);

	return result;
}

template <typename T>
void RemoveDuplicates(std::vector<T>& vec) {
	auto counter = CountElements( std::vector<std::vector<T>>{vec} );

    vec.erase( std::remove_if( vec.begin(), vec.end(),
            [&counter](const T& value) {
                return counter[value] > 1;
            }), vec.end());
}

template <typename T>
std::vector<T> Intersection(std::vector<std::vector<T>> arrays) {
	for(auto& array : arrays) RemoveDuplicates(array);

	std::vector<T> result;

	auto counter = CountElements(arrays);
	for(auto& i: counter) if(i.second == arrays.size()) result.push_back(i.first);

	return result;
}


template <typename T, typename A>
typename T Partition(const T begin, const T end, std::function<bool(const A, const A)> comp) {
	auto i = begin;

	for(auto j = begin; j<end; ++j) if( comp(*j, *(end - 1)) ) {
		std::swap(*j, *i);
		++i;
	}

	std::swap(*i, *(end-1));
	return i;
}

template <typename T, typename A>
void QuickSort(const T begin, const T end, std::function<bool(const A, const A)> comp) {
	if(begin>=end) return;

	auto pivot = Partition(begin, end, comp);

	QuickSort(begin, pivot, comp);
	QuickSort(pivot+1, end, comp);
}

}

