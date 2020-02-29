/*
Linus Listix string class
(c) Nicolaus Anderson

You are free to use this code for both private and commercial purposes.
*/

#include "LinusListix.h"

#include <irrstring.h>

typedef char ch8;


namespace Linus
{

class LLxString
{
private:
	LListix<ch8> str;

public:

		//! Convert stringc to LLxString
	/* Constant, available converter for converting irrlicht strings
	of type c8 to a Linus Listix string of type ch8. */
	static LListix<ch8> * convertStringcToLListixch8( irr::core::stringc text )
	{
		LListix<ch8> * newstring;

		for ( si32 c = 0; c < (si32)text.size(); c++ )
		{
			newstring->push_back( text[c] );
		}

		return newstring;
	}

		//! Constructor
	/**/
	LLxString() {}

		//! Constructor
	/**/
	LLxString( const char * text )
	{
		for ( si32 c = 0; text[c]; c++ ) // this could cause issues
		{
			str.push_back( text[c] );
		}
	}

		//! Constructor
	/**/
	LLxString( LListix<ch8> text )
	{
		for ( si32 c = 0; c < text.Size(); c++ )
		{
			str.push_back( text[c] );
		}
	}

		//! Constructor
	/**/
	LLxString( LListix<ch8> * text )
	{
		for ( si32 c = 0; c < text->Size(); c++ )
		{
			str.push_back( text->copyOf(c) );
		}
	}

		//! Constructor
	/**/
	LLxString( irr::core::stringc text )
	{
		str = *((LListix<ch8> *)convertStringcToLListixch8( text ));
	}

		//! Constructor
	/**/
	LLxString( irr::core::stringw text )
	{
		str = *((LListix<ch8> *)convertStringcToLListixch8( irr::core::stringc(text) ));
	}
	
		//! Direct access oprator
	/* Find and return a copy of the object at this particular location */
	ch8& operator[] (si32 index)
	{
		return (ch8&)str[index];
	}

		//! Empty string
	/* Clears the contents of the string. */
	void clear()
	{
		str.clear();
	}

		//! Return string size
	/**/
	si32 Size()
	{
		str.Size();
	}

		//! Insert character
	/**/
	void insert( ch8 chr, si32 index )
	{
		str.insert( chr, index );
	}

		//! Insert string
	/**/
	void insert( irr::core::stringc text, si32 index )
	{
		LListix<ch8> * endtext = str.cutOff( index, true, false );

		LLxString * newtext = new LLxString(
			(LListix<ch8>*)convertStringcToLListixch8( text )
			);

		str.append( &(newtext->str) );

		str.append( endtext );
	}

		//! Append string
	/**/
	void append( irr::core::stringc text )
	{
		str.append(
			convertStringcToLListixch8( text )
			);
	}

		//! Direct assignment operator
	/* Copies the contents of the given string to this one. */
	void operator= ( LLxString text )
	{
		for ( si32 c = 0; c < str.Size() && c < text.Size(); c++ )
		{
			str.replace( c, text[c] );
		}

		if ( text.Size() < str.Size() )
		{
			for ( si32 c = text.Size(); c < str.Size(); str.deleteAt( c ) );
		} else {
			if ( str.Size() < text.Size() )
			{
				for ( si32 c = str.Size(); c < text.Size(); str.push_back(text[c]) );
			}
		}

	}

		//! Return string as stringc
	/**/
	irr::core::stringc toStringc()
	{
		irr::core::stringc returnstring;

		for ( si32 c = 0; c < str.Size(); c++ )
		{
			returnstring.append( str[c] );
		}

		return returnstring;
	}
};


} // end namespace Linus