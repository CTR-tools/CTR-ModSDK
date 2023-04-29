// complete struct
struct Item
{
	struct Item* next;
	struct Item* prev;
};

// complete struct
struct LinkedList
{
	struct Item* first;
	struct Item* last;
	int count;
};