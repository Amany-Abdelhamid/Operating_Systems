#include<iostream>
#include"list.h"
#include<math.h>
#include<string>
using namespace std;

void FCFS(){
	list  bt, wt;
	int n, x, i, j; float  avwt = 0;
	cout << "Enter number of processes:";
	cin >> n;

	cout << "\nEnter Process Burst Time\n";
	for (i = 0; i < n; i++)
	{
		cout << "P[" << i + 1 << "]:";
		cin >> x;
		bt.add(x);
	}

	wt.add(0);    //waiting time for first process is 0

	//calculating waiting time
	for (i = 1; i < n; i++)
	{
		x = 0;
		for (j = 1; j < i + 1; j++)
			x += bt.getNodeData(j);
		wt.add(x);
	}

	cout << "\nProcess\t\tBurst Time\tWaiting Time";

	for (i = 0; i < n; i++)
	{
		cout << "\nP[" << i + 1 << "]" << "\t\t" << bt.getNodeData(i + 1) << "\t\t" << wt.getNodeData(i + 1);
	}

	avwt = (float)wt.sum() / i;

	cout << "\n\nAverage Waiting Time:" << avwt << "\n";

	cout << "\nGantt Chart:\n\n";
	cout << "\t( 0 )\t";
	for (i = 0; i < n - 1; i++)
	{
		cout << "P[" << i + 1 << "]" << "\t( " << wt.getNodeData(i + 2) << " )\t";
	}
	cout << "P[" << i + 1 << "]" << "\t( " << bt.sum() << " )\t" << "\n";


};
void NSJF(){
	list bt, p, wt;int i, j, n, pos, temp,x; float avwt = 0;
	cout<<"Enter number of process:";
	cin >> n;

	cout << "\nEnter Burst Time:\n";
	for (i = 0; i<n; i++)
	{
		cout << "P[" << i + 1 << "]:";
		cin >> x;
		bt.add(x);
		p.add(i + 1);           //contains process number
	}

	//sorting burst time in ascending order using selection sort
	for (i = 0; i<n; i++)
	{
		pos = i;
		for (j = i + 1; j<n; j++)
		{
			if (bt.getNodeData(j+1)<bt.getNodeData(pos+1))
				pos = j;
		}

		temp = bt.getNodeData(i+1);
		bt.getNode(i + 1)->setData(bt.getNodeData(pos+1));
		bt.getNode(pos + 1)->setData(temp);

		temp = p.getNodeData(i + 1);
		p.getNode(i + 1)->setData(p.getNodeData(pos + 1));
		p.getNode(pos + 1)->setData(temp);
	}

	wt.add(0);            //waiting time for first process will be zero

	//calculate waiting time
	for (i = 1; i < n; i++)
	{
		x = 0;
		for (j = 1; j < i + 1; j++)
			x += bt.getNodeData(j);
		wt.add(x);
	}
	cout << "\nProcess\t    Burst Time    \tWaiting Time\t";
	for (i = 0; i < n; i++)
	{
		cout << "\nP[" << p.getNodeData(i+1) << "]" << "\t\t" << bt.getNodeData(i + 1) << "\t\t" << wt.getNodeData(i + 1);
	}
	avwt = (float)wt.sum()/ n;      //average waiting time
	
	cout << "\n\nAverage Waiting Time= " << avwt << endl;

	cout << "\nGantt Chart:\n\n";
	cout << "\t( 0 )\t";
	for (i = 0; i < n - 1; i++)
	{
		cout << "P[" << p.getNodeData(i+1) << "]" << "\t( " << wt.getNodeData(i + 2) << " )\t";
	}
	cout << "P[" << p.getNodeData(i + 1) << "]" << "\t( " << bt.sum() << " )\t" << "\n";


};
void NPRIO(){
	list bt, p, wt, pr; int i, j, n,x,y, pos, temp; float avwt = 0;
	cout << "Enter Total Number of Process:";
	cin >> n;

	cout << "\nEnter Burst Time and Priority\n";
	for (i = 0; i<n; i++)
	{
		cout << "\nP[" << i + 1 << "] : \t";
		cout << "Burst Time =";
		cin >> x;
		bt.add(x);
		cout << "\tPriority =";
		cin >> y;
		pr.add(y);
		p.add( i + 1);           //contains process number
	}

	//sorting burst time, priority and process number in ascending order using selection sort
	for (i = 0; i<n; i++)
	{
		pos = i;
		for (j = i + 1; j<n; j++)
		{
			if (pr.getNodeData(j + 1)<pr.getNodeData(pos + 1))
				pos = j;
		}

		temp = pr.getNodeData(i + 1);
		pr.getNode(i + 1)->setData(pr.getNodeData(pos + 1));
		pr.getNode(pos + 1)->setData(temp);

		temp = bt.getNodeData(i + 1);
		bt.getNode(i + 1)->setData(bt.getNodeData(pos + 1));
		bt.getNode(pos + 1)->setData(temp);

		temp = p.getNodeData(i + 1);
		p.getNode(i + 1)->setData(p.getNodeData(pos + 1));
		p.getNode(pos + 1)->setData(temp);
	}

	wt.add(0) ;            //waiting time for first process is zero

	//calculate waiting time
	for (i = 1; i < n; i++)
	{
		x = 0;
		for (j = 1; j < i + 1; j++)
			x += bt.getNodeData(j);
		wt.add(x);
	}

	avwt = (float)wt.sum()/ n;      //average waiting time

	cout << "\nProcess\t    Burst Time    \tWaiting Time\tPriority Time";
	for (i = 0; i < n; i++)
	{
		cout << "\nP[" << p.getNodeData(i + 1) << "]" << "\t\t" << bt.getNodeData(i + 1) << "\t\t" << wt.getNodeData(i + 1) << "\t\t" << pr.getNodeData(i + 1);
	}

	cout << "\n\nAverage Waiting Time=" << avwt;

	cout << "\n\nGantt Chart:\n\n";
	cout << "\t( 0 )\t";
	for (i = 0; i < n - 1; i++)
	{
		cout << "P[" << p.getNodeData(i + 1) << "]" << "\t( " << wt.getNodeData(i + 2) << " )\t";
	}
	cout << "P[" << p.getNodeData(i + 1) << "]" << "\t( " << bt.sum() << " )\t" << "\n";
};
void RR(){
	list bt, p,bt2,p2, wt; int q,i, j, n, x,max; float avwt = 0;
	cout << "Enter number of process:";
	cin >> n;

	cout << "\nEnter Quantum Time: ";
	cin >> q;
	cout << "\nEnter Burst Time:\n";
	for (i = 0; i<n; i++)
	{
		cout << "P[" << i + 1 << "]:";
		cin >> x;
		bt.add(x);
		p.add(i + 1);           //contains process number
	}
	max = bt.max();
	//dividing processes burst time according to Quantum Time
	for (j = 0; j < ceil(max / q)+1; j++)
	{
		for (i = 0; i < n; i++)
		{
			//if (bt.getNodeData(i + 1) == 0){ }
			if (bt.getNodeData(i + 1) < q && bt.getNodeData(i + 1) > 0)
			{
				bt2.add(bt.getNodeData(i + 1));
				p2.add(p.getNodeData(i + 1));
				bt.getNode(i + 1)->setData(0);
			}
			else if (bt.getNodeData(i + 1) >= q)
			{
				bt2.add(q);
				p2.add(p.getNodeData(i + 1));
				bt.getNode(i + 1)->setData(bt.getNodeData(i + 1) - q);
			}
		}
	}
	wt.add(0);            //waiting time for first process will be zero

	//calculate waiting time fpr drawing gantt chart
	for (i = 1; i < (n+ceil(max/q)+1); i++)
	{
		x = 0;
		for (j = 1; j < i + 1; j++)
			x += bt2.getNodeData(j);
		wt.add(x);
	}
	
	//unfortunately ,no time to calc. average waiting time

	cout << "\nGantt Chart:\n\n";
	cout << "\t( 0 )\t";
	for (i = 0; i < (n + ceil(max / q)); i++)
	{
		cout << "P[" << p2.getNodeData(i + 1) << "]" << "\t( " << wt.getNodeData(i + 2) << " )\t";
	}
	cout << "P[" << p2.getNodeData(i + 1) << "]" << "\t( " << bt2.sum() << " )\t" << "\n";
};
int main()
{
	string sch;
	cout << "Enter The Scheduler Type: ";
	cin >> sch;
	if (sch == "FCFS")
		FCFS();
	else if (sch == "NSJF")
		NSJF();
	else if (sch == "NPRIO")
		NPRIO();
	else if (sch == "RR")
		RR();
	else
		cout << "Invalid Type" << endl;
	
	system("pause");
	return 0;
}

