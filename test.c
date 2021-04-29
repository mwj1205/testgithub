/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("[----- [�ѹο�] [2018038047] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}
/* inorder��� tree ��ȸ */
void inorderTraversal(Node* ptr)
{
	if(ptr){
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}
/* preorder��� tree ��ȸ */
void preorderTraversal(Node* ptr)
{
	if(ptr){
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);

	}
}
/* postorder��� tree ��ȸ */
void postorderTraversal(Node* ptr)
{
	if(ptr){
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

int insert(Node* head, int key)
{
	/* check pre conditions */
	if(head == NULL){
		printf("Binary search tree is not initialized.\n");
		return 0;
	}

	Node* curr = head->left; // ���� ��ġ
	Node* prev = NULL; // ������ġ(�θ���)
	Node* newnode; // ���ο� ��� ������ ������ �����ص�

	/* ���� Ʈ���̸� */
	if(head->left == NULL){
		newnode = (Node*)malloc(sizeof(Node));
		newnode->key = key;
		newnode->left = newnode->right = NULL;
		head->left = newnode; // root�� ����
		return 0;
	}
	/* ������ ��ġ Ž�� */
	while(curr){
		if(key == curr->key) { // ���� key���� �ִٸ�
			printf("same key is not allowed.\n");
			return 0;
		}
		prev = curr; 
		if(key < curr->key) curr = curr->left; // key�� ũ�⿡ ���� ����, ������ �ڽ� ���� �̵�
		else curr = curr->right;
	}
	newnode = (Node*)malloc(sizeof(Node));
	newnode->key = key;
	newnode->left = newnode->right = NULL;
	/* �θ��� �ؿ� ���� */
	if(key < prev->key) prev->left = newnode; 
	else prev->right = newnode;
}

int deleteLeafNode(Node* head, int key)
{
	/* check pre conditions */
	if(head == NULL){
		printf("Binary search tree is not initialized.\n");
		return 0;
	}
	Node* delnode = head->left;
	Node* prev = head;

	while(delnode != NULL && delnode->key != key){ // ������ ��� Ž��
		prev = delnode;
		if(delnode->key > key) delnode = delnode->left;
		else delnode = delnode->right;
	}

	/* ���ϴ� ��尡 ���ٸ� delnode == NULL */
	if(!delnode){
		printf("Cannot find the node [%d]\n",key);
		return 0;
	}
	// ������� ����
	if(delnode->left == NULL && delnode->right == NULL){
		printf("%d �� ������� \n",key);
		if(prev != head){ // ������ ��尡 root�� �ƴ� ���
			printf("%d �� ��Ʈ�� �ƴϾ�\n",key);
			if(prev->left == delnode) prev->left == NULL;
			else prev->right == NULL;
		}
		else {
			printf("%d �� ��Ʈ�� \n",key);
			head->left == NULL;
			} // ������ ��尡 root�� ���
        printf("�����ض�\n");
		free(delnode);
	}
	else{
		printf("the node [%d] is  not a leaf\n",key);
		return 0;
	}
}

Node* searchRecursive(Node* ptr, int key)
{
	/* �Է¹��� key�� ������ key�� ���� ��尡 ���ų�
	���� Ʈ���� ��� */
	if(ptr == NULL) return NULL;

	if(key == ptr->key) return ptr; // ���ϴ� �� ã�Ƽ� ����
	else if(key < ptr->key) return searchRecursive(ptr->left, key);
	return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	/* check pre conditions */
	if(head == NULL){
		return NULL;
	}
	Node* node = head->left;
	while(node){
		if(key == node->key) return node; //�Է¹��� key�� ������ key���� ��� ã���� �� ����� �ּ� ����
		if(key < node->key) node = node->left; //�Է¹��� key�� Ʈ���� key���� ������ ���� �ڽ����� �̵�
		else node = node->right; // �Է¹��� key�� Ʈ���� key���� ũ�� ������ �ڽ����� �̵�
	}
	return NULL; // ã�� ���� ������ NULL ����
}

/* postorder traversal ������ Ʈ�� ��ȸ�ϸ� �޸� ���� */
int freeBST(Node* head) 
{	
	if(head == NULL) return 0;
	freeBST(head->left);
	if(head->right != head)// headnode���� ���ѷ��� ����
		freeBST(head->right);
	free(head);
}