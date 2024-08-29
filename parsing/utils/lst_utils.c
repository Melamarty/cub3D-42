#include "../parsing.h"

t_list *create_node(const char *line) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_node->line = strdup(line); // Allocate memory and copy the line
    if (!new_node->line) {
        perror("Failed to allocate memory for line");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    new_node->last = NULL;
    new_node->next = NULL;
    return new_node;
}

// Function to add a line to the list
void add_line(t_list **head, const char *line) {
    t_list *new_node = create_node(line);
    
    new_node->checked = 0;
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_list *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->last = temp;
    }
}

// Function to print the list
void print_list(t_list *head) {
    t_list *temp = head;
    while (temp != NULL) {
        printf("%d--%s",temp->checked, temp->line);
        temp = temp->next;
    }
}

int lst_len(t_list **list)
{
    t_list *tmp;
    int len;

    tmp = *list;
    len = 0;
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}

void free_list(t_list *head) {
    t_list *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->line);
        free(temp);
    }
}