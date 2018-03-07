/* ALEKSANDER SZEWCZAK
 * RedBlackTree
 * Press 0 to stop scanning.
 * -1 == root
 */

import java.util.LinkedList;
import java.util.Scanner;

public class RedBlackTree {

    private final int RED = 0;
    private final int BLACK = 1;

    private class Node {

        int key = -1, color = BLACK;
        Node left = nil, right = nil, parent = nil;

        Node(int key) {
            this.key = key;
        } 
    }

    private final Node nil = new Node(-1); 
    private Node root = nil;

	public void printTree(Node node) {
        if (node == nil) {
            return;
        }
        printTree(node.left);
        System.out.print(((node.color==RED)?"Color: RED   |":"Color: BLACK |")+" Key: "+node.key+" | Parent: "+node.parent.key+"\n");
        printTree(node.right);
        
    }

    private Node findNode(Node findNode, Node node) {
        if (root == nil) {
            return null;
        }

        if (findNode.key < node.key) {
            if (node.left != nil) {
                return findNode(findNode, node.left);
            }
        } else if (findNode.key > node.key) {
            if (node.right != nil) {
                return findNode(findNode, node.right);
            }
        } else if (findNode.key == node.key) {
            return node;
        }
        return null;
    }

    private void insert(Node node) {
        Node temp = root;
        if (root == nil) {
            root = node;
            node.color = BLACK;
            node.parent = nil;
        } else {
            node.color = RED;
            while (true) {
                if (node.key < temp.key) {
                    if (temp.left == nil) {
                        temp.left = node;
                        node.parent = temp;
                        break;
                    } else {
                        temp = temp.left;
                    }
                } else if (node.key >= temp.key) {
                    if (temp.right == nil) {
                        temp.right = node;
                        node.parent = temp;
                        break;
                    } else {
                        temp = temp.right;
                    }
                }
            }
            fixTree(node);
            
        }
    }

    private void fixTree(Node node) {
        while (node.parent.color == RED) {
            Node uncle = nil; //parent's brother
            if (node.parent == node.parent.parent.left) {
                uncle = node.parent.parent.right;

                if (uncle != nil && uncle.color == RED) {
                    node.parent.color = BLACK;
                    uncle.color = BLACK;
                    node.parent.parent.color = RED;
                    node = node.parent.parent;
                    continue;
                } 
                if (node == node.parent.right) {
                    //double rotation need
                    node = node.parent;
                    rotateLeft(node);
                } 
                node.parent.color = BLACK;
                node.parent.parent.color = RED;
                // if wasn't else if it would be only a one rotation
                rotateRight(node.parent.parent);
            } else {
                uncle = node.parent.parent.left;
                 if (uncle != nil && uncle.color == RED) {
                    node.parent.color = BLACK;
                    uncle.color = BLACK;
                    node.parent.parent.color = RED;
                    node = node.parent.parent;
                    continue;
                }
                if (node == node.parent.left) {
                    //double rotation needed
                    node = node.parent;
                    rotateRight(node);
                }
                node.parent.color = BLACK;
                node.parent.parent.color = RED;
             // if wasn't else if it would be only a one rotation
                rotateLeft(node.parent.parent);
            }
        }
        root.color = BLACK;
    }

    void rotateLeft(Node node) {
        if (node.parent != nil) {
            if (node == node.parent.left) {
                node.parent.left = node.right;
            } else {
                node.parent.right = node.right;
            }
            node.right.parent = node.parent;
            node.parent = node.right;
            if (node.right.left != nil) {
                node.right.left.parent = node;
            }
            node.right = node.right.left;
            node.parent.left = node;
        } else {//need to rotate root
            Node right = root.right;
            root.right = right.left;
            right.left.parent = root;
            root.parent = right;
            right.left = root;
            right.parent = nil;
            root = right;
        }
    }

    void rotateRight(Node node) {
        if (node.parent != nil) {
            if (node == node.parent.left) {
                node.parent.left = node.left;
            } else {
                node.parent.right = node.left;
            }

            node.left.parent = node.parent;
            node.parent = node.left;
            if (node.left.right != nil) {
                node.left.right.parent = node;
            }
            node.left = node.left.right;
            node.parent.right = node;
        } else {//need to rotate root
            Node left = root.left;
            root.left = root.left.right;
            left.right.parent = root;
            root.parent = left;
            left.right = root;
            left.parent = nil;
            root = left;
        }
    }

    //deletes whole tree
    void deleteTree(){
        root = nil;
    }
    
    //delete single item
    void transplant(Node target, Node with){ 
          if(target.parent == nil){
              root = with;
          }else if(target == target.parent.left){
              target.parent.left = with;
          }else
              target.parent.right = with;
          with.parent = target.parent;
    }
    
    boolean delete(Node z){
        if((z = findNode(z, root))==null)
        	return false;
        Node x;
        Node y = z; // temporary
        int y_original_color = y.color;
        
        if(z.left == nil){
            x = z.right;  
            transplant(z, z.right);  
        }else if(z.right == nil){
            x = z.left;
            transplant(z, z.left); 
        }else{
            y = treeMinimum(z.right);
            y_original_color = y.color;
            x = y.right;
            if(y.parent == z)
                x.parent = y;
            else{
                transplant(y, y.right);
                y.right = z.right;
                y.right.parent = y;
            }
            transplant(z, y);
            y.left = z.left;
            y.left.parent = y;
            y.color = z.color; 
        }
        if(y_original_color==BLACK)
            deleteFixup(x);  
        return true;
    }
    
    void deleteFixup(Node x){
        while(x!=root && x.color == BLACK){ 
            if(x == x.parent.left){
                Node w = x.parent.right;
                if(w.color == RED){
                    w.color = BLACK;
                    x.parent.color = RED;
                    rotateLeft(x.parent);
                    w = x.parent.right;
                }
                if(w.left.color == BLACK && w.right.color == BLACK){
                    w.color = RED;
                    x = x.parent;
                    continue;
                }
                else if(w.right.color == BLACK){
                    w.left.color = BLACK;
                    w.color = RED;
                    rotateRight(w);
                    w = x.parent.right;
                }
                if(w.right.color == RED){
                    w.color = x.parent.color;
                    x.parent.color = BLACK;
                    w.right.color = BLACK;
                    rotateLeft(x.parent);
                    x = root;
                }
            }else{
                Node w = x.parent.left;
                if(w.color == RED){
                    w.color = BLACK;
                    x.parent.color = RED;
                    rotateRight(x.parent);
                    w = x.parent.left;
                }
                if(w.right.color == BLACK && w.left.color == BLACK){
                    w.color = RED;
                    x = x.parent;
                    continue;
                }
                else if(w.left.color == BLACK){
                    w.right.color = BLACK;
                    w.color = RED;
                    rotateLeft(w);
                    w = x.parent.left;
                }
                if(w.left.color == RED){
                    w.color = x.parent.color;
                    x.parent.color = BLACK;
                    w.left.color = BLACK;
                    rotateRight(x.parent);
                    x = root;
                }
            }
        }
        x.color = BLACK; 
    }
    
    Node treeMinimum(Node subTreeRoot){
        while(subTreeRoot.left!=nil){
            subTreeRoot = subTreeRoot.left;
        }
        return subTreeRoot;
    }
    
    Node treeMaximum(Node subTreeRoot){
        while(subTreeRoot.right!=nil){
            subTreeRoot = subTreeRoot.right;
        }
        return subTreeRoot;
    }
    
     int minDepth(Node node) {
        if(node == null)
            return 0;
        if(node.left == null && node.right == null) 
        	return 1; //just a root
        if(node.left == null) 
        	return minDepth(node.right) + 1;  
        if (node.right == null)
            return minDepth(node.left) + 1;
      
         return Math.min(minDepth(node.left), minDepth(node.right)) + 1;
 
    }
     
     public int maxDepth(Node node) {
    	    if(node==null)
    	        return 0;
    	 
    	    int leftDepth = maxDepth(node.left);
    	    int rightDepth = maxDepth(node.right);
    	 
    	    int bigger = Math.max(leftDepth, rightDepth);
    	 
    	    return bigger+1;
    	}
   
    
    public void consoleUI() {
        Scanner scan = new Scanner(System.in);
        while (true) {
            System.out.println("\n1. - Add items\n"
                    + "2. - Delete items\n"
                    + "3. - Check items\n"
                    + "4. - Print tree\n"
                    + "5. - Delete tree\n"
                    + "6. - Minmum depth\n"
                    + "7. - Maximum depth\n"
                    + "8. - Min/Max treeItem\n"
                    + "10. - Exit\n");
            int choice = scan.nextInt();

            int item;
            Node node;
            switch (choice) {
                case 1:
                    item = scan.nextInt();
                    while (item != - 0 ) {
                        node = new Node(item);
                        insert(node);
                        item = scan.nextInt();
                    }
                    printTree(root);
                    break;
                case 2:
                    item = scan.nextInt();
                    while (item != 0) {
                        node = new Node(item);
                        System.out.print("\nDeleting item " + item);
                        if (delete(node)) {
                            System.out.print(": deleted!");
                        } else {
                            System.out.print(": does not exist!");
                        }
                        item = scan.nextInt();
                    }
                    System.out.println();
                    printTree(root);
                    break;
                case 3:
                    item = scan.nextInt();
                    while (item != 0) {
                        node = new Node(item);
                        System.out.println((findNode(node, root) != null) ? "found" : "not found");
                        item = scan.nextInt();
                    }
                    break;
                case 4:
                    printTree(root);
                    break;
                case 5:
                    deleteTree();
                    System.out.println("Tree deleted!");
                    break;
                case 6:
                	System.out.println("Minimum depth: " + minDepth(root));
                	break;
                case 7:
                	System.out.println("Maximum depth: " + maxDepth(root));
                	break;
                case 8:
                    System.out.println("treeMinimum: " + treeMinimum(root).key);
                    System.out.println("treeMaximum: " + treeMaximum(root).key);
                    break;
                case 10:
                	System.out.println("Exited");
                	System.exit(0);
                	break;
                default:
                	System.out.println("False");
                	
            }
        }
    }
    public static void main(String[] args) {
        RedBlackTree rbt = new RedBlackTree();
        rbt.consoleUI();
    }
}