
#include <iostream>
using namespace std;

#include "Listix.h"
using namespace util;

template<class T> void printList( Listix<T> * list );

void test();

class listix_debugger
{
	int opt;
	char out;

	Listix<int> tryList;

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
	void test_forward_iter();
	void test_backward_iter();
	void test_swap();
	void test_relocate();
	void test_append();
	void test_appendRange();
	void test_destroyFront();
	void test_destroyBack();
	void test_destroyRange();

} debugger;


int main()
{
	debugger.menu();
	return 0;
}


void listix_debugger::menu()
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
			<< "\n10) Test forwards iterator."
			<< "\n11) Test backwards iterator."
			<< "\n12) Test swap()."
			<< "\n13) Test relocate()."

			// functions may involve other lists or outputting lists
			<< "\n16) Test append()."

			<< "\n17) Test appendRange()."
			<< "\n18) Test destroyFront()."
			<< "\n19) Test destroyBack()."
			<< "\n20) Test destroyRange()."

			<< "\n\n: ";

		cin >> opt;
		cout << "\n------------------------------------------------\n";

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
		case 10: test_forward_iter(); break;
		case 11: test_backward_iter(); break;
		case 12: test_swap(); break;
		case 16: test_append(); break;
		case 17: test_appendRange(); break;
		case 18: test_destroyFront(); break;
		case 19: test_destroyBack(); break;
		case 20: test_destroyRange(); break;
		default: break;
		}
	}
}

void listix_debugger::show_contents()
{
	cout << "\n\nList contents: ";
	printList( &(this->tryList) );
	cout << "\nSize = " << tryList.getSize();
}

void listix_debugger::test_insert()
{
	int ent; // entry

	cout << "\n\nEnter location to insert into:";
	cin >> ent;

	cout << "\n\nNow testing insert...";
	tryList.insert( 12, ent); cout << "\ninsert(12," << ent << ")";
	cout << "\nFinished attempting to insert object 12 at position " << ent << ".";

	show_contents();
}

void listix_debugger::test_push_back()
{
	int ent; // entry
	
	cout << "\n\nEnter item to be added to the list:";
	cin >> ent;

	cout << "\n\nNow testing push_back... ";
	tryList << ent;
	cout << "\n<< " << ent;
	cout << "\nInserted object " << ent << " at the end of the list.";

	show_contents();
}

void listix_debugger::test_push_front()
{
	int ent; // entry

	cout << "\n\nEnter item to be added to the list:";
	cin >> ent;

	cout << "\n\nNow testing push_front...";
	tryList.push_front( ent ); cout << "\npush_front(" << ent << ")";
	cout << "\nInserted object " << ent << " at the front of the list.";

	show_contents();
}

void listix_debugger::test_deleteAt()
{
	int ent; // entry

	cout << "\n\nEnter location to delete from:";
	cin >> ent;

	cout << "\n\nNow testing delete...";
	tryList.deleteAt( ent ); cout << "\ndeleteAt(" << ent << ")";
	cout << "\nFinished attempting to delete object at " << ent << ".";

	show_contents();
}

void listix_debugger::test_replace()
{
	int ent; // entry

	cout << "\n\nEnter location to make replacement:";
	cin >> ent;

	cout << "\n\nNow testing replace with 12";
	tryList.replace( ent, 12 ); cout << "\nreplace(" << ent << ", 12)";
	cout << "\nFinished attempting to replace object at " << ent;

	show_contents();
}

void listix_debugger::test_clear()
{
	cout << "\n\nNow testing clear (list should become empty)";
	tryList.clear();

	show_contents();
}

void listix_debugger::test_accessor_squarebrackets()
{
	cout << "\n\nNow testing functionality of accessor [] by showing list contents...\n";
	for ( Listix<int>::index_type i = 0; i < tryList.getSize(); i++ )
	// alternatively:
	//for ( decltype(tryList.getSize()) i = 0; i < tryList.getSize(); i++ )
		cout << endl << tryList[i];
}

void listix_debugger::test_forward_iter()
{
	cout << "\n\nNow testing forward iterator - starting from 0...";
	Listix<int>::ForwardIter iter = tryList.createForwardIterator();
	while ( ! iter.isDone() ) {
		cout << "\n" << iter.next();
	}
	cout << "\nTest finished.";
}

void listix_debugger::test_backward_iter()
{
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

	cout << "\n\nNow testing backwards iterator.";

	Listix<int>::BackwardIter iter = tryList.createBackwardIterator();
	while ( ! iter.isDone() ) {
		cout << "\n" << iter.next();
	}
	cout << "\nTest finished.";
}

void listix_debugger::test_swap()
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

void listix_debugger::test_relocate()
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

void listix_debugger::test_append()
{
	cout << "\n\nCreating list to append.";
	Listix<int> tryList2;

	cout << "\n\nAssigning elements 0,1,2,3,4 to list to append using push_back.";
	for ( int i = 0; i < 5; i++ )
	{
		tryList2.push_back(i);
	}

	cout << "\nContents of list to be appended: ";
	printList( &tryList2 );

	cout << "\n\nNow testing append...";
	tryList.append( tryList2 );

	show_contents();
}

void listix_debugger::test_appendRange()
{
	cout << "\n\nCreating list to append.";
	Listix<int> tryList2;

	cout << "\n\nAssigning elements 0-9 to list to append using push_back.";
	for ( int i = 0; i < 10; i++ )
	{
		tryList2.push_back(i);
	}

	int rangeStart = 1;
	int rangeEnd = 3;

	cout << "\n\nNow testing appendRange to test list using range "
		<< rangeStart << " - " << rangeEnd;

	tryList.appendRange(tryList2, rangeStart, rangeEnd);

	show_contents();
}

void listix_debugger::test_destroyFront()
{
	int index = 2;
	cout << "\n\nTesting destroyFront using index " << index;
	tryList.destroyFront(index);

	show_contents();
}

void listix_debugger::test_destroyBack()
{
	int index = 2;
	cout << "\n\nTesting destroyBack using index " << index;
	tryList.destroyBack(index);

	show_contents();
}

void listix_debugger::test_destroyRange()
{
	cout << "\n\nCreating list to destroy.";
	Listix<int> tryList2;

	cout << "\n\nAssigning elements 0-9 to list to append using push_back.";
	for ( int i = 0; i < 10; i++ )
	{
		tryList2.push_back(i);
	}

	int rangeStart = 1;
	int rangeEnd = 3;

	cout << "\nList contents: ";
	printList( &tryList2 );

	cout << "\n\nNow testing destroyRange to test list using range "
		<< rangeStart << " - " << rangeEnd;

	tryList2.destroyRange(rangeStart, rangeEnd);

	cout << "\n\nNew list: ";
	printList( &tryList2 );
}


// extra functions for testing purposes

template<class T>
void printList( Listix<T> * list )
{
	cout << "[";
	for ( int i = 0; i < list->getSize(); i++ )
	{
		cout << list->copyOf(i);

		if ( i != list->getSize() - 1)
			cout << ", ";
	}
	cout << "]";
}
