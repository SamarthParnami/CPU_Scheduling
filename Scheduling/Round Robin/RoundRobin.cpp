#include<bits/stdc++.h>
using namespace std;
//cout<<"Developed By Samarth Parnami"<<endl;
static int identity=1;
template<typename var>
void printVector(vector<var> a)
{
	for(int i=0;i<a.size();i++)
	{
		cout<<a[i]<<" ";
	}cout<<endl;
}
template<typename var>
void printVectorOfVector(vector<vector<var>> a)
{
	for(int i=0;i<a.size();i++)
	{
		printVector(a[i]);
	}
}
template<typename var>
void printMatrix(vector<vector<var>> m)
{
	for(int i=0;i<m.size();i++)
	{
		printVector(m[i]);	
	}
	
}
template<typename var>
var vectorSum(vector<var> a)
{
	var sum=0;
	for(int i=0;i<a.size();i++)
	{
		sum+=a[i];
	}
	return sum;
}
class Process
{
	//cout<<"Developed By Samarth Parnami"<<endl;
public:
	int id;
	float burstTime;
	float arrivalTime;
	
	Process(float aT,float bT,int id)
	{
		this->burstTime=bT;
		this->arrivalTime=aT;
		this->id=id;
	}
	void updateBurst(float bT)
	{
		this->burstTime=bT;
	}
	friend ostream& operator<<(ostream& out,Process p)
	 {
	 	
	 	out<<"id="<<p.id<<" at="<<p.arrivalTime<<" bt="<<p.burstTime;
	 	return out; 
	 }
	 bool operator==(Process b)
	 {
	 	return id==b.id?true:false;
	 }
	 bool operator!=(Process b)
	 {
	 	return *this==b?false:true;
	 }
};
class RoundRobin
{
	//cout<<"Developed By Samarth Parnami"<<endl;
public:
	float quantum;
	vector<Process> job;
	vector<vector<float>> startTime;
	vector<vector<float>> endTime;
	float defaultTime;
	RoundRobin(vector<Process> j,float quantum,float start=0):startTime(j.size()),endTime(j.size())
	{
		job=j;
		this->quantum=quantum;
		defaultTime=start;
		processTime();
	}
	void processTime()
	{
		//cout<<"enter processTime"<<endl;
		//cout<<"Developed By Samarth Parnami"<<endl;
		vector<Process> p=job;
		float time=defaultTime;
		while(p.size()>0)
		{
			for(int i=0;i<p.size();i++)
			{
				
				time=p[i].arrivalTime<time?time:p[i].arrivalTime;
				//cout<<time<<endl;
				startTime[p[i].id-1].push_back(time);
				if(p[i].burstTime<=quantum)
				{
					time+=p[i].burstTime;
					endTime[p[i].id-1].push_back(time);
					p[i].burstTime=0;					
					p.erase(p.begin()+i);
					i--;
				}
				else	
				{
					time+=quantum;
					endTime[p[i].id-1].push_back(time);
					p[i].burstTime-=quantum;
				}
				if(time<=p[i+1].arrivalTime)
				{
					break;
				}
			}
		}
		
		//cout<<"exit processTime"<<endl;
	}
	void sendNewJob(vector<Process> p)
	{
		//cout<<"Entering sendNewJob vector"<<endl;
		job.insert(job.end(),p.begin(), p.end());
		startTime.clear();
		startTime.resize(job.size());
		endTime.clear();
		endTime.resize(job.size());
		processTime();
		//cout<<"Exiting sendNewJob vector "<<endl;	
		
	}
	vector<float> getstartTime()
	{
		//cout<<"Entering getstartTime"<<endl;
		vector<float> ans(job.size());
		for(int i=0;i<job.size();i++)
		{
			ans[i]=startTime[i][0];
		}
		//cout<<"Exiting getstartTime"<<endl;	
		return ans;
	}
	vector<float> getendTime()
	{
		
		//cout<<"Entering getendTime"<<endl;
		vector<float> ans(job.size());
		for(int i=0;i<job.size();i++)
		{
			//cout<<endTime[i].size()-1<<" ";
			ans[i]=(endTime[i][endTime[i].size()-1]);
		}
		//cout<<"\nExiting getendTime"<<endl;	
		return ans;
	}
	vector<float> waitingTime()
	{
		//cout<<"Entering waiting time"<<endl;
		vector<vector<float>> e=endTime;
		for(int i=0;i<job.size();i++)
		{
			e[i].insert(e[i].begin(),job[i].arrivalTime);
		}
		
		vector<float> ans(job.size(),0);
		for(int i=0;i<startTime.size();i++)
		{
			for(int j=0;j<startTime[i].size();j++)
			{
				ans[i]+=(startTime[i][j]-e[i][j]);
			}
		}
		//cout<<"Exiting waiting time"<<endl;	
		
		return ans;
	}
	vector<float> turnaroundTime()
	{
		//cout<<"Entering turnaroundTime"<<endl;
		vector<float> ans(job.size(),0);
		for(int i=0;i<job.size();i++)
		{
			ans[i]=(*(endTime[i].end()-1)-job[i].arrivalTime);
		}
		//cout<<"Exiting turnaroundTime"<<endl;	
		
		return ans;
	}
};


void printHandle(vector<Process> p,vector<float> start,vector<float> end)
{
	
	cout<<"No. of job(s):"<<p.size()<<endl;
	
	cout<<"Sr No.\t\tArrival Time(s)\t\tBurst Time(s)\t\tStart\t\tEnd"<<endl;
	
		   // .........|.........|.........|.........|.........|
	for(int i=0;i<p.size();i++)
	{
		cout<<setfill('0')<<setw(2)<<p[i].id;
		cout<<setfill(' ')<<setw(18)<<p[i].arrivalTime;
		cout<<setfill(' ')<<setw(18)<<p[i].burstTime;
		cout<<setfill(' ')<<setw(19)<<start[i];
		cout<<setfill(' ')<<setw(10)<<end[i]<<endl;
	}
	//cout<<"exitingprinthandle"<<endl;
}
vector<Process> handle()
{
	vector<Process> ans;
	int count;
	//cout<<"handle"<<endl;
	cin>>count;
	
	for(int i=0;i<count;i++)
	{
		
		float aT;
		cin>>aT;
		float bT;
		cin>>bT;
		ans.push_back(Process(aT,bT,identity++));
	}
	//cout<<"exitinghandle"<<endl;
	return ans;
}
string toLower(string a)
{
	for(int i=0;i<a.length();i++)
	{
		if(a[i]>='A'&&a[i]<='Z')
		{
			a[i]=(char)(a[i]-('A'-'a'));
		}
	}
	return a;
}

int main()
{
	//reduce the runtime of th program
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);


	// for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
   // printHandle();

	string input;

    //cout<<"Developed By Samarth Parnami"<<endl;
    
    float quantum;
    cin>>quantum;
     RoundRobin* obj=nullptr;

    while(cin>>input)
    {
     	input=toLower(input);
     	
		if(input=="addjobs"||input=="addjob"||input=="add job"||input=="add jobs")
		{
			//cout<<"addjob"<<endl;

			vector<Process> p=handle();
			if(obj)
			{
				obj->sendNewJob(p);
			}
			else
			{
				obj=new RoundRobin(p,quantum);
			}

			printHandle(obj->job,obj->getstartTime(),obj->getendTime());		
		}
		else if(input=="waiting")
		{
			vector<float> wait=obj->waitingTime();
			cout<<"\nAverage Waiting Time: "<<vectorSum(wait)/wait.size()<<endl;
			cout<<"Job Waiting times: ";
			printVector(wait);
			cout<<endl;
		} 
		else if(input=="turnaround")
		{
			vector<float> turn=obj->turnaroundTime();
			cout<<"\nAverage Turnaround Time: "<<vectorSum(turn)/turn.size()<<endl;
			cout<<"Job Turnaround times: ";
			printVector(turn);
			cout<<endl;
		}
		else if(input=="exit")
		{
			break;
		} 
		else if(input=="start")
		{
			vector<float> start=obj->getstartTime();
			cout<<"Starting Time: ";
			printVector(start);
		}
		else if (input=="end")
		{
			vector<float> end=obj->getendTime();
			cout<<"Ending Time: ";
			printVector(end);
		}
		else if(input=="help")
		{
			cout<<"addjob - add new processes to schedule.\nend - to get endtimes of the processes.\nexit - to close the program.\nstart - to get starttimes of the processes.\nturnaround - to get turnaround time of the processes.\nwaiting - to get waiting times of the processes.\n"<<endl;
		}
		else 
		{
			cout<<"Type help to get all commands\n";
		} 
		  		

    }
    return 0;
    //cout<<"Developed By Samarth Parnami"<<endl;
}