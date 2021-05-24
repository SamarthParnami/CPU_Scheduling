#include<bits/stdc++.h>
using namespace std;
//cout<<"Developed By Samarth Parnami"<<endl;
static int identity=1;


template<typename var>
void swaping(var &a,var &b)
{
	var temp=a;
	a=b;
	b=temp;
}

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
public:
	int id;
	float burstTime;
	float arrivalTime;
	Process()
	{

	}
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

class ProcessQueue
{
public:
	vector<Process> job;
	unordered_map<int,int> map;
	ProcessQueue():job(0)
	{
		
	}
	ProcessQueue(vector<Process> p)
	{
		job=p;
		for(int i=0;i<job.size();i++)
		{
			map[job[i].id]=i;
		}
		buildMinHeap();		
	}
	void buildMinHeap()
	{
		for(int i=job.size()/2-1;i>=0;i--)
		{
			min_heapify(i);
		}
	}
	void min_heapify(int index)
	{
		//cout<<index<<endl;
		int left=index*2+1;
		int right=index*2+2;
		if(left<job.size()&&right<job.size())
		{
			if(job[left].burstTime<job[right].burstTime||(job[left].burstTime==job[right].burstTime&&job[left].arrivalTime<=job[right].arrivalTime))
			{
				if(job[index].burstTime>job[left].burstTime)
				{
					swaping(job[left],job[index]);
					int temp=map[job[left].id];
					map[job[left].id]=map[job[index].id];
					map[job[index].id]=temp;
					min_heapify(left);
				}
				else if(job[index].burstTime==job[left].burstTime)
				{
					if(job[index].arrivalTime>job[left].arrivalTime)
					{
						swaping(job[left],job[index]);
						int temp=map[job[left].id];
					map[job[left].id]=map[job[index].id];
					map[job[index].id]=temp;
						min_heapify(left);
					}
				}
			}
			else if(job[left].burstTime>job[right].burstTime||(job[left].burstTime==job[right].burstTime&&job[left].arrivalTime>job[right].arrivalTime))
			{
				if(job[index].burstTime>job[right].burstTime)
				{
					swaping(job[right],job[index]);
					int temp=map[job[right].id];
					map[job[right].id]=map[job[index].id];
					map[job[index].id]=temp;
					min_heapify(right);
				}
				else if(job[index].burstTime==job[right].burstTime)
				{
					if(job[index].arrivalTime>job[right].arrivalTime)
					{
						swaping(job[right],job[index]);
						int temp=map[job[right].id];
						map[job[right].id]=map[job[index].id];
						map[job[index].id]=temp;
						min_heapify(right);
					}
				}
			}

		}
		else if(left<job.size())
		{
			if(job[index].burstTime>job[left].burstTime||((job[left].burstTime==job[index].burstTime&&job[left].arrivalTime<=job[index].arrivalTime)))
			{
				swaping(job[index],job[left]);
				int temp=map[job[left].id];
					map[job[left].id]=map[job[index].id];
					map[job[index].id]=temp;
				min_heapify(left);
			}
		}
	}
	Process extractRoot()
	{
		Process ans=job[0];
		job[0]=job[job.size()-1];
		job.erase(job.end()-1);
		min_heapify(0);
		return ans;
	}
	Process top()
	{
		return job[0];
	}
	void insert(Process a)
	{
		job.push_back(a);
		buildMinHeap();
	}
	bool isEmpty()
	{
		return job.size()==0?true:false;
	}
	void updateBurst(int id ,float to)
	{
		int index=map[id];
		job[index].burstTime=to;
		min_heapify(index);
	}
};







class PSJF
{
public:
	vector<Process> job;
	vector<vector<float>> startTime;
	vector<vector<float>> endTime;
	int time;
	PSJF(vector<Process> p):startTime(p.size()),endTime(p.size())
	{
		job=p;
		time=job[0].arrivalTime;
		processTime();		
	}
	void processTime()
	{
		//cout<<"Entering processTime"<<endl;
		vector<Process> p=job;
		ProcessQueue que;
		//cout<<time<<endl;
		while(p.size()>0)
		{
			Process on;
			if(!que.isEmpty())
			{
				//cout<<"NoN Empty Queue"<<endl;
				on=que.extractRoot();
			}
			else
			{
				//cout<<"Empty Queue"<<endl;
				time=p[0].arrivalTime;
				//cout<<p[0]<<endl;
				while(p.size()>0&&p[0].arrivalTime<=time)
				{
					que.insert(p[0]);
					p.erase(p.begin());
				}
				continue;
			}
			//cout<<on<<endl;
			float greater=on.arrivalTime>time?on.arrivalTime:time;
			startTime[on.id-1].push_back(greater);
			while(p.size()>0)
			{
				if(p[0].arrivalTime<=greater+on.burstTime)
				{
					time=p[0].arrivalTime;
					if(p[0].burstTime<on.burstTime-(time-greater))
					{
						//cout<<"NEW BTIME= "<<on.burstTime-(time-greater)<<endl;
						que.insert(p[0]);
						p.erase(p.begin());
						on.burstTime-=(time-greater);
						que.insert(on);
						endTime[on.id-1].push_back(time);
						break;
					}
					else
					{
						que.insert(p[0]);
						p.erase(p.begin());
					}
					
				}
				else
				{
					endTime[on.id-1].push_back(greater+on.burstTime);
					time=greater+on.burstTime;
					break;
				}
			}
			if(startTime[on.id-1].size()>endTime[on.id-1].size())
			{
				time=greater+on.burstTime;
				endTime[on.id-1].push_back(time);
			}

		}
		while(!que.isEmpty())
		{
			Process on=que.extractRoot();
			float greater=on.arrivalTime>time?on.arrivalTime:time; 
			startTime[on.id-1].push_back(greater);
			time=greater+on.burstTime;
			endTime[on.id-1].push_back(time);
		}

		//cout<<"Exiting processTime"<<endl;		
	}
	void sendNewJob(vector<Process> p)
	{
		//cout<<"Entering sendNewJob vector"<<endl;
		job.insert(job.end(),p.begin(), p.end());
		time=job[0].arrivalTime;
		startTime.clear();
		startTime.resize(job.size());
		endTime.clear();
		endTime.resize(job.size());
		processTime();
		//cout<<"Exiting sendNewJob vector "<<endl;	
		
	}
	void sendNewJob(Process p)
	{
		//cout<<"Entering sendNewJob object."<<endl;
		job.push_back(p);
		//cout<<"Exiting sendNewJob object."<<endl;	
		sendNewJob({p});
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
		cout<<"Entering waiting time"<<endl;
		vector<vector<float>> e=endTime;
		e.insert(e.begin(),vector<float>(1,0));
		vector<float> ans(job.size(),0);
		for(int i=0;i<startTime.size();i++)
		{
			for(int j=0;j<startTime[i].size();j++)
			{
				ans[i]+=(startTime[i][j]-e[i][j]);
			}
		}
		cout<<"Exiting waiting time"<<endl;	
		
		return ans;
	}
	vector<float> turnaroundTime()
	{
		cout<<"Entering turnaroundTime"<<endl;
		vector<float> ans(job.size(),0);
		for(int i=0;i<job.size();i++)
		{
			ans[i]=(*(endTime[i].end()-1)-startTime[i][0]);
		}
		cout<<"Exiting turnaroundTime"<<endl;	
		
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
    /*Process p1(0,5,1),p2(2,6,2),p3(4,2,3),p4(9,4,4),p5(10,2,5);
    PSJF obj({p1,p2,p3,p4,p5});
    vector<vector<float>> start=obj.startTime;
    printMatrix(start);*/
    //printHandle({p1,p2,p3,p4,p5},obj.startTime,obj.endTime);
     PSJF* obj=nullptr;

    while(cin>>input)
    {
     	input=toLower(input);
     	
		if(input=="addjobs"||input=="addjob"||input=="add job"||input=="add jobs")
		{

			vector<Process> p=handle();
			if(obj)
			{
				obj->sendNewJob(p);
			}
			else
			{
				obj=new PSJF(p);
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
}