/*
 * Binary Search Tree #2
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

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack()
{

}



int main()
{
	char command;
	int key;
	Node* head = NULL;
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
		printf("------------[ �� �� �� ]------------[ 2018038014 ]---------------\n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
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

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s �����ڷ� 32�������� �����Ͽ����ϴ�.
 */
// �ݺ��� ���� ��ȸ 
void iterativeInorder(Node* node)
{
	top =-1;  // ������ �ʱ�ȭ
	for(;;)
	{
		for(;node; node = node->left)  // ��尡 ���� �ƴҶ����� ���� ��� Ž��
		{
			push(node); // ���ÿ� ����
		}
		node = pop(); // ���ؿ��� ����
		if(!node) break; // ���� �����̸� �ݺ����� �����Ѵ�.

		printf(" [%d] ", node->key);		// Ű�� ���
		node = node ->right ;  			// ����� ���������� Ž��
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	enQueue(ptr);		//ť�� ��Ʈ��带 �ϳ� �־����

	
	for(;;)
	{
		ptr = deQueue();	// ť�� ���Ե� ����� �ּҸ� ����

		if(ptr)									// ��Ʈ ��尡 ���� �ƴϸ�
		{
			printf(" [%d] ",ptr->key);		
			if(ptr->left)			 			// ���� �ڽ� ��尡 ������ 
			{
				enQueue(ptr->left);				// ť�� ���� �ڽ� ��� ����
			}
			if(ptr->right)						// ������ �ڽ� ��尡 ������
			{
				enQueue(ptr->right);			// ť�� ������ �ڽ� ��� ����

			}
		}
		else if(!ptr)	// ��尡 ���̸� �ݺ����� Ż���Ѵ�.
			break;
		
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* ptr=head->left;                    //��Ʈ��带 ����Ų��
	Node* previous=NULL;                    //������ ������带 NULL�� �ʱ�ȭ ���ֱ� ���ؼ� ����
	Node* find=NULL;                        //�ڽĳ�尡2���� ��忡�� �����ʿ��� ���������� Ȥ�� ���ʿ��� ����ū ����� ���� ã������ ���
	Node* check=NULL;
	Node* fprevious=NULL;                  //find�� ������带 ã�� ���� ���� ����
	while (ptr)                               //��尡 NULL�϶� ����
	{
		if(ptr->key==key)                      //�ش��尡 key���̶� ��ġ�ϸ�
		{

			//�ڽ��� 0���� �ܸ�����϶�
			if(ptr->left==NULL&&ptr->right==NULL)   //�ش��尡 ���ʰ� �������� ����->�ܸ�������� Ȯ�����ϰ�
			{
				if(previous==NULL)                 //��Ʈ��带 �����Ұ��
				{
					free(ptr);                     //������
					head->left=NULL;               //����� ���� �ʱ�ȭ
					break;
				}

				                                    //�ܸ����� �ö� ������忡�� ���ʿ��� ���� �����ʿ��� ���� Ȯ��
				if(previous->left!=NULL)            //���� ��尡 ���̸� �߻��ϴ� ����ó��
				{
				  if(previous->left->key==key)       //�������� �ش� ���ʳ���� key���� ������
				  {
					free(ptr);                        //�����Ҵ�����->����
					previous->left=NULL;              //������ ������尡 ����Ű�°��� NULL�� �ʱ�ȭ
				  }
				}
				if(previous->right!=NULL)         //������ ��尡 ���̸� �߻��ϴ� ����ó��
				{
				 if(previous->right->key==key)    //�� �������� key���� ��ġ�ϸ�
				 {
					free(ptr);                    //�����Ҵ�����->����
					previous->right=NULL;         //������ ������尡 ����Ű�°��� NULL�� �ʱ�ȭ
				 }
				}
				break;                          //key���� ��ġ�ϴ� ��带 ������ while���� ����
			}
			//�ڽ��� 1���� ��������϶�(������ �ڽ��϶�)
			if(ptr->left!=NULL&&ptr->right==NULL)
			{
				if (previous == NULL)                 //��Ʈ��带 �����Ұ��
				{
					head->left = ptr->left;           //��Ʈ��带 ������ ��尡 ������ �ִ� �ڽĳ��� ����
					free(ptr);                        //����
					break;
				}
				                                    //�ܸ����� �ö� ������忡�� ���ʿ��� ���� �����ʿ��� ���� Ȯ��
				if(previous->left!=NULL)            //���� ��尡 ���̸� �߻��ϴ� ����ó��
				{
				  if(previous->left->key==key)       //�������� �ش� ���ʳ���� key���� ������
				  {
					previous->left=ptr->left;         //ptr�� ����� �ϳ��� �ڽ��� ������忡 ����
					free(ptr);                        //�����Ҵ�����->����
				  }
				}
				if(previous->right!=NULL)         //������ ��尡 ���̸� �߻��ϴ� ����ó��
				{
				 if(previous->right->key==key)    //�� �������� key���� ��ġ�ϸ�
				 {
					previous->right=ptr->left;         //ptr�� ����� �ϳ��� �ڽ��� ������忡 ����
					free(ptr);                    //�����Ҵ�����->����
				 }
				}
				break;                          //key���� ��ġ�ϴ� ��带 ������ while���� ����

			}
			//�ڽ��� 1���� ��������϶�(�������� �ڽ��϶�)
			if(ptr->left==NULL&&ptr->right!=NULL)
			{
				if (previous == NULL)                 //��Ʈ��带 �����Ұ��
				{
					head->left = ptr->right;          //��Ʈ��带 ������ ��尡 ������ �ִ� �ڽĳ��� ����
					free(ptr);                        //����
					break;
				}
				                                    //�ܸ����� �ö� ������忡�� ���ʿ��� ���� �����ʿ��� ���� Ȯ��
				if(previous->left!=NULL)            //���� ��尡 ���̸� �߻��ϴ� ����ó��
				{
				  if(previous->left->key==key)       //�������� �ش� ���ʳ���� key���� ������
				  {
					previous->left=ptr->right;         //ptr�� ����� �ϳ��� �ڽ��� ������忡 ����
					free(ptr);                        //�����Ҵ�����->����
				  }
				}
				if(previous->right!=NULL)         //������ ��尡 ���̸� �߻��ϴ� ����ó��
				{
				 if(previous->right->key==key)    //�� �������� key���� ��ġ�ϸ�
				 {
					previous->right=ptr->right;         //ptr�� ����� �ϳ��� �ڽ��� ������忡 ����
					free(ptr);                    //�����Ҵ�����->����
				 }
				}
				break;                          //key���� ��ġ�ϴ� ��带 ������ while���� ����

			}
			//�ڽ��� 2���� ��������϶�
			if(ptr->left!=NULL&&ptr->right!=NULL)
			{
				//�����ʿ��� ���� ���� ��带 ã�Ƽ� ������ ��忡 ����(ã�� ���� ����)�ϴ� ���
				previous=ptr;                      //���������� �ѹ� ���⶧���� ������带 ����
				check=ptr->right;                  //������ ������ üũ
				find=check;                      //������ ����Ʈ���� ���ʳ�尡 ������ ����Ʈ���� ��Ʈ�� ���� �������
				while(check->right||check->left) //�����ҳ���� ������ ����Ʈ������ ���� �������� ã�´�.
				{
					if(check->left)            //������ ������ ������ ������ �۴�
					{
					fprevious=check;          //���� ��带 ����
					find=check->left;
					}
					else                      //������ ������ ���������� Ž��
					check=check->right;

				}
				//�������� ����� �����ʿ� ��尡 ������
				if(fprevious!=NULL)         //find��尡 ��� �ѹ� �������� ������
				{
				 if(find->right!=NULL)
				 {                          //�׳� �����ϰ� �Ǹ� �ش� find->right�� ��带 ã���� ���Եȴ�.
					fprevious->left=find->right;            
				 }
				 //����������尡 �ܸ�����϶�
				 else
				 {
				  fprevious->left=NULL;       //����������带 �����ϱ��� �ش��带 ����Ű�� ��������� ��ũ�� NULL�� �ʱ�ȭ
				 }
				 ptr->key=find->key;        //������������� key�� ������ ��忡 ����
				 free(find);                      //������ ��� �����Ҵ�����
				 break;                          //key���� ��ġ�ϴ� ��带 ������ while���� ����
				}
				else   //������ ����Ʈ������ �������� �ѹ��� ���� �ʾ�����
				{
					previous->key=find->key;
					previous->right=find->right;
					free(find);
					break;
				}
			}
		}
		if(ptr->key<key)                           //key���� ���� ��庸�� ũ��
		{
			previous=ptr;                          //������带 Ȯ���ϱ� ���� �����ϰ�
			ptr=ptr->right;                        //���������� �̵�
		}
		else                                      //key���� ���� ��庸�� ������
		{
			previous=ptr;                         //������带 Ȯ���ϱ� ���� �����ϰ�
		    ptr=ptr->left;                         //�������� �̵�
		}
	}
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}


Node* pop()
{
	if (top == -1)		// top = -1�̸� ������ �����
		return NULL;

	return stack[top--]; // ������ �ֻ��� ���Ҹ� �����ϰ� ��ȯ 
}


void push(Node* aNode)
{
	if(top<(MAX_STACK_SIZE - 1))				// top�� ���� �迭�� �ִ� ũ�� ������ ����
	{
		stack[++top] = aNode;
	}
	else										// MAX_STACK_SIZE ���� Ŭ�� ���� ���� ���
		printf("������ �� á���ϴ�.\n");
}

/* ���� ť front�� ���Ҹ� �����ϴ� �Լ�*/
Node* deQueue()
{

	if(rear == front) 		// rear �� front�� ������ ť�� ����ٴ� ��������
	{
		return NULL;		// �ΰ��� ��ȯ
	}
	return queue[++front];

}

/* ���� ť�� rear�� ���Ҹ� �����ϴ� �Լ�*/
void enQueue(Node* aNode)
{
	if(rear>= MAX_QUEUE_SIZE - 1) //  ���� �迭�� ũ�Ⱑ �Ѿ�� ������ �߻�
	{
		printf("ť�� �� á���ϴ�\n");
		return;
	}
	else						//  �迭�� ũ�Ⱑ ���� �ʾҴٸ� �����͸� �����Ѵ�.
		queue[++rear]=aNode;
}

