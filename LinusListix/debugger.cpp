
#include <iostream>
using namespace std;

#include "LinusListix.h"
//#include "LLxString.h"
using namespace Linus;

void test();

template<class T> void printList( LListix<T> * list );

bool Square( int* value, si32 index, void* external );
bool PrintData( int* value, si32 index, void* external );

class llistix_debugger
{
	int opt;
	char out;

	LListix<int> tryList;

public:
	void menu();
	void show_contents();
	void test_insert();
	void test_push_back();
	void test_push_front();
	void test_deleteAt();
	void test_replace();
	void test_clear();
	void test_accessor_squarebrackets();
	void test_next();
	void test_cont();
	void test_iterable_method();
	void test_swap();
	void test_relocate();
	void test_replaceAll();
	void test_replicate();
	void test_append();
	void test_merge();
	void test_cutOff();
	void test_cutOut();
	void test_2D_list();
	void test_assign();

} debugger;


int main()
{
	debugger.menu();
	return 0;
}


void llistix_debugger::menu()
{
	opt = 1;

	while ( opt != 0 )
	{

		cout << "\n\n================================================"
			<< "\nEnter option to apply to the current list."
			<< "\n0) Exit driver."
			<< "\n1) Show list contents."
			<< "\n2) Test insert()."
			<< "\n3) Test push_back() / operator << ."
			<< "\n4) Test push_front()."
			<< "\n5) Test deleteAt()."
			<< "\n6) Test replace()."
			<< "\n7) Test clear()."
			<< "\n8) Test accessor []."
			<< "\n9) Test next() - forwards and backwards iteration."
			<< "\n10) Test cont() - forwards and backwards iteration."
			<< "\n11) Test iterable method."
			<< "\n12) Test swap()."
			<< "\n13) Test relocate()."
			<< "\n14) Test replaceAll()."

			// functions may involve other lists or outputting lists
			<< "\n15) Test replicate()."
			<< "\n16) Test append()."
			<< "\n17) Test merge()."
			<< "\n18) Test cutOff()."
			<< "\n19) Test cutOut()."

			// other functions for special features
			<< "\n20) Test creating a 2D list."

			// test for assignment
			<< "\n21) Test for operator= and constructor from list."
			<< "\n\n: ";

		cin >> opt;
		cout << "\n------------------------------------------------";

		switch( opt )
		{
		case 1: show_contents(); break;
		case 2: test_insert(); break;
		case 3: test_push_back(); break;
		case 4: test_push_front(); break;
		case 5: test_deleteAt(); break;
		case 6: test_replace(); break;
		case 7: test_clear(); break;
		case 8: test_accessor_squarebrackets(); break;
		case 9: test_next(); break;
		case 10: test_cont(); break;
		case 11: test_iterable_method(); break;
		case 12: test_swap(); break;
		case 13: test_relocate(); break;
		case 14: test_replaceAll(); break;
		case 15: test_replicate(); break;
		case 16: test_append(); break;
		case 17: test_merge(); break;
		case 18: test_cutOff(); break;
		case 19: test_cutOut(); break;
		case 20: test_2D_list(); break;
		case 21: test_assign(); break;
		default: break;
		}
	}
}

void llistix_debugger::show_contents()
{
	cout << "\n\nList contents: ";
	printList( &(this->tryList) );
	cout << "\nSize = " << tryList.Size();
}

void llistix_debugger::test_insert()
{
	int ent; // entry

	cout << "\n\nEnter location to insert into:";
	cin >> ent;

	cout << "\n\nNow testing insert...";
	tryList.insert( 12, ent); cout << "\ninsert(12," << ent << ")";
	cout << "\nFinished attempting to insert object 12 at position " << ent << ".";

	show_contents();
}

void llistix_debugger::test_push_back()
{
	int ent; // entry
	
	cout << "\n\nEnter item to be added to the list:";
	cin >> ent;

	cout << "\n\nNow testing push_back... ";
	tryList << ent; cout << "\n<< " << ent;
	cout << "\nInserted object " << ent << " at the end of the list.";

	show_contents();
}

void llistix_debugger::test_push_front()
{
	int ent; // entry

	cout << "\n\nEnter item to be added to the list:";
	cin >> ent;

	cout << "\n\nNow testing push_front...";
	tryList.push_front( ent ); cout << "\npush_front(" << ent << ")";
	cout << "\nInserted object " << ent << " at the front of the list.";

	show_contents();
}

void llistix_debugger::test_deleteAt()
{
	int ent; // entry

	cout << "\n\nEnter location to delete from:";
	cin >> ent;

	cout << "\n\nNow testing delete...";
	tryList.deleteAt( ent ); cout << "\ndeleteAt(" << ent << ")";
	cout << "\nFinished attempting to delete object at " << ent << ".";

	show_contents();
}

void llistix_debugger::test_replace()
{
	int ent; // entry

	cout << "\n\nEnter location to make replacement:";
	cin >> ent;

	cout << "\n\nNow testing replace with 12";
	tryList.replace( ent, 12 ); cout << "\nreplace(" << ent << ", 12)";
	cout << "\nFinished attempting to replace object at " << ent;

	show_contents();
}

void llistix_debugger::test_clear()
{
	cout << "\n\nNow testing clear (list should become empty)";
	tryList.clear();

	show_contents();
}

void llistix_debugger::test_accessor_squarebrackets()
{
	cout << "\n\nNow testing functionality of accessor [] by showing list contents...\n";
	for ( si32 i = 0; i < tryList.Size(); i++ )
		cout << endl << tryList[i];
}

void llistix_debugger::test_next()
{
	int iter = 0;
	int iter2 = 0;

	cout << "\n\nNow testing next(). Note that, for this testing procedure,"
		<< " output will terminate when the output is identified as being equal"
		<< " to the initial output.";

	cout << "\n\nNow testing next(forward), starting from 0...";
	iter = tryList[0];
	do {
		iter2 = iter;
		iter = tryList.next(); // next=next(true) by default
		cout << "\n" << iter2;
	} while ( iter != iter2 );

	cout << "\n\nNow testing next(backward), starting from size - 1...";
	iter = tryList[-1];
	do {
		iter2 = iter;
		iter = tryList.next(false);
		cout << "\n" << iter2;
	} while ( iter != iter2 );
}

void llistix_debugger::test_cont()
{
	int iter = 0;

	cout << "\n\nNow testing cont(). Note that, for this testing procedure,"
		<< " output will be the entire length of the list given twice to test"
		<< " wraparound capability.";

	cout << "\n\nNow testing cont(true) - forward iteration - starting from 0...";
	iter = tryList[0];
	for ( int i = 0; i < tryList.Size() * 2; i++ )
	{
		cout << "\n" << iter;
		iter = tryList.cont(); // cont=cont(true) by default
	}

	cout << "\n\nNow testing cont(false) - backward iteration - starting from size - 1...";
	iter = tryList[-1];
	for ( int i = 0; i < tryList.Size() * 2; i++ )
	{
		cout << "\n" << iter;
		iter = tryList.cont(false); // cont=cont(true) by default
	}
}

void llistix_debugger::test_iterable_method()
{
#ifdef LLISTIX_2014
	cout << "\n\nFirst: clearing contents of list ...";
	tryList.clear();

	show_contents();

	cout << "\n\nSecond: applying insertion of 1,2,3,4,5,6 ...";
	tryList.insert( 1, 0 ); cout << "\ninsert(1,0)";
	tryList.insert( 2, 1 ); cout << "\ninsert(2,1)";
	tryList.insert( 3, 2 ); cout << "\ninsert(3,2)";
	tryList.insert( 4, 3 ); cout << "\ninsert(4,3)";
	tryList.insert( 5, 4 ); cout << "\ninsert(5,4)";
	tryList.insert( 6, 5 ); cout << "\ninsert(6,5)";

	cout << "\n\nNow testing iterable method application...";
	// try to save a function
	tryList.setIterableMethod( Square );
	cout << "\nFunction saved = Square - Squares the values stored in each node.";

	/* applying the function to the list while getting a return value requires
	that space be allocated to a void * and yet this cannot be done without
	malloc unless we just allocate space to a pointer of a certain type and give
	it to the void pointer */
	int * ini = new int(0); cout << "\nCreating ini (int *) and saving to it new int(0)";
	void * ext = ini; cout << "\nCreating ext (void *) and saving to it ini";
	
	cout << "\nNow testing using the function...";
	// apply the function to the list
	tryList.iterationWithMethod( 0, -1, 1, ext );

	cout << "\nAfter iteration with method, ext = " << *((int*)ext);

	show_contents();

	cout << "\nEstablishing new function.";
	tryList.setIterableMethod( PrintData );
	cout << "\nFunction saved = PrintData - Prints the index and value of each element.";

	cout << "\nNow iterating through backwards.";
	tryList.iterationWithMethod( -1, 0, -1, 0 );
#else
	cout << "\n\nFunction requires 2014 version.";
#endif
}

void llistix_debugger::test_swap()
{
	int loc1; // first location
	int loc2; // second location
	
	cout << "\n\nEnter first location in the list to be swapped: ";
	cin >> loc1;
	cout << "\nEnter second location in the list to be swapped: ";
	cin >> loc2;

	cout << "\n\nNow testing swap...";
	tryList.swap( loc1, loc2 );

	show_contents();
}

void llistix_debugger::test_relocate()
{
	int ent; // item to relocate
	int nloc; // new location
	
	cout << "\n\nEnter index of item to relocate: ";
	cin >> ent;
	cout << "\nEnter index of where to move the item: ";
	cin >> nloc;

	cout << "\n\nNow testing relocate...";
	tryList.relocate( ent, nloc );

	show_contents();
}

void llistix_debugger::test_replaceAll()
{
	// Testing replaceAll and operator=

	cout << "\n\nNow testing operator= ...\n";

	cout << "\n\nFirst clearing the list.";
	tryList.clear();
	
	show_contents();

	cout << "\n\nNow adding to the list to be replaced...";
	tryList.push_back(1);
	tryList.push_back(2);
	tryList.push_back(3);

	cout << "\n\nCreating list to replace...";
	LListix<int> tryList2;
	tryList2.push_back(6);
	tryList2.push_back(5);
	tryList2.push_back(4);

	cout << "\n\nPrinting lists for certainty of contents...";
	cout << "\nFirst list: "; printList( &tryList );
	cout << "\nsize = " << tryList.Size();
	cout << "\nSecond list: "; printList( &tryList2 );
	cout << "\nsize = " << tryList2.Size();

	cout << "\n\nNow making assignment: contents of list 2 to list 1...";
	tryList = &tryList2;

	show_contents();
}

void llistix_debugger::test_replicate()
{
#if !(defined __GNUC__) && !(defined __GNUG__)
	int start = 3;
	int end = 8;

	cout << "\n\nFirst generating list using push_back...";
	for ( int i = 0; i < 10; i++ )
	{
		tryList.push_back( i+1 );
	}

	show_contents();

	cout << "\n\nCreating new list to receive information.";
	LListix<int> tryList2;

	cout << "\n\nNow testing replicate...";
	tryList2 = tryList.replicate(start,end);
	cout << "\nreplicate(" << start << "," << end << ")";

	cout << "\nFinished replicating elements "
		<< start << " through "
		<< end << " in the list.";

	cout << "\n\nContents of extracted list.";
	printList( &tryList2 );
#else
	cout << "\n\nFunction not available for GNU g++";
#endif
}

void llistix_debugger::test_append()
{
	cout << "\n\nCreating list to append.";
	LListix<int> tryList2;

	cout << "\n\nAssigning elements 0,1,2,3,4 to list to append using push_back.";
	for ( int i = 0; i < 5; i++ )
	{
		tryList2.push_back(i);
	}
	cout << "\nContents of list to be appended: ";
	printList( &tryList2 );

	cout << "\n\nNow testing append...";
	tryList.append( &tryList2 );

	show_contents();
}

void llistix_debugger::test_merge()
{
	cout << "\n\nCreating list to merge.";
	LListix<int> tryList2;

	cout << "\n\nAssigning elements 0,1,2,3,4 to list to merge using push_back.";
	for ( int i = 0; i < 5; i++ )
	{
		tryList2.push_back(i);
	}
	cout << "\nContents of list to be merged: ";
	printList( &tryList2 );

	cout << "\n\nNow testing merge...";
	tryList.merge( &tryList2 );

	show_contents();

	cout << "\n\nNow testing if merge was complete...";

	cout << "\n\nPrinting contents of the list using the second pointer.\n";
	printList( &tryList2 );

	cout << "\n\nPrinting contents of the list using the first pointer.";
	show_contents();

	cout << "\n\nSet the size of the second pointer to zero to allow for proper deletion.";
	tryList2.setSize( 0 );
}

void llistix_debugger::test_cutOff()
{
	int loc = 0;
	char input;
	bool head = false;

	cout << "\nCreating list to cut off.";
	LListix<int> tryList2;

	for ( int i=0; i < 10; i++ )
	{
		tryList2.push_back( i );
	}

	cout << "\nCurrent list: ";
	printList( &tryList2 );

	cout << "\nEnter location to cut off: ";
	cin >> loc;

	cout << "\nCut off the head? (y/n): ";
	cin >> input;
	if ( input == 'y' )
		head = true;

	cout << "\nNow cutting off the list.\n";
	tryList2.cutOff( loc, false, head );

	printList( &tryList2 );
}

void llistix_debugger::test_cutOut()
{
	int loc1 = 0;
	int loc2 = 0;

	cout << "\nCreating list to cut from.";
	LListix<int> tryList2;

	for ( int i=0; i < 10; i++ )
	{
		tryList2.push_back( i );
	}

	cout << "\nCurrent list: ";
	printList( &tryList2 );

	cout << "\nEnter the indices of the locations to be cut out: ";
	cin >> loc1 >> loc2;

	cout << "\nCutting out of list.";
	tryList2.cutOut( loc1, loc2, false );

	cout << "\nResulting list: ";
	printList( &tryList2 );
}

// test doubly-linked list
/*
NOTE: Doubly templating does not work in G++.
Meaning this fails:
LListix< LListix<int> > list;

See for more info:
http://stackoverflow.com/questions/6486432/variadic-template-templates-and-perfect-forwarding
*/
void llistix_debugger::test_2D_list()
{
#if ! (defined __GNUC__) && ! (defined __GNUG__)
	int num = 1;

	cout << "\n\nNow testing a two-dimensional linked list.";
	cout << "\nInstantiation.";
	LListix< LListix<int> > doubleDecker;
	cout << "\nPushback of an empty one.";
	doubleDecker.push_back( LListix<int>() );
	cout << "\nAddition of a link containing the number (" << num << ")";
	(( LListix<int> * )doubleDecker.itemAt(-1))->push_back( num );
	cout << "\nRetrieval of the number = ";
	cout << doubleDecker[0][0] ;
	// NOTE: Doubly linked lists must be properly cleared before the program
	// terminates.
	cout << "\nNow deleting columns.";
	for ( int i = 0; i < doubleDecker.Size(); i++ )
	{
		(( LListix<int>* )doubleDecker.itemAt(0))->clear();
	}
#else
	cout << "\n\nFunction not available for GNU g++.";
#endif
}

void llistix_debugger::test_assign()
{
	cout << "\n\nNow testing assignment with assignment symbol.";
	cout << "\nInstantiation.";
	LListix<int> lista;
	cout << "\nAdding to list... ";
	for ( int i = 0; i < 4; i++ )
	{
		lista << i;
		cout << i << ',';
	}
	cout << "\nPrinting list a:";
	printList(&lista);
	cout << "\nAssigning copy to new list, list b.";
	LListix<int>* listb = new LListix<int>();
	*listb = lista;
	cout << "\nPrinting list b:";
	printList(listb);
	cout << "\nDeleting list b.";
	delete listb;
	cout << "\nPrinting list a:";
	printList(&lista);
	cout << "\nCreating list c from list a";
	LListix<int> listc( lista );
	cout << "\nPrinting list c:";
	printList(&listc);
	cout << "\nTest complete.";
}

// extra functions for testing purposes


template<class T>
void printList( LListix<T> * list )
{
	cout << "[";
	for ( int i = 0; i < list->Size(); i++ )
	{
		cout << list->copyOf(i);

		if ( i != list->Size() - 1)
			cout << ", ";
	}
	cout << "]";
}



bool Square( int* value, si32 index, void* external )
{
	int * sum = (int *) external;

	// multiply the value by itself and save the result to itself
	// NOTE: three of the * characters are for dereferencing the pointer
	*(value) = *(value) * *(value);

	// save the sum
	*sum = *sum + *value;

	// save the sum to the external
	external = (void*) sum;

	cout << "\ntotal = " << *sum;

	return true;
}


bool PrintData( int* value, si32 index, void* external )
{
	cout << "\nValue " << index << " is " << *value;

	return true;
}
