#pragma once
#include <vector>
#include <memory>
#include <string>

enum class Transformation {
	sort,		
	intersect,	
	uniqueReverseSorted,
};

struct Result {
	virtual ~Result() = default;
};

struct ArrayOfIntegerArraysResult : Result {
	std::vector<std::vector<int>> m_vData;
};

struct IntegerArrayResult : Result {
	std::vector<int> m_vData;
};

class ArrayTransformer {
public:
    virtual ~ArrayTransformer() {}
    virtual void Transform(std::vector<std::vector<int>>& arrays, bool printResult = true) = 0;
	virtual std::shared_ptr<Result> GetResult() const = 0;
};

class ManualSortTransformer : public ArrayTransformer {
public:
    void Transform(std::vector<std::vector<int>>& arrays, bool printResult) override;
	virtual std::shared_ptr<Result> GetResult() const override;

private:
	ArrayOfIntegerArraysResult m_vResult;
};

class IntersectionTransformer : public ArrayTransformer {
public:
    void Transform(std::vector<std::vector<int>>& arrays, bool printResult) override;
	virtual std::shared_ptr<Result> GetResult() const override;

private:
	IntegerArrayResult m_vResult;

};

class UniqueReverseSortedTransformer : public ArrayTransformer {
public:
    void Transform(std::vector<std::vector<int>>& arrays, bool printResult) override;
	virtual std::shared_ptr<Result> GetResult() const override;
	
private:
	IntegerArrayResult m_vResult;
};

class TransformerFactory {
public:
    static std::unique_ptr<ArrayTransformer> Create(enum Transformation type);
};

