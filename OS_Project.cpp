#include<iostream>
#include<conio.h>
using namespace std;

void SearchStack01(int pnt,int tm);
void SearchStack02(int pnt, int tm);
void AddQue(int pnt);
int arrival_time[50], burst_time[50], completion_time[50]={0}, qt, rqi[50]={0}, c=0,n,st, flg=0, tm=0, noe=0, pnt=0, btm[50]={0}, tt, wt;
float att, awt;

int main()
{
	cout<<"\n\t\tHere Some Attrib use in program \n";
	cout<<"AT = Arrival Time \nBT = Burst Time\nCT = Completion Time\nTT = Turnaround Time\nWT = Waiting Time\n\n";
	cout<<"\t\t\tQuestion No.:- 16: \n";
	cout<<"ROUND ROBIN ALGO : INPUT NUMBER OF PROCESSES: ";
	cin>>n;
	for(int x=0;x<n;x++)
	{
		cout<<"\nProcess "<<x+1;
		cout<<"\nAT=";
		cin>>arrival_time[x];
		cout << "BT=";
		cin>>burst_time[x];
		btm[x]=burst_time[x];
	}
	cout<<"\nEnter time quantum:";
	cin>>qt;
	system("CLS");
	cout<<endl<<"GANTT CHART"<<endl<<arrival_time[0];
	do
	{
		if(flg==0)
		{
			st=arrival_time[0];
													//---ReduceBT
			if(btm[0]<=qt)
			{
				tm=st+btm[0];
				btm[0]=0;
				SearchStack01(pnt,tm);
			}
			else
			{
				btm[0]=btm[0]-qt;
				tm=st+qt;
				SearchStack01(pnt,tm);
				AddQue(pnt);
			}
		}
		else
		{
			pnt=rqi[0]-1;
			st=tm;
														//---DeleteQue
			for(int x=0;x<noe && noe!=1;x++)
			{
				rqi[x]=rqi[x+1];
			}
			noe--;
														//---ReduceBT
			if(btm[pnt]<=qt)
			{
				tm=st+btm[pnt];
				btm[pnt]=0;
				SearchStack02(pnt, tm);
			}
			else
			{
				btm[pnt]=btm[pnt]-qt;
				tm=st+qt;
				SearchStack02(pnt, tm);
				AddQue(pnt);
			}
		}
															// For AssignCTvalue
		if(btm[pnt]==0)
		{
			completion_time[pnt]=tm;
		}
		flg++;
		cout<<"]-P"<<pnt+1<<"-["<<tm;
	}
	while(noe!=0);
	cout<<"\n\nPROCESS\t AT\t BT\t CT\t TT\t WT\n";
	for(int x=0;x<n;x++)
	{
		tt=completion_time[x]-arrival_time[x];
		wt=tt-burst_time[x];
		cout<<"P"<<x+1<<" \t "<<arrival_time[x]<<" \t "<<burst_time[x]<<" \t "<<completion_time[x]<<" \t "<<tt<<" \t "<<wt<<"\n";
		awt=awt+wt;
		att=att+tt;
	}
	cout<<"\nAVERAGE TT: "<<att/n<<"\nAVERAGE WT: "<<awt/n;
}

void SearchStack01(int pnt,int tm)
{
	for(int x=pnt+1;x<n;x++)
	{
		if(arrival_time[x]<=tm){
		rqi[noe]=x+1;
		noe++;}
	}
}

void SearchStack02(int pnt, int tm)
{
	for(int x=pnt+1;x<n;x++)
	{
												//--- For CheckQue
		int fl=0;
		for(int y=0;y<noe;y++)
		{
			if(rqi[y]==x+1)
			{
				fl++;
			}
		}
		if(arrival_time[x]<=tm && fl==0 && btm[x]!=0)
		{
			rqi[noe]=x+1;
			noe++;}
		}
	}

void AddQue(int pnt)
{
	rqi[noe]=pnt+1;
	noe++;
}
