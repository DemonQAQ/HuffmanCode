#include "function.h"
int main()
{
	int length = 0;
	huffmancode* code = input_code_list_keybroad(&length);
	btree* root = huffmamtree_rebuild(code, length);
	tree_display(root,0);
	return 0;
}