//	LinkedBag340.cpp
//	Updated by Danny Ceron
#include"LinkedBag.h"
#include<iostream>
#include<string>
#include<vector>//for the vector in ramdom remove
#include<stdlib.h>//srand, rand
#include<time.h>//time

//#include"LinkedBag.cpp"
//#include"BagInterface.h"

	// Remove the second node using smart pointers
template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() 
{
	bool statement = false;
	std::shared_ptr<Node<ItemType>> pointerToDelete{ headPtr };
	headPtr = headPtr->getNext();

	if (headPtr!= nullptr)
	{
		headPtr->setItem(pointerToDelete->getItem());
		statement = true;
		itemCount--;
	}
	return statement;
}

// Add a node to the end of the linked list using smart pointers
template<typename ItemType>
bool  LinkedBag<ItemType>::addEnd340(const ItemType& item)
{
	//Node<ItemType>* lastNode = headPtr;
	std::shared_ptr<Node<ItemType>> lastNode{ headPtr};
	std::shared_ptr<Node<ItemType>> pointerToDelete = std::make_unique<Node<ItemType>>();
	
	while (lastNode->getNext() != nullptr)
	{
		lastNode = lastNode->getNext();
	}
	pointerToDelete->setItem(item);

	lastNode->setNext(pointerToDelete);
	itemCount++;

	return true;
}

// getCurrentSize() - Iterative
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const
{
	int bagsize = 0;
	//Node<ItemType>* current = headPtr;
	std::shared_ptr<Node<ItemType>> current{ headPtr };
	while ((current != nullptr)&&(bagsize<itemCount))
	{
		bagsize++;
		current = current->getNext();
	}
	return bagsize;
}

// getCurrentSize() - Recursive
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const
{
	const std::shared_ptr<Node<ItemType>>current{ headPtr };
	return getCurrentSize340RecursiveHelper(current);
}

// getCurrentSize() - Recursive

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const
{
	/*its impossible to traverse to each node recursively without any parameter passing. 
	that why i just called the other function, not usre if I am allowed*/
	return getCurrentSize340Recursive();
}

// getFrequencyOf340Recursive() - Recursive
template<typename ItemType>
 int LinkedBag<ItemType> :: getFrequencyOf340Recursive(const ItemType& itemName) const
{
	 //Node<ItemType>* current = headPtr;
	 std::shared_ptr<Node<ItemType>> current{ headPtr };
	 return getFrequencyOf340RecursiveHelper(current,itemName);
}

// getFrequencyOf340Recursive() - Recursive
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& itemName) const
{
	//I gain it is hard to do recursion without passing the next node in parameters.
	//I tried using static but that did not work. and most of samples online youtube, they pass node on the parameters.
	return getFrequencyOf340Recursive(itemName);
}

// Remove a random node
template<typename ItemType>
ItemType LinkedBag<ItemType> :: removeRandom340()
{
	/*doing this is time and memory in efficient, but it is easier to see whats going on
	doing this is more secure to remove items that are actually in the bag.*/ 
	std::vector<ItemType> temp = this->toVector();//using std because vactor is part of it

	srand(time(NULL));//initialized random seed
	//generating random number from 0 to the size of the vector.
	int random_number = rand() % temp.size();

	ItemType var = temp[random_number];//we can just use the righside in the revome
	//temp.erase(random_number);//erases randomnumber from the vector.
	remove(var);
	return var ;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(const std::shared_ptr<Node<ItemType>>& node)const
{
	//Node<ItemType>* current = node;
	std::shared_ptr <Node<ItemType>> current{ node };
	if (current->getNext() == nullptr) { return 1; }//check to see if the next node is a node. to not over count. ;D
	else
	{
		return 1 + getCurrentSize340RecursiveHelper(current->getNext());//+1 to increase by one for each node.
	}
}
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(const std::shared_ptr<Node<ItemType>>& node, const ItemType& itemInbag) const
{
	//Node<ItemType>* current = node;
	std::shared_ptr <Node<ItemType>> current{node};
	if (current == nullptr) { return 0; }
	else if(current->getItem() == itemInbag)
	{
		return 1 + getFrequencyOf340RecursiveHelper(current->getNext(), itemInbag);//
	}
	else
	{
		return getFrequencyOf340RecursiveHelper(current->getNext(), itemInbag);//
	}
	return 0;
}//very needed
