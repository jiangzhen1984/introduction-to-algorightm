

#include <stdlib.h>
#include <stdio.h>
#include <string.h>





struct binary_tree {
	struct binary_tree * p;
	struct binary_tree * left;
	struct binary_tree * right;
	int key;
};



void in_order_tree_walk(struct binary_tree * root)
{
	if (root->left != NULL) {
		in_order_tree_walk(root->left);
	}
	printf(" %d,", root->key);
	if (root->right != NULL) {
		in_order_tree_walk(root->right);
	}
}

void pre_order_tree_walk(struct binary_tree * root)
{
	printf(" %d,", root->key);
	if (root->left != NULL) {
		pre_order_tree_walk(root->left);
	}
	if (root->right != NULL) {
		pre_order_tree_walk(root->right);
	}
}

void post_order_tree_walk(struct binary_tree * root)
{
	if (root !=  NULL) {
		post_order_tree_walk(root->left);
		post_order_tree_walk(root->right);
		printf(" %d,", root->key);
	}
}




struct binary_tree * tree_search(struct binary_tree * root, int key)
{
	struct binary_tree * node = root;
	while (node != NULL) {
		if (key > node->key) {
			node = node->right;
		} else if(key < node->key) {
			node = node->left;
		} else {
			return node;
		}
	}

	return node;
}

struct binary_tree * tree_minimum(struct binary_tree * root)
{
	struct binary_tree * node = root;
	while (node->left != NULL) {
		node = node->left;
	}

	return node;
}

struct binary_tree * tree_maixmum(struct binary_tree * root)
{
	struct binary_tree * node = root;
	while (node->right != NULL) {
		node = node->right;
	}

	return node;
}


struct binary_tree * tree_successor(struct binary_tree * node)
{
	struct binary_tree * yp =  node->p;
	if (node->right != NULL) {
		return tree_minimum(node->right);
	}

	while (yp != NULL && node == yp->right) {
		yp = node;
		node = node->p;
	}

	return yp;
}




void tree_insert(struct binary_tree ** pproot, struct binary_tree * node)
{
	struct binary_tree * root = *pproot;
	struct binary_tree * x = *pproot;
	struct binary_tree * y = NULL;

	while (x != NULL) {
		y = x;
		if (x->key < node->key) {
			x = x->right;
		} else {
			x = x->left;
		}
	}
	
	if (y == NULL) {
		*pproot = node;
	} else if(y->key < node->key) {
		y->right = node;
		node->p = y;
	} else {
		y->left = node;
		node->p = y;
	}
	
}



void tree_transplant(struct binary_tree ** pproot, struct binary_tree * old, struct binary_tree * new)
{
	if (old->p == NULL) {
		*pproot = new;
	} else if (old->p->left == old) {
		old->p->left = new;
	} else if (old->p->right == old) {
		old->p->right = new;
	}

	if(new != NULL) {	
		new->p = old->p;
	}
}


void tree_delete(struct binary_tree ** root, struct binary_tree * node)
{
	struct binary_tree * successor;
	if (node->left == NULL && node->right != NULL) {
		tree_transplant(root, node, node->right);
	} else if (node->right == NULL && node->left != NULL) {
		tree_transplant(root, node, node->left);
	} else {
		successor = tree_minimum(node->right);	
		if (successor->p != node) {
			tree_transplant(root, successor, successor->right);
			successor->right = node->right;
			successor->right->p = successor;
		}
		tree_transplant(root, node, successor);
		if (successor->p != NULL) {	
			printf("======%lld   %lld   %lld %lld\n", successor, successor->p, successor->p->left, successor->p->right);
		}
		successor->left = node->left;
		successor->left->p = successor;
	}
}



void free_binary_tree(struct binary_tree * node) {
	if (node != NULL) {
	free_binary_tree(node->left);
	free_binary_tree(node->left);
	
	if (node->p != NULL) {
		if (node->p->left == node) {
			node->p->left = NULL;
		} else if (node->p->right == node) {
			node->p->right = NULL;
		}
	}
	free(node);
	}
}


struct binary_tree * root = NULL;

int main(int argc, char ** argv)
{
	int cmd;
	int key;

	do {
		printf(" 1. Insert node to tree\n");
		printf(" 2. Delete node to tree\n");
		printf(" 3. Search node to tree\n");
		printf(" 4. Pre order walk tree\n");
		printf(" 5. In order walk tree\n");
		printf(" 6. Post order walk tree\n");
		printf(" 0. Exit \n");
		printf("Input command:");
		scanf("%d", &cmd);
		if (cmd < 0 || cmd > 6) {
			printf("=======================\n");
			printf("[ERROR Command]\n");
			printf("=======================\n");
			continue;
		}

		if (cmd == 0) {
			//TODO release memory
			free_binary_tree(root);
			exit(0);
		} else if (cmd == 1) {
			printf("Input Key:");
			scanf("%d", &key);
			struct binary_tree * node = (struct binary_tree  *) malloc(sizeof(struct binary_tree));
			node->key = key;	
			tree_insert(&root, node);
		} else if (cmd == 2) {
			printf("Input Delete Key:");
			scanf("%d", &key);

			struct binary_tree * node =tree_search(root, key);
			if (node == NULL) {
				printf(" Can not search key %d\n", key);
			} else {
				tree_delete(&root, node);
			}
		} else if (cmd == 3) {
			printf("Input Search Key:");
			scanf("%d", &key);
			struct binary_tree * node =tree_search(root, key);
			if (node == NULL) {
				printf(" Can not search key %d\n", key);
			} else {
				printf(" Found key %d\n", node->key);
			}

		} else if (cmd == 4) {
			pre_order_tree_walk(root);
			printf("\n");
		} else if (cmd == 5) {
			in_order_tree_walk(root);
			printf("\n");
		} else if (cmd == 6) {
			post_order_tree_walk(root);
			printf("\n");
		}
	} while(1);

	return 0;
}
