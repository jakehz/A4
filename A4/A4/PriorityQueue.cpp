#include "pqueue1.h"
#include <iostream>

PriorityQueue::PriorityQueue()
{
	// initialize with no pointer to any head
	head_ptr = NULL;
	// and with a count of zero nodes in the queue
	many_nodes = 0;
}

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
	// start at the head of the linked list.
	Node* cursor = head_ptr; 
	Node* precursor = NULL;
	if (head_ptr == NULL)
	{
		// initialize each part of the head
		head_ptr = new Node;
		head_ptr->data = entry;
		head_ptr->priority = priority;
		head_ptr->link = NULL;
	}
	else
	{
		// we store all the items in order, and let the get front function
		// get the highest function. this way we don't worry about storing 
		// in order

		// go to the end of the list
		while (cursor != NULL)
		{
			precursor = cursor; 
			cursor = cursor->link;
		}
		// at this point cursor must be NULL
		// so we create a new node in its place
		cursor = new Node;
		// and initialize it with data
		cursor->data = entry;
		cursor->priority = priority;
		// link to NULL since its the last node of the list
		cursor->link = NULL;
		if (precursor != NULL)
		{
			// former last node points to new last node
			precursor->link = cursor;
		}
	}
	many_nodes++;
}
PriorityQueue::Item PriorityQueue::get_front()
{
	Node* cursor = head_ptr;
	Node* precursor = NULL;
	Item nodeItem = 0;
	Node* maxNode = NULL;
	Node* preMaxNode = NULL;
	unsigned int maxPrior = 0;
	if (size() > 0)
	{
		// cycle through each node of the list
		while (cursor != NULL)
		{
			// check to see if the current node's priority is GREATER
			// that the max recorded.
			// if it is equal, it is ignored, so the first instance will only be recorded.
			if (cursor->priority > maxPrior)
			{
				// record the max priority
				maxPrior = cursor->priority;
				// and the address of the node that has it
				maxNode = cursor;
				preMaxNode = precursor;
			}
			// move on to next node.
			precursor = cursor;
			cursor = cursor->link;
		}
		// once this is done we will have the node with the highest priority's address
		// precursor, and priority.
		if (maxNode != NULL)
		{
			// get the max node's data to return.
			nodeItem = maxNode->data;
		}
		// if the max node is the head pointer
		if (maxNode == head_ptr || preMaxNode == NULL)
		{
			// make a temp pointer 
			Node *remove_ptr;
			// then set it to the head
			remove_ptr = head_ptr;
			// move the head to the next pointer
			head_ptr = head_ptr->link;
			// then remove the old head
			delete remove_ptr;
		} 
		else
		{
			// make a temp remove pointer
			Node* remove_ptr;
			// set the remove pointer to the node after the pre max node (max node)
			remove_ptr = preMaxNode->link;
			// set the pre max node link to the link of the former max node
			preMaxNode->link = remove_ptr->link;
			// delete the max node 
			delete remove_ptr;
		}
		many_nodes--;
	}

	return nodeItem;
}

PriorityQueue::PriorityQueue(const PriorityQueue& source)
{
	// cursor to iterate through each node of source
	Node* cursor = source.head_ptr;
	// variables for holding the current node's data
	size_t curr_prior;
	Item curr_data;
	while (cursor != NULL)
	{
		// get the current priority and data of this node
		curr_prior = cursor->priority;
		curr_data = cursor->data;
		// then insert it into the linked list of the current queue
		insert(curr_data, curr_prior);
		// go on to the next node
		cursor = cursor->link;
	}
}

void PriorityQueue::operator =(const PriorityQueue& source)
{
	if (&source == this)
	{
		return;
	}
	// goes through and deletes each node by getting the front node and subsequently 
	// deleting that node
	while (size() != 0)
	{
		get_front();
	}

	// cursor to iterate through each node of source
	Node* cursor = source.head_ptr;
	// variables for holding the current node's data
	size_t curr_prior;
	Item curr_data;
	while (cursor != NULL)
	{
		// get the current priority and data of this node
		curr_prior = cursor->priority;
		curr_data = cursor->data;
		// then insert it into the linked list of the current queue
		insert(curr_data, curr_prior);
		// go on to the next node
		cursor = cursor->link;
	}
}

PriorityQueue::~PriorityQueue()
{
	// goes through and deletes each node by getting the front node and subsequently 
	// deleting that node
	while (size() != 0)
	{
		get_front();
	}
	head_ptr = NULL;
	many_nodes = 0;
}
