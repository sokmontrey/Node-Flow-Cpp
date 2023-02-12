#include "node.h"

/*------------------------------Node------------------------------*/
template <typename TT>
template <typename... Args>
Node<TT>::Node(Args&&... args): _tensor(std::forward<Args>(args)...){ }

template <typename TT>
Node<TT>::Node(TT&predefined_tensor){
	this->_tensor= predefined_tensor;
}

/*Compute------------------------------*/
template <typename TT>
TT& Node<TT>::evaluate(){
	if(this->_node_type != CONSTANT) this->_derivative_tensor_a = TT(0);
	if(this->_node_type == OPERATOR) this->_derivative_tensor_b = TT(0);
	return this->_tensor;
}
template <typename TT>
void Node<TT>::differentiate(TT &derivative_factor){
	if(this->_node_type != CONSTANT){
		tns::Add<TT>::evaluateTo(
				&this->_derivative_tensor_a, 
				&this->_derivative_tensor_a, 
				&derivative_factor);
	}
}
template <typename TT>
void Node<TT>::differentiate(){
	TT default_derivative_tensor_a(1);
	this->differentiate(default_derivative_tensor_a);
}

/*Getter------------------------------*/
template <typename TT>
TT& Node<TT>::getTensor(){
	return this->_tensor;
}
template <typename TT>
TT& Node<TT>::getDerivativeTensor(){
	return this->_derivative_tensor_a;
}
template <typename TT>
NODE_TYPE Node<TT>::getNodeType(){
	return this->_node_type;
}
/*Setter------------------------------*/
template <typename TT>
void Node<TT>::setTensor(TT&tensor){
	this->_tensor= tensor;
}
template <typename TT>
void Node<TT>::operator=(TT&tensor){
	this->setTensor(tensor);
}

/*-------------------------------Variable-----------------------------*/

/*-------------------------------Constant-----------------------------*/

/*------------------------------Operator------------------------------*/
template <template <typename, typename, typename> class FUNCTION,
	typename TT, typename TA, typename TB>
Op<FUNCTION, TT, TA, TB>
::Op(Node<TA> *node_a, Node<TB> *node_b)
: Node<TT>(){
	this->_node_a = node_a;
	this->_node_b = node_b;
}

/*Compute-----------------------------*/

template <template <typename, typename, typename> class FUNCTION,
	typename TT, typename TA, typename TB>
TT& Op<FUNCTION, TT, TA, TB>::evaluate(){
	this->_derivative_tensor_a = TT(0);

	if(this->_node_b){
		FUNCTION<TT, TA, TB>::evaluateTo(
			&this->_tensor,
			&this->_node_a->evaluate(),
			&this->_node_b->evaluate()
		);
	}else{
		FUNCTION<TT,TA,TB>::evaluateTo(
			&this->_tensor,
			&this->_node_a->evaluate()
		);
	}

	return this->_tensor;
}

template <template <typename, typename, typename> class FUNCTION,
		 typename TT, typename TA, typename TB>
void Op<FUNCTION, TT, TA, TB>::differentiate(TT &derivative_factor){
	if(this->_node_b){
	}
}

/*Getter-----------------------------*/
template <template <typename, typename, typename> class FUNCTION,
		 typename TT, typename TA, typename TB>
TT& Op<FUNCTION, TT, TA, TB>::getDerivativeTensorA(){
	return this->_derivative_tensor_a;
}
template <template <typename, typename, typename> class FUNCTION,
		 typename TT, typename TA, typename TB>
TT& Op<FUNCTION, TT, TA, TB>::getDerivativeTensorB(){
	return this->_derivative_tensor_b;
}
