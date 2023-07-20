// armadillo library
#include <armadillo>
// system and c++ libraries
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <vector>
#include <numeric>
// my libraries

//namespaces
using namespace std;
using namespace arma;
// -----------------------------------------------------------------------------------

int P;
vector<int>* T;

// -----------------------------------------------------------------------------------

Mat<int> mod(Mat<int> A, int );
//Col<int> mod(Col<int> A, int n);

bool next_mat(Mat<int>&);
bool next_ind_sig(Col<int>&);
bool next_cut_sig(Col<int>&);

bool isEqual(const Mat<int>&, const Mat<int>&);
bool isDiag(const Mat< int>&);

bool isGoodCondition(const Mat<int>&);
bool isCloseToGen(const Mat<int>&);

bool isPrime(int num);

void genPointWise(const Mat<int>&);

int extGCD(int, int, int&, int&);

// -----------------------------------------------------------------------------------
int main( int argc, char** argv)
{

	int Prime[20]={3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 3};
	Col<int> ind_sig(4, fill::zeros);
	ind_sig(0) = 0;
	ind_sig(1) = 1;
	ind_sig(2) = 1;
	ind_sig(3) = 1; // the lambda

	Col<int> cut_sig(4, fill::zeros);
	cut_sig(0) = 1;
	cut_sig(1) = 2;	// the omega
	cut_sig(2) = 2; // the omega
	cut_sig(3) = 1;

	bool check_for_T = true;

	for(int i=3;i<=30;i++)
	{
		if (!isPrime(i))
			continue;
		P = i;
		Mat<int> M(2, 2, fill::zeros);
		M(0,0) = 1;
		M(0,1) = 1;
		M(1,0) = 1;
		M(1,1) = 1;

		ind_sig(0) = 0;
		ind_sig(1) = 1;
		ind_sig(2) = 1;
		ind_sig(3) = 1; // the lambda

		bool M_flag = true, ind_flag = true, cut_flag = true;
		Mat<int> I2(2,2, fill::eye);
		cout<<"starting to work on new prime number:..."<<endl;
		//P = Prime[i];
		cout<<"the resize..."<<endl;
		T = new vector<int>(P,0);
		cout<<"the array is ready"<<endl;
		//std::fill(*T.begin(), *T.end(), 0);
		cout<<"the array in set to zero"<<endl;
		//P = 7;
		cout<<P<<endl;
		check_for_T = true;
		while(ind_flag && check_for_T)
		{
		//	while(cut_flag)
			{
				while(M_flag && check_for_T)
				{
					Mat<int> r = mod(M*M.t(), P);
					//if(isEqual(r, I2))
					if(isDiag(r))
					{
						Mat<int> M2 = mod(kron(M,M), P);

						Mat<int> R = mod(M2* ind_sig, P);

						bool check = isGoodCondition(R);

						if(check)
						{
							cout<<"M is:"<<endl<<M<<endl<<"--"<<endl;
							cout<<"ind_sig is:"<<endl<<ind_sig<<endl<<"--"<<endl;
							cout<<"the product is:"<<endl;
							cout<< R <<"\n-----"<<endl;
							genPointWise(R);
							cout<<"["<<P<<"]: ";
							for(int ii=0;ii<P;ii++)
							{
								cout<<T->at(ii)<<" ";
							}
							bool temp_check = true;;
							for(int ii=1;ii<P;ii++)
							{
								if(T->at(ii)!=1)
								{
									temp_check = false;
									break;
								}
							}
							check_for_T = temp_check;
							cout<<endl;
							cout<<"--------------------------------------\n";
							if(M(0,0) != M(1, 1) && M(0,1) != M(1, 0))
							{
								int xxx;
								cin>>xxx;
							}
						}
					}
					//cout<<">\n"<<endl<<M<<endl;
					M_flag = next_mat(M);
				}
			}
			ind_flag = next_ind_sig(ind_sig);
		}
		delete T;
	}
	return 0;
}

// -----------------------------------------------------------------------------------
Mat<int> mod(Mat<int> A, int n)
{
	return A - arma::ceil(A/n)*n;
}

bool next_mat(Mat<int>& M)
{
	M(0,0)++;
	bool flag = true;
	if(M(0,0) == P)
	{
		M(0,1)++;
		M(0,0) = 0;
	}
	if(M(0,1) == P)
	{
		M(1,0)++;
		M(0,1) = 0;
	}
	if(M(1,0) == P)
	{
		M(1,1)++;
		M(1,0) = 0;
	}
	if(M(1,1) == P)
	{
		flag = false;
	}
	return flag;
}
bool next_ind_sig(Col<int>& s)
{
	s(3)++;
	if(s(3) == P)
		return false;
	return true;
}
bool next_cut_sig(Col<int>& s)
{
	s(1)++;
	s(2)++;
	if(s(1) == P)
		return false;
	return true;
}

bool isEqual(const Mat<int>& M,const Mat<int>& N)
{
	 uword n = accu(M==N);
	 if(n == M.size())
	 	return true;
	return false;
}

bool isDiag(const Mat<int>& M)
{
	int check = M(0,0);
	for(uword i=0;i<M.n_rows;i++)
	{
		for(uword j=0;j<M.n_rows;j++)
		{
			if(i==j)
			{
				if(M(i,j)==0 || M(i,j)!=check)
					return false;
			}
			else
			{
				if(M(i,j)!=0)
					return false;
			}
		}
	}
	return true;
}

bool isGoodCondition(const Mat<int>& M)
{
	if((M(0)!=0) && (M(1)!=0) && (M(2)!=0) && (M(3)!=0))
	{
		if((M(0)==M(1)) && (M(1)==M(2)) && (M(2)!=M(3)))
			return true;
		//if((M(1)==M(2)) && (M(2)==M(3)) && (M(0)!=M(3)))
		//		return true;
	}
	return false;
}
bool isCloseToGen(const Mat<int>& M)
{
	if((M(0)==1) && (M(1)==1) && (M(2)==1) && (M(3)!=1))
		return true;
	return false;
}

void genPointWise(const Mat<int>& R)
{
	Mat<int> S = R;
	//cout<<"###########"<<endl;
	for(int i=0; i<P-1;i++)
	{
		if(isCloseToGen(S))
		{
			Mat<int> Q = S;
			cout<<"^^^^^^^^: "<<P<<endl;
			for(int j=0; j<P-1;j++)
			{
				Q = mod(Q%S, P);
				T->at(Q(3)) = 1;
				cout<<Q<<endl;
				cout<<"---"<<endl;
			}
			cout<<"vvvvvvvv"<<endl;
		}
		int x, y;
		int rem = extGCD(S(0), P, x, y);
		if(x<0)
		{
			x+=P;
		}

		if(S(0)!=1)
		{
			Mat<int> Q_1 = mod(x * S, P);
			Mat<int> Q = Q_1;

			//cin>>x;
			//cout<<S(0)<<" "<<P<<" "<<x<<" "<<y<<endl<<Q<<endl;
			//cin>>x;
			cout<<"^^^^^^^^: (x^(-1)), prime number:"<<P<<endl;
			for(int j=0; j<P-1;j++)
			{
				Q = mod(Q%Q_1, P);
				T->at(Q(3)) = 1;
				cout<<Q<<endl;
				cout<<"R-1---"<<endl;
			}
			cout<<"vvvvvvvv"<<endl;
		}
		S = mod(S%R, P);
	}
	//cout<<"###########"<<endl;
}

int extGCD(int a, int b, int& x, int& y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}



bool isPrime(int num)
{
    if (num < 2)
		{
        return false;
    }

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}
