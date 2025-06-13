#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    	int data;
    	struct Node* next;
};

struct Node* createNode(int value) {
    	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    	if (!newNode) {
        		fprintf(stderr, "Memory allocation failed\n");
        		exit(1);
    	}
    	newNode->data = value;
    	newNode->next = NULL;
    	return newNode;
}

void printL(struct Node* head) {
    	if (!head) {
        		printf("Empty list\n");
        		return;
    	}
    	printf("Number: ");
    	while (head) {
        		printf("%d ", head->data);
        		head = head->next;
    	}
    	printf("END\n");
}

void freeL(struct Node* head) {
    	struct Node* temp;
    	while (head) {
        		temp = head;
        		head = head->next;
        		free(temp);
    	}
}

struct Node* revL(struct Node* head) {
    	struct Node *prev = NULL, *current = head, *next = NULL;
    	while (current) {
        		next = current->next;
        		current->next = prev;
        		prev = current;
        		current = next;
    	}
    	return prev;
}

struct Node* addL(struct Node* l1, struct Node* l2) {
    	l1 = revL(l1);
    	l2 = revL(l2);
    	struct Node *result = NULL, *tail = NULL;
    	int carry = 0;

    	while (l1 || l2 || carry) {
        		int sum = carry;
        		if (l1) {
            		sum += l1->data;
            		l1 = l1->next;
        		}
        		if (l2) {
            		sum += l2->data;
            		l2 = l2->next;
        		}
        		carry = sum / 10;
        		int digit = sum % 10;
        		struct Node* newNode = createNode(digit);
        		if (!result) {
            		result = tail = newNode;
        		} 
		else {
            		tail->next = newNode;
            		tail = newNode;
        		}
    	}
    	result = revL(result);
    	return result;
}

struct Node* readNumber() {
    	struct Node *head = NULL, *tail = NULL;
    	int ch, hasDigit = 0;

    	printf("Enter a number (end with +): ");
    	while ((ch = getchar()) != EOF) {
        		if (ch == '+') {
            		if (hasDigit) {
                			while (getchar() != '\n'); 
                			break;
            		}
            		printf("No input: ");
            		continue;
        		}
        		if (isdigit(ch)) {
            		struct Node* newNode = createNode(ch - '0');
            		if (!head) {
                			head = tail = newNode;
            		} 
			else {
                			tail->next = newNode;
                			tail = newNode;
            		}
            		hasDigit = 1;
        		} 
		else if (ch == '\n') {
            		if (!hasDigit) {
                			printf("No digits entered, try again: ");
            		}
            		continue;
        		}
    	}
    	return head;
}

int main() {
    	struct Node *head1 = NULL, *head2 = NULL;

    	head1 = readNumber();
    	if (!head1) {
        		printf("No valid first number entered\n");
        		return 1;
    	}
    	printL(head1);
    	head2 = readNumber();
    	if (!head2) {
        		printf("No valid second number entered\n");
        		freeL(head1);
        		return 1;
    	}
    	printL(head2);

    	struct Node* sum = addL(head1, head2);
    	printf("Sum: ");
    	printL(sum);

    	freeL(head1);
    	freeL(head2);
    	freeL(sum);

    	return 0;
}