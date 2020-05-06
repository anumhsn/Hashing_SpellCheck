//Modified by Anum Hassan
// Linear Probing class that provides the functions needed to retrieve information about the hashtable

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>

// Linear probing implementation.
template <typename HashedObj>
class HashTableDouble{
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x, int r) const {
    return IsActive(FindPos(x, r));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    collisions_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x, int r) {
    // Insert x as active
    size_t current_pos = FindPos(x, r);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash(r);    
    return true;
  }
    
  bool Insert(HashedObj && x, int r) {
    // Insert x as active
    size_t current_pos = FindPos(x, r);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash(r);

    return true;
  }

  bool Remove(const HashedObj & x, int r) {
    size_t current_pos = FindPos(x, r);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

// return number of elements
int GetNumElements(){
  return current_size_;
}

// return table size
int GetSizeOfTable(){
  return array_.size();
}

// get number of collisions
int GetNumCollisions(){
  return collisions_;
}

// get number of probes
int GetNumProbes(){
  return probes_;
}
 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
  mutable size_t collisions_;
  mutable size_t probes_;

  // int r;
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x , int r ) const {
    size_t offset = DoubleHash(x, r);
    size_t current_pos = InternalHash(x);
    probes_ = 1;
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      collisions_++;
      probes_++;
      current_pos += offset;  // Compute ith probe.
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash(int r) {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_), r);
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }

  size_t DoubleHash(const HashedObj & x, int r) const {
      static std::hash<HashedObj> hf;
      
      return (r - (hf(x) %r) % array_.size());
  }
};

#endif  // LINEAR_PROBING_H