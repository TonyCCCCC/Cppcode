#include <iostream>
#include "FAI_2DFSDEsolver.h"
#include"gamma.h"
#include <time.h>
#include <iomanip> 
#define PI  3.1415926535897932384626433832
const uint_32 level=8;
const uint_32 N=32;
const double X_L=0,X_R=PI,Y_Low=0,Y_Upp=PI,T=0.5,alpha=0.1;
const double eps=0.5e-8;
const double tol=1.0e-8;
double inf_norm_real(double* vec,uint_32 veclen);
double averageiter(uint_32* vec,uint_32 veclen);
int main()
{
	uint_32 M,i,j,Ms;
	clock_t t1,t2;
	double s;
	t1=clock();
	M=_Pow_int(2,level)-1;
	Ms=M*M;
	double tau=T/(double)N,miu,oneovermiu;
	miu=pow(tau,alpha)*Gamma(2-alpha);
	double h1,h2;
	h1=(X_R-X_L)/(double)(M+1);
	h2=(Y_Upp-Y_Low)/(double)(M+1);
	oneovermiu=1.0/miu;
	double onema=1-alpha,apkp1,apk;
	double* ak=new double[N];
	apk=0; apkp1=1;
	for(i=0;i<N;i++)
	{
		ak[i]=apkp1-apk;
		apk=apkp1;
		apkp1=pow(i+2,onema);
	}
	double* Frac_div_appro_coeff=new double[N];
	Frac_div_appro_coeff[0]=oneovermiu;
	for (i=1;i<N;i++)
	{
		Frac_div_appro_coeff[i]=oneovermiu*(ak[i]-ak[i-1]);
	}
	delete[]ak;
	complex** rhs=new complex*[N];
	double* sinx=new double[M],*cosx=new double[M],*cosy=new double[M],*siny=new double[M];
	double* sinxsiny=new double[Ms];
	double mh2,mh1;
	uint_32 indy;
	for (i=0;i<M;i++)
	{
		mh1=X_L+(i+1)*h1;
		mh2=Y_Low+(i+1)*h2;
		sinx[i]=sin(mh1);
		cosx[i]=cos(mh1);
		siny[i]=sin(mh2);
		cosy[i]=cos(mh2);
	}

	for (j=0;j<M;j++)
	{
		indy=j*M;
		for (i=0;i<M;i++)
		{
			sinxsiny[indy+i]=sinx[i]*siny[j];
		}
	}

	for (i=0;i<N;i++)
	{
		rhs[i]=new complex[Ms];
	}

	for (j=0;j<M;j++)
	{
		indy=j*M;
		mh2=Y_Low+(j+1)*h1;
		for (i=0;i<M;i++)
		{
			mh1=X_L+(i+1)*h1;
			rhs[0][indy+i].r=2*sinxsiny[indy+i]-mh1*sinx[i]*cosy[j]-mh2*cosx[i]*siny[j];
			rhs[0][indy+i].r*=exp(mh1*mh2);
		}
	}
	delete[]cosx;delete[]sinx;delete[]siny;delete[]cosy;
	double tovergta=2.0/Gamma(3-alpha),twoma=2-alpha,t,tpow;
	for (i=1;i<N;i++)
	{
		t=(i+1)*tau;
		tpow=pow(t,twoma)*tovergta;
		for (j=0;j<Ms;j++)
		{
			rhs[i][j].r=t*t*rhs[0][j].r+tpow*sinxsiny[j];
			rhs[i][j].i=0;
		}
	}
	t=tau;
	for (j=0;j<Ms;j++)
	{
		tpow=pow(t,twoma)*tovergta;

		rhs[0][j].r*=(t*t);
		rhs[0][j].r+=(tpow*sinxsiny[j]);
		rhs[0][j].i=0;
	}
	
	uint_32* iter_num_arr=new uint_32[N];

	Time_frac_diffusion_2Deq_solver(N,level,X_L,X_R,Y_Low,Y_Upp,Frac_div_appro_coeff,rhs,eps,iter_num_arr,tol);
	delete[]Frac_div_appro_coeff;
	double norm1,error;
	norm1=inf_norm_real(sinxsiny,Ms);
	norm1*=(T*T);
	double ts,taus=tau*tau,*temsolver=new double[Ms],max=0,max2;

	for (i=0;i<N;i++)
	{
		ts=(i+1)*(i+1)*taus;
		for (j=0;j<Ms;j++)
		{
			temsolver[j]=rhs[i][j].r-sinxsiny[j]*ts;
		}
		delete[]rhs[i];
		max2=inf_norm_real(temsolver,Ms);
		if(max<max2) max=max2;
	}
	delete[]temsolver;
	t2=clock();
	std::cout<<"iter:"<<averageiter(iter_num_arr,N)<<std::endl;
	error=max/norm1;
	std::cout<<"the relative error under infinite norm is:"<<error<<std::endl;
	s=(double)(t2-t1)/CLOCKS_PER_SEC;
	std::cout.setf(std::ios::fixed);
	std::cout<<std::setprecision(7)<<"the running time is :"<<s<<std::endl;

	delete[]sinxsiny;
}
double inf_norm_real(double* vec,uint_32 veclen)
{
	double max=fabs(vec[0]);
	for (uint_32 i=1;i<veclen;i++)
	{
		if (max<fabs(vec[i]))
		{
			max=fabs(vec[i]);
		}
	}
	return max;
}
double averageiter(uint_32* vec,uint_32 veclen)
{
	double average=vec[0];
	for (uint_32 i=1;i<veclen;i++)
	{
		average+=vec[i];
	}
	return average/(double)veclen;
}

