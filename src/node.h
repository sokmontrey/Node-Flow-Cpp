#ifndef NODE_H
#define NODE_H

#include <memory>
#include <stdexcept>
#include <iostream>

enum NODE_TYPE{
	VARIABLE = 1,
	CONSTANT = 2,
	OPERATOR = 3,
};

//TODO: deconstructor
//TODO: check type of T then assign if Premitive or Other (Matric, etc)
//Base class for other type of Node such as Var, Const, and Op
template <typename T>
class Node{
	protected:
		NODE_TYPE _type;

		T _value;
		T _d_value = T();

	public:
		Node();

		virtual void setValue(T new_value);
		virtual void operator=(T value);

		virtual T evaluate();
		virtual void differentiate(T derivative_factor=1);

		T getValue();
		T getDValue();

		NODE_TYPE getType();
};


template <typename T>
class Var: public Node<T>{
	public:
		Var();
		Var(T value);

		T evaluate() override ;

		void differentiate(T derivative_factor=1);
};

template <typename T>
class Const: public Node<T>{
	public:
		Const();
		Const(T value);

		void setValue (T new_value) override;
		void operator=(T value) override;
};

template <template <typename> class OP, typename T>
class Op: public Node<T>{
	private:
		std::shared_ptr<Node<T>> _a;
		std::shared_ptr<Node<T>> _b;

	public:
		//Both arguments are normal object
		//	OR there is only one argument that is a normal object
		Op(Node<T>* a, Node<T>* b=nullptr);

		//One of the arguments is a temporary object
		//	a is a temp object
		//	OR there is only a and a is a temporary object
		Op(Node<T>&& a, Node<T>* b=nullptr);

		//	b is a temp object
		Op(Node<T>* a, Node<T>&& b);

		//Both arguments are temporary
		Op(Node<T>&& a, Node<T>&& b);

		void setValue(T new_value) override;
		void operator=(T value);

		T evaluate() override;

		void differentiate(T derivative_factor=1) override;
};


#endif //NODE_H
