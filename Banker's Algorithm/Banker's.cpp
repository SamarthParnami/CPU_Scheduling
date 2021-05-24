
#include<bits/stdc++.h>
using namespace std;
template<typename v>
vector<v> operator+(vector <v> a,vector<v> b)
{
	for(int i=0;i<a.size();i++)
	{
		a[i]=a[i]+b[i];
	}
	return a;
}
template<typename v>
vector<v> operator-(vector <v> a,vector<v> b)
{
	for(int i=0;i<a.size();i++)
	{
		a[i]=a[i]-b[i];
	}
	return a;
}
template<typename v>
ostream& operator <<(ostream& os,vector<v> a)
{
	os<<"[";
	for(int i=0;i<a.size()-1;i++)
	{
		os<<a[i]<<" ";
	}
	os<<(*(a.end()-1))<<"]";
	return os;
}
template<typename v>
istream& operator>>(istream& is,vector<v>&a)
{
	
	for(int i=0;i<a.size();i++)
	{
		is>>a[i];
	}
	return is;
}
template<typename v>
bool operator ==(vector<v> a, vector<v> b)
{
	if(a.size()!=b.size())
	{
		return false;
	}
	for(int i=0;i<a.size();i++)
	{
		if(a[i]!=b[i])
		{
			return false;
		}
	}
	return true;
}
template<typename v>
bool operator !=(vector<v> a, vector<v> b)
{
	
	return !(a==b);
}
template <typename v>
bool operator <(vector<v> a, vector<v> b)
{
	
	for(int i=0;i<a.size();i++)
	{
		if(b[i]<a[i])
		{
			return false;
		}
	}
	return true&&(a!=b);
}
template <typename v>
bool operator >(vector<v> a, vector<v> b)
{
	
	for(int i=0;i<a.size();i++)
	{
		if(a[i]<b[i])
		{
			return false;
		}
	}
	return true&&(a!=b);
}

template <typename v>
bool operator <=(vector<v> a, vector<v> b)
{
	return (a<b)||(a==b);
}
template <typename v>
bool operator >=(vector<v> a, vector<v> b)
{
	return (a>b)||(a==b);
}

class Process
{
public:
	int id;
	vector<int> alloc;
	vector<int> max;
	vector<int> need;
	Process(int id,vector<int> alloc,vector<int> max)
	{
		this->id=id;
		this->alloc=alloc;
		this->max=max;
		this->need=max-alloc;
		
	}
	friend ostream& operator<<(ostream &os,const Process p)
	{
		os<<"Id = "<<p.id<<endl;
		os<<"Max required ="<<p.max<<endl;
		os<<"Allocated ="<<p.alloc<<endl;
		os<<"Need      ="<<p.need<<endl;
		return os;
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
    int process;
    int resource;
    cin>>process;
    cin>>resource;

   	vector<int> available(resource); 
   
   	vector<vector<int>> maxReq(process,vector<int>(resource));
	vector<vector<int>> alloc(process,vector<int>(resource));
	queue<Process*> ready;
	queue<Process*> done;
	
	cin>>available;
	cin>>maxReq;
	cin>>alloc;
	for(int i=0;i<process;i++)
	{
		ready.push(new Process(i,alloc[i],maxReq[i]));
	}
	cout<<"I/O handled"<<endl;
	while(!ready.empty())
	{
		
		Process* p=ready.front();
		//cout<<(*p)<<endl;
		if((p->need)<=available)
		{
			available=available+p->alloc;
			done.push(p);
			ready.pop();			
		}
		else
		{
			
			ready.push(p);
			ready.pop();
		}
	}
	cout<<"Safe Sequence =";
	for(int i=0;i<process;i++)
	{
		cout<<(*done.front()).id<<" " ;
		done.pop();
	}
	cout<<endl;
	return 0;
}
