/*
 * BinaryHeap.h
 *
 *  Created on: Feb 25, 2018
 *      Author: KevinBeshears
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <vector>
#include <iostream>

using namespace std;

template <typename Comparable>
class BinaryHeap2
{
  public:
    explicit BinaryHeap2( ){
    		currentSize = 0;
    		array.resize(10);
    }

    explicit BinaryHeap2( const vector<Comparable> & items )
      : array( items.size( ) + 10 ), currentSize( items.size( ) )
    {
        for( int i = 0; i < items.size( ); i++ )
            array[ i + 1 ] = items[ i ];
        buildHeap( );
    }

    bool isEmpty( ) const{
    		//cout << "element in array is " << array[1] << endl;
    		if (array[1].getDescription() == "NULL"){
    			return true;
    		}
    		return false;
    		//return array[1] == NULL;
    }
    const Comparable & findMin( ) const{
    		return array[1];
    }

    void insert( const Comparable & x )
    {
        if( currentSize == array.size( ) - 1 )
            array.resize( array.size( ) * 2 );

            // Percolate up
        int hole = ++currentSize;
        for( ; hole > 1 && x < array[ hole / 2 ] && array[ hole / 2].getDescription() != "NULL"; hole /= 2 )  // while hole is greater(hole being the position of the whole) than 1 and x(value we are inserting) is less than array indexed at hole / 2(its connected neighbor above)
            array[ hole ] = array[ hole / 2 ];                 // hole now contains what its upper neighbor was and hole then becomes its upper neighbors spot
        array[ hole ] = x;                                     // x is placed into hole
//        cout << "x was placed in position " << hole << endl;
//        cout << "so that means that array[1] is " << array[1] << endl;
//        cout << "while x is " << x << endl;
    }

    void remove(const Comparable & p){
   		int min = array[1];
    		int x = array[p] - min;
    		decreaseKey(p,x + 1);
    		deleteMin();
    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        if( isEmpty( ) ){
        	//throw UnderflowException( );
        }

        array[ 1 ] = array[ currentSize-- ];
        //array[currentSize + 1] = NULL;
        array[currentSize + 1].setDescription();
        percolateDown( 1 );
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) ){
            //throw UnderflowException( );
        }

        minItem = array[ 1 ];
        array[ 1 ] = array[ currentSize-- ];
        percolateDown( 1 );
    }

    void makeEmpty( ){
		for(int i = 1; array[i] != NULL; ++i){
			array[i] = NULL;
		}
		array.resize(10);
    }

    void print(){
    		if(isEmpty()){
    			cout << "The queue is empty" << endl;
    		}
    		else{
    			for(int i = 1; i <= currentSize; ++i){
    				cout << array[i] << " ";
    			}
    			cout << endl;
    		}
    }

    int size(){
    		return currentSize;
    }

  private:
    int                currentSize;  // Number of elements in heap
    vector<Comparable> array;        // The heap array

    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; i-- )
            percolateDown( i );
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    void percolateDown( int hole )
    {
        int child;
        Comparable tmp = array[ hole ];                                     // temp is now the current value we are on

        for( ; hole * 2 <= currentSize; hole = child )                      // while holes downstairs neighbor is not blank
        {
            child = hole * 2;                                               // child is now the index to holes downstairs neighbor
            if( child != currentSize && array[ child + 1 ] < array[ child ])   // if child is not the last value in the array and child's neighbor to the right is not less than child
                child++;                                                       //child increments(so we move to the right one
            if( array[ child ] < tmp )                                        //if holes downstairs neighbors value is less than holes value
                array[ hole ] = array[ child ];                              //hole and child swap places
            else
                break;
        }
        array[ hole ] = tmp;                                              //wherever hole is, hole takes on the value of temp
    }

    void decreaseKey(const Comparable & p, const Comparable & x){
    		int x2 = array[p] - x;
    		array[p] = x2;

    		int hole = p;
    		for( ; hole > 1 && x2 < array[ hole / 2 ]; hole /= 2 )  // while hole is greater(hole being the position of the whole) than 1 and x(value we are inserting) is less than array indexed at hole / 2(its connected neighbor above)
    			array[ hole ] = array[ hole / 2 ];                 // hole now contains what its upper neighbor was and hole then becomes its upper neighbors spot
    		array[ hole ] = x2;


    }
};

#endif /* BINARYHEAP_H_ */
