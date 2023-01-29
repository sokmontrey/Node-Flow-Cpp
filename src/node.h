#ifndef NODE_H
#define NODE_H

#include <memory>
#include <stdexcept>
#include <iostream>

template <typename OBJECT_TYPE>
class Node{
	protected:
		OBJECT_TYPE _object;
		OBJECT_TYPE _derivative_object;
	public:
		template <typename... Args>
		Node(Args&&... args);

		//create copy data from a predefined object
		Node(OBJECT_TYPE &predefined_object);

		OBJECT_TYPE& getObject();
		OBJECT_TYPE& getDerivativeObject();
};

/*
enum NODE_TYPE{
	VARIABLE = 1,
	CONSTANT = 2,
	OPERATOR = 3,
};

template <typename T>
class BaseNode{
	protected:
		NODE_TYPE _node_type;

		T _value;
		T _d_value;

	public:
		BaseNode(NODE_TYPE node_type);

		virtual void setValue(T new_value);
		virtual void operator=(T value);

		virtual T evaluate();
		virtual void differentiate(T derivative_factor=1);

		T getValue();
		T getDValue();

		NODE_TYPE getNodeType();
};

template <typename T>
class Var: public BaseNode<T>{
	public:
		Var();
		Var(T value);

		T evaluate() override ;

		void differentiate(T derivative_factor=1);
};

template <typename T>
class Const: public BaseNode<T>{
	public:
		Const();
		Const(T value);

		void setValue (T new_value) override;
		void operator=(T value) override;

		void differentiate(T derivative_factor=1) override ;
};

template <typename T, template <typename> class OP>
class Op: public BaseNode<T>{
	private:
		std::shared_ptr<BaseNode<T>> _a;
		std::shared_ptr<BaseNode<T>> _b;

	public:
		//Both arguments are normal object
		//	OR there is only one argument that is a normal object
		Op(BaseNode<T>* a, BaseNode<T>* b=nullptr);

		//One of the arguments is a temporary object
		//	a is a temp object
		//	OR there is only a and a is a temporary object
		Op(BaseNode<T>&& a, BaseNode<T>* b=nullptr);

		//	b is a temp object
		Op(BaseNode<T>* a, BaseNode<T>&& b);

		//Both arguments are temporary
		Op(BaseNode<T>&& a, BaseNode<T>&& b);

		void setValue(T new_value) override;
		void operator=(T value);

		T evaluate() override;

		void differentiate(T derivative_factor=1) override;
};
*/
#endif //NODE_H
