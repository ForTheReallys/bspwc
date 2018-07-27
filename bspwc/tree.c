#include "bspwc/tree.h"

struct node* node_create()
{
	wlr_log(WLR_DEBUG, "Creating node");
	struct node* node = calloc(1, sizeof(struct node));

	node->window = NULL;

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void node_destroy(struct node* node)
{
	wlr_log(WLR_DEBUG, "Destroying node");
	if (node->left != NULL)
	{
		node_destroy(node->left);
	}

	if (node->right != NULL)
	{
		node_destroy(node->right);
	}

	free(node->window);
	free(node);
    
    node = NULL;
}


bool insert(const struct config* config, struct node* root, struct node* child)
{
	wlr_log(WLR_DEBUG, "Inserting %p into %p", (void*)child,(void*)root);
    
    if (config == NULL)
    {
        wlr_log(WLR_ERROR, "Config is null");
        return false;
    }

    if (mode == AUTOMATIC)
    {
        wlr_log(WLR_INFO, "Manual insertion mode is not implemented");
        return false;
    }

    if (root == NULL)
    {
        root = child;
    }
    else
    {
        node* other_child = node_create();

        // copy data
        // remove data from root
        
        if (config->polarity == LEFT)
        {
            root->left = child
            root->right = other_child
        }
        else // config->polarity == RIGHT
        {
            root->right = child
            root->left = other_child
        }
        
        other_child->parent = root;
        child->parent = root;
    }

    // resize windows


    return true;
}
