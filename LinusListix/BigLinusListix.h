/*
This is the header file for LinusListix
(C) Nic Anderson
Date created: Feb 15, 2013
99% of the code taken from LinusListix.h, created Oct 2, 2011

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

*/

/*
Note that the original LinuxListix.h (upon which this file is based) has been
changed and had at least one or more bug fixes since its publication.
Therefore, this file is out of date. It is also unused.
*/

// don't double define this
	// if "_BigLinusListix_INCLUDED" is not defined...
#ifndef _BigLinusListix_INCLUDED_
	// ... define it (and define the namespace as well)
#define _BigLinusListix_INCLUDED_


// simple definitions for usage with this list
//#ifdef _MSC_VER
//typedef long __int32                 si64;
//#else
//typedef long signed int              si64;
//#endif

#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
typedef __int64					si64;
#elif __GNUC__
#if __WORDSIZE == 64
typedef long int 				si64;
#else
__extension__ typedef long long			si64;
#endif
#else
typedef long long				si64;
#endif


// namespace containing the list
namespace Linus
{
	template<class Unk>
	class BigLListixNode
	{
	public:
		BigLListixNode<Unk> * Prior; // the node preceding this one
		BigLListixNode<Unk> * Post; // the node after this one
		
		Unk ThisItem; // the item stored here

		//! constructor
		BigLListixNode( Unk item )
		{
			ThisItem = item;
		}

		//! deconstructor
		void deleteMe() { delete this; }
	};

	template<class Unk>
	class BigLListix
	{
	private:
		si64 size; // list size
		BigLListixNode<Unk> * HeadNode; // leading node
		BigLListixNode<Unk> * TailNode; // last node
		
		/* Node between the leading and the last node
		- in the region being used the most - i.e., the grabber. */
		BigLListixNode<Unk> * Midix;
		si64 midixL; // location of Midix - the node being pointed to by Midix

		/* For setIterableMethod function - capability of applying a
		function to the list objects. */
			/* Pointer to a function whose operations are applied to
			list items. */
		bool (*Function)(Unk * listItem, si64 index, void* external);
		bool hasFunc; // Indicates if a function has been saved to the pointer
		si64 FunctionID; // In case you wanted to identify the function you saved here

	public:

			//! Constructor
		BigLListix()
		{
			size = 0;
			midixL = 0;
			hasFunc = false;
		}

			//! Destructor
		~BigLListix()
		{ this->clear(); }

			//! Midix location
		/* Returns the location of Midix.
		Same as "getCurrLoc". Retained for compatibility purposes. */
		si64 midixLocation()
		{ return midixL; }

			//! Get current node location
		/* Returns the index value of the last node normally accessed. */
		si64 getCurrLoc()
		{ return midixL; }

			//! Get current node
		/* Returns a pointer to the last node normally accessed. */
		BigLListixNode<Unk> * getCurrNode()
		{ return Midix; }

			//! Get current node item
		/* Returns a pointer to the item of the last node normally accessed. */
		Unk * getCurrItem()
		{ return &(Midix->ThisItem); }

			//! Check bounds
		/* Check if the given index is within the bounds of the list.
		\param index - The index to be checked.
		\param alter - If the index should be altered to ensure it is in range.
		Returns false if the index is NOT out of bounds. Otherwise it returns true. */
		bool CheckBound( si64 * index, bool alter=false)
		{
			// This index cannot be used
			if ( size == 0 ) return true;

			if ( *index >= size || *index < 0 )
			{
				// Is this index fixable?
				if ( alter )
				{
					// Don't worry about corrections if there are no items
					// - let the calling function handle this scenario
					if ( size == 0 ) return false;

					// Correction for low values
					while ( *index < 0 ) *index = *index + size;

					// Correction for high values
					while ( *index >= size ) *index = *index - size;

					// This index can be used
					return false;
				} else {
					// Indicate this index should not be used
					return true;
				}
			} else {
				// This index can be used
				return false;
			}
		}

			//! Return pointer-to
		/* Find and return the pointer to a node at this particular location */
		BigLListixNode<Unk> * at( si64 loc )
		{
			/* if there is no item in the list yet,
			or the desired location is larger than the list size:
			return a blank */
			if ( size == 0 ) return 0;

			// Ensure the given index is within the boundaries
			if ( CheckBound( &loc, true ) ) return 0;

			/* If the location is closer to the last link than either the
			the first one or the Midix, start from the last link to obtain it. */
			if ( loc > (size + midixL)/2 )
			{
				Midix = TailNode; // set the Midix to the tail
				midixL = size - 1; // set the location to the end
			} else {
				/* If the location is closer to the first link than the
				Midix, start from the first link to obtain it. */
				if ( loc < midixL/2 )
				{
					Midix = HeadNode; // set the Midix to the head
					midixL = 0; // set the location to the start
				}
			}

			while ( loc > midixL )
			{
				Midix = Midix->Post;
				midixL = midixL + 1;
			}
			while ( loc < midixL )
			{
				Midix = Midix->Prior;
				midixL = midixL - 1;
			}

			return Midix;
		}

			//! Return copy-of
		/* Find and return a copy of the object at this particular location */
		Unk& operator[] ( si64 loc )
		{
			return (this->at(loc))->ThisItem;
		}

			//! Return copy-of
		/* Find and return a copy of the object at this particular location */
		Unk copyOf ( si64 loc )
		{
			return (this->at(loc))->ThisItem;
		}

			//! Item at
		/* Get a pointer to the item at the given location. */
		Unk * itemAt( si64 loc )
		{
			return &((this->at(loc))->ThisItem);
		}
		
			//! Is this the beginning?
		/* Returns true if the given index equals 0. */
		bool atStart( si64 index )
		{
			return (index == 0);
		}
		
			//! Is this the end?
		/* Returns true if the given index equals the size - 1 */
		bool atEnd( si64 index )
		{
			return (index == (size-1));
		}

			//! Is the end reached?
		/* Returns true if the midix is at the end. */
		bool end()
		{
			return (midixL == (size-1));
		}

			//! Size
		/* Returns the size of this list */
		si64 Size() { return size; }

			//! Set size
		/* Sets the size of the list if altered by some function outside of
		this class. */
		void setSize( si64 newSize ) { this->size = newSize; }

			//! Reset Midix
		/* Resets the pointer for grabbing items back to the head node */
		void resetMidix()
		{
			Midix = HeadNode;
			midixL = 0;
		}

			//! Set head node
		/* Sets the head node of the list if altered by some function outside
		of this class. */
		void setHeadNode( BigLListixNode<Unk> * newHeadNode )
		{
			this->HeadNode = newHeadNode;
		}

			//! Set tail node
		/* Sets the tail node of the list if altered by some function outside
		of this class. */
		void setTailNode( BigLListixNode<Unk> * newTailNode )
		{
			this->TailNode = newTailNode;
		}

			//! Replace item
		/* Find and return the node at this particular location */
		void replace( si64 loc, Unk item )
		{
			if ( CheckBound( &loc, true ) ) return;

			(this->at(loc))->ThisItem = item;
		}

			//! Replace this list
		/* Replace this list's contents with the one given */
		void replaceAll( BigLListix<Unk> * other )
		{
			si64 index = 0;

			/* Replace the individual items without deleting the nodes
			since doing so is costly. */
			for (; index < size; index++ )
			{
				if ( index < other->Size() )
				{
					this->at(index)->ThisItem = other->copyOf(index);
				} else {
					cutOff( index, false, false );
					break;
				}
			}

			// Add extras to this list from the other if available
			for (; index < other->Size(); index++ )
			{
				push_back( other->copyOf(index) );
			}
		}

			//! Replace this list
		/* Replace this list's contents with the one given */
		void operator=( BigLListix<Unk> * other )
		{
			replaceAll( other );
		}

			//! Insert
		/* Insert a link at a specific location in the chain. The new link
		will possess the location index of the location parameter given. */
		void insert( Unk item, si64 loc )
		{
			// Ensure non-negative index
			if ( size > 0 )
				while ( loc < 0 ) loc = size + loc;

			// if this is not one of the first links to be added
			if ( size >= 2 )
			{
				// go to this location if it is not the last one
				if ( loc < size )
				{
					// if this is to be the first link
					if ( loc == 0 )
					{
						HeadNode->Prior = new BigLListixNode<Unk>( item );
						HeadNode->Prior->Post = HeadNode; // connect the links
						HeadNode = HeadNode->Prior; // set the new link as the head
						midixL = midixL + 1; // account for a new link placed before Midix
					} else {
						// go to this location
						this->at(loc);

						// save another pointer
						BigLListixNode<Unk> * preceder = Midix->Prior;

						// create a new node
						Midix->Prior = new BigLListixNode<Unk>( item );

						// connect the new link to the...
						Midix->Prior->Post = Midix; // ... one following it
						Midix->Prior->Prior = preceder; // ... one preceding it

						// connect the link following the new link to the new link
						preceder->Post = Midix->Prior;

						// account for the new link
						midixL = midixL + 1;
					}

				} else { // insertion after the last link

					// tack on a new link
					TailNode->Post = new BigLListixNode<Unk>( item );

					// set the tail link's preceding link to this one
					TailNode->Post->Prior = TailNode;

					// set the tail link to the new tail
					TailNode = TailNode->Post;
				}

				size = size + 1; // account for the newly added link
			} else {
				// if this is the first link
				if ( size == 0 )
				{
					HeadNode = new BigLListixNode<Unk> ( item );
					TailNode = HeadNode;
					Midix = HeadNode;
					midixL = 0;
				} else { // there is at least one link, so add a new one
					if ( loc == 0 ) // new head
					{
						TailNode->Prior = new BigLListixNode<Unk> ( item );
						TailNode->Prior->Post = TailNode; // connect the links
						HeadNode = TailNode->Prior; // save this new link to the head
						Midix = TailNode;
						midixL = 1; // the Midix has moved up one
					} else {
						HeadNode->Post = new BigLListixNode<Unk> ( item );
						HeadNode->Post->Prior = HeadNode; // connect the links
						TailNode = HeadNode->Post; // save this new link to the head
						Midix = HeadNode;
						midixL = 0; // the Midix starts from the beginning
					}
				}

				size = size + 1; // account for the newly added link
			}
		}

			//! Add to back
		/* Add an item to the end of the chain */
		void push_back( Unk item )
		{
			insert( item, this->size );
		}

			//! Add to front
		/* Add an item to the beginning of the chain */
		void push_front( Unk item )
		{
			insert( item, 0 );
		}
		
			//! Add to back successively
		/* Adds an item to the end of the chain */
		void operator << ( Unk item )
		{
			push_back( item );
		}

			//! Delete
		/* Remove an item from somewhere in the list */
		void deleteAt( si64 loc )
		{
			// if there are any links
			if ( size > 0 )
			{
				// account for indexes that are out of bounds
				if ( CheckBound( &loc, true ) ) return;

				// if this is the only link in the chain
				if ( size == 1 )
				{
					HeadNode->deleteMe(); // delete the only item
					size = 0;
					midixL = 0;
				} else {
					// if the head
					if ( loc == 0 )
					{
						// the Midix may need to move
						if ( Midix == HeadNode )
						{
							Midix = Midix->Post;
						} else
							midixL -= 1; // account for the position change

						// set the head link to the next link after the first one
						HeadNode = HeadNode->Post;

						// delete the old first link
						HeadNode->Prior->deleteMe();

						// Remove access to it
						HeadNode->Prior = 0;
					} else {
						// if the tail
						if ( loc == size - 1 )
						{
							// the Midix may need to move
							if ( Midix == TailNode )
							{
								Midix = Midix->Prior;
								midixL = size - 2;
							}

							// set the tail link to the link prior to the last one
							TailNode = TailNode->Prior;

							// delete the old tail link
							TailNode->Post->deleteMe();

							// Remove access to it
							TailNode->Post = 0;
						} else {
							// find the location just prior to this
							this->at(loc-1);

							// create a pointer to the following one
							BigLListixNode<Unk> * follower = Midix->Post->Post;

							// delete the middle node
							Midix->Post->deleteMe();

							// connect the two parts of the chain
							Midix->Post = follower;
							follower->Prior = Midix;
						}
					}

					size = size - 1; // account for the loss of a link
				}
			}
		}

			//! Empty
		/* Clear the contents of the list */
		void clear()
		{
			while ( size > 0 )
			{
				deleteAt(-1);
			}
		}


			//! Swap
		/* Exchange two items in the list. */
		void swap( si64 item1_loc, si64 item2_loc )
		{
			// Account for indexes that are out of bounds
			if ( CheckBound( &item1_loc, true ) || CheckBound( &item2_loc, true ) )
				return;

			// save the first item to be moved
			Unk item = *( itemAt(item1_loc) );

			// relocate the other item to be moved
			*( itemAt( item1_loc ) ) = *( itemAt( item2_loc ) );

			// resave the item in temporary storage
			*( itemAt( item2_loc ) ) = item;
		}

			//! Relocate
		/* Moves the link at the given location to the new location.
		\param loc - Current index of the link.
		\param newloc - Index where to move the link.
		Returns true if the relocation was successful. */
		bool relocate( si64 loc, si64 newloc )
		{
			// Account for indexes that are out of bounds
			if ( CheckBound( &loc, true ) || CheckBound( &newloc, true ) )
				return false;

			// Insert the item at the specific slot
			if ( loc < newloc )
				insert( *(itemAt( loc )), newloc+1 );
			else
				this->insert( *(itemAt( loc )), newloc );

			/* Delete the old link, depending on its location relative
			to the new one, since the index of the old one will change
			if the new link is inserted before it. */
			if ( newloc < loc )
				deleteAt( loc + 1 );
			else
				deleteAt( loc );

			// Successful relocation of the link
			return true;
		}

			//! Continue
		/* Continue to extract items following the immediate location of the
		last normally-accessed item. If an end point of the list is reached,
		iteration restarts from the other end.
		(See function "next" if stopping at the last item is desired.)
		\param foward - indicates whether to iterate towards the ending or
		towards the beginning. */
		Unk cont(bool forward=true)
		{
			// iterate forwards through the list
			if ( forward )
			{
				// wrapping
				if ( midixL + 1 == size )
					return this->copyOf(0); // NOTE: midixL will be set to zero by at()
				else
					return this->copyOf(midixL + 1);
			} else {
				// iterate backwards through the list
				if ( midixL == 0 )
					return this->copyOf(size - 1); // NOTE: midixL will be set to (size - 1) by at()
				else
					return this->copyOf(midixL - 1);
			}
		}

			//! Next
		/* Continue to extract items following the immediate location of the
		last normally-accessed item. If an end point of the list is reached, the
		function returns zero.
		\param foward - indicates whether to iterate towards the ending or
		towards the beginning. */
		Unk next(bool forward=true)
		{
			// iterate forwards through the list
			if ( forward )
			{
				if ( midixL + 1 == size )
					return this->copyOf(-1);
				else
					return this->copyOf(midixL + 1);
			} else {
				// iterate backwards through the list
				if ( midixL == 0 )
					return this->copyOf(0);
				else
					return this->copyOf(midixL - 1);
			}
		}

			//! Iterate
		/* Designed for for-loops and while loops. Calls the cont() function
		but returns true when the iteration has made a complete cycle. Pass
		in a pointer to the variable to receive the value in the list at each
		iteration. */
		bool iter( bool forward=true, Unk * val=0 )
		{
			bool isCycle = false;

			if ( midixL == size - 1 && forward )
			{ isCycle = true; }
			else {
				if ( midixL == 0 && forward == false )
				{ isCycle = true; }
			}

			if ( size != 0 )
				*val = cont(true);
			else
				return true;

			return isCycle;
		}


		//********** SPECIAL OPERATION FUNCTIONS ***********
		/* The following functions define procedures for setting up and using
		a function whose operations are to be applied to the items in the
		linked list in an iterative manner. */

			//! Iterable method
		/* Set a function whose operations are to be applied to items
		stored in this list.
		*function contains:
		\param listItem - A pointer to the item in the linked list.
		\param index - The index of the item in the linked list.
		\param external - For your own use.
		The function must return a boolean value to indicate whether or not
		iteration should continue.
		\param functionID - The ID of the function if you want to give it one.
		*/
		void setIterableMethod(
				bool (*function)( Unk * listItem, si64 index, void* external ),
				si64 functionID=0
			)
		{
			this->Function = function;
			hasFunc = true;
			this->FunctionID = functionID;
		}

			//! Has iterable method
		/* Indicates if a function has been saved using
		setIterableMethod. */
		bool hasIterableMethod()
		{
			return hasFunc;
		}

			//! Use function
		/* Uses the function passed to this list via setIterableMethod
		by passing to it each item in the list between (and including) the items
		given by start and end.
		\param start - The starting point of iteration.
		\param end - The final point of iteration.
		\param iter - The iteration amount / the skip.
		\param external - For your own use.
		Returns false if the loop broke by failure within the function
		(as signaled by the user function return). */
		bool iterationWithMethod( si64 start=0, si64 end=-1,
									si64 iter=1, void* external=0 )
		{
			// Don't bother doing anything if there is no function for use
			if ( !hasFunc ) return 0;

			bool cont_flag = true; // indicates if the loop should continue

			// Account for indexes that are out of bounds
			if ( CheckBound(&start, true) || CheckBound(&end, true) ) return false;

			// Don't bother doing anything if there are no items
			if ( size == 0 ) return 0;

			// Account for the flip
			if ( start > end )
			{
				end -= 2;
				iter = -1;
			}

			for ( si64 i = start; i != end+1; i += iter )
			{
				// Continue only if the user says
				if ( cont_flag )
				{
					// Use the function
					cont_flag = Function( itemAt(i), i, external );
				} else
					break;
			}

			// Return success or internal termination
			return cont_flag;
		}


		//********** COPY, COMBINE, OR BREAK LIST FUNCTIONS ***********
		/* The following functions define procedures merging lists or parts
		of lists or breaking lists into pieces. */

			//! Copy list
		/* Copies a specified section of the list to a new list and returns
		a pointer to that list.
		\param start - First index to copy.
		\param end - Last index to copy. */
		BigLListix<Unk> * replicate( si64 start=0, si64 end=this->size )
		{
			// Account for indexes that are out of bounds
			if ( CheckBound(&start,false) || CheckBound(&end,false) )
				return 0;

			// Don't bother doing anything if there are no items
			if ( size == 0 ) return 0;

			// new list to be returned
			BigLListix<Unk> * return_list = new BigLListix<Unk>();

			// Append to the new list thi data from indexes between start and end
			for ( si64 i = start; i <= end; i++ )
			{
				return_list->push_back( this->copyOf(i) );
			}

			return return_list;
		}

			//! Append list
		/* Appends the data from the given list to this one. */
		void append( BigLListix<Unk> * list )
		{
			for ( si64 i = 0; i < list->Size(); i++ )
			{
				this->push_back( list->copyOf(i) );
			}
		}

			//! Merge lists
		/* Merges the lists to where the given list to follow this list. Both
		list instantiations will then reference the same list.
		
		ATTN: For a program to terminate properly after having used this function,
		the sizes of all but one list tied into one must be set to zero. */
		void merge( BigLListix<Unk> * list )
		{
			// Set the tail and head nodes
			if ( this->size > 0 && list->Size() > 0 )
			{
				// Link the middle
				list->at(0)->Prior = this->TailNode;
				this->TailNode->Post = list->at(0);

				// Link the ends
				this->TailNode = list->at(-1);
				list->setHeadNode( this->HeadNode );
			} else {
				// First list is the one with items
				if ( this->size > 0 )
				{
					list->setHeadNode( this->HeadNode );
					list->setTailNode( this->TailNode );
				} else {
					// Second list is the one with items
					this->HeadNode = list->at(0);
					this->TailNode = list->at(0);
				}
			}

			// Set the new size
			this->size += list->Size();
			list->setSize( this->size );

			// Reset the midix locations
			this->resetMidix();
			list->resetMidix();
		}

			//! Cut off list
		/* Cuts off the list at a certain index and either returns a pointer
		to a new list carrying the cut off values or deletes these values.
		\param index - Index of the first node to cut off.
		\param retPtr - If the cut part of the list should return a pointer
		to a new list. Otherwise, the nodes will be deleted.
		\param front - If the front of the list should be cut. */
		BigLListix<Unk> * cutOff( si64 index, bool retPtr=false, bool front=false )
		{
			BigLListix<Unk> * return_list;

			// Account for indexes that are out of bounds
			if ( CheckBound( &index, true ) ) return 0;

			// Don't bother doing anything if there are no items
			if ( this->size == 0 ) return 0;

			if ( retPtr )
			{
				// Generate a new list to save to
				return_list = new BigLListix<Unk>();

				// Transfer contents without copying

				// Simple case
				if ( size == index && front || index == 0 && !front )
				{
					// Prepare to take the list
					return_list->setHeadNode( this->HeadNode );
					return_list->setTailNode( this->HeadNode );
					
					// Drop the list
					this->HeadNode = 0;
					this->TailNode = 0;

				} else {

					// Complex case
					if ( front )
					{
						// Prepare to hold onto the front end of the list
						return_list->setHeadNode( this->HeadNode );
						return_list->setTailNode( this->at(index) );

						// Prepare to let go of the front of the list
						this->HeadNode = this->at(index+1);

						// Drop the front of the list
						this->HeadNode->Prior->Post = 0;
						this->HeadNode->Prior = 0;
					} else {
						// Prepare to hold onto the back end of the list
						return_list->setHeadNode( this->at(index) );
						return_list->setTailNode( this->TailNode );

						// Prepare to let go of the back of the list
						this->TailNode = this->at(index-1);

						// Drop the front of the list
						this->TailNode->Post->Prior = 0;
						this->TailNode->Post = 0;
					}

				}

				// Account for list size change
				this->size -= (index+1);
				resetMidix();

				// Prepare the returnable list for use
				return_list->setSize( index+1 );
				return_list->resetMidix();

				// Remove connections to the old nodes
				return_list->at(0)->Prior = 0;
				return_list->at(index)->Post = 0;

			} else {
				// For not returning the cut:

				// If deletion is for the front nodes
				if ( front ) {
					for ( si64 i = 0 ; i < index; i++ )
					{
						deleteAt(0);
					}
				} else {
					for ( si64 i = size ; i > index; i-- )
					{
						deleteAt(-1);
					}
				}

				return 0;
			}

			return return_list;
		}

			//! Cut out list
		/* Cuts out the specified section of the list between the given
		indexes and either returns a pointer to a new list carrying the cut
		out values or deletes these values.
		\param start - Index of the first node to cut out.
		\param end - Index of the last node to cut out.
		\param retPtr - If the cut part of the list should return a pointer
		to a new list. Otherwise, the nodes will be deleted. */
		BigLListix<Unk> * cutOut( si64 start, si64 end, bool retPtr )
		{
			BigLListix<Unk> * return_list;

			// Account for indexes that are out of bounds
			if ( CheckBound( &start, true ) || CheckBound( &end, true ) )
				return 0;

			// Don't bother doing anything if there are no items
			if ( size == 0 ) return 0;

			// Flip the indexes if need be
			si64 temp;
			if ( start > end )
			{
				temp = start;
				start = end;
				end = temp;
			}

			// Prepare to cut out part of the list
			return_list = new BigLListix<Unk>();

			// Link up the places to cut out
			return_list->setHeadNode( this->at( start ) );
			return_list->setTailNode( this->at( end ) );

				// If all of the link are included in the range, just give them away
			if ( end - start + 1 == size )
			{
				this->HeadNode = 0;
				this->TailNode = 0;
				this->size = 0;
			} else {
				// If the head was included
				if ( start == 0 )
				{
					// Set the head to the location after the last to be cut out
					this->HeadNode = this->at(end+1);
				} else {
					// If the tail was included
					if ( end == size - 1 )
					{
						// Set the tail to the location after the first to be cut out
						this->TailNode = this->at(start-1);
					} else {
						
						// The cut is somewhere between the head node and the tail node

						// Tie together the two ends of the list
						this->at(end)->Post->Prior = this->at(start)->Prior;
						this->at(start)->Prior->Post = this->at(end)->Post;
					}
				}

				// Cut the size down by the amount that was lost
				this->size = this->size - (end - start + 1);
			}

			// Account for the size change in the new list
			return_list->setSize( end - start + 1 );
			return_list->resetMidix();

			// Cut off the ends
			return_list->at(0)->Prior = 0;
			return_list->at( end - start )->Post = 0;

			// Reset the location of the midix to the head node
			resetMidix();

			// If the cut out part of this list should be returned
			if ( retPtr )
			{
				return return_list;
			} else {
				return_list->clear();
				return 0;
			}
		}

	};
}

#endif
