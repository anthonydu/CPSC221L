/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
  /// Update to return the index you are choosing to be your root.
  return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const {
  /// Update to return the index of the left child.
  return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const {
  /// Update to return the index of the right child.
  return currentIdx * 2 + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const {
  /// Update to return the index of the parent.
  return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const {
  /// Update to return whether the given node has a child
  return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const {
  /// Update to return the index of the child with highest priority
  /// as defined by higherPriority()
  auto l = leftChild(currentIdx);
  auto r = rightChild(currentIdx);
  if (r >= _elems.size()) return l;
  return higherPriority(_elems[l], _elems[r]) ? l : r;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx) {
  /// Implement the heapifyDown algorithm.
  if (!hasAChild(currentIdx)) return;
  size_t maxChildIdx = maxPriorityChild(currentIdx);
  if (higherPriority(_elems[maxChildIdx], _elems[currentIdx])) {
    std::swap(_elems[currentIdx], _elems[maxChildIdx]);
    heapifyDown(maxChildIdx);
  }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx) {
  if (currentIdx == root()) return;
  size_t parentIdx = parent(currentIdx);
  if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
    std::swap(_elems[currentIdx], _elems[parentIdx]);
    heapifyUp(parentIdx);
  }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
  /// Depending on your implementation, this function may or may
  /// not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) {
  /// Construct a heap using the buildHeap algorithm
  /// Your algorithm should use heapifyDown() so that it constructs
  /// the same heap as our test case.
  _elems = elems;
  if (_elems.size() == 0) {
    heap();
    return;
  }
  for (size_t i = _elems.size() - 1; i != 0; i--) {
    heapifyDown(i);
  }
  heapifyDown(0);
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
  /// Remove, and return, the element with highest priority
  auto elem = peek();
  _elems[root()] = _elems[_elems.size() - 1];
  _elems.pop_back();
  heapifyDown(root());
  return elem;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
  /// Return, but do not remove, the element with highest priority
  return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem) {
  /// Add elem to the heap
  _elems.push_back(elem);
  heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
  /// Determine if the heap is empty
  return _elems.empty();
}
