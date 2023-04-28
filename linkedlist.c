#include "shell.h"

alias_t *add_end_alias(alias_t **head, char *name, char *value);
void free_list_alias(alias_t *head);
list_t *add_end_node(list_t **head, char *dir_path);
void free_list(list_t *head);

/**
 * add_end_alias - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias that is to be added
 * @value: The value of the new alias that is to be added.
 *
 * Return: If an error occurs - NULL. Otherwise return
 *  a pointer to the new node.
 */

alias_t *add_end_alias(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlength(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_end_node - Adds a node to the end of a list_t linked list
 * @head: A pointer to the head of list_t list
 * @dir_path: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_end_node(list_t **head, char *dir_path)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir_path;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_list_alias - Frees an alias_t linked list
 * @head: head of the alias_t list
 */

void free_list_alias(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * free_list - Frees a list_t linked list
 * @head: head of the list_t list.
 */

void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
