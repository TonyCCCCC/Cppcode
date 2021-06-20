#ifndef  _NONSQSOLVER_H_
#define _NONSQSOLVER_H_
#include "LinearSpace.h"
using namespace Linspace;
template<typename valtype>
class Linspace::NSsolver
{
private:
	typedef NSsolver<valtype> _NSsol;
	typedef Linspace::unique_arr<valtype> UarrVal;
	typedef Linspace::unique_arr<uint_32> Uarruint;
	typedef std::vector<valtype> SVecval;
	typedef std::vector<uint_32> SVecUint;
	typedef	 Linspace::vector<valtype> LVecval;
	typedef Linspace::vector<valtype> LVecuint;
	typedef Linspace::SprsMat<valtype> SMval;
	typedef const Linspace::SprsMat<valtype> CSMval;
	typedef const std::vector<valtype> CSVecval;
	typedef const std::vector<uint_32> CSVecUint;
	typedef	const  Linspace::vector<valtype> CLVecval;
	typedef const Linspace::vector<valtype> CLVecuint;
	typedef const NSsolver<valtype> _CNSsol;
	typedef const uint_32 Cuint;
	uint_32* diaginds;
	SMval Mat;
	_NSsol operator=(NSsolver<valtype>);
	void reallocind(Cuint& colsize){
		if(Mat.elems){
			if(Mat.colmsize!=colsize){
				delete[]diaginds;
				diaginds=new uint_32[colsize];
			}
		}
		else{
			diaginds=new uint_32[colsize];
		}
	}
public:
	friend class SMval;
	NSsolver():Mat(),diaginds(NULL){}
	NSsolver(UarrVal& elemnts,Uarruint& colmind,Uarruint& elenumel,Cuint& rsize,Cuint& colsize):Mat(){
			if(rsize<colsize){
				std::cout<<"NSsolver error: only reveive high matrix of which rowsize>=column size!!"<<std::endl;
				return;
			}
			Mat.setmatrix(elemnts,colmind,elenumel,rsize,colsize);
			diaginds=Mat.gnertdiaginds();
	}
	NSsolver(CSVecval& elemnts,CSVecUint& colmind,CSVecUint& elenumel,Cuint& rsize,Cuint& colsize):Mat(){
			if(rsize<colsize){
				std::cout<<"NSsolver error: only reveive high matrix of which rowsize>=column size!!"<<std::endl;
				return;
			}
			Mat.setmatrix(elemnts,colmind,elenumel,rsize,colsize);
			diaginds=Mat.gnertdiaginds();
	}
	NSsolver(CLVecval& elemnts,CLVecuint& colmind,CLVecuint& elenumel,Cuint& rsize,Cuint& colsize):Mat(){
			if(rsize<colsize){
				std::cout<<"NSsolver error: only reveive high matrix of which rowsize>=column size!!"<<std::endl;
				return;
			}
			Mat.setmatrix(elemnts,colmind,elenumel,rsize,colsize);
			diaginds=Mat.gnertdiaginds();
	}
	NSsolver(CSMval& Matrix){
		if(Matrix.rowsize<Matrix.colmsize){
			std::cout<<"NSsolver error: only reveive high matrix of which rowsize>=column size!!"<<std::endl;
			return;
		}
		Mat=Matrix;
		diaginds=Mat.gnertdiaginds();
	}
	~NSsolver(){
		Mat.free();
		if(diaginds){delete[]diaginds;diaginds=NULL;}
	}

	void swap(_NSsol& othersol){
			uint_32* mptr;
			mptr=diaginds;
			diaginds=othersol.diaginds;
			othersol.diaginds=mptr;
			Mat.swap(othersol.Mat);
	}

	void copy(_CNSsol& othersol){
		if(othersol.Mat.elems){
			reallocind(othersol.Mat.colmsize);
			Mat=othersol.Mat;
			uint_32 len=Mat.colmsize;
			for(uint_32 i(0);i<len;i++){
				diaginds[i]=othersol.diaginds[i];
			}
		}
		else{
			free();
			Mat.rowsize=othersol.Mat.rowsize;
			Mat.colmsize=othersol.Mat.colmsize;
		}
	}

	bool Is_true()const{
		return Mat.Is_true();
	}

	void convert(CSMval& matrix){
		if(matrix.rowsize<matrix.colmsize){
			std::cout<<"NSsolver error: only reveive high matrix of which rowsize>=column size!!"<<std::endl;
			return;
		}
		Mat=matrix;
		diaginds=matrix.gnertdiaginds();
	}

	void setsolver(UarrVal& elemnts,Uarruint& colmind,Uarruint& elenumel,Cuint& rsize,Cuint& colsize){
		if(rsize<colsize){
			std::cout<<"NSsolver error: only reveive high matrix of which rowsize>=column size!!"<<std::endl;
			free();
			return;
		}
		Mat.setmatrix(elemnts,colmind,elenumel,rsize,colsize);
		if(diaginds){delete[]diaginds;}
		diaginds=Mat.gnertdiaginds();
	}

	void setsolver(CSVecval& elemnts,CSVecUint& colmind,CSVecUint& elenumel,Cuint& rsize,Cuint& colsize){
		if(rsize<colsize){
			std::cout<<"NSsolver error: only reveive high matrix of which rowsize>=column size!!"<<std::endl;
			return;
		}
		Mat.setmatrix(elemnts,colmind,elenumel,rsize,colsize);
		if(diaginds){delete[]diaginds;}
		diaginds=Mat.gnertdiaginds();
	}

	void setsolver(CLVecval& elemnts,CLVecuint& colmind,CLVecuint& elenumel,Cuint& rsize,Cuint& colsize){
		if(rsize<colsize){
			std::cout<<"NSsolver error: only reveive high matrix of which rowsize>=column size!!"<<std::endl;
			return;
		}
		Mat.setmatrix(elemnts,colmind,elenumel,rsize,colsize);
		if(diaginds){delete[]diaginds;}
		diaginds=Mat.gnertdiaginds();
	}
	void show()const{
		std::cout<<Mat.elems[0]<<std::endl;
	}
};
#endif   

