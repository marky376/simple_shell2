#include "shell.h"

/**
 *jjmyhistory - function  displays the history list
 *each command on seperate line
 *@member: Struct containg members used in most functions
 *Return: always 0;
 */
int jjmyhistory(memb_t *member)
{
	n_print_list(member->history);
	return (0);
}

/**
 *m_print_alias - prints an alias string
 *@node: the alias node
 *Return: always 0 on success else otherwise
 */
int m_print_alias(list_t *node)
{
	char *c = NULL, *s = NULL;

	if (node)
	{
		c = n_strchr(node->str, '=');
		for (s = node->str; s <= c; s++)
			n_putchar(*s);
		n_putchar('\'');
		n_puts(c + 1);
		n_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 *mark_set_alias - create an alias
 *@memb: Struct containg members used in most functions
 *@str: a string alias
 *Return: always 0 on success else otherwise
 */
int mark_set_alias(memb_t *memb, char *str)
{
	char *p;

	p = n_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (bb_unset_alias(memb, str));

	bb_unset_alias(memb, str);
	return (n_add_node_end(&(memb->alias), str, 0) == NULL);
}

/**
 *bb_unset_alias - delete the alias for a command
 *@memb: Struct containg members used in most functions
 *@str: the string alias
 *Return: always 0 on success else otherwise
 */
int bb_unset_alias(memb_t *memb, char *str)
{
	char *p, c;
	int ret;

	p = n_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = n_delete_node_at_index(&(memb->alias),
		n_get_node_index(memb->alias, n_node_starts_with(memb->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 *merc_myalias -  function mimics the alias builtin alias command
 *@member: Struct containg members used in most functions
 *Return: always 0
 */
int merc_myalias(memb_t *member)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (member->argc == 1)
	{
		node = member->alias;
		while (node)
		{
			m_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; member->argv[i]; i++)
	{
		p = n_strchr(member->argv[i], '=');
		if (p)
			mark_set_alias(member, member->argv[i]);
		else
			m_print_alias(n_node_starts_with(member->alias, member->argv[i], '='));
	}

	return (0);
}
