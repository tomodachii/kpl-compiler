
typedef struct {
	char word[1000];
	int freq;
  int lines[4000];
} elementType;
typedef char* keytype;

typedef struct binaryTree node;
struct binaryTree{
  elementType data;
  node *left;
  node *right;
};

typedef node *treeType;

void MakeNullTree(treeType *root);
int isEmptyTree(treeType root);
treeType MakeNewNode(elementType data);
int isLeaf(treeType node);
treeType FindMin(treeType node);
treeType FindMax(treeType node);
void getNodeData(treeType node);
void inOrderPrint(treeType root);
treeType Search(treeType root, keytype key);
void InsertNode(treeType *root, elementType data);
void DeleteNode(treeType *root, keytype key);
void inOrderPrintFile(treeType root, FILE *fp);
