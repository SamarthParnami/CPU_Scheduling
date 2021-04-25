#include<bits/stdc++.h>
using namespace std;
template<typename var>
void printVector(vector<var> a)
{
	for(int i=0;i<a.size();i++)
	{
		cout<<a[i]<<" ";
	}cout<<endl;
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
};
class FCFS
{
	vector<Process> e;
	vector<float> startTime;
	vector<float> endTime;
public:
	 FCFS(vector<Process> p):startTime(),endTime()
	 {
	 	e=p;
	 	processTime(e[0].arrivalTime,0,e.size());
	 }
	 FCFS():e(),startTime(),endTime()
	 {
	 	//cout<<"exitingdefaultconstructor"<<endl;

	 }
	 void processTime(float start,int index,int length)
	 {
	 	
	 	for(int i=index;i<index+length;i++)
	 	{
	 		startTime.push_back(start);
	 		endTime.push_back(startTime[i]+e[i].burstTime);
	 		start+=e[i].burstTime;
	 	}
	 	//cout<<"exitingprocesstime"<<endl;
	 }

	 void sendNewJob(vector<Process> p)
	 {
	 	float newStart=p[0].arrivalTime>=*(endTime.end()-1)?p[0].arrivalTime:*(endTime.end()-1);
	 	int previousLength=e.size();
	 	e.insert(e.end(),p.begin(), p.end());
	 	
	 	processTime(newStart,previousLength,p.size());
	 	//cout<<"exitingsendnewjob"<<endl;
	 }
	 void sendNewJob(Process p)
	 {
	 	sendNewJob({p});
	 }
	 vector<float> waitingTime()
	 {
	 	vector<float> time;
	 	for(int i=0;i<startTime.size();i++)
	 	{
	 		time.push_back(startTime[i]-e[i].arrivalTime);
	 	}
	 	//cout<<"exitingwaitingtime"<<endl;
	 	return time;
	 }
	 vector<float> turnaroundTime()
	 {
	 	vector<float> time;
	 	for(int i=0;i<startTime.size();i++)
	 	{
	 		time.push_back(endTime[i]-e[i].arrivalTime);
	 	}
	 	//cout<<"exitingturnaroundtime"<<endl;
	 	return time;
	 }
	 vector<float> getstartTime()
	 {
	 	return startTime;
	 }
	 vector<float> getendTime()
	 {
	 	return endTime;
	 }
	 
	
};
void printHandle(vector<Process> p)
{
	
	cout<<"No. of job(s):"<<p.size()<<endl;
	
	cout<<"Sr No.	   Arrival Time(s) 	   Burst Time(s)\n";
		   // .........|.........|.........|.........|.........|
	for(int i=0;i<p.size();i++)
	{
		cout<<setfill('0')<<setw(2)<<i+1<<".		";
		cout<<setfill(' ')<<setw(10)<<p[i].arrivalTime<<setfill(' ')<<setw(17)<<p[i].burstTime<<endl;
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
		ans.push_back(Process(aT,bT,i));
	}
	printHandle(ans);
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
     string input;
     FCFS* obj=nullptr;
     
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
				obj=new FCFS(p);
			}
			
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
	
	//cout<<"end"<<endl;
	return 0;
}