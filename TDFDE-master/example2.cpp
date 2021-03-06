/*
#include <iostream>
#include "FAI_2DFSDEsolver.h"
#include"gamma.h"
#include <time.h>
#include <iomanip> 
#define PI  3.1415926535897932384626433832
const uint_32 level=9;
const uint_32 N=4;
const double X_L=0,X_R=0.5,Y_Low=0,Y_Upp=0.5,T=1,alpha=1.0/3.0;
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
   double fovergmfma=Gamma(4)/Gamma(4-alpha);
   double t,*expx=new double[M],*expy=new double[M];
    double* exactsol=new double[Ms];
	double mh1,mh2,tmalpha=3-alpha,tq,tptma,oneoverh1s=1/(h1*h1),oneoverh2s=1/(h2*h2);
	double x_s=X_L+0.5*h1,x_e=X_L+(M+0.5)*h1,y_s=Y_Low+0.5*h2,y_e=Y_Low+(M+0.5)*h2;
	double expxl=exp(X_L),expxr=exp(X_R),expyl=exp(Y_Low),expyu=exp(Y_Upp);
	double oneoh1sxl=oneoverh1s*expxl,oneoh1sxr=oneoverh1s*expxr,oneoh2syl=oneoverh2s*expyl,oneoh2syu=oneoverh2s*expyu;
	double fovemtptma;
	uint_32 Mm1=M-1,Mmmm1=Mm1*M;
	for (i=0;i<M;i++)
	{
		expx[i]=exp(X_L+(i+1)*h1);
		expy[i]=exp(Y_Low+(i+1)*h2);
	}
	uint_32 indy,n;
	for (j=0;j<M;j++)
	{
		indy=j*M;
		for (i=0;i<M;i++)
		{
			exactsol[indy+i]=expx[i]*expy[j];
		}
	}
	delete[]expx;delete[]expy;

	double *expxy=new double[Ms];

	for (j=0;j<M;j++)
	{
		indy=j*M;
		mh2=Y_Low+(j+1)*h2;
		for (i=0;i<M;i++)
		{
			expxy[indy+i]=exp(mh2*(X_L+(i+1)*h1));
		}
	}

	for (n=0;n<N;n++)
	{
		t=(n+1)*tau;
		tptma=pow(t,tmalpha);
		tq=t*t*t;
		fovemtptma=fovergmfma*tptma;
		rhs[n]=new complex[Ms];
		for (j=0;j<M;j++)
		{
			mh2=Y_Low+(j+1)*h2;
			indy=j*M;
			for (i=0;i<M;i++)
			{
				mh1=X_L+(i+1)*h1;
				rhs[n][indy+i].r=exactsol[indy+i]*(fovemtptma-tq*expxy[indy+i]*(2+mh1+mh2));
				rhs[n][indy+i].i=0;
			}
			rhs[n][indy].r+=(oneoh1sxl*postv_func(x_s,mh2)*tq*exp(mh2));
			rhs[n][indy+Mm1].r+=(oneoh1sxr*postv_func(x_e,mh2)*tq*exp(mh2));
		}
		for (i=0;i<M;i++)
		{
			mh1=X_L+(i+1)*h1;
			rhs[n][i].r+=(oneoh2syl*postv_func(mh1,y_s)*tq*exp(mh1));
			rhs[n][Mmmm1+i].r+=(oneoh2syu*postv_func(mh1,y_e)*tq*exp(mh1));
		}
	}
	delete[]expxy;


   uint_32* iter_num_arr=new uint_32[N];

   Time_frac_diffusion_2Deq_solver(N,level,X_L,X_R,Y_Low,Y_Upp,Frac_div_appro_coeff,rhs,eps,iter_num_arr,tol);
    t2=clock();
	delete[]Frac_div_appro_coeff;

   double norm1,error,*tempsolver=new double[Ms],max=0,max1;
   norm1=inf_norm_real(exactsol,Ms);
   norm1*=pow(T,3);
   for (n=0;n<N;n++)
   {
	   t=(n+1)*tau;
	   tq=t*t*t;
	   for (i=0;i<Ms;i++)
	   {
		   tempsolver[i]=rhs[n][i].r-tq*exactsol[i];
	   }
	   max1=inf_norm_real(tempsolver,Ms);
	   if(max<max1) max=max1;
   }
   
 std::cout<<"averageiter:"<<averageiter(iter_num_arr,N)<<std::endl;
 error=max/norm1;
 std::cout<<"the relative error under infinite norm is:"<<error<<std::endl;
 s=(double)(t2-t1)/CLOCKS_PER_SEC;
  std::cout.setf(std::ios::fixed);
 std::cout<<std::setprecision(7)<<"the running time is :"<<s<<std::endl;

/ *
 for (i=0;i<Ms;i++)
 {
	 std::cout<<exactsol[i]*pow(T,onepalpha)-rhs[N-1][i].r<<std::endl;
 }
* /


   delete[]exactsol;
   delete[]tempsolver;
   for (i=0;i<N;i++)
   {
	   delete[]rhs[i];
   }
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
}*/