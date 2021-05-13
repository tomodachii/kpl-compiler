#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

void MakeNullTree(treeType *root)
{
  (*root) = NULL;
}

int isEmptyTree(treeType root)
{
  return (root == NULL);
}

int isLeaf(treeType node)
{
  if (node->left == NULL && node->right == NULL)
  {
    return 1;
  }
  return 0;
}

treeType MakeNewNode(elementType data)
{
  treeType new = NULL;
  new = (treeType)malloc(sizeof(node));
  if (new == NULL)
  {
    printf("Memory allocate failed!\n");
    return NULL;
  }
  else
  {
    new->left = NULL;
    new->right = NULL;
    new->data = data;
  }
  return new;
}

treeType FindMin(treeType node)
{
  if (node == NULL)
    return NULL;
  else
  {
    if (node->left == NULL)
      return node;
    else
      return (FindMin(node->left));
  }
}

treeType FindMax(treeType node)
{
  if (node == NULL)
    return NULL;
  else
  {
    if (node->right == NULL)
      return node;
    else
      return (FindMax(node->right));
  }
}

void getNodeData(treeType node)
{
  if (node != NULL)
  {
    printf("%s - %d - ", node->data.word, node->data.freq);
    printf("lines : ");
    for (int i = 0; i < node->data.freq - 1; i++)
    {
      printf("%d, ", node->data.lines[i]);
    }
    printf("%d\n", node->data.lines[node->data.freq - 1]);
  }
}

void inOrderPrintFile(treeType root, FILE *fp)
{
  if (root != NULL)
  {
    inOrderPrintFile(root->left, fp);
    fprintf(fp, "%s - %d - lines: ", root->data.word, root->data.freq);
    for (int i = 0; i < root->data.freq - 1; i++)
    {
      fprintf(fp, "%d, ", root->data.lines[i]);
    }
    fprintf(fp, "%d\n", root->data.lines[root->data.freq - 1]);
    inOrderPrintFile(root->right, fp);
  }
}

void inOrderPrint(treeType root)
{
  if (root != NULL)
  {
    inOrderPrint(root->left);
    getNodeData(root);
    inOrderPrint(root->right);
  }
}

treeType Search(treeType root, keytype key)
{
  if (isEmptyTree(root))
  {
    return NULL;
  }
  else if (strcmp(key, root->data.word) > 0)
  {
    return Search(root->right, key);
  }
  else if (strcmp(key, root->data.word) < 0)
  {
    return Search(root->left, key);
  }
  else
    return root;
}

void InsertNode(treeType *root, elementType data)
{
  if (isEmptyTree(*root))
  {
    *root = MakeNewNode(data);
  }
  else
  {
    if (strcmp((*root)->data.word, data.word) > 0)
    {
      InsertNode(&(*root)->left, data);
    }
    else if (strcmp((*root)->data.word, data.word) < 0)
    {
      InsertNode(&(*root)->right, data);
    }
    else
      (*root)->data = data;
  }
}

void DeleteNode(treeType *root, keytype key)
{
  if (*root == NULL)
  {
    printf("(!) NULL!\n");
  }
  else if (strcmp(key, (*root)->data.word) > 0)
  {
    DeleteNode(&(*root)->right, key);
  }
  else if (strcmp(key, (*root)->data.word) < 0)
  {
    DeleteNode(&(*root)->left, key);
  }
  else
  {
    if ((*root)->right != NULL && (*root)->left != NULL)
    {
      treeType minRight = FindMin((*root)->right);
      (*root)->data = minRight->data;
      DeleteNode(&(*root)->right, (minRight)->data.word);
    }
    else
    {
      treeType del = *root;
      if ((*root)->right == NULL)
      {
        (*root) = (*root)->left;
      }
      else if ((*root)->left == NULL)
      {
        (*root) = (*root)->right;
      }
      free(del);
    }
  }
}
