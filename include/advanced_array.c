#include "advanced_array.h"

struct advanced_array *head;

void insert(int key, void *value) {
    struct advanced_array *newNode = (struct advanced_array*)page_allocator(sizeof(struct advanced_array));
    struct advanced_array *lastNode = head;

    newNode->key = key;
    newNode->addressValue = value;

    if(head == NULL) {
        head = newNode;
    }

    while(lastNode->next != 0) {
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
}

void Display() {
}

void *search(int key) {
	int isFound = 1;
	while(head != NULL)
	{
		if(head->key == key)
			return head->addressValue;
		else
			isFound = 0;
			
		head = head->next;
	}
	
	if(isFound == 0)
		return 0;
}
