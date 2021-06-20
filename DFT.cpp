#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<math.h>
#include<complex>
#include<vector>
#include<iomanip>

#define PI 3.1415926
using namespace std;

/*
class FDT
{ffff
public:
	vector<complex<double>> fdt(vector<double>arg,int n);
	vector<double> ifdt(vector<complex<double>>a,int n);
};
*/

vector<complex<double>> fdt(vector<double>arg,int n)
{
	vector<complex<double>> t;
	complex<double> tmp;
	double ral=0, img=0;
	for (int i = 0; i < n; i++)
	{
		ral = 0;
		img = 0;
		for (int j = 0; j < n; j++)
		{
			ral += arg[j] * cos(i*j*(-2)*PI / n  );
			img += arg[j] * sin(i*j*(-2)*PI / n  );
		}
		tmp.real(ral);
		tmp.imag(img);
		t.push_back(tmp);
	}
	return t;
}


vector<double> ifdt(vector<complex<double>>a,int n)
{
	vector<double> t2;
	
	complex<double> arg,tmp;

	for (int i = 0; i < n; i++)
	{
		tmp = { 0,0};
		for (int j = 0; j < n; j++)
		{
			arg = { cos(2 * PI*j*i / n/ PI),sin(2 * PI*j*i / n / PI) };
			tmp += a[j] * arg;

		}

		t2.push_back(tmp.real() / n);

	}
	return t2;
}


int main()
{
	vector<double>a,b;
	vector<complex<double>>FD;
	int n;
	cin >> n;

	double tmp;
	for (int i = 0; i < n; i++) 
	{
		cin >> tmp;
		a.push_back(tmp);
	}	

	FD = fdt(a, n);
	

	
	for (int i = 0; i < n; i++)
	{
		cout<< setiosflags(ios::fixed) << setprecision(3) << FD[i]<< endl;
	}
	

	//cout << "::::::::::::::::::::::::::::::::"<<endl;
	//complex<double> t3;
	//t3.real(3);
	//t3.imag(2);
	//t2 = (1,2);
	//cout << t3 << endl;
	//cout << t3*t3 << endl;
	//cout << t3.imag() << endl;

	b = ifdt(FD, n);
	/*
	for (int i = 0; i < n; i++)
	{
		cout << b[i] << endl;
	}	
	*/







	return 0;
}
