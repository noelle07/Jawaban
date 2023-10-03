#include <stdio.h>
#include <stdlib.h>

// Define a structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Structure for a node in a queue (used in level-order traversal)
struct QueueNode {
    struct TreeNode* data;
    struct QueueNode* next;
};

// Structure for a queue
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to initialize a queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to enqueue a tree node into the queue
void enqueue(struct Queue* q, struct TreeNode* node) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = node;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

// Function to dequeue a tree node from the queue
struct TreeNode* dequeue(struct Queue* q) {
    if (q->front == NULL)
        return NULL;
    struct QueueNode* temp = q->front;
    struct TreeNode* node = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return node;
}

// Pre-order traversal without recursion
void preOrder(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    struct TreeNode* stack[100]; // Assuming a maximum of 100 nodes
    int top = -1;

    stack[++top] = root;

    while (top >= 0) {
        struct TreeNode* node = stack[top--];
        printf("%d ", node->data);

        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }
}

// In-order traversal without recursion
void inOrder(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    struct TreeNode* stack[100]; // Assuming a maximum of 100 nodes
    int top = -1;
    struct TreeNode* current = root;

    while (top >= 0 || current) {
        while (current) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Post-order traversal without recursion
void postOrder(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    struct TreeNode* stack1[100]; // Assuming a maximum of 100 nodes
    struct TreeNode* stack2[100];
    int top1 = -1;
    int top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0) {
        struct TreeNode* node = stack1[top1--];
        stack2[++top2] = node;

        if (node->left)
            stack1[++top1] = node->left;
        if (node->right)
            stack1[++top1] = node->right;
    }

    while (top2 >= 0) {
        struct TreeNode* node = stack2[top2--];
        printf("%d ", node->data);
    }
}

// Level-order traversal without recursion
void levelOrder(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct Queue* queue = createQueue();
    struct TreeNode* current = root;
    enqueue(queue, current);

    while (queue->front) {
        current = dequeue(queue);
        printf("%d ", current->data);

        if (current->left)
            enqueue(queue, current->left);
        if (current->right)
            enqueue(queue, current->right);
    }
}

int main() {
    // Create a sample binary tree
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Pre-order traversal: ");
    preOrder(root);
    printf("\n");

    printf("In-order traversal: ");
    inOrder(root);
    printf("\n");

    printf("Post-order traversal: ");
    postOrder(root);
    printf("\n");

    printf("Level-order traversal: ");
    levelOrder(root);
    printf("\n");

    return 0;
}

