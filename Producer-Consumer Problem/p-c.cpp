#include<bits/stdc++.h>
using namespace std;

typedef struct S
{
	int mutex;
	int empty;
	int full;

} semaphore;

int produce(int min=0,int max=INT_MAX)
{
	return (rand()%max)+min;
}
void insertInBuffer(semaphore &a, int item,queue<int> & buffer)
{
	
	a.empty--;
	buffer.push(item);
	a.full++;
	
}
int removeFromBuffer(semaphore &a,queue<int> & buffer)
{
	a.empty++;
	int item=buffer.front();
	buffer.pop();
	a.full--;
	return item;
}
void producer(semaphore &a,queue<int> &buffer)
{	
	int item=produce(1,10);
	while(true)
	{
		if(a.mutex==1)
		{
			
			if(a.empty!=0)
			{
				cout<<"Inserting item = "<<item<<endl;
				a.mutex=0;
				insertInBuffer(a,item,buffer);
				a.mutex=1;
			}
			else
			{
				cout<<"Buffer overflow."<<endl;
			}
			return;
			
		}
	}
}
int consumer(semaphore &a,queue<int> &buffer)
{
	int item=0;
	while(true)
	{
		if(a.mutex==1)
		{
			
			if(a.full>0)
			{
				a.mutex=0;
				item=removeFromBuffer(a,buffer);
				a.mutex=1;
			}
			else
			{
				cout<<"Buffer underflow.";
			}
			
			return item;
		}
		
	}
}
int main()
{
	srand(time(0));
	//reduce the runtime of th program
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);


	// for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    int bSize;
    cin>>bSize;
    semaphore a={1,bSize,0};
    queue<int> buffer;
    producer(a,buffer);
    producer(a,buffer);
    producer(a,buffer);
    producer(a,buffer);
    producer(a,buffer);
    producer(a,buffer);
   cout<<consumer(a,buffer)<<endl;
   cout<<consumer(a,buffer)<<endl;
   cout<<consumer(a,buffer)<<endl;
   cout<<consumer(a,buffer)<<endl;
   cout<<consumer(a,buffer)<<endl;
   cout<<consumer(a,buffer)<<endl;
	
	
	return 0;
}