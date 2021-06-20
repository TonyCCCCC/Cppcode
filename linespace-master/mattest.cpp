/*
#include "LinearSpace.h"
#include <vector>
int main()
{
	Linspace::unique_arr<double> v(9);
	v[0]=0;v[1]=2;v[2]=2;v[3]=5;v[4]=1;v[5]=17;v[6]=0;v[7]=45;v[8]=67;
	Linspace::unique_arr<uint_32>col(9),numel(5);
	col[0]=1;col[1]=2;col[2]=3;col[3]=0;col[4]=2;col[5]=3;col[6]=0;col[7]=1;col[8]=3;
	numel[0]=0;numel[1]=3;numel[2]=3;numel[3]=6;numel[4]=9;
	//for(uint_32 iii(5);iii<12;iii++){numel[iii]=9;}
	Linspace::SprsMat<double> A(v,col,numel,4,4);
	std::cout<<"A:"<<std::endl;
	A.show();
	std::cout<<std::endl;

	/ *v[0]=4;
	v[1]=7;
	v[4]=6;
	SprsMat B(v,col,numel,4,4);
	cout<<"B:"<<endl;
	B.show();
	cout<<endl;

	SprsMat D;
	D=A+B;
	cout<<"D:"<<endl;
	D.show();
	cout<<endl;* /
/ *
	cout<<"A:"<<endl;
	A.show();
	cout<<endl;
	A.compress();
	cout<<"A:"<<endl;
	A.show();
	cout<<endl;
	A=A.transpose();
	cout<<"A^T:"<<endl;
	A.show();
	cout<<endl;* /
	Linspace::SprsMat<double> B;
	Linspace::SprsMat<double> F;
	std::vector<Linspace::SprsMat<double>> vm;
	B=A;
	Linspace::vector<double> vt(4,2);
	std::cout<<"test......................."<<std::endl;
	F=B*A;
	std::cout<<"F:"<<std::endl;
	F.show();
	std::cout<<"test......................."<<std::endl;
	std::cout<<F.norm("F")<<std::endl;
	F.SprMatFout("matdata.txt",3,1);
	A.SprMatFin("newmat.txt","dense");
	std::cout<<"A:"<<std::endl;
	A.show();
	std::cout<<A.density()<<std::endl;
	/ *vm.push_back(B);
	std::cout<<"B:"<<std::endl;
	B.show();
	std::cout<<std::endl<<std::endl;
	B.compress();
	//B.show();
	std::cout<<"A:"<<std::endl;
	A.show();
	std::cout<<std::endl;
	std::cout<<"B:"<<std::endl;
	B.show();
	std::cout<<std::endl;
	A.compress();
	Linspace::SprsMat<double> D;
	std::cout<<"test space..................................................................."<<std::endl;
	D=A*B;
	std::cout<<"test space..................................................................."<<std::endl;
	std::cout<<"D:"<<std::endl;
	D.show();
	std::cout<<std::endl;
	std::cout<<"A:"<<std::endl;
	A=D.transpose();
	A.show();	//vector<Linspace::SprsMat> va;

	std::cout<<std::endl;
	std::cout<<"D:"<<std::endl;
	D.show();
	std::cout<<"-----------------------------"<<std::endl;
	D.showdiaginds();* /
/ *
	B=A.transpose();
	cout<<"B:"<<endl;
	B.show();	for(int i=0;i<10;i++)
	{
		va.push_back(A);
	}
	for (int i=0;i<10;i++)
	{
		va[i].show();
	}
	cout<<endl<<endl;
	v[0]=5;
	va[0].setmatrix(v,col,numel,4,4);
	for (int i=0;i<10;i++)
	{
		va[i].show();
	}	vector<double> valreceiver(1),valsender(4);
	vector<uint_32> indreceiver(1), indsender(4);
	valreceiver[0]=2;//valreceiver[1]=-3;valreceiver[2]=3;valreceiver[3]=-4;
	indreceiver[0]=1;//indreceiver[1]=2;indreceiver[2]=3;indreceiver[3]=4;
	valsender[0]=2;valsender[1]=3;valsender[2]=-3;valsender[3]=4;
	indsender[0]=1;indsender[1]=2;indsender[2]=3;indsender[3]=4;
	SprsArr v1(valreceiver,indreceiver),v2(valsender,indsender);
	v1+=v2;
	v1.show();* /
}*/