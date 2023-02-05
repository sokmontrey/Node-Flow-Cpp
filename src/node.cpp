#include "node.h"

/*------------------------------Node------------------------------*/
template <typename TENSOR_TYPE>
template <typename... Args>
Node<TENSOR_TYPE>::Node(Args&&... args): _tensor(std::forward<Args>(args)...){ }

template <typename TENSOR_TYPE>
Node<TENSOR_TYPE>::Node(TENSOR_TYPE &predefined_tensor){
	this->_tensor= predefined_tensor;
}

/*Compute------------------------------*/
template <typename TENSOR_TYPE>
TENSOR_TYPE& Node<TENSOR_TYPE>::evaluate(){
	this->_derivative_tensor = TENSOR_TYPE();
	return this->_tensor;
}
template <typename TENSOR_TYPE>
void Node<TENSOR_TYPE>::differentiate(TENSOR_TYPE &derivative_factor){
	std::cout << "NODE DIFFERENTIATE\n";
	tns::Add<TENSOR_TYPE>::evaluateTo(
			&this->_tensor, 
			&this->_tensor, 
			&derivative_factor);
}

/*Getter------------------------------*/
template <typename TENSOR_TYPE>
TENSOR_TYPE& Node<TENSOR_TYPE>::getTensor(){
	return this->_tensor;
}
template <typename TENSOR_TYPE>
TENSOR_TYPE& Node<TENSOR_TYPE>::getDerivativeTensor(){
	return this->_derivative_tensor;
}
template <typename TENSOR_TYPE>
NODE_TYPE Node<TENSOR_TYPE>::getNodeType(){
	return this->_node_type;
}
/*Setter------------------------------*/
template <typename TENSOR_TYPE>
void Node<TENSOR_TYPE>::setTensor(TENSOR_TYPE &tensor){
	this->_tensor= tensor;
}
template <typename TENSOR_TYPE>
void Node<TENSOR_TYPE>::operator=(TENSOR_TYPE &tensor){
	this->setTensor(tensor);
}


/*-------------------------------Variable-----------------------------*/


/*Compute------------------------------*/
template <typename TENSOR_TYPE>
TENSOR_TYPE& Var<TENSOR_TYPE>::evaluate(){
	this->_derivative_tensor = TENSOR_TYPE();
	return this->_tensor;
}
template <typename TENSOR_TYPE>
void Var<TENSOR_TYPE>::differentiate(TENSOR_TYPE &derivative_factor){
	std::cout << "VAR DIFFERENTIATE\n";
	tns::Add<TENSOR_TYPE>::evaluateTo(
			&this->_tensor, 
			&this->_tensor, 
			&derivative_factor);
}

/*-------------------------------Constant-----------------------------*/

/*Compute-----------------------------*/
template <typename TENSOR_TYPE>
TENSOR_TYPE& Const<TENSOR_TYPE>::evaluate(){
	return this->_tensor;
}

template <typename TENSOR_TYPE>
void Const<TENSOR_TYPE>::differentiate(TENSOR_TYPE& derivative_factor){ }

/*------------------------------Operator------------------------------*/

template <
	template <typename> class FUNCTION,
	typename TENSOR_TYPE, 
	typename TENSOR_TYPE_A,
	typename TENSOR_TYPE_B
>
Op<FUNCTION, TENSOR_TYPE, TENSOR_TYPE_A, TENSOR_TYPE_B>
::Op(Node<TENSOR_TYPE_A> *node_a, Node<TENSOR_TYPE_B> *node_b)
: Node<TENSOR_TYPE>(){
	this->_node_a = node_a;
	this->_node_b = node_b;
}

/*Compute-----------------------------*/

template <
	template <typename> class FUNCTION,
	typename TENSOR_TYPE, 
	typename TENSOR_TYPE_A,
	typename TENSOR_TYPE_B
>
TENSOR_TYPE& Op<FUNCTION, TENSOR_TYPE, TENSOR_TYPE_A, TENSOR_TYPE_B>::evaluate(){
	this->_derivative_tensor = TENSOR_TYPE();

	if(this->_node_b){
		FUNCTION<TENSOR_TYPE>::evaluateTo(
			&this->_tensor,
			&this->_node_a->evaluate(),
			&this->_node_b->evaluate()
		);
	}else{
		FUNCTION<TENSOR_TYPE>::evaluateTo(
			&this->_tensor,
			&this->_node_a->evaluate()
		);
	}

	return this->_tensor;
}

/*

template <typename T, template <typename> class OP>
T Op<T, OP>::evaluate() {
	//reset derivative value because
	//	when taking the derivative _d_value will be += to chain_value
	this->_d_value = T();

	if(_b) 
		this->_value = OP<T>::evaluate(_a->evaluate(), _b->evaluate());
	else 
		this->_value = OP<T>::evaluate(_a->evaluate());

	return this->_value;
}

template <typename T, template <typename> class OP>
void Op<T, OP>::differentiate(T derivative_factor) {
	this->_d_value += derivative_factor;

	if(_b){
		if(_a->getNodeType() != CONSTANT){
			_a->differentiate( derivative_factor * 
				OP<T>::differentiate(true, _a->getValue(), _b->getValue()) 
			);
		}

		if(_b->getNodeType() != CONSTANT){
			_b->differentiate( derivative_factor * 
				OP<T>::differentiate(false, _a->getValue(), _b->getValue())
			);
		}
	}else{
		if(_a->getNodeType() != CONSTANT){
			_a->differentiate( derivative_factor * 
				OP<T>::differentiate(true, _a->getValue()) 
			);
		}
	}
}
*/
