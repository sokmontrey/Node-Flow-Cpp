#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include "./node.cpp"

//TRIED:Use operator overload to create Operator
//	complicated pointer. Might need to overload the operator multiple time
//TODO: make data type into class instead.
//TODO: higher degree of derivative
//TODO: error handling

enum TENSOR_TYPE{
	SCALAR = 1,
	VECTOR = 2,
	MATRIX = 3
};

/*
template <typename T>
class Scalar: public Tensor<T, 1>{
	public:
		Scalar(): Tensor<T, 1>(SCALAR) {}
		Scalar(T initial_value) : Tensor<T, 1>(SCALAR){
			this->_data[0] = initial_value;
		}

		T getValue() const override { return this->_data[0]; }
};

template <typename T, size_t ROWS, size_t COLS>
class Matrix: public Tensor<T, ROWS * COLS>{
	public:
		Matrix(): Tensor<T, ROWS * COLS>(MATRIX) {}

		Matrix(T initial_value): Tensor<T, ROWS * COLS>(MATRIX) {
			for(size_t row=0; row<ROWS; row++){
				for(size_t col=0; col<COLS; col++){
					this->_data[index(row, col)] = initial_value;
				}
			}
		}

		Matrix(double min_random, double max_random, double seed)
		: Tensor<T, ROWS * COLS>(MATRIX) {
			std::srand(seed);
			for(size_t row=0; row<ROWS; row++){
				for(size_t col=0; col<COLS; col++){
					this->_data[index(row, col)] = (double)std::rand()/RAND_MAX*(max_random-min_random)+min_random;
				}
			}
		}

		Matrix(T (&&arr)[ROWS][COLS]): Tensor<T, ROWS*COLS>(MATRIX){
			for(size_t row=0; row<ROWS; row++){
				for(size_t col=0; col<COLS; col++){
					this->_data[index(row, col)] = arr[row][col];
				}
			}
		}

		//TODO: override getValue with no arguments
		T getValue(size_t row, size_t col) {
			return this->_data[index(row, col)];
		}
		T setValue(size_t row, size_t col, T value){
			this->_data[index(row, col)] = value;
		}

		T& operator()(size_t row, size_t col){
			return this->_data[index(row, col)];
		}

		void print(){
			std::cout << "\n";
			for(size_t row=0; row<ROWS; row++){
				for(size_t col=0; col<COLS; col++){
					std::cout << this->_data[index(row, col)] << " ";
				}
				std::cout << "\n";
			}
			std::cout << "\n";
		}

		size_t index(size_t row, size_t col){
			//column-major indexing
			return row * COLS + col;
		}
};

*/

//TODO: make TENSOR even more general for n-dimension object

/*
 *
 * shape is 1D array that from right to left, 
 * represent the size from the largest to the smallest dimension respectively
 * Example: {4, 3, 10}
 * In this case, the Tensor is 3 dimension which has
 * 4 set of 3 set of 10 elements
 * Or in other word, 4 set of 3, and in each one there are 10 elements.
 *
 */

template <typename T, size_t T_SIZE=1, size_t DIMENSION=1>
class Tensor{
	protected:
		T _data[T_SIZE] = {0};

		size_t _shape[DIMENSION];
		size_t _indexing_multiplyer[DIMENSION];

		virtual size_t _indexing(size_t (&indexes)[DIMENSION]){
			size_t index = 0;
			for(size_t i=0; i<DIMENSION; i++){
				index += this->_indexing_multiplyer[i] * indexes[i];
			}
			return index;
		}

	public:
		Tensor(size_t (&&shape)[DIMENSION] = {1},
				bool is_define_indexing_multiplyer=true){

			this->_shape[0] = shape[0];
			this->_indexing_multiplyer[DIMENSION-1] = 1;

			if(is_define_indexing_multiplyer){
				size_t last_indexing_multiplyer = 1;
				for(size_t i=1; i<DIMENSION; i++){
					//transfer shape data from the argument to _shape 
					//while initiallizing index_multiplyer
					//to save iteration time
					this->_shape[i] = shape[i];

					//{ A*B*...*N-1, A*B*...*N-2, A*B, A }
					last_indexing_multiplyer *= shape[DIMENSION-i];
					this->_indexing_multiplyer[DIMENSION-i-1] = last_indexing_multiplyer;
				}
			}
		}

		void initDefault(T initial_value){
			std::fill(this->_data, this->_data + T_SIZE, initial_value);
		}

		void initRandom(double min_random, double max_random, double seed){
			std::srand(seed);
			for(size_t i=0; i<T_SIZE; i++){
					this->_data[i] = (double)std::rand()/
						RAND_MAX*(max_random-min_random)+min_random;
			}
		}

		void setValue(T value, size_t index=0){
			this->_data[index] = value;
		}
		void setValue(T value, size_t (&&indexes)[DIMENSION]){
			this->_data[this->_indexing(indexes)] = value;
		}

		T getValue(size_t index=0){
			return this->_data[index];
		}
		T getValue(size_t (&&indexes)[DIMENSION]){
			return this->getValue(this->_indexing(indexes));
		}

		virtual void print() const {
			std::cout << "\n";
			for(size_t i=0; i<T_SIZE; i++){
				std::cout << this->_data[i] << " ";
			}
			std::cout << "\n";
		}
};

int main(){
	Tensor<double, 6, 2> a({2, 3});
	a.initRandom(-1, 1, 1);

	a.print();
	std::cout << a.getValue({1,1});

	return 0;
}

