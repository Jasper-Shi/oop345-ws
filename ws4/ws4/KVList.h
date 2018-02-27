#pragma once
template <typename K, typename V, int N>
class KVList {
	K k[N];
	V v[N];
	size_t count;
public:
	KVList() //- default constructor - adopts a safe empty state
	{
		count = 0;
	}
	size_t size() const //- returns the number of entires in the key - value list
	{
		return count;
	}
	const K& key(int i) const //- returns an unmodifiable reference to the key of element i in the list
	{
		if (i < N)
			return k[i];
	}
	const V& value(int i) const //- returns an unmodifiable reference to the value of element i in the list
	{
		if (i < N)
			return v[i];
	}
	KVList& add(const K& tempk, const V& tempv) //- adds a new element to the list if room exists and returns a reference to the current object, does nothing if no room exists
	{
		if (count < N) {
			k[count] = tempk;
			v[count] = tempv;
			count++;
		}
		return *this;
	}
	int find(const K& tempk) const //- returns the index of the first element in the list with a key equal to k - defaults to 0
	{
		int temp = 0;
		for (int i = 0; i < count; i++) {
			if (k[i] == tempk)
				temp = i;
		}
		return temp;
	}
	KVList& replace(int i, const K& tempk, const V& tempv) //- replaces element i in the list with the key and value received and returns a reference to the current object
	{
		if (i < count) {
			k[i] = tempk;
			v[i] = tempv;
		}
		return *this;
	}
};