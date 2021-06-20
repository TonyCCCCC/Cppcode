#include "nonsqsolver.h"
using namespace std;
int main()
{
	  Linspace::SprsMat<double> mat1;
	  mat1.SprMatFin("matdata.txt","sparse");
   NSsolver<double> sol1(mat1),sol2;
   sol1.show();
}