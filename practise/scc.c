#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node;

node *createnode(int val)
{
    node *z = (node *)malloc(sizeof(node));
    z->next = NULL;
    z->val = val;
    return z;
}

int hasCycle(node **arr, int n, int cur, int *path, int *visited)
{
    visited[cur - 1] = 1;
    path[cur - 1] = 1;

    if (arr[cur - 1] == NULL)
        return 0;

    node *temp = arr[cur - 1]->next;

    while (temp)
    {
        if (!visited[temp->val - 1])
        {
            if (hasCycle(arr, n, temp->val, path, visited))
                return 1;
        }
        else if (path[temp->val - 1])
            return 1;
        temp = temp->next;
    }

    path[cur - 1] = 0;
    return 0;
}

int isDag(node **arr, int n)
{
    int *visited = (int *)calloc(sizeof(int), n);
    int *path = (int *)calloc(sizeof(int), n);

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i - 1])
        {
            if (hasCycle(arr, n, i, path, visited))
                return 0;
        }
    }

    return 1;
}

node **transpose(node **arr, int n)
{
    node **tarr = (node **)malloc(sizeof(node *) * n);
    for (int i = 0; i < n; i++)
        tarr[i] = createnode(i + 1);

    for (int i = 0; i < n; i++)
    {
        node *temp = arr[i]->next;
        while (temp)
        {
            node *head = tarr[temp->val - 1];
            node *z = createnode(i + 1);
            z->next = head->next;
            head->next = z;
            temp = temp->next;
        }
    }

    return tarr;
}

void finisher(node **arr, int n, int cur, int *visited, int *stack, int *size)
{
    visited[cur - 1] = 1;
    node *temp = arr[cur - 1]->next;

    while (temp)
    {
        if (!visited[temp->val - 1])
        {
            finisher(arr, n, temp->val, visited, stack, size);
        }
        temp = temp->next;
    }

    stack[(*size)++] = cur;
}

void counter(node **tarr, int n, int cur, int *visited)
{
    visited[cur - 1] = 1;
    node *temp = tarr[cur - 1]->next;

    while (temp)
    {
        if (!visited[temp->val - 1])
        {
            counter(tarr, n, temp->val, visited);
        }
        temp = temp->next;
    }
}

int countStrong(node **arr, int n)
{
    node **tarr = transpose(arr, n);

    int *visited = (int *)calloc(sizeof(int), n);
    int *stack = (int *)calloc(sizeof(int), n);
    int size = 0;

    // makes stack
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i - 1])
        {
            finisher(arr, n, i, visited, stack, &size);
        }
    }

    for (int i = 0; i < n; i++)
        visited[i] = 0;
    int count = 0;

    for (int i = size - 1; i >= 0; i--)
    {
        if (!visited[stack[i] - 1])
        {
            counter(tarr, n, stack[i], visited);
            count++;
        }
    }

    return count;
}

int main()
{
    int n, m;
    char buffer;

    scanf("%d %d", &n, &m);

    node **arr = (node **)calloc(sizeof(node *), n);

    for (int i = 0; i < n; i++)
    {

        int head;

        scanf("%d%c", &head, &buffer);
        arr[head - 1] = createnode(head);
        node *temp = arr[head - 1];

        while (buffer != '\n')
        {
            scanf("%d%c", &head, &buffer);
            temp->next = createnode(head);
            temp = temp->next;
        }
    }

    // for(int i = 0;i<n;i++){
    // node*temp = arr[i];
    // while(temp){
    // printf("%d ",temp->val);
    // temp = temp->next;
    // }
    // printf("\n");
    // }

    while (1)
    {
        char ch;
        scanf("%c", &ch);

        if (ch == 'a')
        {
            int s = isDag(arr, n);
            if (s)
                printf("1\n");
            else
                printf("-1\n");
        }

        else if (ch == 'b')
        {
            int c = countStrong(arr, n);
            printf("%d\n", c);
        }

        else if (ch == 'x')
            break;
    }

    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);

    return 0;
}
