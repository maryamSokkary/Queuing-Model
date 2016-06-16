#include <bits/stdc++.h>

using namespace std;

struct Customer {
	float arrival;
	float departure;
	float serviceTime;
	float serviceStartTime;
	float clock;
};

int completed;
vector <Customer> q;
vector < pair <Customer, bool> > FEL;
float totalFlowTime;
float totalWaitingTime;
float lamda1;
float lamda2;
vector <float> servers;
int numOfServers;

ostream& operator<< (ostream& out, Customer c){
	out << "arrival :" << c.arrival << endl <<  "service time: " << c.serviceTime << endl << "Start Time: " <<
			c.serviceStartTime << endl << "departure: " << c.departure << endl;
	out << "Clock: " << c.clock << endl;
	return out;
}


double expo (float lamda){
	 double U =((double)rand()/(double)RAND_MAX); // an uniform distribution U
	return  log (1.0 - U )/(-1*lamda); // this is an exponential distribution

	 //x = log(1-u)/(−λ)
}

bool bla (pair <Customer, bool> a, pair <Customer, bool> b){
	return a.first.clock< b.first.clock;
}

bool cmp (Customer a, Customer b){
	return a.clock < b.clock;
}



void arrival (float Time){

	Customer c;
	c.arrival = Time;
	c.serviceTime = expo (lamda2);
	c.serviceStartTime = max (c.arrival, servers[0]);
	c.departure = c.serviceStartTime + c.serviceTime ;
	c.clock = c.departure;


	if (c.serviceStartTime > c.arrival)
		q.push_back(c);


	else {
		servers[0] = c.departure;
		totalFlowTime += c.departure - c.arrival;
		sort (servers.begin(), servers.end());
	}

	FEL.push_back(make_pair (c, 1));
	double nextCustomer = expo (lamda1);
	c.arrival = c.arrival + nextCustomer;
	c.clock = c.arrival;
	FEL.push_back(make_pair (c, 0));
	sort (q.begin(), q.end(), cmp);
	sort (FEL.begin(), FEL.end(), bla);

}


void depature (){

	++completed;
	if (q.empty()){
		sort(servers.begin(), servers.end());
	}
	else {
		Customer c = q.front();
		q.erase(q.begin() + 0);
		totalFlowTime+= c.departure - c.arrival;
		totalWaitingTime+= c.serviceStartTime - c.arrival;
		servers[0] = c.departure;
		c.clock = c.departure;
		FEL.push_back (make_pair (c, 1));
		sort (servers.begin(), servers.end());
	}
}

void initialize (float l1, float l2, int numServers){
	completed = 0;
	totalFlowTime = 0;
	totalWaitingTime = 0;
	numOfServers = numServers;
	lamda1 = l1;
	lamda2 = l2;
	servers.clear();
	for (int i = 0; i < numServers; i++)
		servers.push_back (0);
}

int main (){

	numOfServers = 2;

	initialize (2.5, 2, numOfServers);
	Customer c;
	c.arrival = 0;
	FEL.push_back(make_pair (c, 0));
	while (completed!= 1000){

		pair <Customer, bool> p = FEL[0];
		FEL.erase(FEL.begin() + 0);

		if (p.second == 0)
			arrival(p.first.arrival);
		else
			depature();


		sort (q.begin(), q.end(), cmp);
		sort (FEL.begin(), FEL.end(), bla);

	}

	cout << "Case 1 " << endl;
	cout << "Total waiting Time" << endl << totalWaitingTime/1000.0 << endl;
	cout << endl;

	initialize (2.5, 3.25, numOfServers);
	c.arrival = 0;
	FEL.push_back(make_pair (c, 0));
	while (completed!= 1000){

		pair <Customer, bool> p = FEL[0];
		FEL.erase(FEL.begin() + 0);
		sort (servers.begin(), servers.end());

		if (p.second == 0)
			arrival(p.first.arrival);
		else
			depature();


		sort (q.begin(), q.end(), cmp);
		sort (FEL.begin(), FEL.end(), bla);
		sort (servers.begin(), servers.end());

	}

	cout << "Case 2 " << endl;
	cout << "Total waiting Time" << endl << totalWaitingTime/1000.0 << endl;
	cout << endl;


}


