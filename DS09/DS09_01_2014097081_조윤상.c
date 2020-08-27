/*Description : Tree의 이진 트리 순회 -> inorder, preorder, postorder 순회*/
#include <stdio.h>
#include <stdlib.h>


typedef struct node *treePointer;
typedef struct node {
	char data;
	treePointer leftchild, rightchild;
}node;

/*왼쪽 가장 밑부터 넣어주기 후 부모로 이동*/

/*			A
		B       C
	  D   E   F   G
	H   I              */
node A1 = { 'H',NULL,NULL };
node A2 = { 'I', NULL,NULL };
node A3 = { 'D',&A1,&A2 };
node A4 = { 'E',NULL,NULL };
node A5 = { 'B', &A3,&A4 };
node A6 = { 'F', NULL,NULL };
node A7 = { 'G' ,NULL,NULL };
node A8 = { 'C' ,&A6,&A7 };
node A9 = { 'A' ,&A5,&A8 };
node *root = &A9;

/*        +
		*   E
	  *   D
	/   C
  A   B              */
node B1 = { 'A',NULL,NULL };
node B2 = { 'B', NULL,NULL };
node B3 = { '/',&B1,&B2 };
node B4 = { 'C',NULL,NULL };
node B5 = { '*', &B3,&B4 };
node B6 = { 'D', NULL,NULL };
node B7 = { '*' ,&B5,&B6 };
node B8 = { 'E' ,NULL,NULL };
node B9 = { '+' ,&B7,&B8 };
node *root2 = &B9;

void inorder(treePointer);
void preorder(treePointer);
void postorder(treePointer);

int main()
{
	printf("Preorder : ");
	preorder(root);
	printf("\n");
	printf("Inorder : ");
	inorder(root);
	printf("\n");
	printf("Postorder : ");
	postorder(root);
	printf("\n");
	printf("Preorder : ");
	preorder(root2);
	printf("\n");
	printf("Inorder : ");
	inorder(root2);
	printf("\n");
	printf("Postorder : ");
	postorder(root2);
	printf("\n");
	return 0;
}

void inorder(treePointer  ptr)
{
	if (ptr) {
		inorder(ptr->leftchild);
		printf("%c", ptr->data);
		inorder(ptr->rightchild);
	}
}
void preorder(treePointer ptr)
{
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftchild);
		preorder(ptr->rightchild);
	}
}
void postorder(treePointer ptr)
{
	if (ptr) {
		postorder(ptr->leftchild);
		postorder(ptr->rightchild);
		printf("%c", ptr->data);
	}
}