#include "ordered_array.hpp" include < iostream>
ordered_array::ordered_array(int cap)
{
	max = cap;
}
//private variables sz, and max in .hpp file
// destructor
ordered_array::~ordered_array()
{
//	delete[] data;
}

/* size()
   Returns the size (number of elements in the array). */
int ordered_array::size()
{
	return sz;
}
/* capacity()
   Returns the maximum size of the array. */
int ordered_array::capacity()
{
	return max;
}
/* insert(e)
   Insert e into the array. Note that it is OK to insert duplicates; if n
   copies of a value are inserted into the array then n copies should appear
   in the array.
   If size() == capacity() then this does nothing.
   If e == -2147483648 then this does nothing (i.e., -2147483648 is not a
   valid value to insert). */
void ordered_array::insert(int elem)
{
	if (elem == -2147483648)
	{
		return;
	}
	if (sz >= max)
	{
		return;
	}
	else
	{
		data.push_back(elem);
		sz++;
		for (int i = sz - 1; i > 0; i--)
		{
			if (data[i - 1] > data[i])
			{
				int temp = data[i];
				data[i] = data[i - 1];
				data[i - 1] = temp;
			}
		}
	}
	return;
}
/* remove(e)
   Remove e from the array, if it exists. (If it does not exist, the
   array should be unchanged.) If multiple copies of e are present, only
   one should be removed.
   If e = -2147483648 then this does nothing. */
void ordered_array::remove(int elem)
{
	if (elem == -2147483648)
	{
		return;
	}
	if (sz == 0)
	{
		return;
	}
	for (int i = 0; i < sz; i++)
	{
		if (data[i] == elem)
		{
			for (int j = i; j < sz - 1; j++)
			{
				data[j] = data[j + 1];
			}
			data.pop_back();
			sz--;
			return;
		}
	}
	return;
}
/* exists(e)
   Returns true if e is present at least once in the array.
   If e == -2147483648 then this returns false. */
bool ordered_array::exists(int elem)
{
	if (elem == -2147483648)
	{
		return false;
	}
	for (int i = 0; i < sz; i++)
	{
		if (data[i] == elem)
		{
			return true;
		}
	}
	return false;
}
/* at(i)
   Returns the value in the array at index i, which should be >= 0 and <
   size().
   If i < 0 or i >= size(), then at(i) should throw a std::out_of_range
   exception. (This is what std::vector does in this situation.)
   Note that at() should *never* return -2147483648 (because insert() should
   never insert it).c */
int ordered_array::at(int i)
{
	if (i < 0 || i >= sz)
	{
		throw std::out_of_range("int out of range");
	}
	else
	{
		return data[i];
	}
}
