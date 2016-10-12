
/**
 * Created by divyam on 13/10/16.
 * So we will first introduce the problem of least common ancestor of 2 nodes in a binary search tree
 *
 *Let T be a rooted tree. The lowest common ancestor between two nodes n1 and n2 is defined as the lowest node in T
 that has both n1 and n2 as descendants (where we allow a node to be a descendant of itself)
 * for every pair of nodes in a tree we have root node as an ancestor but the problem is to find the lowest common ancestor
 * ie we have to find the lca_node such that the sum of distance of  the lca_node to the given nodes n1 and n2 is minimum
 *


 */

public class bst_lca {
    class Node
    {
        int data;
        Node left, right;

        Node(int item)
        {
            data = item;
            left = right = null;
        }
    }
    Node root;

    /* Function to find LCA of n1 and n2. The function assumes that both
       n1 and n2 are present in BST */
    Node lca(Node node, int n1, int n2)
    {
        if (node == null)
            return null;

        // If both n1 and n2 are smaller than root, then LCA lies in left
        if (node.data > n1 && node.data > n2)
            return lca(node.left, n1, n2);

        // If both n1 and n2 are greater than root, then LCA lies in right
        if (node.data < n1 && node.data < n2)
            return lca(node.right, n1, n2);

        //the final case when nodes n1 and n2 lie on opposite sides of the present node , we return that node
        return node;
    }

}
