#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<math.h>
#include<iomanip>
#include<vector>
#include<complex>


//#define Pi 3.14159265
#define Pi 4*atan(1.0)
using namespace std;

vector<complex<double>> FFT(vector<complex<double>> vec, int n)
{
	vector<complex<double>> arg(vec);
	int S = n;
	int T = 0;
	complex<double> temp;
	while (S != 1)
	{
		T = n / S;
		for (int k = 1; k <= T; k++)
		{
			for (int l = (k - 1)*S; l <= (k - 1)*S + S / 2 - 1; l++)
			{
				temp = arg[l];
				arg[l] = temp + arg[l + S / 2];
				complex<double> w(cos(2.0 * Pi*(l) / double(S)), -sin(2.0 * Pi*(l) / double(S)));
				//w.real(cos(-2.0 * Pi*double(l) / double(S)));
				//w.imag(sin(-2.0 * Pi*double(l) / double(S)));
				arg[l + S / 2] = (temp - arg[l + S / 2])*w;
			}
		}
		S = S / 2;
	}

	return arg;
}


int  rev(int n,int k)
{
	vector<int> binary;
	//int binary;
	while (n > 0)
	{
		binary.push_back(n % 2);
		n /= 2;
	}
	int sum = 0;
	int len = binary.size();
	for (int i = 0; i < k - len; i++)
	{
		binary.push_back(0);
	}
	for (int i = 0; i<k; i++)
	{
	//cout << binary[i] << endl;
		sum += binary[i] * pow(2, k - 1 - i);
	//sum += binary[i]*pow(2, binary.size() - i);
	}
	return sum;
}


int main()
{
	int n,tmp;
	cin >> n;
	int k = 0;
	tmp = n;
	while (tmp > 1)
	{
		if (tmp % 2 != 0)
		{
			cout << "n is not a power function of 2" << endl;
			return 0;
		}
		tmp /= 2;
		k += 1;
	}

	//cout << k << endl;

	vector<complex<double>>an;
	double temp;

	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		an.push_back(temp);
	}
	

	//following commands are used to produce the test data!
	//for (int i = 0; i < n; i++)
	//{
	//	an.push_back(i);
	//}
	/////////////


	an = FFT(an, n);

	for (int i = 0; i < n; i++)
	{
		cout << setiosflags(ios::fixed) << setprecision(4) << an[rev(i, k)] << endl;
	//cout << i << endl;
	//cout << rev(i,k)<<endl;
	}

	return 0;
}
