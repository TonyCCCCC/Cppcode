#ifndef   _LINEARSPACE_H_
#define  _LINEARSPACE_H_
#ifndef _ITERATOR_DEBUG_LEVEL
#define _ITERATOR_DEBUG_LEVEL 0
#else
#undef _ITERATOR_DEBUG_LEVEL
#define _ITERATOR_DEBUG_LEVEL 0
#endif

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include<fstream>
#include "nonsqsolver.h"
typedef unsigned int uint_32;
namespace Linspace
{
	//class unique_arr
	template<typename valtype>
	class unique_arr
	{
	private:
		valtype* arr;
		uint_32 arr_len;
		unique_arr operator=(unique_arr<valtype>);
	public:
		unique_arr():arr(NULL),arr_len(0){}
	
		unique_arr(const uint_32 len):arr_len(len){
			switch(len){
			case 0:
				arr=NULL;
				break;
			default:
				arr=new valtype[len];
				break;
			}
		}
		~unique_arr(){
			clear();
		}

		uint_32 size()const{return arr_len;}

		void clear(){
			switch(arr_len){
			case 0:
				break;
			default:
				delete[]arr;
				arr=NULL;
				arr_len=0;
				break;
			}
		}

		void swap(unique_arr<valtype>& otherarr){
			uint_32 mlen;
			valtype* mptr;
			mlen=arr_len;
			arr_len=otherarr.arr_len;
			otherarr.arr_len=mlen;
			mptr=arr;
			arr=otherarr.arr;
			otherarr.arr=mptr;
		}

		void move(unique_arr<valtype>& movedarr){
			clear();
			arr_len=movedarr.arr_len;
			arr=movedarr.arr;
			movedarr.arr_len=0;
			movedarr.arr=NULL;
		}

		void copy(unique_arr<valtype>& referarr){
			resize(referarr.size());
			for(uint_32 i(0);i<arr_len;i++){
				arr[i]=referarr[i];
			}
		}
		void set(const valtype* inputarr,const uint_32 len){
			resize(len);
			for (uint_32 i(0);i<len;i++){
				arr[i]=inputarr[i];
			}
		}

		void set(const std::vector<valtype>& inputarr){
			std::vector<valtype>::const_iterator its=inputarr.begin(),ite=inputarr.end();
			resize(inputarr.size());
			for (uint_32 i(0);its<ite;i++){arr[i]=*its++;}
		}

		operator bool()const{return(arr_len==0?0:1);}
		void initial(const valtype& val){
			for (uint_32 i(0);i<arr_len;i++){this->arr[i]=val;}
		}

		void resize(const uint_32 newsize){
			if (newsize!=arr_len)
			{
				switch(newsize){
				case 0:
					clear();
					break;
				default:
					clear();
					arr_len=newsize;
					arr=new valtype[arr_len];
					break;
				}
			} 		
		}

		valtype* release(){
			valtype* rsltptr=arr;
			arr=NULL;
			arr_len=0;
			return rsltptr;
		}
		valtype& operator[](const uint_32 ind)const{
			return(*(arr+ind));
		}
	};


	//class virtvec
	template<typename type>
	class SprsMat;

	template<typename type>
	class VirtualSprMat;

	template<typename type>
	class vector;

	template<typename vtype>
	class virtvec
	{
	private:
		vtype* data;
		uint_32 length;
		friend vector<vtype>;
		friend class SprsMat<vtype>;
		friend class VirtualSprMat<vtype>;
		virtvec();
		virtvec(const uint_32&);
		virtvec(const uint_32&,const vtype& val );
		void reset();
		void copy(const vector<vtype>& rvec);
		void free();
	public:
		virtvec<vtype> operator+(const vector<vtype>& rvec);
		virtvec<vtype> operator+(virtvec<vtype>& rvec);
		virtvec<vtype> operator-(const vector<vtype>& rvec);
		virtvec<vtype> operator-(virtvec<vtype>& rvec);
	};


	//class vector
	template<typename type>
	class vector
	{
	private:
		type* data;
		uint_32 length;
	public:
		vector();
		vector(const uint_32& defsize);
		vector(unique_arr<type>& referarr);
		vector(const std::vector<type>& defvec);
		vector(const type* arr,const uint_32& arrlen);
		vector(const uint_32& deflen, const type& val);
		friend class SprsMat<type>;
		friend class VirtualSprMat<type>;
		~vector();
		void clear();
		uint_32 size()const;
		void resize(const uint_32& newsize);
		void swap(vector<type>& othervec);
		bool empty()const;
		void initial(const type& val);
		void set(const std::vector<type>& refervec);
		void set(const vector<type>& refervec);
		type& operator[](const uint_32& ind)const;
		friend virtvec<type>;
		void operator=(const vector<type>& rvec);
		void operator=(virtvec<type>& rvec);
		virtvec<type> operator+(const vector<type>& rvec)const;
		virtvec<type> operator+(virtvec<type>& rvec)const;
		void operator+=(const vector<type>& rvec);
		void operator+=(virtvec<type>& rvec);
		void operator+=(const type& val);
		virtvec<type> operator-(const vector<type>& rvec)const;
		virtvec<type> operator-(virtvec<type>& rvec)const;
		void operator-=(const vector<type>& rvec);
		void operator-=(virtvec<type>& rvec);
		void operator*=(const type& val);
		double norm(const std::string& normname)const;
	};


	//member functions of class virtvec
	template<typename vtype>
	virtvec<vtype>::virtvec():data(NULL),length(0){}

	template<typename vtype>
	virtvec<vtype>::virtvec(const uint_32& defsize):length(defsize){
		switch(defsize){
		case 0:
			data=NULL;
			break;
		default:
			data=new vtype[defsize];
			break;
		}
	}

	template<typename vtype>
	virtvec<vtype>::virtvec(const uint_32& defsize,const vtype&val):length(defsize){
		switch(defsize){
		case 0:
			data=NULL;
			break;
		default:
			data=new vtype[defsize];
			for(uint_32 i(0);i<defsize;i++){
				data[i]=val;
			}
		}
	}


	template<typename vtype>
	void virtvec<vtype>::reset(){
		data=NULL;
	}

	template<typename vtype>
	void virtvec<vtype>::copy(const vector<vtype>& rvec){
		if(length==rvec.length){
			for(uint_32 i(0);i<length;i++){data[i]=rvec.data[i];}
		}
		else{
			length=rvec.length;
			delete[]data;
			if(length){
				data=new vtype[length];
				for(uint_32 i(0);i<length;i++){data[i]=rvec.data[i];}
			}
			else{data=NULL;}
		}
	}

	template<typename vtype>
	void virtvec<vtype>::free(){
		if(length){delete[]data;}
	}

	template<typename vtype>
	virtvec<vtype> virtvec<vtype>::operator+(const vector<vtype>& rvec){
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The two vector should be of the same length for '+' operation"<<std::endl;
		}
		virtvec<vtype> rsltvec(length);
		for (uint_32 i(0);i<length;i++){
			rsltvec.data[i]=data[i]+rvec.data[i];
		}
		free();
		return rsltvec;
	}

	template<typename vtype>
	virtvec<vtype> virtvec<vtype>::operator+(virtvec<vtype>& rvec){
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The two vector should be of the same length for '+' operation"<<std::endl;
		}
		virtvec<vtype> rsltvec(length);
		for (uint_32 i(0);i<length;i++){
			rsltvec.data[i]=data[i]+rvec.data[i];
		}
		free();
		rvec.free();
		return rsltvec;
	}

	template<typename vtype>
	virtvec<vtype> virtvec<vtype>::operator-(const vector<vtype>& rvec){
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The two vector should be of the same length for '-' operation"<<std::endl;
		}
		virtvec<vtype> rsltvec(length);
		for (uint_32 i(0);i<length;i++){
			rsltvec.data[i]=data[i]-rvec.data[i];
		}
		free();
		return rsltvec;
	}

	template<typename vtype>
	virtvec<vtype> virtvec<vtype>::operator-(virtvec<vtype>& rvec){
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The two vector should be of the same length for '-' operation"<<std::endl;
		}
		virtvec<vtype> rsltvec(length);
		for (uint_32 i(0);i<length;i++){
			rsltvec.data[i]=data[i]-rvec.data[i];
		}
		free();
		rvec.free();
		return rsltvec;
	}



	//member functions of class vector
	template<typename type>
	vector<type>::vector():data(NULL),length(0){}

	template<typename type>
	vector<type>::vector(const uint_32& defsize):length(defsize){
		switch(defsize){
		case 0:
			data=NULL;
			break;
		default:
			data=new type[defsize];
			break;
		}
	}

	template<typename type>
	vector<type>::vector(unique_arr<type>& referarr){
		length=referarr.arr_len;
		data=referarr.release();
	}

	template<typename type>
	vector<type>::vector(const std::vector<type>& defvec){
		length=defvec.size();
		switch(length){
		case 0:
			data=NULL;
			break;
		default:
			data=new type[length];
			copy(defvec.begin(),defvec.end(),data);
			break;
		}
	}

	template<typename type>
	vector<type>::vector(const type* arr,const uint_32& arrlen):length(arrlen){
		switch(length){
		case 0:
			data=NULL;
			break;
		default:
			data=new type[length];
			for(uint_32 i(0);i<length;i++){data[i]=arr[i];}
			break;
		}
	}

	template<typename type>
	vector<type>::vector(const uint_32& deflen, const type& val):length(deflen){
		if(length){
			data=new type[length];
			for(uint_32 i(0);i<length;i++){
				data[i]=val;
			}
		}
		else{data=NULL;}
	}

	template<typename type>
	vector<type>::~vector(){
		switch(length){
		case 0:
			break;
		default:
			delete[]data;
			break;
		}
	}

	template<typename type>
	void vector<type>::clear(){
		switch(length){
		case 0:
			break;
		default:
			length=0;
			delete[]data;
			data=NULL;
			break;
		}
	}

	template<typename type>
	uint_32 vector<type>::size()const{return length;}

	template<typename type>
	void vector<type>::resize(const uint_32& newsize){
		if(newsize!=length){
			clear();
			switch(newsize){
			case 0:
				break;
			default:
				data=new type[newsize];
				length=newsize;
				break;
			}
		}
	}

	template<typename type>
	void vector<type>::swap(vector<type>& othervec){
		uint_32 mlen;
		type* mdata;
		mlen=length;
		length=othervec.length;
		othervec.length=mlen;
		mdata=data;
		data=othervec.data;
		othervec.data=mdata;
	}

	template<typename type>
	bool vector<type>::empty()const{
		return(length==0?1:0);
	}

	template<typename type>
	void vector<type>::initial(const type& val){
		for(uint_32 i(0);i<length;i++){data[i]=val;}
	}

	template<typename type>
	void vector<type>::set(const std::vector<type>& refervec){
		resize(refervec.size());
		std::vector<type>::const_iterator its=refervec.begin(),ite=refervec.end();
		for(uint_32 i(0);its<ite;i++,its++){data[i]=*its++;}
	}

	template<typename type>
	void vector<type>::set(const vector<type>& refervec){
		resize(refervec.size());
		for(uint_32 i(0);i<length;i++){data[i]=refervec.data[i];}
	}

	template<typename type>
	type& vector<type>::operator[](const uint_32& ind)const{
		return *(data+ind);
	}

	template<typename type>
	void vector<type>::operator=(const vector<type>& rvec){
		resize(rvec.length);
		for (uint_32 i(0);i<length;i++)
		{
			data[i]=rvec.data[i];
		}
	}

	template<typename type>
	void vector<type>::operator=(virtvec<type>& rvec){
		clear();
		data=rvec.data;
		length=rvec.length;
		rvec.reset();
	}

	template<typename type>
	virtvec<type> vector<type>::operator+(const vector<type>& rvec)const{
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The two vector should be of the same length for '+' operation"<<std::endl;
		}
		virtvec<type> rsltvec(length);
		for (uint_32 i(0);i<length;i++){
			rsltvec.data[i]=data[i]+rvec.data[i];
		}
		return rsltvec;
	}

	template<typename type>
	virtvec<type> vector<type>::operator+(virtvec<type>& rvec)const{
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The two vector should be of the same length for '+' operation"<<std::endl;
		}
		virtvec<type> rsltvec(length);
		for (uint_32 i(0);i<length;i++){
			rsltvec.data[i]=data[i]+rvec.data[i];
		}
		rvec.free();
		return rsltvec;
	}

	template<typename type>
	void vector<type>:: operator +=(const vector<type>& rvec){
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The vectors on both sides of '=' should be of the same length for '+=' operation"<<std::endl;
		}
		for (uint_32 i(0);i<length;i++)
		{
			data[i]+=rvec.data[i];
		}
	}

	template<typename type>
	void vector<type>::operator +=(virtvec<type>& rvec){
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The vectors on both sides of '=' should be of the same length for '+=' operation"<<std::endl;
		}
		for (uint_32 i(0);i<length;i++)
		{
			data[i]+=rvec.data[i];
		}
		rvec.free();
	}

	template<typename type>
	void vector<type>::operator+=(const type& val){
		for(uint_32 i(0);i<length;i++){data[i]+=val;}
	}

	template<typename type>
	virtvec<type> vector<type>::operator-(const vector<type>& rvec)const{
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The two vector should be of the same length for '-' operation"<<std::endl;
		}
		virtvec<type> rsltvec(length);
		for (uint_32 i(0);i<length;i++){
			rsltvec.data[i]=data[i]-rvec.data[i];
		}
		return rsltvec;
	}

	template<typename type>
	virtvec<type> vector<type>::operator-(virtvec<type>& rvec)const{
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The two vector should be of the same length for '-' operation"<<std::endl;
		}
		virtvec<type> rsltvec(length);
		for (uint_32 i(0);i<length;i++){
			rsltvec.data[i]=data[i]-rvec.data[i];
		}
		rvec.free();
		return rsltvec;
	}

	template<typename type>
	void vector<type>:: operator -=(const vector<type>& rvec){
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The vectors on both sides of '=' should be of the same length for '-=' operation"<<std::endl;
		}
		for (uint_32 i(0);i<length;i++)
		{
			data[i]-=rvec.data[i];
		}
	}

	template<typename type>
	void vector<type>:: operator -=(virtvec<type>& rvec){
		//check the parameters
		if(length!=rvec.length){
			std::cout<<"Linspace::vector error: The vectors on both sides of '=' should be of the same length for '-=' operation"<<std::endl;
		}
		for (uint_32 i(0);i<length;i++)
		{
			data[i]-=rvec.data[i];
		}
		rvec.free();
	}

	template<typename type>
	void vector<type>::operator*=(const type& val){
		for (uint_32 i(0);i<length;i++){data[i]*=val;}
	}

	template<typename type>
	double vector<type>::norm(const std::string& nname)const{
		switch(length)
		{
		case 0:
			std::cout<<"Linspace::vector error: norm of empty vector is null"<<std::endl;
			return -1;
		default:
			break;
		}
		double rslt;
		if(nname.compare("infty")==0){
			type positival;
			rslt=data[0]<0?-data[0]:data[0];
			for (uint_32 i(1);i<length;i++){
				positival=data[i]<0?-data[i]:data[i];
				if(rslt<positival){rslt=positival;}
			}
			return rslt;
		}

		if(nname.compare("1")==0){
			rslt=data[0]<0?-data[0]:data[0];
			for (uint_32 i(1);i<length;i++){
				rslt+=data[i]<0?-data[i]:data[i];
			}
			return rslt;
		}

		if(nname.compare("2")==0){
			rslt=data[0]*data[0];
			for (uint_32 i(1);i<length;i++){
				rslt+=data[i]*data[i];
			}
			return sqrt(rslt);
		}

		std::cout<<"Linsapce::vector error: undefined norm"<<std::endl;
		return -1;
	}


	//class SparseArray

	template<typename T>
	class SprsArr;

	//this is an auxiliary class which is actually the same as the class 'SprsArr', 
	//but only used in some cases for avoiding reallocating memories. 
	template<typename T>
	class VirtualSprArr
	{
	protected:
		T *elems;
		uint_32* inds;
		uint_32 size;
		VirtualSprArr();
		void reset();
		void free();
		void copy(const SprsArr<T>& rarr);
		friend class SprsArr<T>;
	};


	//this is an auxiliary class for  SprsMat class
	//generally, it couldn't be used by users
	template<typename T>
	class SprsArr
	{
	protected:
		T *elems;//save elements of array
		uint_32* inds;//save corresponding indices of elements in elems
		uint_32 size;// 'size' is the length of elems
		SprsArr(const T* elements,const uint_32* indices, const uint_32 sprsize);
		SprsArr(const SprsArr<T>& arr);
		SprsArr();
		~SprsArr();
		void move(T* elements,uint_32* indices, const uint_32 sprsize);
		void move(VirtualSprArr<T>& movedarr);
		void setarr(const T* elements,const uint_32* indices, const uint_32 sprsize);
		void setarr(const T scalar,const T* elements,const uint_32* indices, const uint_32 sprsize);
		void reallocate(const uint_32 rightsize);
		void free();
		void swap(SprsArr<T>& otherarr);
		void operator=(const SprsArr<T>& rightarr);
		void operator=(VirtualSprArr<T>& rightarr);
		void operator*=(const T scalar);
		void operator+=(const SprsArr<T>& rightarr);
		void compress();
		void show()const;
		void reset();
		friend class SprsMat<T>;
	};

	//member functions of VirtualSprArr
	template<typename T>
	VirtualSprArr<T>::VirtualSprArr():elems(NULL),inds(NULL),size(0){}

	template<typename T>
	void VirtualSprArr<T>::reset()
	{
		elems=NULL;
		inds=NULL;
	}

	template<typename T>
	void VirtualSprArr<T>::free()
	{
		if(size){delete[]elems;elems=NULL;
		delete[]inds;inds=NULL;
		}
	}

	template<typename T>
	void VirtualSprArr<T>::copy(const SprsArr<T>& rarr){
		if(size==rarr.size){
			for(uint_32 i(0);i<size;i++){
				inds[i]=rarr.inds[i];
				elems[i]=rarr.elems[i];
			}
		}
		else{
			size=rarr.size;
			delete[]inds;
			delete[]elems;
			if(size){
				inds=new uint_32[size];
				elems=new T[size];
				for(uint_32 i(0);i<size;i++){
					inds[i]=rarr.inds[i];
					elems[i]=rarr.elems[i];
				}
			}
			else{
				inds=NULL;
				elems=NULL;
			}
		}
	}

	//member functions of SprsArr
	template<typename T>
	SprsArr<T>::SprsArr(const T* elements,const uint_32* indices, const uint_32 sprsize):size(sprsize)
	{
		if (size)
		{
			elems=new T[size];
			inds=new uint_32[size];
			for (uint_32 i(0);i<size;i++)
			{
				elems[i]=elements[i];
				inds[i]=indices[i];
			}
		}
		else
		{
			elems=NULL;
			inds=NULL;
		}
	}

	template<typename T>
	SprsArr<T>::SprsArr()
	{
		elems=NULL;
		inds=NULL;
		size=0;
	}


	template<typename T>
	SprsArr<T>::SprsArr(const SprsArr<T>& arr)
	{
		size=arr.size;
		if(size)
		{
			elems=new T[size];
			inds=new uint_32[size];
			for (uint_32 i(0);i<size;i++)
			{
				elems[i]=arr.elems[i];
				inds[i]=arr.inds[i];
			}
		}
		else
		{
			elems=NULL;
			inds=NULL;
		}
	}

	template<typename T>
	SprsArr<T>::~SprsArr()
	{
		if(size)
		{
			delete[]elems;
			elems=NULL;
			delete[]inds;
			inds=NULL;
		}
	}

	template<typename T>
	void SprsArr<T>::free()
	{
		if (size)
		{
			size=0;
			delete[]elems;
			elems=NULL;
			delete[]inds;
			inds=NULL;
		}
	}


	template<typename T>
	void SprsArr<T>::swap(SprsArr<T>& otherarr)
	{
		uint_32 median;
		uint_32* indmedian;
		T* elemsmedian;
		median=size;
		size=otherarr.size;
		otherarr.size=median;
		indmedian=inds;
		inds=otherarr.inds;
		otherarr.inds=indmedian;
		elemsmedian=elems;
		elems=otherarr.elems;
		otherarr.elems=elemsmedian;
	}

	template<typename T>
	void SprsArr<T>::operator=(const SprsArr<T>& rightarr)
	{
		if (rightarr.size)
		{
			if (size!=rightarr.size)
			{
				size=rightarr.size;
				delete[]elems;
				delete[]inds;
				elems=new T[size];
				inds=new uint_32[size];
			}
			for (uint_32 i(0);i<size;i++)
			{
				elems[i]=rightarr.elems[i];
				inds[i]=rightarr.inds[i];
			}
		}
		else
		{
			free();
		}
	}

	template<typename T>
	void SprsArr<T>::operator=(VirtualSprArr<T>& rightarr)
	{
		move(rightarr);
	}

	//move the data from input to sparse array and the input is set as NULL
	template<typename T>
	void SprsArr<T>::move(T* elements,uint_32* indices, const uint_32 sprsize)
	{
		size=sprsize;
		elems=elements;
		inds=indices;
		elements=NULL;
		indices=NULL;
	}

	template<typename T>
	void SprsArr<T>::move(VirtualSprArr<T>& movedarr)
	{
		free();
		inds=movedarr.inds;
		elems=movedarr.elems;
		size=movedarr.size;
		movedarr.reset();
	}

	template<typename T>
	void SprsArr<T>::operator *=(const T scalar)
	{
		for (uint_32 i(0);i<size;i++)
		{
			elems[i]*=scalar;
		}
	}

	template<typename T>
	void SprsArr<T>::operator +=(const SprsArr<T>& rightarr)
	{

		if(!rightarr.size)//if the sender is empty
		{
			return;
		}
		//if the receiver is empty, then copy the sender
		if(!size)
		{
			size=rightarr.size;
			elems=new T[size];
			inds=new uint_32[size];		
			for(uint_32 i(0);i<size;i++)
			{
				inds[i]=rightarr.inds[i];
				elems[i]=rightarr.elems[i];
			}
		}
		T* currentvalptr,*othervalptr,*mvalptr;
		uint_32* currentindptr,*otherindptr,*mindptr;
		uint_32 currentupd,currentcover=0,count=0,othercover=1,otherubd,media;

		//initializing variables for accounting intersection indices between two index array
		if(rightarr.inds[0]<inds[0])
		{
			currentindptr=inds;
			currentvalptr=elems;
			otherindptr=rightarr.inds;
			othervalptr=rightarr.elems;
			currentupd=size;
			otherubd=rightarr.size;
		}
		else if(inds[0]==rightarr.inds[0])
		{
			othercover=0;
			currentindptr=rightarr.inds;
			otherindptr=inds;
			currentvalptr=rightarr.elems;
			othervalptr=elems;
			currentupd=rightarr.size;
			otherubd=size;
		}
		else
		{
			currentindptr=rightarr.inds;
			otherindptr=inds;
			currentvalptr=rightarr.elems;
			othervalptr=elems;
			currentupd=rightarr.size;
			otherubd=size;
		}
		if (currentindptr[0]>otherindptr[otherubd-1])
		{
			//if there is no intersection between two  indices array then the length of new std::vector is reclen+sedlen
			count=size+rightarr.size;
		} 
		else
		{
			uint_32 i,insecub;
			insecub=inds[size-1]<rightarr.inds[rightarr.size-1]?inds[size-1]:rightarr.inds[rightarr.size-1];
			if (othercover!=0)
			{
				//to find othercover
				othercover=0;
				for (i=1;i<otherubd;i++)
				{
					if (currentindptr[0]<=otherindptr[i])
					{
						othercover=i-1;
						break;
					}
				}
			}
			//compute the length of new std::vector
			while(currentindptr[currentcover]<=insecub)
			{
				if (currentindptr[currentcover]<otherindptr[othercover])
				{
					currentcover++;
				}
				else if(currentindptr[currentcover]==otherindptr[othercover])
				{
					if (currentvalptr[currentcover]==(-othervalptr[othercover]))
					{
						count++;
					}
					count++;
					currentcover++;
					othercover++;
				}
				else{
					//if currentindex> other stationary index then swap them
					mindptr=currentindptr;currentindptr=otherindptr;otherindptr=mindptr;
					mvalptr=currentvalptr;currentvalptr=othervalptr;othervalptr=mvalptr;
					media=currentcover;currentcover=othercover;othercover=media;
					media=currentupd;currentupd=otherubd;otherubd=media;
					currentcover++;
				}
				if (currentupd<=currentcover)
				{
					break;
				}
			}
			count=size+rightarr.size-count;
		}		
		//if final length is zero then the result std::vector is empty
		if (count==0)
		{
			free();
		}
		else
		{
			uint_32* oldindreceiver=inds;
			T* oldvalreceiver=elems;
			elems=new T[count];
			inds=new uint_32[count];
			uint_32 newcount=0;
			currentcover=1;othercover=0;
			if (rightarr.inds[0]<oldindreceiver[0])
			{
				currentindptr=rightarr.inds;
				otherindptr=oldindreceiver;
				currentvalptr=rightarr.elems;
				othervalptr=oldvalreceiver;
				currentupd=rightarr.size;
				otherubd=size;
				inds[0]=currentindptr[0];
				elems[0]=currentvalptr[0];
				newcount++;
			}
			else if(rightarr.inds[0]==oldindreceiver[0])
			{
				currentindptr=rightarr.inds;
				otherindptr=oldindreceiver;
				currentvalptr=rightarr.elems;
				othervalptr=oldvalreceiver;
				currentupd=rightarr.size;
				otherubd=size;
				if (currentvalptr[0]!=(-othervalptr[0]))
				{
					inds[0]=currentindptr[0];
					elems[0]=currentvalptr[0]+othervalptr[0];
					newcount++;
				}		
				othercover++;		
			}
			else
			{
				currentindptr=oldindreceiver;
				otherindptr=rightarr.inds;
				currentvalptr=oldvalreceiver;
				othervalptr=rightarr.elems;
				currentupd=size;
				otherubd=rightarr.size;
				inds[0]=currentindptr[0];
				elems[0]=currentvalptr[0];
				newcount++;
			}
			while((currentcover<currentupd)&&newcount!=count)
			{
				//if other array achieves the end, then swap two arrays and break the 'while' circle
				if (otherubd<=othercover)
				{
					otherindptr=currentindptr;
					othervalptr=currentvalptr;
					otherubd=currentupd;
					othercover=currentcover;
					break;
				}
				if (currentindptr[currentcover]<otherindptr[othercover])
				{
					inds[newcount]=currentindptr[currentcover];
					elems[newcount]=currentvalptr[currentcover];
					currentcover++;
					newcount++;
				}
				else if(currentindptr[currentcover]==otherindptr[othercover])
				{
					//if the indices coincide then check whether the result of plus is zero
					if (currentvalptr[currentcover]!=(-othervalptr[othercover]))
					{
						inds[newcount]=currentindptr[currentcover];
						elems[newcount]=currentvalptr[currentcover]+othervalptr[othercover];
						newcount++;
					}		
					currentcover++;
					othercover++;	
				}
				else{
					//if currentindex> other stationary index then commute them
					mindptr=currentindptr;currentindptr=otherindptr;otherindptr=mindptr;
					mvalptr=currentvalptr;currentvalptr=othervalptr;othervalptr=mvalptr;
					media=currentcover;currentcover=othercover;othercover=media;
					media=currentupd;currentupd=otherubd;otherubd=media;
					inds[newcount]=currentindptr[currentcover];
					elems[newcount]=currentvalptr[currentcover];
					currentcover++;
					newcount++;
				}
			}
			while (othercover<otherubd)
			{
				if (count<=newcount)
				{
					break;
				}
				inds[newcount]=otherindptr[othercover];
				elems[newcount]=othervalptr[othercover];
				newcount++;
				othercover++;
			}
			size=count;
			delete[]oldindreceiver;
			delete[]oldvalreceiver;
		}
	}

	template<typename T>
	void SprsArr<T>::reallocate(const uint_32 rightsize)
	{
		if (rightsize)
		{
			if (size!=rightsize)
			{
				free();
				elems=new T[rightsize];
				inds=new uint_32[rightsize];
			}
		}
		else
		{
			free();
		}
	}

	template<typename T>
	void SprsArr<T>::compress()
	{
		if (size)
		{
			uint_32 i,count=0;
			for (i=0;i<size;i++)
			{
				if (elems[i]!=0)
				{
					count++;
				}
			}
			if (count==0)
			{
				return;
			}
			else
			{
				uint_32* newinds=new uint_32[count];
				T* newelems=new T[count];
				uint_32 k=0;
				for(i=0;i<size;i++)
				{
					if (elems[i]!=0)
					{
						newinds[k]=inds[i];
						newelems[k]=elems[i];
						k++;
					}
					if (k==count)
					{
						break;
					}
				}
				size=count;
				delete[]elems;
				delete[]inds;
				elems=newelems;
				inds=newinds;
			}
		}
	}

	template<typename T>
	void SprsArr<T>::setarr(const T* elements,const uint_32* indices, const uint_32 sprsize)
	{
		reallocate(sprsize);
		size=sprsize;
		if (sprsize)
		{		    
			for(uint_32 i(0);i<size;i++)
			{
				elems[i]=elements[i];
				inds[i]=indices[i];
			}
		} 
	}

	template<typename T>
	void SprsArr<T>::setarr(const T scalar,const T* elements,const uint_32* indices, const uint_32 sprsize)
	{
		reallocate(sprsize);
		size=sprsize;
		if (sprsize)
		{		    
			for(uint_32 i(0);i<size;i++)
			{
				elems[i]=elements[i]*scalar;
				inds[i]=indices[i];
			}
		} 
	}

	template<typename T>
	void SprsArr<T>::reset()
	{
		size=0;
		inds=NULL;
		elems=NULL;
	}

	template<typename T>
	void SprsArr<T>::show()const
	{
		if (size)
		{
			std::cout<<"length of sparse array is:"<<size<<std::endl;
			for (uint_32 i(0);i<size;i++)
			{
				std::cout<<"("<<inds[i]<<","<<elems[i]<<")"<<",  ";
			}
		}
		else
		{
			std::cout<<"empty array"<<std::endl;
		}
	}



	//class sparse matrix
	//this is an auxiliary class whose private members are actually the same as those of the class 'SprsMat', 
	//but only used in some cases for avoiding reallocating memories. 
	template<typename T>
	class VirtualSprMat
	{
	protected:
		T* elems;
		uint_32* colinds;
		uint_32* numel;
		uint_32 colmsize,rowsize;
		VirtualSprMat();
		VirtualSprMat(const uint_32& rsize,const uint_32& colsize);
		void reallocate(const uint_32& sparselen,const uint_32& rsize);
		void copy(const SprsMat<T>& matrix);
		VirtualSprMat(const T scalr,const SprsMat<T>& matrix);
		void free();
		void reset();
		friend class SprsMat<T>;
	public:
		VirtualSprMat<T> operator*(const SprsMat<T>& rmat);
		VirtualSprMat<T> operator*(VirtualSprMat<T>& rmat);
		VirtualSprMat<T> operator+(const SprsMat<T>& rmat);
		VirtualSprMat<T> operator+(VirtualSprMat<T>& rmat);
		VirtualSprMat<T> operator-(const SprsMat<T>& rmat);
		VirtualSprMat<T> operator-(VirtualSprMat<T>& rmat);
		virtvec<T> operator*(const vector<T>& rvec);
		virtvec<T> operator*(virtvec<T>& rvec);
	};


	//this is a class which is a data type of sparse matrix based on the "compressed row structure"
	template<typename T>
	class NSsolver;

	template<typename T>
	class SprsMat
	{
	protected:
		typedef Linspace::unique_arr<T> UarrVal;
		typedef Linspace::unique_arr<uint_32> Uarruint;
		typedef std::vector<T> SVecval;
		typedef std::vector<uint_32> SVecUint;
		typedef	 Linspace::vector<T> LVecval;
		typedef Linspace::vector<uint_32> LVecuint;
		typedef Linspace::VirtualSprMat<T> VSMval;
		typedef Linspace::virtvec<T> VVecval;
		typedef Linspace::SprsMat<T> SMval;
	
		T* elems;//save nonzero elements of matrix under row-major order
		uint_32* colinds;//save column subscripts of nonzero entries of matrix under row-major order
		uint_32* numel;//numel[0]=0; numel[i] is number of nonzero entries in 0~(i-1)th rows of matrix for 1<=i<=N
		uint_32 colmsize,rowsize;//column size and rowsize of matrix
		SprsMat(const T* elemnts,const uint_32* colmind,const uint_32* elenumel,const uint_32& rsize,const uint_32& colsize);
		void move(T* elemnts,uint_32* colmind,uint_32* elenumel,const uint_32& rsize,const uint_32& colsize);
		void move(VSMval& movedmat);
		void setmatrix(const T* elemnts,const uint_32* colmind,const uint_32* elenumel,const uint_32& rsize,const uint_32& colsize);
		void reallocate(const uint_32& sparselen,const uint_32& rsize);
		uint_32* gnertdiaginds()const;
	public:
		template<class> friend class NSsolver;
     	friend class VSMval;
		SprsMat();
		SprsMat(const SMval& matrix);
		SprsMat(UarrVal& elemnts,Uarruint& colmind,Uarruint& elenumel,const uint_32& rsize,const uint_32& colsize);
		SprsMat(const SVecval& elemnts,const SVecUint& colmind,const SVecUint& elenumel,const uint_32& rsize,const uint_32& colsize);
		SprsMat(const LVecval& elemnts,const LVecuint& colmind,const LVecuint& elenumel,const uint_32& rsize,const uint_32& colsize);
		SprsMat(const uint_32& rsize,const uint_32& columnsize);
		~SprsMat();
		void setmatrix(const SVecval& elemnts,const SVecUint& colmind,const SVecUint& elenumel,const uint_32& rsize,const uint_32& colsize);
		void setmatrix(const LVecval& elemnts,const LVecuint& colmind,const LVecuint& elenumel,const uint_32& rsize,const uint_32& colsize);
		void setmatrix(UarrVal& elemnts,Uarruint& colmind,Uarruint& elenumel,const uint_32& rsize,const uint_32& colsize);
		bool Is_true()const;
		bool Is_empty()const;
		double density()const;
		void free();
		void show()const;
		void operator=(const SMval& matrix);
		void operator=(VSMval& rmatrix);
		void swap(SMval& othermatrix);
		void operator*=(const SMval& rmatrix);
		void operator*=(VSMval& rmatrix);
		void compress();
		void SprMatFout(const std::string& filename,const uint_32& setprecisn,const bool ifcover)const;
		void SprMatFin(const std::string& filename,const std::string& format);
		double norm(const std::string& normname)const;
		T getvalue(const uint_32& rowindex, const uint_32& colindex)const;
		VSMval transpose()const;
		VSMval operator*(const SMval& rightmatrix)const;
		VSMval operator*(VSMval& rightmatrix)const;
		VSMval  operator+(const SMval& rightmatrix)const;
		VSMval operator+(VSMval & rmat)const;
		VSMval  operator-(const SMval& rmatrix)const;
		VSMval  operator-(VSMval & rmat)const;
		VVecval operator*(const LVecval& rvec)const;
		VVecval operator*(VVecval& rvec)const;

	};

	//member functions of  class VirtualSprMat
	template<typename T>
	VirtualSprMat<T>::VirtualSprMat():colinds(NULL),numel(NULL),elems(NULL),rowsize(1),colmsize(1){}

	template<typename T>
	VirtualSprMat<T>::VirtualSprMat(const uint_32& rsize,const uint_32& colsize):colinds(NULL),numel(NULL),elems(NULL),
		rowsize(rsize),colmsize(columnsize){}

	template<typename T>
	void VirtualSprMat<T>::reallocate(const uint_32& sparselen,const uint_32& rsize)
	{
		if(sparselen)//if the goal of replication is nonempty
		{
			if (elems)//if matrix is nonempty
			{
				if (numel[rowsize]!=sparselen)
				{
					delete[]elems;
					delete[]colinds;
					elems=new T[sparselen];
					colinds=new uint_32[sparselen];
				}
				if (rowsize!=rsize)
				{
					delete[]numel;
					numel=new uint_32[rsize+1];
				}
			} 
			else//if matrix is empty
			{
				elems=new T[sparselen];
				colinds=new uint_32[sparselen];
				numel=new uint_32[rsize+1];
			}
		}
		else//if the goal of replication is empty
		{
			free();
		}
	}

	template<typename T>
	void VirtualSprMat<T>::copy(const SprsMat<T>& rmatrix)
	{
		//if the right matrix is nonempty, then perform copy
		if (rmatrix.elems)
		{
			uint_32 i,len;
			bool ifclearelems=1,ifclearnumel=1;
			len=rmatrix.numel[rmatrix.rowsize];
			reallocate(len,rmatrix.rowsize);
			rowsize=rmatrix.rowsize;
			colmsize=rmatrix.colmsize;
			for (i=0;i<len;i++)
			{
				elems[i]=rmatrix.elems[i];
				colinds[i]=rmatrix.colinds[i];
			}
			len=rowsize+1;
			for (i=0;i<len;i++)
			{
				numel[i]=rmatrix.numel[i];
			}
		} 
		else//if right matrix is empty, then free the left matrix
		{
			free();
			colmsize=rmatrix.colmsize;
			rowsize=rmatrix.rowsize;
		}
	}

	template<typename T>
	VirtualSprMat<T>::VirtualSprMat(const T scalr,const SprsMat<T>& matrix):rowsize(matrix.rowsize),colmsize(matrix.colmsize)
	{
		switch((bool)(matrix.elems&&scalr!=0))
		{
		case true:
			uint_32 i,len;
			len=matrix.numel[rowsize];
			elems=new T[len];
			colinds=new uint_32[len];
			for(i=0;i<len;i++){elems[i]=scalr*matrix.elems[i];
			colinds[i]=matrix.colinds[i];}
			len=rowsize+1;
			numel=new uint_32[len];
			for(i=0;i<len;i++){numel[i]=matrix.numel[i];}
			break;
		case false:
			elems=NULL;colinds=NULL;numel=NULL;
			break;
		}
	}

	template<typename T>
	void VirtualSprMat<T>::reset()
	{
		colinds=NULL;
		numel=NULL;
		elems=NULL;
	}

	template<typename T>
	void VirtualSprMat<T>::free()
	{
		if(elems){
			delete[]elems;
			delete[]colinds;
			delete[]numel;
			colinds=NULL;
			numel=NULL;
			elems=NULL;
		}
	}

	template<typename T>
	VirtualSprMat<T> VirtualSprMat<T>::operator*(const SprsMat<T>& rmat){
		SprsMat<T> newlmat;
		newlmat.move(*this);
		VirtualSprMat<T> rsltmat;
		rsltmat=newlmat*rmat;
		newlmat.free();
		return rsltmat;
	}

	template<typename type>
	VirtualSprMat<type> VirtualSprMat<type>::operator*(VirtualSprMat<type>& rmat){
		SprsMat<type> newlmat,newrmat;
		newlmat.move(*this);
		newrmat.move(rmat);
		VirtualSprMat<type> rsltmat;
		rsltmat=newlmat*newrmat;
		newlmat.free();
		newrmat.free();
		return rsltmat;
	}

	template<typename type>
	VirtualSprMat<type> VirtualSprMat<type>::operator+(const SprsMat<type>& rmat){
		SprsMat<type> newlmat;
		newlmat.move(*this);
		VirtualSprMat<type> rsltmat;
		rsltmat=newlmat+rmat;
		newlmat.free();
		return rsltmat;
	}

	template<typename type>
	VirtualSprMat<type> VirtualSprMat<type>::operator+(VirtualSprMat<type>& rmat){
		SprsMat<type> newlmat,newrmat;
		newlmat.move(*this);
		newrmat.move(rmat);
		VirtualSprMat<type> rsltmat;
		rsltmat=newlmat+newrmat;
		newlmat.free();
		newrmat.free();
		return rsltmat;
	}

	template<typename type>
	VirtualSprMat<type> VirtualSprMat<type>::operator-(const SprsMat<type>& rmat){
		SprsMat<type> newlmat;
		newlmat.move(*this);
		VirtualSprMat<type> rsltmat;
		rsltmat=newlmat-rmat;
		newlmat.free();
		return(rsltmat);
	}

	template<typename type>
	VirtualSprMat<type> VirtualSprMat<type>::operator-(VirtualSprMat<type>& rmat){
		SprsMat<type> newlmat,newrmat;
		newlmat.move(*this);
		newrmat.move(rmat);
		VirtualSprMat<type> rsltmat;
		rsltmat=newlmat-newrmat;
		newlmat.free();
		newrmat.free();
		return rsltmat;
	}

	template<typename type>
	virtvec<type> VirtualSprMat<type>::operator*(const vector<type>& rvec){
		//check parameters
		if(colmsize!=rvec.length){
			std::cout<<"Linspace::SprsMat error: length of vector must be equal to column size of matrix in matrix-vector multiplication"<<std::endl;
			virtvec<type> rsltvec;
			return rsltvec;
		}
		virtvec<type> rsltvec(rowsize,0);
		if(elems){
			uint_32 i,j;
			for (i=0;i<rowsize;i++){
				for(j=numel[i];j<numel[i+1];j++){
					rsltvec.data[i]+=elems[j]*rvec.data[colinds[j]];
				}
			}
		}
		free();
		return rsltvec;
	}

	template<typename type>
	virtvec<type> VirtualSprMat<type>::operator*(virtvec<type>& rvec){
		//check parameters
		if(colmsize!=rvec.length){
			std::cout<<"Linspace::SprsMat error: length of vector must be equal to column size of matrix in matrix-vector multiplication"<<std::endl;
			virtvec<type> rsltvec;
			return rsltvec;
		}
		virtvec<type> rsltvec(rowsize,0);
		if(elems){
			uint_32 i,j;
			for (i=0;i<rowsize;i++){
				for(j=numel[i];j<numel[i+1];j++){
					rsltvec.data[i]+=elems[j]*rvec.data[colinds[j]];
				}
			}
		}
		free();
		rvec.free();
		return rsltvec;
	}

	//move data from arrays to SprsMat matrix and evaluate original arrays as NULL
	template<typename T>
	void SprsMat<T>::move(T* elemnts,uint_32* colmind,uint_32* elemsnumel,const uint_32& rsize,const uint_32& columnsize)
	{
		free();
		rowsize=rsize;
		colmsize=columnsize;
		elems=elemnts;
		colinds=colmind;
		numel=elemsnumel;
		elemnts=NULL;colmind=NULL;elemsnumel=NULL;
	}

	template<typename T>
	void SprsMat<T>::move(VSMval& movedmat)
	{
		free();
		elems=movedmat.elems;
		colinds=movedmat.colinds;
		numel=movedmat.numel;
		rowsize=movedmat.rowsize;
		colmsize=movedmat.colmsize;
		movedmat.reset();
	}

	//reallocate memory for SprsMat matrix
	template<typename T>
	void SprsMat<T>::reallocate(const uint_32& sparselen,const uint_32& rsize)
	{
		if(sparselen)//if the goal of replication is nonempty
		{
			if (elems)//if matrix is nonempty
			{
				if (numel[rowsize]!=sparselen)
				{
					delete[]elems;
					delete[]colinds;
					elems=new T[sparselen];
					colinds=new uint_32[sparselen];
				}
				if (rowsize!=rsize)
				{
					delete[]numel;
					numel=new uint_32[rsize+1];
				}
			} 
			else//if matrix is empty
			{
				elems=new T[sparselen];
				colinds=new uint_32[sparselen];
				numel=new uint_32[rsize+1];
			}
		}
		else//if the goal of replication is empty
		{
			free();
		}
	}

	template<typename T>
	SprsMat<T>::SprsMat(UarrVal& elemnts,Uarruint& colmind,
		Uarruint& elenumel,const uint_32& rsize,const uint_32& columnsize)
	{
		if (!elemnts)
		{std::cout<<"SprsMat error: empty matrix"<<std::endl;return;}
		if (elemnts.size()!=colmind.size())
		{std::cout<<"SprsMat error: lengths of element and column indices vector must be consistent!"<<std::endl;return;}
		if (columnsize==0||rsize==0)
		{std::cout<<"SprsMat error: wrong matrix size"<<std::endl;return;}
		if (elenumel.size()!=(rsize+1))
		{std::cout<<"SprsMat error: size of(elemntnumel) must be equal to rowsize+1"<<std::endl;return;}
		if((elemnts.size())!=elenumel[elenumel.size()-1])
		{std::cout<<"SprsMat error: number of nonzero entries of matrix should be equal to size of elements"<<std::endl;return;}
		elems=elemnts.release();
		colinds=colmind.release();
		numel=elenumel.release();
		rowsize=rsize;
		colmsize=columnsize;
	}

	template<typename T>
	SprsMat<T>::SprsMat():colinds(NULL),numel(NULL),elems(NULL),rowsize(1),colmsize(1){}

	template<typename T>
	SprsMat<T>::SprsMat(const T* elemnts,const uint_32* colmind,
		const uint_32* elemsnumel,const uint_32& rsize,const uint_32& columnsize):rowsize(rsize),colmsize(columnsize)
	{
		if(elemnts)
		{
			uint_32 i,len=rowsize+1;
			elems=new T[elemsnumel[rowsize]];
			colinds=new uint_32[elemsnumel[rowsize]];
			numel=new uint_32[len];
			std::copy(elemsnumel,elemsnumel+len,numel);
			len=elemsnumel[rowsize];
			for(i=0;i<len;i++){colinds[i]=colmind[i];elems[i]=elemnts[i];}}
		else{colinds=NULL;elems=NULL;numel=NULL;}
	}

	template<typename T>
	void SprsMat<T>::setmatrix(const T* elemnts,const uint_32* colmind,const uint_32* elemsnumel,const uint_32& rsize,const uint_32& columnsize)
	{
		if(elemnts)
		{
			reallocate(elemsnumel[rsize],rsize);
			rowsize=rsize;
			colmsize=columnsize;
			uint_32 i,len=rowsize+1;
			for (i=0;i<len;i++)
			{
				numel[i]=elemsnumel[i];
			}
			len=elemsnumel[rowsize];
			for(i=0;i<len;i++)
			{
				colinds[i]=colmind[i];elems[i]=elemnts[i];
			}
		}
		else
		{
			free();
			rowsize=rsize;
			colmsize=columnsize;
		}
	}

	template<typename T>
	SprsMat<T>::SprsMat(const uint_32& rsize,const uint_32& columnsize)
	{if(!columnsize||!rsize){std::cout<<"error: wrong matrix size"<<std::endl;return;}
	rowsize=rsize;colmsize=columnsize;numel=NULL;elems=NULL;colinds=NULL;}

	template<typename T>
	SprsMat<T>::SprsMat(const SVecval& elemnts,const SVecUint& colmind,const SVecUint& elemsnumel,const uint_32& rsize,const uint_32& columnsize)
	{
		if (elemnts.empty())
		{std::cout<<"SprsMat error: empty matrix"<<std::endl;return;}
		if (elemnts.size()!=colmind.size())
		{std::cout<<"SprsMat error: lengths of element and column indices vector must be consistent!"<<std::endl;return;}
		if (columnsize==0||rsize==0)
		{std::cout<<"SprsMat error: wrong matrix size"<<std::endl;return;}
		if (elemsnumel.size()!=(rsize+1))
		{std::cout<<"SprsMat error: size of(elemntnumel) must be equal to rowsize+1"<<std::endl;return;}
		if((elemnts.size())!=elemsnumel.back())
		{std::cout<<"SprsMat error: number of nonzero entries of matrix should be equal to size of elements"<<std::endl;return;}
		elems=new T[elemnts.size()];
		std::copy(elemnts.begin(),elemnts.end(),elems);
		colinds=new uint_32[colmind.size()];
		std::copy(colmind.begin(),colmind.end(),colinds);
		numel=new uint_32[elemsnumel.size()];
		std::copy(elemsnumel.begin(),elemsnumel.end(),numel);
		rowsize=rsize;
		colmsize=columnsize;
	}

	template<typename T>
	SprsMat<T>::SprsMat(const LVecval& elemnts,const LVecuint& colmind,const LVecuint& elenumel,const uint_32& rsize,const uint_32& colsize){
		if (elemnts.empty())
		{std::cout<<"SprsMat error: empty matrix"<<std::endl;return;}
		if (elemnts.size()!=colmind.size())
		{std::cout<<"SprsMat error: lengths of element and column indices vector must be consistent!"<<std::endl;return;}
		if (columnsize==0||rsize==0)
		{std::cout<<"SprsMat error: wrong matrix size"<<std::endl;return;}
		if (elenumel.size()!=(rsize+1))
		{std::cout<<"SprsMat error: size of(elemntnumel) must be equal to rowsize+1"<<std::endl;return;}
		if((elemnts.size())!=elenumel.back())
		{std::cout<<"SprsMat error: number of nonzero entries of matrix should be equal to size of elements"<<std::endl;return;}
		uint_32 len=elemnts.size(),i;
		elems=new T[len];
		colinds=new uint_32[len];
		for(i=0;i<len;i++){
			elems[i]=elemnts.data[i];
			colinds[i]=colmind.data[i];
		}
		len=elenumel.size();
		numel=new uint_32[len];
		for (i=0;i<len;i++){
			numel[i]=elenumel.data[i];
		}
		rowsize=rsize;
		colmsize=columnsize;
	}


	template<typename T>
	void SprsMat<T>::setmatrix(const SVecval& elemnts,const SVecUint& colmind,\
		const SVecUint& elemsnumel,const uint_32& rsize,const uint_32& columnsize)
	{
		if (elemnts.empty())
		{std::cout<<"SprsMat error: empty matrix"<<std::endl;return;}
		if (elemnts.size()!=colmind.size())
		{std::cout<<"SprsMat error: lengths of element and column indices vector must be consistent!"<<std::endl;return;}
		if (columnsize==0||rsize==0)
		{std::cout<<"SprsMat error: wrong matrix size"<<std::endl;return;}
		if (elemsnumel.size()!=(rsize+1))
		{std::cout<<"SprsMat error: size of(elemntnumel) must be equal to rowsize+1"<<std::endl;return;}
		if((elemnts.size())!=elemsnumel.back())
		{std::cout<<"SprsMat error: number of nonzero entries of matrix should be equal to size of elements"<<std::endl;return;}
		reallocate(elemsnumel[rsize],rsize);
		std::copy(elemnts.begin(),elemnts.end(),elems);
		std::copy(elemsnumel.begin(),elemsnumel.end(),numel);
		std::copy(colmind.begin(),colmind.end(),colinds);
		rowsize=rsize;
		colmsize=columnsize;
	}


	template<typename T>
	void SprsMat<T>::setmatrix(const LVecval& elemnts,const LVecuint& colmind,const LVecuint& elenumel,const uint_32& rsize,const uint_32& colsize){
		if (elemnts.empty())
		{std::cout<<"SprsMat error: empty matrix"<<std::endl;return;}
		if (elemnts.size()!=colmind.size())
		{std::cout<<"SprsMat error: lengths of element and column indices vector must be consistent!"<<std::endl;return;}
		if (columnsize==0||rsize==0)
		{std::cout<<"SprsMat error: wrong matrix size"<<std::endl;return;}
		if (elenumel.size()!=(rsize+1))
		{std::cout<<"SprsMat error: size of(elemntnumel) must be equal to rowsize+1"<<std::endl;return;}
		if((elemnts.size())!=elenumel.back())
		{std::cout<<"SprsMat error: number of nonzero entries of matrix should be equal to size of elements"<<std::endl;return;}
		reallocate(elenumel[rsize],rsize);
		uint_32 len=elemnts.size(),i;
		for(i=0;i<len;i++){
			elems[i]=elemnts.data[i];
			colinds[i]=colmind.data[i];
		}
		len=elenumel.size();
		for (i=0;i<len;i++){
			numel[i]=elenumel.data[i];
		}
		rowsize=rsize;
		colmsize=columnsize;
	}



	template<typename T>
	void SprsMat<T>::setmatrix(UarrVal& elemnts,Uarruint& colmind,
		Uarruint& elenumel,const uint_32& rsize,const uint_32& columnsize)
	{
		if (elemnts)
		{std::cout<<"SprsMat error: empty matrix"<<std::endl;return;}
		if (elemnts.size()!=colmind.size())
		{std::cout<<"SprsMat error: lengths of element and column indices vector must be consistent!"<<std::endl;return;}
		if (columnsize==0||rsize==0)
		{std::cout<<"SprsMat error: wrong matrix size"<<std::endl;return;}
		if (elenumel.size()!=(rsize+1))
		{std::cout<<"SprsMat error: size of(elemntnumel) must be equal to rowsize+1"<<std::endl;return;}
		if((elemnts.size())!=elenumel[elenumel.size()-1])
		{std::cout<<"SprsMat error: number of nonzero entries of matrix should be equal to size of elements"<<std::endl;return;}
		free();
		elems=elemnts.release();
		colinds=colmind.release();
		numel=elenumel.release();
		rowsize=rsize;
		colmsize=columnsize;
	}

	template<typename T>
	void SprsMat<T>::free()
	{
		if(elems){delete[]elems;elems=NULL;}
		if(numel){delete[]numel;numel=NULL;}
		if(colinds){delete[]colinds;colinds=NULL;}
	}

	template<typename T>
	void SprsMat<T>::operator=(const SMval& rmatrix)
	{
		//std::cout<<"hi"<<std::endl;
		//if the right matrix is nonempty, then perform copy
		if (rmatrix.elems)
		{
			uint_32 i,len;
			bool ifclearelems=1,ifclearnumel=1;
			len=rmatrix.numel[rmatrix.rowsize];
			reallocate(len,rmatrix.rowsize);
			rowsize=rmatrix.rowsize;
			colmsize=rmatrix.colmsize;
			for (i=0;i<len;i++)
			{
				elems[i]=rmatrix.elems[i];
				colinds[i]=rmatrix.colinds[i];
			}
			len=rowsize+1;
			for (i=0;i<len;i++)
			{
				numel[i]=rmatrix.numel[i];
			}
		} 
		else//if right matrix is empty, then free the left matrix
		{
			free();
			colmsize=rmatrix.colmsize;
			rowsize=rmatrix.rowsize;
		}
	}

	template<typename T>
	void SprsMat<T>::operator=(VSMval& rmatrix){
		move(rmatrix);
	}

	template<typename T>
	SprsMat<T>::SprsMat(const SMval& matrix):rowsize(matrix.rowsize),colmsize(matrix.colmsize)
	{
		if(matrix.elems){uint_32 i,len;
		len=matrix.numel[rowsize];
		elems=new T[len];
		colinds=new uint_32[len];
		for(i=0;i<len;i++){elems[i]=matrix.elems[i];
		colinds[i]=matrix.colinds[i];}
		len=rowsize+1;
		numel=new uint_32[len];
		for(i=0;i<len;i++){numel[i]=matrix.numel[i];}
		}
		else{elems=NULL;colinds=NULL;numel=NULL;}
	}

	template<typename T>
	bool SprsMat<T>::Is_true()const
	{
		if(elems)
		{//check for numel
			if(colmsize*rowsize<=numel[rowsize]){
				std::cout<<"SprsMat error: number of nonzero entries must be less than column_size*row_size"<<std::endl;
				return 0;
			}
			if(numel[0]!=0){
				std::cout<<"SprsMat error: the first entry of the array 'numel' should be 0"<<std::endl;
				return 0;
			}
			uint_32 i,j=0;
			for (i=1;i<=rowsize;i++){	
				if (numel[i]<j)	{	
					std::cout<<"SprsMat error: please ensure that numel[i+1]>=num[i]"<<std::endl;
					return 0;
				}
				if (colmsize<(numel[i]-j)){
					std::cout<<"SprsMat error: number of nonzero entries in each row should be less than or equal to column size"<<std::endl;
					return 0;
				}
				j=numel[i];
			}
			uint_32 k;
			//check for colinds
			for (i=0;i<rowsize;i++){
				k=colinds[numel[i]];
				if (colmsize<=k){
					std::cout<<"SprsMat error: column index of any entry should be less than colmsize"<<std::endl;return 0;}
				for (j=numel[i]+1;j<numel[i+1];j++){
					if (colmsize<=colinds[j]){
						std::cout<<"SprsMat error: column index of any entry should be less than colmsize"<<std::endl;return 0;}
					if (colinds[j]<=k){
						std::cout<<"SprsMat error: column index in each row should be put in an strictly creasing order"<<std::endl;return 0;}
					k=colinds[j];}}}
		else{
			if(colinds||numel||colinds||!rowsize||!colmsize){
				std::cout<<"SprsMat error: empty matrix mustn't contain any entries and matrix size should be positive"<<std::endl;return 0;
			}
		}
		return 1;
	}

	template<typename T>
	uint_32* SprsMat<T>::gnertdiaginds()const{
		if(elems==NULL){
			return NULL;
		}
		
		uint_32 diaglen=rowsize>colmsize?colmsize:rowsize;
		uint_32* diaginds=new uint_32[diaglen];
		uint_32 i,lowind,upind,mind;
		for(i=0;i<diaglen;i++){
			if (numel[i]==numel[i+1]){
				diaginds[i]=numel[rowsize];
			}
			else{	
				lowind=numel[i];
				upind=numel[i+1]-1;
				mind=numel[rowsize]+2;
				if(colinds[lowind]<i&&colinds[upind]>i){
					while(lowind!=upind&&((upind-lowind)>1))
					{
						mind=(upind+lowind)/2;
						if(colinds[mind]==i){
							diaginds[i]=mind;
							break;
						}
						else if(colinds[mind]>i){
							upind=mind;
						}
						else{
							lowind=mind;
						}
					}
					if(numel[rowsize]<mind){
						diaginds[i]=numel[rowsize];
					}
					else if(colinds[mind]!=i){
						diaginds[i]=numel[rowsize];
					}
				}	
				else if(colinds[lowind]==i){
					diaginds[i]=lowind;
				}
				else if(colinds[upind]==i){
					diaginds[i]=upind;
				}
				else{
					diaginds[i]=numel[rowsize];
				}
			}
		}
		return diaginds;
	}



	template<typename T>
	bool SprsMat<T>::Is_empty()const{return elems? 0:1;}

	template<typename T>
	double SprsMat<T>::density()const{
		if(elems){return (double)numel[rowsize]/(double)(rowsize*colmsize);}
		else{return 0;}
	}


	template<typename T>
	void SprsMat<T>::show()const
	{
		if (elems==NULL)
		{
			std::cout<<"empty matrix!"<<std::endl;
			return;
		}
		std::cout<<"elements:"<<std::endl;
		for (uint_32 i=0;i<numel[rowsize];i++)
		{
			std::cout<<elems[i]<<", ";
		}
		std::cout<<std::endl;
		std::cout<<"column indices: "<<std::endl;
		for (uint_32 i=0;i<numel[rowsize];i++)
		{
			std::cout<<colinds[i]<<", ";
		}
		std::cout<<std::endl;
		std::cout<<"numel: "<<std::endl;
		for (uint_32 i=0;i<rowsize+1;i++)
		{
			std::cout<<numel[i]<<", ";
		}
		std::cout<<std::endl;
		std::cout<<"rowsize:"<<rowsize<<",  "<<"columnsize:"<<colmsize<<std::endl;
		std::cout<<std::endl;
	}

	template<typename T>
	void SprsMat<T>::compress()
	{
		if (elems)
		{
			uint_32 count=0,i,j;
			for (i=0;i<rowsize;i++)
			{
				for (j=numel[i];j<numel[i+1];j++)
				{
					if(elems[j]!=0)
					{
						count++;
					}
				}
			}
			if (!count)//if the matrix became empty after compressed
			{
				free();
				return;
			}
			if(count==numel[rowsize])
			{std::cout<<"SprsMat warning: the sparse matrix is compact, there is no need to compress it"<<std::endl;return;}
			uint_32 oldnumeli,oldlen;
			oldlen=numel[rowsize];
			T* newelems=new T[count];
			uint_32* newcolinds=new uint_32[count];
			uint_32 k=0;
			for (i=0;i<rowsize;i++)
			{
				oldnumeli=numel[i];numel[i]=k;
				for (j=oldnumeli;j<numel[i+1];j++)
				{
					if(elems[j]!=0)
					{
						newelems[k]=elems[j];
						newcolinds[k]=colinds[j];
						k++;
					}
				}
				if (k==count)
				{
					for (j=i+1;j<=rowsize;j++)
					{
						numel[j]=k;
					}
				}
			}
			delete[]elems;
			delete[]colinds;
			elems=newelems;
			colinds=newcolinds;
		}
	}

	template<typename T>
	void SprsMat<T>::SprMatFout(const std::string& filename,const uint_32& setprecisn,const bool ifcover)const{
		std::ofstream fout;
		if(ifcover){
		fout.open(filename);
		}
		else{
					fout.open(filename,std::ios::out|std::ios::app);
		}
		if(!fout.is_open()){
			std::cout<<"Linspace::SprsMat error: can not open the file '"<<filename<<"'"<<std::endl;
			fout.clear();
			return;
		}
		fout<<std::endl<<"rowsize: "<<rowsize<<","<<"column size: "<<colmsize<<","<<"tight size: ";
		if(elems){
			fout<<numel[rowsize]<<std::endl;
			uint_32 width1=5,width2=5,digit=10;
			while(rowsize/digit){
				width1++;
				digit*=10;
			}
			digit=10;
			while(colmsize/digit){
				width2++;
				digit*=10;
			}
			fout.precision(setprecisn);
			fout.setf(std::ios_base::fixed);
			uint_32 i,j;
			for(i=0;i<rowsize;i++){
				for(j=numel[i];j<numel[i+1];j++){
					fout.width(width1);
					fout<<std::left<<i;
					fout.width(width2);
					fout<<std::left<<colinds[j];
					fout<<std::left<<elems[j]<<std::endl;
				}
			}
		}
		else{
			fout<<0<<std::endl;
		}
		fout<<std::endl;
		fout.close();
		fout.clear();
	}

	template<typename T>
	void SprsMat<T>::SprMatFin(const std::string& filename,const std::string& format){
		if(format.compare("dense")&&format.compare("sparse")){
			std::cout<<"Linspace::SprsMat error: undefined format '"<<format<<"'"<<std::endl;
		}
		std::ifstream fin;
		fin.open(filename);
		if(!fin.is_open()){std::cout<<"Linspace::SprsMat error: can not open the file '"<<filename<<"'"<<std::endl;
		fin.close();fin.clear();return;}
		if(fin.peek()==std::ifstream::traits_type::eof()){
			std::cout<<"Linspace::SprsMat error: empty file!"<<std::endl;
			fin.close();
			fin.clear();
			return;
		}
	
		//to find the rowsize and column size in the first line of the file
		char curs;

		//to find the rowsize of matrix
		fin>>curs;
		if(fin.eof()){std::cout<<"Linspace::SprsMat error: no data about matrix in the file '"<<filename<<"'"<<std::endl;
		fin.close();fin.clear();return;}
		while(curs<49||57<curs){
			fin>>curs;
			if(fin.eof()){std::cout<<"Linspace::SprsMat error: no data about matrix in the file '"<<filename<<"'"<<std::endl;
			fin.close();fin.clear();return;}
		}
		fin.seekg(-1,std::ios_base::cur);
		uint_32 nrowsize;
		fin>>nrowsize;
		uint_32 oldlen=0;
		if(elems){
			oldlen=numel[rowsize];
			if(rowsize!=nrowsize){
				delete[]numel;
				numel=NULL;
			}
		}
		//to find the column size of matrix
		fin>>curs;
		if(fin.eof()){std::cout<<"Linspace::SprsMat error: data insufficient in the file '"<<filename<<"'"<<std::endl;
		fin.close();fin.clear();return;}
		while(curs<49||57<curs){
			fin>>curs;
			if(fin.eof()){std::cout<<"Linspace::SprsMat error: data insufficient in the file '"<<filename<<"'"<<std::endl;
			fin.close();fin.clear();return;}
		}
		fin.seekg(-1,std::ios_base::cur);
		fin>>colmsize;

		//read matrix entries from the file
		if(format.compare("sparse")==0){			
			//still, to find the length of the matrix in the file
			fin>>curs;
			if(fin.eof()){std::cout<<"Linspace::SprsMat error:  data insufficient in the file '"<<filename<<"'"<<std::endl;fin.close();fin.clear();return;}
			while(curs<48||57<curs){
				fin>>curs;
				if(fin.eof()){std::cout<<"Linspace::SprsMat error: data insufficient in the file '"<<filename<<"'"<<std::endl;
				fin.close();fin.clear();return;}
			}
			uint_32 tightlen;
			fin.seekg(-1,std::ios_base::cur);
			fin>>tightlen;
			if(colmsize*nrowsize<tightlen){
				std::cout<<"Linspace::SprsMat error: wrong length of sparse matrix in the file '"<<filename<<"'"<<std::endl;
				free();fin.close();fin.clear();return;
			}
			//if the tightlen is zero, then the result is empty matrix, and nothing to go on
			if(tightlen==0){
				free();
				rowsize=nrowsize;
				fin.close();
				fin.clear();
				return;
			}

			if(elems==NULL){
				elems=new T[tightlen];
				colinds=new uint_32[tightlen];
				rowsize=nrowsize;
				numel=new uint_32[rowsize+1];
			}
			else{
				if(rowsize!=nrowsize){
					rowsize=nrowsize;
					numel=new uint_32[rowsize+1];
				}
				//if newlength!=oldlen then reallocate memory for matrix
				if(tightlen!=oldlen){
					delete[]elems;
					delete[]colinds;
					elems=new T[tightlen];
					colinds=new uint_32[tightlen];
				}
			}	
			
			uint_32 count=0,temp;
			for(;count<rowsize;count++){
				numel[count]=0;
			}
			numel[count]=0;
			count=0;
			//read data from file to matrix
			while(count<tightlen){		
				//to find the row index
				fin>>curs;
				if(fin.eof()){std::cout<<"Linspace::SprsMat error:  data  insufficient in the file '"<<filename<<"'"<<std::endl;
				free();fin.close();fin.clear();return;
				}

				while(curs<48||57<curs){
					fin>>curs;
					if(fin.eof()){std::cout<<"Linspace::SprsMat error: data insufficient in the file '"<<filename<<"'"<<std::endl;
					fin.close();fin.clear();return;}
				}
		
				fin.seekg(-1,std::ios_base::cur);
				fin>>temp;
				if(rowsize<=temp){
					std::cout<<"Linspace::SprsMat error: wrong row index in the file '"<<filename<<"'"<<std::endl;free();fin.close();fin.clear();return;
				}
				numel[temp+1]++;

				//to find the column index
				fin>>curs;
				if(fin.eof()){std::cout<<"Linspace::SprsMat error:  data  insufficient in the file '"<<filename<<"'"<<std::endl;
				free();fin.close();fin.clear();return;
				}
				while(curs<48||57<curs){
					fin>>curs;
					if(fin.eof()){std::cout<<"Linspace::SprsMat error: data insufficient in the file '"<<filename<<"'"<<std::endl;
					fin.close();fin.clear();return;}
				}
				fin.seekg(-1,std::ios_base::cur);
				fin>>colinds[count];
				if(colmsize<=colinds[count]){
					std::cout<<"Linspace::SprsMat error:  wrong column index in the file '"<<filename<<"'"<<std::endl;free();fin.close();fin.clear();return;
				}

				//find the elment of matrix
				fin>>curs;
				if(fin.eof()){std::cout<<"Linspace::SprsMat error:  data  insufficient in the file '"<<filename<<"'"<<std::endl;free();fin.close();fin.clear();return;}
				while(curs!='-'&&(curs<48||57<curs)){
					fin>>curs;
					if(fin.eof()){std::cout<<"Linspace::SprsMat error:  data  insufficient in the file '"<<filename<<"'"<<std::endl;free();fin.close();fin.clear();return;}
				}
				fin.seekg(-1,std::ios_base::cur);
				fin>>elems[count];
				if(fin.fail()){
					if(fin.eof()){std::cout<<"Linspace::SprsMat error:  invalid character in the file '"<<filename<<"'"<<std::endl;free();fin.close();fin.clear();return;}
				}
				count++;
			}	

			for(count=0;count<rowsize;count++){
				numel[count+1]+=numel[count];
			}
		}
		else{
			free();
			rowsize=nrowsize;
			SVecUint* newcolinds=new SVecUint[rowsize];
			SVecval* newelems=new SVecval[rowsize];
			numel=new uint_32[rowsize+1];
			uint_32 count=0,currow=0;
			T tempval;

			//read data from file to matrix
			while(currow<rowsize){
				newcolinds[currow].reserve(colmsize);
				newelems[currow].reserve(colmsize);
				fin>>curs;
				if(fin.eof()){std::cout<<"Linspace::SprsMat error:  data  insufficient in the file '"<<filename<<"'"<<std::endl;free();fin.close();fin.clear();return;}
				while(curs!='-'&&(curs<48||57<curs)){
					fin>>curs;
					if(fin.eof()){std::cout<<"Linspace::SprsMat error:  data  insufficient in the file '"<<filename<<"'"<<std::endl;free();fin.close();fin.clear();return;}
				}
				fin.seekg(-1,std::ios_base::cur);
				fin>>tempval;
				if(fin.fail()){
					if(fin.eof()){std::cout<<"Linspace::SprsMat error:  invalid character in the file '"<<filename<<"'"<<std::endl;free();fin.close();fin.clear();return;}
				}
				if(tempval!=0){
					newelems[currow].push_back(tempval);
					newcolinds[currow].push_back(count%colmsize);
				}
				count++;
				if(count%colmsize==0){
					newelems[currow].reserve(newelems[currow].size());
					newcolinds[currow].reserve(newcolinds[currow].size());
					currow++;
				}
			}
			numel[0]=0;
			for(count=0;count<rowsize;count++){
				numel[count+1]=numel[count]+newcolinds[count].size();
			}
			if(numel[rowsize]==0){
				std::cout<<"Linspace::SprsMat warning: entirely sparse matrix in the file '"<<filename<<"'"<<std::endl;
				delete[]newcolinds;
				newcolinds=NULL;
				delete[]newelems;
				newelems=NULL;
				free();
				return;
			}
			elems=new T[numel[rowsize]];
			colinds=new uint_32[numel[rowsize]];
			for(count=0;count<rowsize;count++){
				for(currow=numel[count];currow<numel[count+1];currow++){
					elems[currow]=newelems[count][currow-numel[count]];
					colinds[currow]=newcolinds[count][currow-numel[count]];
				}
				newcolinds[count].clear();
				newelems[count].clear();
			}
			delete[]newcolinds;
			delete[]newelems;
			newcolinds=NULL;
			newelems=NULL;
		}
		fin.close();
		fin.clear();
	}


	template<typename T>
	double SprsMat<T>::norm(const std::string& nname)const{
		if(nname.compare("F")==0){
			double rslt=0;
			if(elems){
				uint_32 len=numel[rowsize];
				for(uint_32 i(0);i<len;i++){rslt+=elems[i]*elems[i];}
				return sqrt(rslt);
			}
			return rslt;
		}
		if(nname.compare("infty")==0){
			double rslt=0;
			if(elems){
				uint_32 i;
				for(i=numel[0];i<numel[1];i++){
					rslt+=elems[i]<0?-elems[i]:elems[i];
				}
				uint_32 j;
				double curmax;
				for(i=1;i<rowsize;i++){
					curmax=0;
				     for(j=numel[i];j<numel[i+1];j++){
						 curmax+=elems[j]<0?-elems[j]:elems[j];
					 }
					 if(rslt<curmax){rslt=curmax;}
				}
			}
			return rslt;
		}
		if(nname.compare("1")==0){
			double rslt=0;
			if(elems){
				vector<double> colnorms(colmsize,0);
				uint_32 i,j;
				for(i=0;i<rowsize;i++){
					for(j=numel[i];j<numel[i+1];j++){
						colnorms.data[colinds[j]]+=elems[j]<0?-elems[j]:elems[j];
					}
				}
				rslt=colnorms.data[0];
				for(i=1;i<colmsize;i++){
					if(rslt<colnorms.data[i]){rslt=colnorms.data[i];}
				}
				colnorms.clear();
			}
			return rslt;
		}
		std::cout<<"Linspace::SprsMat error: Undefined matrix norm!!"<<std::endl;
		return -1;
	}

	template<typename T>
	T SprsMat<T>::getvalue(const uint_32& rowindex, const uint_32& colindex)const
	{
		if (rowsize<=rowindex||colmsize<=colindex){std::cout<<"SprsMat error: wrong index!"<<std::endl;return 0;}
		if(elems){
			if(numel[rowindex]!=numel[rowindex+1]){
				uint_32 lowind=numel[rowindex],upind=numel[rowindex+1]-1,mind;
				if(colinds[lowind]<colindex&&colinds[upind]>colindex){		
					while((upind-lowind)>1)
					{	
						mind=(upind+lowind)/2;
						if(colinds[mind]==colindex){
							return elems[mind];
						}
						else if(colinds[mind]>colindex){
							upind=mind;
						}
						else{
							lowind=mind;
						}
					}
					return 0;
				}
				if(colinds[lowind]==colindex){
					return elems[lowind];
				}
				if(colinds[upind]==colindex){
					return elems[upind];
				}
				return 0;
			}
			return 0;
		}
		return 0;
	}

	template<typename T>
	void SprsMat<T>::operator*=(const SMval& rmatrix)
	{
		//if the size of two matrices don't match, return an error empty matrix as result
		if (colmsize!=rmatrix.rowsize)
		{std::cout<<"SprsMat error: columnsize of left matrix should be equal to rowsize of rightmatrix"<<std::endl;
		free();
		rowsize=0;
		colmsize=0;
		return;}
		//if one of the left and right matrix is empty, return an empty matrix
		if(!elems||!rmatrix.elems)
		{
			free();
			colmsize=rmatrix.colmsize;
			return;
		}
		T** newelems=new T*[rowsize];
		uint_32** newcolinds=new uint_32*[rowsize];
		uint_32* rsltnumel=new uint_32[rowsize+1];
		rsltnumel[0]=0;
		SprsArr<T> recarr,sendarr;
		uint_32 i,j,m,reclen=0,sedlen=0;
		for (i=0;i<rowsize;i++)
		{
			//if the ith row of leftmatrix is empty
			if(numel[i+1]==numel[i])
			{
				rsltnumel[i+1]=rsltnumel[i];
				newelems[i]=NULL;
				newcolinds[i]=NULL;
			}
			else//if  ith row of left matrix is nonempty, then compute the ith row of result matrix
			{
				//to find the first jth nonempty row of right matrix
				//initialize value receiver and indices receiver
				recarr.free();
				for (j=numel[i];j<numel[i+1];j++)
				{
					reclen=rmatrix.numel[colinds[j]+1]-rmatrix.numel[colinds[j]];
					//if colinds[j]th row of right matrix is nonempty
					if (0<reclen)
					{
						recarr.setarr(elems[j],rmatrix.elems+rmatrix.numel[colinds[j]],rmatrix.colinds+rmatrix.numel[colinds[j]],reclen);
						break;
					}
				}
				//to find the remaining nonempty row of right matrix correspongding to 
				//column indices in ith row of left matrix
				//initialize value sender and indices sender
				for (m=j+1;m<numel[i+1];m++)
				{
					sedlen=rmatrix.numel[colinds[m]+1]-rmatrix.numel[colinds[m]];
					sendarr.setarr(elems[m],rmatrix.elems+rmatrix.numel[colinds[m]],rmatrix.colinds+rmatrix.numel[colinds[m]],sedlen);
					//do the addition of sparse vector
					recarr+=sendarr;
				}
				//obtain the ith row of resultmatrix
				//save value (column indices) of ith row of resultmatrix in valreceiver(indreceiver) temporarily
				newelems[i]=recarr.elems;
				newcolinds[i]=recarr.inds;
				rsltnumel[i+1]=rsltnumel[i]+recarr.size;
				recarr.reset();
				//reclen is the number of nonzero entries in  ith row of resultmatrix 		
			}
		}
		//if the resultmatrix is empty after multiplication
		if(rsltnumel[rowsize]==0)
		{
			//release variables
			delete[]newcolinds;
			delete[]newelems;
			delete[]rsltnumel;
			free();
			colmsize=rmatrix.colmsize;
			return;
		}
		else//if the resultmatrix is nonempty, then copy the values and indices from newelems and newcolinds to resultmatrix
		{
			//apply memory for elems and colinds of resulmatrix
			colmsize=rmatrix.colmsize;
			if (numel[rowsize]!=rsltnumel[rowsize])
			{
				delete[]elems;
				elems=new T[rsltnumel[rowsize]];
				delete[]colinds;
				colinds=new uint_32[rsltnumel[rowsize]];
			}
			delete[]numel;
			numel=rsltnumel;
			rsltnumel=NULL;
			for (i=0;i<rowsize;i++)
			{
				//m is length of ith row of resulmatrix
				m=numel[i+1]-numel[i];
				//evaluate value and column indices of ith row of resultmatrix
				for(j=0;j<m;j++)
				{
					elems[numel[i]+j]=newelems[i][j];
					colinds[numel[i]+j]=newcolinds[i][j];
				}
				//after converting the data delete ith row in temporary array
				if(newelems[i])
				{
					delete[]newelems[i];
					newelems[i]=NULL;
					delete[]newcolinds[i];
					newcolinds[i]=NULL;
				}
			}
			delete[]newcolinds;
			newcolinds=NULL;
			delete[]newelems;
			newelems=NULL;
		}
	}

	template<typename T>
	void SprsMat<T>::operator*=(VSMval& rmat){
		SMval newrmat;
		newrmat.move(rmat);
		(*this)*=newrmat;
		newrmat.free();
	}

	//this is a function to realize sparse matrices product
	template<typename T>
	VirtualSprMat<T> SprsMat<T>::operator*(const SMval& rmatrix)const
	{
		VSMval resultmatrix;
		//if the size of two matrices don't match, return an error empty matrix as result
		if (colmsize!=rmatrix.rowsize)
		{std::cout<<"SprsMat error: columnsize of left matrix should be equal to rowsize of rightmatrix"<<std::endl;
		resultmatrix.rowsize=0;
		resultmatrix.colmsize=0;
		return resultmatrix;}
		//if one of the left and right matrix is empty, return an empty matrix
		if(!elems||!rmatrix.elems)
		{
			resultmatrix.rowsize=rowsize;
			resultmatrix.colmsize=rmatrix.colmsize;
			return resultmatrix;
		}
		T** newelems=new T*[rowsize];
		uint_32** newcolinds=new uint_32*[rowsize];
		SprsArr<T> recarr,sendarr;

		resultmatrix.numel=new uint_32[rowsize+1];
		resultmatrix.numel[0]=0;resultmatrix.rowsize=rowsize;
		resultmatrix.colmsize=rmatrix.colmsize;
		uint_32 i,j,m,reclen=0,sedlen=0;
		for (i=0;i<rowsize;i++)
		{
			//if the ith row of leftmatrix is empty
			if(numel[i+1]==numel[i])
			{
				resultmatrix.numel[i+1]=resultmatrix.numel[i];
				newelems[i]=NULL;
				newcolinds[i]=NULL;
			}
			else//if  ith row of left matrix is nonempty, then compute the ith row of result matrix
			{
				//to find the first jth nonempty row of right matrix
				//initialize value receiver and indices receiver
				recarr.free();
				for (j=numel[i];j<numel[i+1];j++)
				{
					reclen=rmatrix.numel[colinds[j]+1]-rmatrix.numel[colinds[j]];
					//if colinds[j]th row of right matrix is nonempty
					if (0<reclen)
					{
						recarr.setarr(elems[j],rmatrix.elems+rmatrix.numel[colinds[j]],rmatrix.colinds+rmatrix.numel[colinds[j]],reclen);
						break;
					}
				}
				//to find the remaining nonempty row of right matrix correspongding to 
				//column indices in ith row of left matrix
				//initialize value sender and indices sender
				for (m=j+1;m<numel[i+1];m++)
				{
					sedlen=rmatrix.numel[colinds[m]+1]-rmatrix.numel[colinds[m]];
					sendarr.setarr(elems[m],rmatrix.elems+rmatrix.numel[colinds[m]],rmatrix.colinds+rmatrix.numel[colinds[m]],sedlen);
					//do the addition of sparse vector
					recarr+=sendarr;
				}
				//obtain the ith row of resultmatrix
				//save value (column indices) of ith row of resultmatrix in valreceiver(indreceiver) temporarily
				newelems[i]=recarr.elems;
				newcolinds[i]=recarr.inds;
				resultmatrix.numel[i+1]=resultmatrix.numel[i]+recarr.size;
				recarr.reset();
				//reclen is the number of nonzero entries in  ith row of resultmatrix 		
			}
		}
		//if the resultmatrix is empty after multiplication
		if(resultmatrix.numel[rowsize]==0)
		{
			//release variables
			delete[]newcolinds;
			newcolinds=NULL;
			delete[]newelems;
			newelems=NULL;
			delete[]resultmatrix.numel;
			resultmatrix.numel=NULL;
			return(resultmatrix);
		}
		else//if the resultmatrix is nonempty, then copy the values and indices from newelems and newcolinds to resultmatrix
		{
			//apply memory for elems and colinds of resulmatrix
			resultmatrix.elems=new T[resultmatrix.numel[rowsize]];
			resultmatrix.colinds=new uint_32[resultmatrix.numel[rowsize]];
			for (i=0;i<rowsize;i++)
			{
				//m is length of ith row of resulmatrix
				m=resultmatrix.numel[i+1]-resultmatrix.numel[i];
				//evaluate value and column indices of ith row of resultmatrix
				for(j=0;j<m;j++)
				{
					resultmatrix.elems[resultmatrix.numel[i]+j]=newelems[i][j];
					resultmatrix.colinds[resultmatrix.numel[i]+j]=newcolinds[i][j];
				}
				//after converting the data delete ith row in temporary array
				if(newelems[i])
				{
					delete[]newelems[i];
					newelems[i]=NULL;
					delete[]newcolinds[i];
					newcolinds[i]=NULL;
				}
			}
			delete[]newcolinds;
			delete[]newelems;
			newcolinds=NULL;
			newelems=NULL;
			return resultmatrix;
		}
	}

	template<typename T>
	VirtualSprMat<T> SprsMat<T>::operator*(VSMval& rightmatrix)const{
		SprsMat<T> newrmat;
		newrmat.move(rightmatrix);
		VSMval rsltmat;
		rsltmat=*this*newrmat;
		newrmat.free();
		return rsltmat;
	}

	template<typename T>
	virtvec<T> SprsMat<T>::operator*(const LVecval& rvec)const{
		//check parameters
		if(colmsize!=rvec.length){
			std::cout<<"Linspace::SprsMat error: length of vector must be equal to column size of matrix in matrix-vector multiplication"<<std::endl;
			VVecval rsltvec;
			return rsltvec;
		}
		VVecval rsltvec(rowsize,0);
		if(elems){
			uint_32 i,j;
			for (i=0;i<rowsize;i++){
				for(j=numel[i];j<numel[i+1];j++){
					rsltvec.data[i]+=elems[j]*rvec.data[colinds[j]];
				}
			}
		}
		return rsltvec;
	}

	template<typename T>
	virtvec<T> SprsMat<T>::operator*(VVecval& rvec)const{
		//check parameters
		if(colmsize!=rvec.length){
			std::cout<<"Linspace::SprsMat error: length of vector must be equal to column size of matrix in matrix-vector multiplication"<<std::endl;
			VVecval rsltvec;
			return rsltvec;
		}
		VVecval rsltvec(rowsize,0);
		if(elems){
			uint_32 i,j;
			for (i=0;i<rowsize;i++){
				for(j=numel[i];j<numel[i+1];j++){
					rsltvec.data[i]+=elems[j]*rvec.data[colinds[j]];
				}
			}
		}
		rvec.free();
		return rsltvec;
	}


	//this is a function to realize sparse matrix subtraction
	template<typename T>
	VirtualSprMat<T> SprsMat<T>::operator-(const SMval& rmatrix)const
	{
		//before perform the addition, check whether sizes match
		if(rowsize!=rmatrix.rowsize||colmsize!=rmatrix.colmsize)
		{
			//if the sizes don't match, return error matrix
			std::cout<<"SprsMatr error: sizes of two matrices don't match"<<std::endl;
			VSMval rsltmat(0,0);
			return(rsltmat);
		}

		//if one of the two matices is empty ,then return the other one
		if(elems==NULL)
		{
			VSMval rsltmat(-1,rmatrix);
			return(rsltmat);
		}
		if (rmatrix.elems==NULL)
		{
			VSMval rsltmat;
			rsltmat.copy(*this);
			return(rsltmat);
		}

		//if both of them are nonempty, then perform the addtion
		uint_32 i,j,leftsize,rightsize,insecub;
		T* currentvalptr,*othervalptr,*mvalptr;
		uint_32* currentindptr,*otherindptr,*mindptr;
		uint_32 currentupd,currentcover,othercover,otherubd,media;
		VSMval rsltmat(rowsize,colmsize);
		rsltmat.numel=new uint_32[rowsize+1];
		rsltmat.numel[0]=0;
		//count number of nonzero entries of each row of result matrix
		//and save the numbers in 'numel' of result matrix temporarily
		for(i=0;i<rowsize;i++)
		{
			rightsize=rmatrix.numel[i+1]-rmatrix.numel[i];
			leftsize=numel[i+1]-numel[i];
			//if ith row of  any matrix of the two is empty, 
			//then the new length of new row is that of the other one
			if (rightsize==0)
			{
				rsltmat.numel[i+1]=leftsize;
			}
			else if(leftsize==0)
			{
				rsltmat.numel[i+1]=rightsize;
			}
			else
			{
				currentcover=0;othercover=1;
				rsltmat.numel[i+1]=0;
				//initializing variables for accounting intersection indices between two index array
				if (rmatrix.colinds[rmatrix.numel[i]]<colinds[numel[i]])
				{
					currentindptr=colinds+numel[i];
					currentvalptr=elems+numel[i];
					otherindptr=rmatrix.colinds+rmatrix.numel[i];
					othervalptr=rmatrix.elems+rmatrix.numel[i];
					currentupd=leftsize;
					otherubd=rightsize;
				}
				else if(colinds[numel[i]]==rmatrix.colinds[rmatrix.numel[i]])
				{
					othercover=0;
					currentindptr=rmatrix.colinds+rmatrix.numel[i];
					otherindptr=colinds+numel[i];
					currentvalptr=rmatrix.elems+rmatrix.numel[i];
					othervalptr=elems+numel[i];
					currentupd=rightsize;
					otherubd=leftsize;
				}
				else
				{
					currentindptr=rmatrix.colinds+rmatrix.numel[i];
					otherindptr=colinds+numel[i];
					currentvalptr=rmatrix.elems+rmatrix.numel[i];
					othervalptr=elems+numel[i];
					currentupd=rightsize;
					otherubd=leftsize;
				}
				if (currentindptr[0]>otherindptr[otherubd-1])
				{
					//if there is no intersection between two  indices array then the length of new vector is reclen+sedlen
					rsltmat.numel[i+1]=leftsize+rightsize;
				} 
				else
				{
					insecub=colinds[numel[i+1]-1]<rmatrix.colinds[rmatrix.numel[i+1]-1]?colinds[numel[i+1]-1]:rmatrix.colinds[rmatrix.numel[i+1]-1];
					if (othercover!=0)
					{
						//to find othercover
						othercover=0;
						for (j=1;j<otherubd;j++)
						{
							if (currentindptr[0]<=otherindptr[j])
							{
								othercover=j-1;
								break;
							}
						}
					}
					//compute the length of new vector
					while(currentindptr[currentcover]<=insecub)
					{
						if (currentindptr[currentcover]<otherindptr[othercover])
						{
							currentcover++;
						}
						else if(currentindptr[currentcover]==otherindptr[othercover])
						{
							if (currentvalptr[currentcover]==(othervalptr[othercover]))
							{
								rsltmat.numel[i+1]++;
							}
							rsltmat.numel[i+1]++;
							currentcover++;
							othercover++;
						}
						else{
							//if currentindex> other stationary index then swap them
							mindptr=currentindptr;currentindptr=otherindptr;otherindptr=mindptr;
							mvalptr=currentvalptr;currentvalptr=othervalptr;othervalptr=mvalptr;
							media=currentcover;currentcover=othercover;othercover=media;
							media=currentupd;currentupd=otherubd;otherubd=media;
							currentcover++;
						}
						if (currentupd<=currentcover)
						{
							break;
						}
					}
					rsltmat.numel[i+1]=leftsize+rightsize-rsltmat.numel[i+1];
				}		
			}
		}
		//construct 'numel array' of result matrix
		for (i=0;i<rowsize;i++)
		{
			rsltmat.numel[i+1]+=rsltmat.numel[i];
		}

		//if the result matrix is empty then return empty matrix
		j=rsltmat.numel[rowsize];
		if (j==0)
		{
			delete[]rsltmat.numel;
			rsltmat.numel=NULL;
			return rsltmat;
		}

		//if the result matrix is nonempty, then allocate memories for result matrix
		rsltmat.elems=new T[j];
		rsltmat.colinds=new uint_32[j];
		uint_32 newcount;
		bool flag;
		for (i=0;i<rowsize;i++)
		{
			j=rsltmat.numel[i];
			insecub=rsltmat.numel[i+1]-j;
			if (insecub)
			{
				rightsize=rmatrix.numel[i+1]-rmatrix.numel[i];
				leftsize=numel[i+1]-numel[i];
				newcount=0;
				if (rightsize==0)
				{
					for (;newcount<insecub;newcount++)
					{
						rsltmat.colinds[j+newcount]=colinds[numel[i]+newcount];
						rsltmat.elems[j+newcount]=elems[numel[i]+newcount];
					}
				}
				else if(leftsize==0)
				{
					for (;newcount<insecub;newcount++)
					{
						rsltmat.colinds[j+newcount]=rmatrix.colinds[rmatrix.numel[i]+newcount];
						rsltmat.elems[j+newcount]=-rmatrix.elems[rmatrix.numel[i]+newcount];
					}
				}
				else
				{
					flag=0;
					currentcover=1;othercover=0;
					if (rmatrix.colinds[rmatrix.numel[i]]<colinds[numel[i]])
					{
						currentindptr=rmatrix.colinds+rmatrix.numel[i];
						otherindptr=colinds+numel[i];
						currentvalptr=rmatrix.elems+rmatrix.numel[i];
						othervalptr=elems+numel[i];
						currentupd=rightsize;
						otherubd=leftsize;
						rsltmat.colinds[j]=currentindptr[0];
						rsltmat.elems[j]=-currentvalptr[0];
						newcount++;
					}
					else if(rmatrix.colinds[rmatrix.numel[i]]==colinds[numel[i]])
					{
						currentindptr=rmatrix.colinds+rmatrix.numel[i];
						otherindptr=colinds+numel[i];
						currentvalptr=rmatrix.elems+rmatrix.numel[i];
						othervalptr=elems+numel[i];
						currentupd=rightsize;
						otherubd=leftsize;
						if (currentvalptr[0]!=(othervalptr[0]))
						{
							rsltmat.colinds[j]=currentindptr[0];
							rsltmat.elems[j]=othervalptr[0]-currentvalptr[0];
							newcount++;
						}		
						othercover++;		
					}
					else
					{
						flag=1;
						currentindptr=colinds+numel[i];
						otherindptr=rmatrix.colinds+rmatrix.numel[i];
						currentvalptr=elems+numel[i];
						othervalptr=rmatrix.elems+rmatrix.numel[i];
						currentupd=leftsize;
						otherubd=rightsize;
						rsltmat.colinds[j]=currentindptr[0];
						rsltmat.elems[j]=currentvalptr[0];
						newcount++;
					}
					while((currentcover<currentupd)&&newcount!=insecub)
					{
						//if other array achieves the end, then swap two arrays and break the 'while' circle
						if (otherubd<=othercover)
						{
							otherindptr=currentindptr;
							othervalptr=currentvalptr;
							otherubd=currentupd;
							othercover=currentcover;
							break;
						}
						if (currentindptr[currentcover]<otherindptr[othercover])
						{
							rsltmat.colinds[j+newcount]=currentindptr[currentcover];
							switch(flag)
							{
							case true:
								rsltmat.elems[j+newcount]=currentvalptr[currentcover];
								break;
							case false:
								rsltmat.elems[j+newcount]=-currentvalptr[currentcover];
								break;
							}
							currentcover++;
							newcount++;
						}
						else if(currentindptr[currentcover]==otherindptr[othercover])
						{
							//if the indices coincide then check whether the result of plus is zero
							if (currentvalptr[currentcover]!=(othervalptr[othercover]))
							{
								rsltmat.colinds[j+newcount]=currentindptr[currentcover];
								switch(flag)
								{
								case true:
									rsltmat.elems[j+newcount]=currentvalptr[currentcover]-othervalptr[othercover];
									break;
								case false:
									rsltmat.elems[j+newcount]=othervalptr[othercover]-currentvalptr[currentcover];
									break;
								}		
								newcount++;
							}		
							currentcover++;
							othercover++;	
						}
						else{
							//if currentindex> other stationary index then commute them
							flag=!flag;
							mindptr=currentindptr;currentindptr=otherindptr;otherindptr=mindptr;
							mvalptr=currentvalptr;currentvalptr=othervalptr;othervalptr=mvalptr;
							media=currentcover;currentcover=othercover;othercover=media;
							media=currentupd;currentupd=otherubd;otherubd=media;
							rsltmat.colinds[j+newcount]=currentindptr[currentcover];
							switch(flag)
							{
							case true:
								rsltmat.elems[j+newcount]=currentvalptr[currentcover];
								break;
							case false:
								rsltmat.elems[j+newcount]=-currentvalptr[currentcover];
								break;
							}

							currentcover++;
							newcount++;
						}
					}
					switch(flag)
					{
					case true:
						while (othercover<otherubd)
						{
							if (insecub<=newcount)
							{
								break;
							}
							rsltmat.colinds[j+newcount]=otherindptr[othercover];
							rsltmat.elems[j+newcount]=othervalptr[othercover];
							newcount++;
							othercover++;
						}
						break;
					case false:
						while (othercover<otherubd)
						{
							if (insecub<=newcount)
							{
								break;
							}
							rsltmat.colinds[j+newcount]=otherindptr[othercover];
							rsltmat.elems[j+newcount]=-othervalptr[othercover];
							newcount++;
							othercover++;
						}
						break;
					}		
				}
			}
		}
		return rsltmat;
	}

	template<typename T>
	VirtualSprMat<T> SprsMat<T>::operator-(VSMval& rmat)const{
		SMval newrmat;
		newrmat.move(rmat);
		VSMval rsltmat;
		rsltmat=*this-newrmat;
		newrmat.free();
		return rsltmat;
	}

	//this is a function to realize sparse matrix addition
	template<typename T>
	VirtualSprMat<T> SprsMat<T>::operator+(const SMval& rmatrix)const
	{
		//before perform the addition, check whether sizes match
		if(rowsize!=rmatrix.rowsize||colmsize!=rmatrix.colmsize)
		{
			//if the sizes don't match, return error matrix
			std::cout<<"SprsMatr error: sizes of two matrices don't match"<<std::endl;
			VSMval rsltmat(0,0);
			return(rsltmat);
		}

		//if one of the two matices is empty ,then return the other one
		if(elems==NULL)
		{
			VSMval rsltmat;
			rsltmat.copy(rmatrix);
			return(rsltmat);
		}
		if (rmatrix.elems==NULL)
		{
			VSMval rsltmat;
			rsltmat.copy(*this);
			return(rsltmat);
		}

		//if both of them are nonempty, then perform the addtion
		uint_32 i,j,leftsize,rightsize,insecub;
		T* currentvalptr,*othervalptr,*mvalptr;
		uint_32* currentindptr,*otherindptr,*mindptr;
		uint_32 currentupd,currentcover,othercover,otherubd,media;
		VSMval rsltmat(rowsize,colmsize);
		rsltmat.numel=new uint_32[rowsize+1];
		rsltmat.numel[0]=0;
		//count number of nonzero entries of each row of result matrix
		//and save the numbers in 'numel' of result matrix temporarily
		for(i=0;i<rowsize;i++)
		{
			rightsize=rmatrix.numel[i+1]-rmatrix.numel[i];
			leftsize=numel[i+1]-numel[i];
			//if ith row of  any matrix of the two is empty, 
			//then the new length of new row is that of the other one
			if (rightsize==0)
			{
				rsltmat.numel[i+1]=leftsize;
			}
			else if(leftsize==0)
			{
				rsltmat.numel[i+1]=rightsize;
			}
			else
			{
				currentcover=0;othercover=1;
				rsltmat.numel[i+1]=0;
				//initializing variables for accounting intersection indices between two index array
				if (rmatrix.colinds[rmatrix.numel[i]]<colinds[numel[i]])
				{
					currentindptr=colinds+numel[i];
					currentvalptr=elems+numel[i];
					otherindptr=rmatrix.colinds+rmatrix.numel[i];
					othervalptr=rmatrix.elems+rmatrix.numel[i];
					currentupd=leftsize;
					otherubd=rightsize;
				}
				else if(colinds[numel[i]]==rmatrix.colinds[rmatrix.numel[i]])
				{
					othercover=0;
					currentindptr=rmatrix.colinds+rmatrix.numel[i];
					otherindptr=colinds+numel[i];
					currentvalptr=rmatrix.elems+rmatrix.numel[i];
					othervalptr=elems+numel[i];
					currentupd=rightsize;
					otherubd=leftsize;
				}
				else
				{
					currentindptr=rmatrix.colinds+rmatrix.numel[i];
					otherindptr=colinds+numel[i];
					currentvalptr=rmatrix.elems+rmatrix.numel[i];
					othervalptr=elems+numel[i];
					currentupd=rightsize;
					otherubd=leftsize;
				}
				if (currentindptr[0]>otherindptr[otherubd-1])
				{
					//if there is no intersection between two  indices array then the length of new vector is reclen+sedlen
					rsltmat.numel[i+1]=leftsize+rightsize;
				} 
				else
				{
					insecub=colinds[numel[i+1]-1]<rmatrix.colinds[rmatrix.numel[i+1]-1]?colinds[numel[i+1]-1]:rmatrix.colinds[rmatrix.numel[i+1]-1];
					if (othercover!=0)
					{
						//to find othercover
						othercover=0;
						for (j=1;j<otherubd;j++)
						{
							if (currentindptr[0]<=otherindptr[j])
							{
								othercover=j-1;
								break;
							}
						}
					}
					//compute the length of new vector
					while(currentindptr[currentcover]<=insecub)
					{
						if (currentindptr[currentcover]<otherindptr[othercover])
						{
							currentcover++;
						}
						else if(currentindptr[currentcover]==otherindptr[othercover])
						{
							if (currentvalptr[currentcover]==(-othervalptr[othercover]))
							{
								rsltmat.numel[i+1]++;
							}
							rsltmat.numel[i+1]++;
							currentcover++;
							othercover++;
						}
						else{
							//if currentindex> other stationary index then swap them
							mindptr=currentindptr;currentindptr=otherindptr;otherindptr=mindptr;
							mvalptr=currentvalptr;currentvalptr=othervalptr;othervalptr=mvalptr;
							media=currentcover;currentcover=othercover;othercover=media;
							media=currentupd;currentupd=otherubd;otherubd=media;
							currentcover++;
						}
						if (currentupd<=currentcover)
						{
							break;
						}
					}
					rsltmat.numel[i+1]=leftsize+rightsize-rsltmat.numel[i+1];
				}		
			}
		}
		//construct 'numel array' of result matrix
		for (i=0;i<rowsize;i++)
		{
			rsltmat.numel[i+1]+=rsltmat.numel[i];
		}

		//if the result matrix is empty then return empty matrix
		j=rsltmat.numel[rowsize];
		if (j==0)
		{
			delete[]rsltmat.numel;
			rsltmat.numel=NULL;
			return rsltmat;
		}

		//if the result matrix is nonempty, then allocate memories for result matrix
		rsltmat.elems=new T[j];
		rsltmat.colinds=new uint_32[j];
		uint_32 newcount;
		for (i=0;i<rowsize;i++)
		{
			j=rsltmat.numel[i];
			insecub=rsltmat.numel[i+1]-j;
			if (insecub)
			{
				rightsize=rmatrix.numel[i+1]-rmatrix.numel[i];
				leftsize=numel[i+1]-numel[i];
				newcount=0;
				if (rightsize==0)
				{
					for (;newcount<insecub;newcount++)
					{
						rsltmat.colinds[j+newcount]=colinds[numel[i]+newcount];
						rsltmat.elems[j+newcount]=elems[numel[i]+newcount];
					}
				}
				else if(leftsize==0)
				{
					for (;newcount<insecub;newcount++)
					{
						rsltmat.colinds[j+newcount]=rmatrix.colinds[rmatrix.numel[i]+newcount];
						rsltmat.elems[j+newcount]=rmatrix.elems[rmatrix.numel[i]+newcount];
					}
				}
				else
				{
					currentcover=1;othercover=0;
					if (rmatrix.colinds[rmatrix.numel[i]]<colinds[numel[i]])
					{
						currentindptr=rmatrix.colinds+rmatrix.numel[i];
						otherindptr=colinds+numel[i];
						currentvalptr=rmatrix.elems+rmatrix.numel[i];
						othervalptr=elems+numel[i];
						currentupd=rightsize;
						otherubd=leftsize;
						rsltmat.colinds[j]=currentindptr[0];
						rsltmat.elems[j]=currentvalptr[0];
						newcount++;
					}
					else if(rmatrix.colinds[rmatrix.numel[i]]==colinds[numel[i]])
					{
						currentindptr=rmatrix.colinds+rmatrix.numel[i];
						otherindptr=colinds+numel[i];
						currentvalptr=rmatrix.elems+rmatrix.numel[i];
						othervalptr=elems+numel[i];
						currentupd=rightsize;
						otherubd=leftsize;
						if (currentvalptr[0]!=(-othervalptr[0]))
						{
							rsltmat.colinds[j]=currentindptr[0];
							rsltmat.elems[j]=currentvalptr[0]+othervalptr[0];
							newcount++;
						}		
						othercover++;		
					}
					else
					{
						currentindptr=colinds+numel[i];
						otherindptr=rmatrix.colinds+rmatrix.numel[i];
						currentvalptr=elems+numel[i];
						othervalptr=rmatrix.elems+rmatrix.numel[i];
						currentupd=leftsize;
						otherubd=rightsize;
						rsltmat.colinds[j]=currentindptr[0];
						rsltmat.elems[j]=currentvalptr[0];
						newcount++;
					}
					while((currentcover<currentupd)&&newcount!=insecub)
					{
						//if other array achieves the end, then swap two arrays and break the 'while' circle
						if (otherubd<=othercover)
						{
							otherindptr=currentindptr;
							othervalptr=currentvalptr;
							otherubd=currentupd;
							othercover=currentcover;
							break;
						}
						if (currentindptr[currentcover]<otherindptr[othercover])
						{
							rsltmat.colinds[j+newcount]=currentindptr[currentcover];
							rsltmat.elems[j+newcount]=currentvalptr[currentcover];
							currentcover++;
							newcount++;
						}
						else if(currentindptr[currentcover]==otherindptr[othercover])
						{
							//if the indices coincide then check whether the result of plus is zero
							if (currentvalptr[currentcover]!=(-othervalptr[othercover]))
							{
								rsltmat.colinds[j+newcount]=currentindptr[currentcover];
								rsltmat.elems[j+newcount]=currentvalptr[currentcover]+othervalptr[othercover];
								newcount++;
							}		
							currentcover++;
							othercover++;	
						}
						else{
							//if currentindex> other stationary index then commute them
							mindptr=currentindptr;currentindptr=otherindptr;otherindptr=mindptr;
							mvalptr=currentvalptr;currentvalptr=othervalptr;othervalptr=mvalptr;
							media=currentcover;currentcover=othercover;othercover=media;
							media=currentupd;currentupd=otherubd;otherubd=media;
							rsltmat.colinds[j+newcount]=currentindptr[currentcover];
							rsltmat.elems[j+newcount]=currentvalptr[currentcover];
							currentcover++;
							newcount++;
						}
					}
					while (othercover<otherubd)
					{
						if (insecub<=newcount)
						{
							break;
						}
						rsltmat.colinds[j+newcount]=otherindptr[othercover];
						rsltmat.elems[j+newcount]=othervalptr[othercover];
						newcount++;
						othercover++;
					}
				}
			}
		}
		return rsltmat;
	}

	template<typename T>
	VirtualSprMat<T> SprsMat<T>::operator+(VSMval& rmat)const{
		SMval newrmat;
		newrmat.move(rmat);
		VSMval rsltmat;
		rsltmat=*this+newrmat;
		newrmat.free();
		return rsltmat;
	}

	//swap two matrix
	template<typename T>
	void SprsMat<T>::swap(SMval& othermatrix)
	{
		T* mvalptr;
		uint_32* mnumptr;
		uint_32 median;

		//swap elems of two matrix
		mvalptr=elems;
		elems=othermatrix.elems;
		othermatrix.elems=mvalptr;

		//swap colinds of two matrix
		mnumptr=colinds;
		colinds=othermatrix.colinds;
		othermatrix.colinds=mnumptr;

		//swap two numel of two matrix
		mnumptr=numel;
		numel=othermatrix.numel;
		othermatrix.numel=mnumptr;


		//swap matrix size
		median=rowsize;
		rowsize=othermatrix.rowsize;
		othermatrix.rowsize=median;
		median=colmsize;
		colmsize=othermatrix.colmsize;
		othermatrix.colmsize=median;
	}

	template<typename T>
	VirtualSprMat<T> SprsMat<T>::transpose()const
	{
		VSMval rsltmatrix(colmsize,rowsize);
		if (elems==NULL)
		{
			return rsltmatrix;
		}
		uint_32 len=numel[rowsize];
		rsltmatrix.elems=new T[len];
		rsltmatrix.colinds=new uint_32[len];
		len=colmsize+1;
		rsltmatrix.numel=new uint_32[len];
		//initialize numel of resultmatrix as zero array
		uint_32 i;
		for (i=0;i<len;i++)
		{
			rsltmatrix.numel[i]=0;
		}
		//to account number of nonzero entries in each column of original matrix
		len=numel[rowsize];
		for(i=0;i<len;i++)
		{
			rsltmatrix.numel[colinds[i]+1]++;
		}

		len=rsltmatrix.rowsize+1;
		uint_32 sum=0;
		for (i=1;i<len;i++)
		{
			sum+=rsltmatrix.numel[i];
		}
		len--;
		for (i=len;i>1;i--)
		{
			sum-=rsltmatrix.numel[i];
			rsltmatrix.numel[i]=sum;
		}

		rsltmatrix.numel[1]=0;
		uint_32 j;
		for (i=0;i<rowsize;i++)
		{
			for (j=numel[i];j<numel[i+1];j++)
			{
				len=colinds[j]+1;
				rsltmatrix.elems[rsltmatrix.numel[len]]=elems[j];
				rsltmatrix.colinds[rsltmatrix.numel[len]]=i;
				rsltmatrix.numel[len]++;
			}
		}
		return rsltmatrix;
	}

	template<typename T>
	SprsMat<T>::~SprsMat()
	{
		if(elems){delete[]elems;elems=NULL;}
		if(numel){delete[]numel;numel=NULL;}
		if(colinds){delete[]colinds;colinds=NULL;}
	}
	
}
#endif