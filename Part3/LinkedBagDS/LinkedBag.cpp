//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation.
	 @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <type_traits>

//   SORTING ----------------------------------------------------
template<class ItemType>
void LinkedBag<ItemType>::sort(int method)
{
	if (itemCount <= 1)
		return;

	if (method == 0)
	{
		mergeSort();
	}
	else
	{
		quickSort();
	}
}

template<class ItemType>
void LinkedBag<ItemType>::mergeSort() //merge sort
{
	headPtr = mergeSortRec(headPtr); //set headptr to sorted headptr after apply merge sort
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::mergeSortRec(Node<ItemType>* head) //recursive function for merge sort
{
	if (!head || !head->getNext()) //base case for only one item or no item
		return head;

	Node<ItemType>* mid = splitMiddle(head); //split the list from middle

	Node<ItemType>* left = mergeSortRec(head); //left list after split
	Node<ItemType>* right = mergeSortRec(mid); //right list after split

	return merge(left, right); //merge sorted lists
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::splitMiddle(Node<ItemType>* head) //split list from middle
{
	if (!head || !head->getNext()) //case if only one item or no item
		return nullptr;

	Node<ItemType>* slow = head, * fast = head->getNext(); //* prev = nullptr; //initial pointers for split

	while (fast && fast->getNext()) //loop for finding middle
	{
		//prev = slow;
		slow = slow->getNext();
		fast = fast->getNext()->getNext();
	}

	Node<ItemType>* second = slow->getNext(); //slow is end of first half
	slow->setNext(nullptr); //split
	return second; //return second half
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::merge(Node<ItemType>* l1, Node<ItemType>* l2) //merge two lists
{
	Node<ItemType> dummy(0), * tail = &dummy; //initial dummy nodes

	while (l1 && l2) //loop when both lists exist
	{
		if (l1->getItem() < l2->getItem()) //find smaller head
		{
			tail->setNext(l1);
			l1 = l1->getNext();
		}
		else
		{
			tail->setNext(l2);
			l2 = l2->getNext();
		}

		tail = tail->getNext();
	}

	tail->setNext(l1 ? l1 : l2); //append the existing list to tail

	return dummy.getNext(); //merged list starts from next node of dummy
}

//Extra Credit -- TO DO: implement quick sort and change its prototype 
//                       if you need to.
template<class ItemType>
void LinkedBag<ItemType>::quickSort() //quick sort
{
	headPtr = quickSortRec(headPtr, getTail(headPtr)); //set headptr to sorted ptr after apply quick sort
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::partition(Node<ItemType>* head, Node<ItemType>* end,
	Node<ItemType>** newHead, Node<ItemType>** newEnd) //partition the list after pivot
{
	Node<ItemType>* pivot = end; //initial nodes
	Node<ItemType>* prev = nullptr;
	Node<ItemType>* curr = head;
	Node<ItemType>* tail = pivot;

	while (curr != pivot) //iterate through the list and partition around the pivot
	{
		if (curr->getItem() < pivot->getItem())
		{
			if (*newHead == nullptr)
				*newHead = curr;  //first node less than pivot

			prev = curr;
			curr = curr->getNext();
		}
		else
		{
			if (prev) //move the node to the tail of the list
				prev->setNext(curr->getNext());

			Node<ItemType>* temp = curr->getNext();
			curr->setNext(nullptr);
			tail->setNext(curr);
			tail = curr;
			curr = temp;
		}
	}

	if (*newHead == nullptr) //set the new tail to the pivot
		*newHead = pivot;

	*newEnd = tail;

	return pivot;
}

template <class ItemType>
Node<ItemType>* LinkedBag<ItemType>::quickSortRec(Node<ItemType>* head, Node<ItemType>* end) //recursive function for quick sort
{
	if (!head || head == end) //base case for only one item or no item
		return head;

	Node<ItemType>* newHead = nullptr, * newEnd = nullptr; //initial head and end

	Node<ItemType>* pivot = partition(head, end, &newHead, &newEnd); //partition the list around a pivot

	if (newHead != pivot) //if the pivot is not the first element, recursively sort the left part
	{
		Node<ItemType>* temp = newHead;

		while (temp->getNext() != pivot) //recursively sort the list before the pivot
			temp = temp->getNext();

		temp->setNext(nullptr);
		newHead = quickSortRec(newHead, temp);

		temp = getTail(newHead); //connect the sorted part to pivot
		temp->setNext(pivot);
	}

	pivot->setNext(quickSortRec(pivot->getNext(), newEnd)); //recursively sort the right part

	return newHead;
}

template <class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getTail(Node<ItemType>* head) //get the tail of the list
{
	while (head != nullptr && head->getNext() != nullptr) //loop till the end
		head = head->getNext();

	return head;
}
// --------------------------------------------------------------

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag) {
	itemCount = aBag.itemCount;
	Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain

	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original bag is empty
	else
	{
		// Copy first node
		headPtr = new Node<ItemType>();
		headPtr->setItem(origChainPtr->getItem());

		// Copy remaining nodes
		Node<ItemType>* newChainPtr = headPtr;		// Points to last node in new chain
		origChainPtr = origChainPtr->getNext();	  // Advance original-chain pointer

		while (origChainPtr != nullptr)
		{
			// Get next item from original chain
			ItemType nextItem = origChainPtr->getItem();

			// Create a new node containing the next item
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		}  // end while

		newChainPtr->setNext(nullptr);				  // Flag end of chain
	}  // end if
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag() {
	clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry) {
	// Add to beginning of chain: new node references rest of chain;
	// (headPtr is null if chain is empty)		  
	Node<ItemType>* nextNodePtr = new Node<ItemType>();

	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);  // New node points to chain
	headPtr = nextNodePtr;			 // New node is now first node
	itemCount++;

	return true;
}  // end add

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
	std::vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}  // end while

	return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry) {
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem) {
		// Copy data from first node to located node
		entryNodePtr->setItem(headPtr->getItem());

		// Delete first node
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		itemCount--;
	} // end if

	return canRemoveItem;
}  // end remove

template<class ItemType>
bool LinkedBag<ItemType>::removeAlt(const ItemType& anEntry) {
	Node<ItemType>* prev = headPtr;
	Node<ItemType>* cur = headPtr;
	bool found = false;

	while ((cur != nullptr) && !found) {
		found = (*(cur->getItem()) == *anEntry);
		if (!found) {
			prev = cur;
			cur = cur->getNext();
		}
	}

	if (found) {
		prev->setNext(cur->getNext());
		// delete cur->getItem();
		delete cur;
		cur = nullptr;
		itemCount--;
	}

	return found;

}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear() {
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr) {
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);

		// delete nodeToDeletePtr->getItem(); 
		delete nodeToDeletePtr;

		nodeToDeletePtr = headPtr;
	}  // end while
	// headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
}  // end clear

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anEntry == curPtr->getItem())
		{
			frequency++;
		} // end if

		counter++;
		curPtr = curPtr->getNext();
	} // end while

	return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const {
	return (getPointerTo(anEntry) != nullptr);
}  // end contains


// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const {
	bool found = false;
	Node<ItemType>* curPtr = headPtr;

	while (!found && (curPtr != nullptr))
	{
		if (anEntry == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	} // end while

	return curPtr;
} // end getPointerTo