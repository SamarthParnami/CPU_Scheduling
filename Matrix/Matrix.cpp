#include<bits/stdc++.h>
using namespace std;
template<typename var> 
void printVector(vector<var> data) //printig array in single line
{
	for(int i=0;i<data.size();i++)
	{
		cout<<setw(3)<<data[i]<<" "; 
	}
	cout<<endl;
}

template<typename var>
class Matrix               
{
	public:
	vector<vector<var>> mat;
	int row;   //0 indexed
	int column; //0indexed

	Matrix(int row,int column,var defV=0):mat(row,vector<var>(column,defV))
	{
		this->row=row;
		this->column=column;
	}
	void insertElementAt(var data,int row,int column)    //inserting data at specific row and column
	{
		mat[row][column]=data;
	}
	void getInput()								//automating data input of whole matrix
	{

		for(int i=0;i<row;i++)
		{
			for(int j=0;j<column;j++)
			{
				var data;
				cin>>data;
				insertElementAt(data,i,j);
			}
		}
	}
	void printMatrix() 					//printing whole matrix
	{
		cout<<endl;
		for(int  i=0;i<row;i++)
		{
			printVector(mat[i]);
		}
		cout<<endl;
	}
	var trace()         //return trace of the matrix
	{
		var sum=0;
		if(row!=column)
		{
			cout<<"Unable to find trace this is not a square matrix."<<endl;
		}
		else
		{
			for(int i=0;i<row;i++)
			{
				sum+=mat[i][i];
			}
		}
		return sum;
	}
	Matrix transpose()   //retrun matrix object with transpose of original matrix
	{
		
		
		Matrix<var> t(column,row);
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<column;j++)
			{
				t.insertElementAt(mat[i][j],j,i);
			}
		}
		return t;
	}
	Matrix operator* (var val)
	{
		Matrix<var> pse (row,column);
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<column;j++)
			{
				pse.insertElementAt(mat[i][j]*val,i,j);
			}
		}
		return pse;
	}
	Matrix operator*(Matrix one)
	{
		if(column!=one.row)
		{
			cout<<"Not Suitable Matrices."<<endl;
			cout<<"Matrix One:"<<endl;
			cout<<"Row(s): "<<row<<endl;
			cout<<"Column(s): "<<column<<endl;
			cout<<endl;
			cout<<"Matrix Two:"<<endl;
			cout<<"Row(s): "<<one.row<<endl;
			cout<<"Column(s): "<<one.column<<endl;
			return *this;		
		}
		Matrix<var> ans(row,one.column);
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<one.column;j++)
			{
				for(int x=0;x<one.row;x++)
				{
					ans.mat[i][j]+=mat[i][x]*one.mat[x][j];
				}
			}
		}
		return ans;
		
	}
	Matrix operator+ (Matrix one)
	{
		if(row!=one.row||column!=one.column)
		{
			cout<<"Not Suitable Matrices."<<endl;
			cout<<"Matrix One:"<<endl;
			cout<<"Row(s): "<<row<<endl;
			cout<<"Column(s): "<<column<<endl;
			cout<<endl;
			cout<<"Matrix Two:"<<endl;
			cout<<"Row(s): "<<one.row<<endl;
			cout<<"Column(s): "<<one.column<<endl;
			return *this;
		}
		else
		{
			
			Matrix <var> ans(row,column);
			for(int i=0;i<row;i++)
			{
				for(int j=0;j<column;j++)
				{
					ans.insertElementAt(mat[i][j]+one.mat[i][j],i,j);
				}
			}
			return ans;
		}

	}
	Matrix operator+(var offset)
	{
		Matrix<var> t(row,column);
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<column;j++)
			{
				t.mat[i][j]=mat[i][j];
				if(i==j)
				{
					t.mat[i][j]+=offset;
				}
			}
		}
		return t;
	}
	void operator+=(var offset)
	{
		for(int i=0;i<row;i++)
		{
			mat[i][i]+=offset;
		}
	}

	
};


int main()
{
	//reduce the runtime of th program
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);


	// for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    Matrix <int>obj(3,2);
    Matrix<int> cld(2,3);
    obj.getInput();    //input from stdin
    cld.getInput();    //input from stdin
    obj.printMatrix();
    cld.printMatrix();
    Matrix<int> result1=obj.transpose();
    Matrix<int> result2=cld+result1;
    Matrix<int> result3=obj*cld;
    result1.printMatrix();
    result2.printMatrix();
    result3.printMatrix();

	return 0;
}