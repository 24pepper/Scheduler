/*
 * Job.h
 *
 *  Created on: Feb 25, 2018
 *      Author: KevinBeshears
 */

#ifndef JOB_H_
#define JOB_H_

#include <string>
#include <iostream>
#include <vector>
#include "Processor.h"

using namespace std;

class Job
{
  public:

	Job(){
		job_description = "NULL";
		n_procs = 0;
		n_ticks = 0;
		job_id = 0;
		count_down = 0;
	}

	Job(string j, int p, int t, int i) {
		job_description = j;
		n_procs = p;
		n_ticks = t;
		job_id = i;
		count_down = t;
	}

    const string & getDescription( ) const
      { return job_description; }

    void setDescription( ){
//    		cout << "set description called, setting root to NULL" << endl;
    		job_description = "NULL";
    }

    const int & getNProcs( ) const
      { return n_procs; }

    const int & getNTics( ) const
      { return n_ticks; }

    const int & getJobID( ) const
      { return job_id; }

    const int & getCountDown( ) const
      { return count_down; }

    void decrementCountDown( )
      { --count_down; }

    void assignProc(Processor p){
    		listOfProc.push_back(p);
    }

    vector<Processor> freeProc(){
    		vector<Processor> tempVec = listOfProc;
    		listOfProc.clear();
    		return tempVec;
    }

    const vector<Processor> & getProc() const{
    		return listOfProc;
    }

    void print(){
    		for(int i = 0; i < listOfProc.size(); ++i){
    			cout << listOfProc[i] << endl;
    		}
    }

    bool operator==( const Job & rhs ) const
      { return getDescription( ) == rhs.getDescription( ); }
    bool operator!=( const Job & rhs ) const
      { return !( *this == rhs ); }
    bool operator >( const Job & rhs ) const
      { return ( getNTics() > rhs.getNTics() ); }
    bool operator <( const Job & rhs ) const
      { return ( getNTics() < rhs.getNTics() ); }
    Job operator =( const Job & rhs ){
    	    job_description = rhs.getDescription();
    	    n_procs = rhs.getNProcs();
    	    n_ticks = rhs.getNTics();
    	    job_id = rhs.getJobID();
    	    count_down = rhs.getCountDown();
    	    listOfProc = rhs.getProc();
    	    return (*this);
    }
    friend ostream &operator<<(ostream &stream, Job j){
    		stream<<j.getDescription() << "\n-------------\n";
    		stream<<"Job ID: " << j.getJobID() << endl;
    		stream<<"Job Procs: " << j.getNProcs() << endl;
    		stream<<"Job Ticks: " << j.getNTics() << "\n-------------\n";
    		return stream;
    }


  private:
	string job_description;
	int n_procs;
	int n_ticks;
	int job_id;
	int count_down;
	vector<Processor> listOfProc;

};


#endif /* JOB_H_ */
