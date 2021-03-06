// implementation basic hashmap (unordered container)
// Mikhail Nesterenko: adapted from Proc C++
// 4/15/2014
#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>
#include <iterator>
//#include <move>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
	DefaultHash(size_t numBuckets = defaultNumBuckets); 
		size_t hash(const T & key) const;
	size_t numBuckets() const { return numBuckets_; }

private:
	// default number of buckets in the hash
	static const size_t defaultNumBuckets = 101;
	size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets) : numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
// note, this function does not work for C++ strings
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
	size_t res = 0;
	for (size_t i = 0; i < sizeof(key); ++i) {
		const unsigned char b =
			*(reinterpret_cast<const unsigned char*>(&key) + i);
		res += b;
	}
	return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value,
	typename Compare = std::equal_to<Key>,
	typename Hash = DefaultHash<Key>>
	class hashmap {

	public:
		typedef pair<const Key, Value> Element;

		// constructor
		// invokes constructors for comparison and hash objects
		hashmap(const Compare& comp = Compare(),
			const Hash& hash = Hash());

		Element* find(const Key& x);      // returns pointer to element with key x,

                 pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>						       
		 insert(const Element& x);    // inserts the key/value pair
  
                 pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>
                erase(const Key& x);         // erases element with key x, if exists

                Value& operator[] (const Key& x); // returns reference on value of

               void rehash(size_t n);
	private:

		// helper function for various searches
		typename list<Element>::iterator findElement(const Key& x, const size_t bucket);

		size_t size_;   // number of elements in the container
		Compare comp_;  // comparison functor, equal_to by default
		Hash hash_;     // hash functor 

		// hash contents: vector of buckets
		// each bucket is a list containing key->value pairs
		vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
hashmap<Key, Value, Compare, Hash>::hashmap(
	const Compare& comp, const Hash& hash) :
	size_(0), comp_(comp), hash_(hash) {
	elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value,
	typename Compare, typename Hash>
	typename list<pair<const Key, Value>>::iterator // return type
	hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket) {

	// look for the key in the bucket
	for (auto it = elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
		if (comp_(it->first, x))
			return it;

	return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

	size_t bucket = hash_.hash(x);
	auto it = findElement(x, bucket);    // use the findElement() helper   

	if (it != elems_[bucket].end())
		// found the element. Return a pointer to it.
		return &(*it); // dereference the iterator to list 
					   // then take the address of list element

	else // didn't find the element -- return nullptr
		return nullptr;
}


// finds the element with key x, inserts an
// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>

pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> // return type
 hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {
	pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> inserted;

	size_t bucket = hash_.hash(x.first);
	auto it = findElement(x.first, bucket);    // try to find the element

	// if not found, insert a new one.
	if (it == elems_[bucket].end()) {
		++size_;
		elems_[bucket].push_back(x);
		inserted.first = &(*(--elems_[bucket].end()));   // first in pair is equal to one less than end at that bucket
		inserted.second = true;                          // second in pair is true
		return inserted;   // reuturns pair
	}
	else {
	        inserted.first = nullptr;    // if not found first in pair is a null pointer
		inserted.second = false;    // if not found second in pair is faluse
		return inserted;    // returns pair
	}
}


// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool>  // return type
hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {
         pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> returned;

	 bool regErase = true;  // bool to determine if a normal erase occurs
	 
	size_t bucket = hash_.hash(x);
	auto it = findElement(x, bucket);    // try to find the element
	if (it != elems_[bucket].end()) {    // the element exists, erase it
	  std::advance(it, 1);     // moves the it up one position

	  int end = elems_.size();    // size of the vector
	  auto pos = it;      // stores the position of the iterator

	  if(it == elems_[bucket].end()){   // if it is at the end of the current bucket

	    size_t index = bucket + 1;  //gets the next position of the bucket
	    auto ip = elems_.begin()+ bucket + 1;

	    for(; ip !=elems_.end();++ip){      // iterates from the next bucket to the end
	      if(!ip->empty()){            //if the current bucket is not empty break out of the loop
		break;
	      }
	      ++index;                   //increments index to the position of the first non empty bucket
	    }
	    if(ip == elems_.end()){   // in case ip reaches the end of the vector
	      returned.first = nullptr;
	      returned.second = true;
	      regErase = false;
	    }
	    else{
	      returned.first = &(*elems_[index].begin());  // if we have not reached the end of the vector while finding the next bucket
	    returned.second = true;  // second is true
	    regErase = false;
	    }
	}

	  if(it == elems_[end - 1].end()){   // if it is at the end of the last bucket
	    returned.first = nullptr;      // first is an null pointer
	    returned.second = true; // second is still true
	    regErase = false;
	  }
	  elems_[bucket].erase(--it);    // erases at the position where given key is stored

	  if(regErase){                      // if none of the other conditons have been met a normal erase occurs
	    returned.first = &(*pos);       // if one past erased is still in current bucket first is equal to next position
	    returned.second = true;         // second is true
	  }	
		--size_;
	}

	else{  // if not found
	  returned.first = nullptr;  
	  returned.second = false;
	}

	return returned;  // returns pair
}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {
        
	Element* found = find(x);
	if (found == nullptr) { // if key not found, create new element with empty value
              
	        auto pos =  insert(make_pair(x, Value())); // returns pair at posotion inseted and bool
		found = pos.first; //   found is equal to first of the returned pair
	}

	
	
	return found->second;
}
//template<typename T>
template <typename Key, typename Value, typename Compare, typename Hash>
//template<typename T>
void  hashmap<Key, Value, Compare, Hash>::rehash(size_t n){
  vector<list<Element>> nv(n);// new vector of list where new rehash is stored


  if(n > size_){

  DefaultHash<Key> defaultH(n);   // contructs new defaultHash with new size
  for(auto it1 = elems_.begin(); it1 != elems_.end(); ++ it1){    // loops through vector
    for(auto it2 = it1->begin(); it2 != it1->end(); ++it2){   // loops through list

      size_t bucket = defaultH.hash(it2->first);   // gets the new bucket for elements in old hashMap
      nv[bucket].push_back(*it2);    // pushes element in new apporiate bucket into nv
    }
    
  }
  elems_ = std::move(nv);    // moves the contents from nv into elems_
  }
  else{
    return;
  }
}
