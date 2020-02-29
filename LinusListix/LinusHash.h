/*
This is the header file for LinusHash
(C) Nic Anderson
Date created: Oct 23, 2012

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

#ifndef _Linus_Hash_INCLUDED_
#define _Linus_Hash_INCLUDED_

// simple definitions for usage with this hash table
#ifdef _MSC_VER
typedef __int32                 si32;
#else
typedef signed int              si32;
#endif

namespace Linus
{

	template<class Value>
	class LinusHashNode
	{
	public:
		si32 key;
		Value value;

		LinusHashNode( si32 new_key=0 ) : key(new_key), value(0)
		{}

		LinusHashNode( si32 new_key=0, Value new_value )
			: key(new_key), value(new_value)
		{}
	};

	template<class Value>
	class LinusHash
	{
		LinusHashNode<Value>* table;
		si32 size;
		si32 contains;
		bool resizes; // Not implemented yet

	public:
		LinusHash( si32 initial_size=100, bool resizeable=false )
			: size(initial_size), resizes(resizeable), contains(0)
		{
			if ( size > 0 )
			{
				table = new LinusHashNode<Value>[initial_size];

				si32 i =0;
				for ( ; i < size; i++ )
				{
					table[i] = new LinusHashNode<Value>();
				}
			}
		}

		si32 getKey( si32 identifier, bool mustBeEmpty=false )
		{
			si32 key = getProperKey( identifier );
			si32 step = 1;

			while (
				( table[key].key != indentifier
				&& table[key].value != 0
				&& !mustBeEmpty )
				|| (mustBeEmpty && contains < size )
				)
			{
				// Quadratic search
				key += step*step;
				step++;

				if ( key >= size )
					key -= size;

				if ( step >= size )
				{
					key = -1;
					break;
				}
			}

			return key;
		}

		void addValue( si32 identifier, Value value )
		{
			si32 key = getKey(value, true);

			if ( key != -1 )
			{
				table[key].key = indentifier;
				table[key].value = value;

				contains++;
			}
		}

		void removeValue( si32 identifier, bool destroy=false )
		{
			si32 key = getKey(indentifier);
			table[key].key = 0;
			if ( destroy )
				delete table[key].value;
			table[key].value = 0;

			contains--;
		}

	protected:
		si32 getProperKey( si32 indentifier )
		{
			return indentifier%size;
		}
	}
}

#endif