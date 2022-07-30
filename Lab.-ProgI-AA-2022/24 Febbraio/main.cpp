//Frame: https://pastebin.com/XjPPK5Gh
//Output: JPEG

#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<typeinfo>
using namespace std;

template<typename T>
class AbstractVec{

	T** data;

protected:

	int max_size;
	int read_index;
	int write_index;

public:

	AbstractVec(int max_size):max_size(max_size), read_index(0), write_index(0){

		data = new T* [max_size];

		for(int i=0; i<max_size; i++)
			data[i] = nullptr;
	}

	virtual T* next() = 0;

	virtual bool insert(T x) = 0;

	int len(){

		int count = 0;

		for(int i=0; i<max_size; i++)
		{
			if(data[i])
				count++;
		}

		return count;
	}

	void shuffle(){

		int j = rand() % max_size;

		for(int i=0; i<max_size; i++)
		{
			if(data[i])
			{
				while(!data[j])
					j = rand() % max_size;

				T* tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}

		}
	}

	virtual ostream& print(ostream& os){

		os << "Class= " << typeid(*this).name() << ", max_size= " << max_size << ", vec=[";

		for(int i=0; i<max_size; i++)
		{
			if(data[i])
				os << *data[i] << " ";
		}

		return os << "], len= " << this->len();
	}

protected: 

	T* get(int index){return data[index];}

	bool exists(int index){

		if(data[index])
			return true;

		return false;
	}

	void set(int i, T x){data[i] = new T(x);}

};

template<typename T>
class PlainVec : public AbstractVec<T>{

	public: 

		PlainVec(int max_size) : AbstractVec<T>(max_size){}

		T* next()override{

			if(AbstractVec<T>::read_index <= AbstractVec<T>::max_size -1)
				return AbstractVec<T>::get(AbstractVec<T>::read_index++);

			return nullptr;
		}

		bool insert(T x)override{

			if(AbstractVec<T>::write_index <= AbstractVec<T>::max_size-1)
			{
				AbstractVec<T>::set(AbstractVec<T>::write_index++, x);
				return true;
			}

			return false;
		}

		ostream& print(ostream& os)override{

			AbstractVec<T> :: print(os);
			return os;
		}

};

template<typename T>
class CircularVec : public AbstractVec<T>{

	int cycles;

public:

	CircularVec(int max_size) : AbstractVec<T>(max_size), cycles(0){}

	T* next()override{

		AbstractVec<T>::read_index++;

		if(AbstractVec<T>::read_index == AbstractVec<T>::max_size)
		{
			AbstractVec<T>::read_index = 0;
			cycles ++;
		}

		return AbstractVec<T>::get(AbstractVec<T>::read_index);
	}

	bool insert(T x)override{

		AbstractVec<T>::set(AbstractVec<T>::write_index++, x);

		if(AbstractVec<T>::write_index == AbstractVec<T>::max_size)
		{
			AbstractVec<T>::write_index = 0;
			cycles++;
		}

		return true;
	}

	int getCycles(){return this->cycles;}

	ostream& print(ostream& os)override{

		AbstractVec<T> :: print(os);
		return os << ", cycles=" << cycles;
	}
};

template<typename T>
ostream& operator<< (ostream& os, AbstractVec<T>& obj){return obj.print(os);}

int main(){

	srand(424242);
	const int DIM = 10;

	AbstractVec<int>* vec [DIM];

	for(int i=0; i<DIM; i++) {
		int size = rand()%16+5;
		if(rand()%2){
			vec[i] = new PlainVec<int>(size);
		} else {
			vec[i] = new CircularVec<int>(size);
		}
	}
	
	for(int i=0; i<DIM*5; i++) {
		int x = rand()%100;
		vec[x%DIM]->insert(x);
	}
	
	for(int i=0; i<DIM; i++)
		vec[i]->shuffle();

	cout << endl;

	int min = vec[0]->len();

	for(int i=0; i<DIM; i++)
	{
		cout << i << ") " << *vec[i] << endl;

		if(vec[i]->len() < min)
			min = vec[i]->len();
	}

	cout << "\nMin len() : " << min << endl;

	cout << endl;
}