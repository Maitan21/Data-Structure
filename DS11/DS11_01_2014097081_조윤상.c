/* 
Description : 이진 탐색 순회의 생성 그리고 탐색 (insert로 트리 구성후 search로 탐색)
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 24


int Temp[MAX_ELEMENTS];
int cnt = 0;

typedef struct {
	int key;
} element;

typedef struct node *treePointer;
typedef struct node {
	element data;
	treePointer leftchild, rightchild;
};

treePointer root;
void insert(treePointer *, int);
treePointer modifiedSearch(treePointer p, int x);
element* search(treePointer tree, int);
void open();
void inorder(treePointer tree);
void postorder(treePointer tree);
void preorder(treePointer tree);

int main()
{
	element* status;
	open();
	printf("Preorder :  ");
	preorder(root);
	printf("\n");
	printf("Inorder :   ");
	inorder(root);
	printf("\n");
	printf("Postorder : ");
	postorder(root);
	printf("\n");
	printf("Search :    ");
	for (int i = 0; i < cnt; i++)
	{
		status = search(root, Temp[i]);
		if (status == NULL) printf("0 "); //NULL값이면 찾는 값이 없으므로 '0'
		else printf("1 "); //포인터값이 반환되면 '1'
	}
	printf("\n");
	return 0;
}

void open()
{
	int temp;

	FILE *fp1 = fopen("input1.txt", "r");
	if (fp1 != NULL)
	{
		while ((fscanf(fp1, "%d", &temp) != EOF)) {

			insert(&root, temp);
		}
	}

	FILE *fp2 = fopen("input2.txt", "r");
	if (fp2 != NULL)
	{
		while ((fscanf(fp2, "%d", &Temp[cnt])) != EOF)
			cnt++;
	}

}

void insert(treePointer *node, int k)
{
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node)) {
		ptr = (treePointer)malloc(sizeof(*ptr));
		ptr->data.key = k;
		ptr->leftchild = NULL; ptr->rightchild = NULL;
		if (*node)
			if (k < temp->data.key) temp->leftchild = ptr; // 여기서 temp는 부모이므로 ptr이 작은값으면 왼쪽으로
			else temp->rightchild = ptr; //ptr 큰 값이면 오른쪽으로
		else *node = ptr;
	}
}
treePointer modifiedSearch(treePointer root, int k) //삽입이 가능한지 탐색하여 가능여부를 반환
{
	treePointer temp = root;
	while (root)
	{
		temp = root;
		if (k < root->data.key) //삽입값이 작으면
			root = root->leftchild; //왼쪽으로 가서 다시 검색
		else if (k > root->data.key) //삽입값이 크면
			root = root->rightchild; // 오른쪽으로 가서 다시 검색
		else
			return NULL;
	}
	return temp; // parent 위치 반환
}
void inorder(treePointer tree)
{
	if (tree)
	{
		inorder(tree->leftchild);
		printf("%d ", tree->data.key);
		inorder(tree->rightchild);
	}
}
void preorder(treePointer tree)
{
	if (tree) {
		printf("%d ", tree->data.key);
		preorder(tree->leftchild);
		preorder(tree->rightchild);
	}
}
void postorder(treePointer tree)
{
	if (tree) {
		postorder(tree->leftchild);
		postorder(tree->rightchild);
		printf("%d ", tree->data.key);
	}
}

element* search(treePointer tree, int k)
{
	if (!tree) return NULL; //값이 없으면 NULL값 반환
	if (k == tree->data.key)return &(tree->data); //값이 있으면 데이타 포인터 반환
	if (k < tree->data.key) // 순회
		return search(tree->leftchild, k);  //root부터 찾는 값이 작으면 왼쪽 자식으로 이동
	return search(tree->rightchild, k); //크면 오른쪽으로 이동
}