#ifndef OPERATOR_H
#define OPERATOR_H

#include <cmath>
#include <iostream>

//tns = tensor
namespace tns{

//TODO: match sizes
template <typename TT, typename TA=TT, typename TB=TT>
struct Add{
	static void evaluateTo(TT *to_be_assign, TA *a, TB *b=nullptr);
	static TT evaluate(TA &a, TB &b);
	static void differentiateTo(bool is_a, TT *to_be_assign, TA *a, TB *b=nullptr);
};

template <typename TT, typename TA=TT, typename TB=TT>
struct Mul{
	static void evaluateTo(TT *to_be_assign, TA *a, TB *b=nullptr);
	static void differentiateTo(bool is_a, TT *to_be_assign, TA *a, TB *b=nullptr);
};

template <typename TT, typename TA=TT, typename TB=TA>
struct MatMul{
	static void evaluateTo(TT *to_be_assign, TA *a, TB *b=nullptr);
};

}

#endif //OPERATOR_H
