/*
 * Scheduler.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: KevinBeshears
 */

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "BinaryHeap.h"
//#include "LeftistHeap.h"
#include "Processor.h"
#include "Job.h"
using namespace std;

bool e;
bool n;
string userInput;
int job_id;
int ticks;
int NUM_PROC = 10;
BinaryHeap2<Job> waitQueue;
//LeftistHeap<Job> waitQueue;
vector<Processor> processorFreePool;
//BinaryHeap2<Job> runQueue;
list<Job> runQueue;

void releaseProcs(Job j){
	vector<Processor> pv = j.freeProc();

	for(int i = 0; i < pv.size(); ++i){
		processorFreePool.push_back(pv[i]);
	}
	return;
}

void decrementTimer(){
	auto iter = runQueue.begin();
	auto iter2 = runQueue.end();
	for(;*iter != *iter2; ++iter){
		Job &j = *iter;
		j.decrementCountDown();
		if(j.getCountDown() < 1){
			releaseProcs(j);
			cout << "Job " << j.getJobID() << " finished. Report:" << endl;
			cout << j << endl;
			runQueue.erase(iter);
		}
	}
	return;
}

void findDelShortest(){
	if((!waitQueue.isEmpty()) && waitQueue.findMin().getNProcs() <= processorFreePool.size()){
		Job temp = waitQueue.findMin();
		waitQueue.deleteMin();
		Job &j = temp;
		for(int i = 0; i < j.getNProcs(); ++i){
			j.assignProc(processorFreePool.back());
			processorFreePool.pop_back();
		}
		runQueue.push_back(j);
	}
	return;
}

void insertJob(string job_description, int n_procs, int n_ticks){

	if(n_ticks < 1){
		cout << "Insertion of job failed. The number of ticks needed to finish the job needs to be greater than 0" << endl;
		return;
	}
	else if(n_procs > 10){
		cout << "Insertion of job failed. The number of processes required for job needs to be less than " << NUM_PROC << endl;
		return;
	}

	Job job(job_description, n_procs, n_ticks, job_id);

	waitQueue.insert(job);

	return;
}

void SubmitJob(){
	cout << endl << "Would you like to submit a new job?(y for yes, n for no, or exit to quit program)" << endl;
	cin >> userInput;
	if(userInput == "y"){
		string job_description;
		int n_procs;
		int n_ticks;

		cout << "What is the name of the job?" << endl;
		cin >> job_description;

		cout << "How many processes will this job take?" << endl;
		cin >> n_procs;

		cout << "How many ticks will this job take?" << endl;
		cin >> n_ticks;

		++job_id;

		insertJob(job_description, n_procs, n_ticks);
		return;
	}
	else if(userInput == "n"){
		n = true;
		return;
	}
	else if(userInput == "exit"){
		e = true;
		n = true;
		return;
	}

	return;

}

void tick(){
	cout << endl << "BEGIN OF NEW TICK" << endl;
	n = false;
	cout << "There have currently been " << ticks << " tick(s)" << endl << endl;

    cout << "The current status of the wait queue is:" << endl;
	waitQueue.print();

	cout << endl << "The current status of the run queue is:" << endl;
	if(runQueue.empty()){
		cout << "The run queue is currently empty" << endl;
	}
	else{
		auto iter = runQueue.begin();
		auto iter2 = runQueue.end();
		for(;*iter != *iter2; ++iter){
			cout << *iter << endl;
		}
	}

	cout << endl << "The current status of the processor free pool is:" << endl;
	if(processorFreePool.empty()){
		cout << "The processor free pool is currently empty" << endl;
	}
	else{
		for(int i = 0; i < processorFreePool.size(); ++i){
			cout << processorFreePool[i] << endl;
		}
	}

	int curJob = job_id;

	while (n == false){
		SubmitJob();
	}

	if(!runQueue.empty()){
		decrementTimer();
	}

	findDelShortest();

	if(curJob != job_id){
		cout << "Jobs inserted at this tick were jobs: " << endl;
		for(int i = curJob + 1; i <= job_id; ++i){
			cout << "Job " << i << endl;
		}
	}

	++ticks;
	return;
}

int main(){

	e = false;
	for(int i = 0; i < NUM_PROC; ++i){
		Processor *p = new Processor(i);
		processorFreePool.push_back(*p);
	}

	while(e == false){
		tick();
	}


} /* namespace std */

//wait queue: needs to run the shortest time first scheduling algorithm, holds jobs that have been submitted but arent running
//run queue: jobs that are currently running
//free pool: free pool where processors that arent being used reside
