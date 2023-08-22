#include "heredoc.h"
#include <stdio.h>
#include <stdlib.h>

char	*heredoc_read()
{
	char *buff;
	char *tmp;
	char *line;

	buff = NULL;
	tmp = try_strdup("");
	line = NULL;
	if(write(1,"> ",2) == -1)
			return(NULL);
	while(true)
	{
		if(buff != NULL)
		{
			tmp = try_strdup(buff); 
			free(buff);
		}
		buff = try_strdup("");
		if(read(0,buff,1) == -1)
			return(NULL);
		if(buff[0] == '\n')
		{
			line = try_strjoin(tmp,buff); 
			free(tmp);
			free(buff);
			break;
		}
		else
			buff = try_strjoin(tmp,buff); 
	}
	return(line);
}

bool	heredoc_read_loop(t_redirect_list *delimiter)
{
	char	*str ;
	char	*tmp ;
	char *buff ;
	char *check ;

	str= try_strdup("");
	check = try_strjoin(delimiter->word,"\n");
	while (true)
	{
		buff = heredoc_read();
		if (buff == NULL)
		{
			free(str);
			return (false);
		}
		if (ft_strcmp(buff, check) == 0)
		{
			free(buff);
			free(delimiter->word);
			free(check);
			delimiter->word = str;
			break ;
		}
		tmp = str;
		str = try_strjoin(str, buff);
		free(buff);
		free(tmp);
	}
	return (true);
}

void	heredoc_delete_quote(t_redirect_list *delimiter)
{
	(void)delimiter;
}

bool	heredoc_get_str(t_redirect_list *node, t_data *d)
{
	t_redirect_list	*delimiter = node->next;
	/* char		*tmp; */
	(void)d;

	if (delimiter == NULL)
		return (false);
	/* if (delimiter->type == PS_QUOTE_DELIMITER) */
		/* heredoc_delete_quote(delimiter); */
	return (heredoc_read_loop(delimiter));
}

void	redirect_delete(t_command *command, t_redirect_list *target)
{
	t_redirect_list *head;
	t_redirect_list *prev;

	head = command->redirect_list;
	prev = head;
	while(head)	
	{
		if(head->word == target->word)
		{
			prev->next = head->next;
			/* free(head); */
			break;
		}
		prev = head;
		head = head->next;
	}
}

bool	heredoc_redirect_list(t_command *command, t_data *d)
{
	t_redirect_list	*node ;
	/* t_redirect_list	*tmp ; */
	
	node = command->redirect_list;

	while (node != NULL)
	{
		if (node->type == PS_HERE_DOCUMENTS)
		{
			if (heredoc_get_str(node, d) == false)
				return (false);
			/* tmp = node->next; */
			redirect_delete(command, node);
			/* break; */
			/* node = tmp; */
		}
		/* else */
			node = node->next;
	}
	return (true);
}

bool	heredoc(t_ast *node, t_data *d)
{
	bool	result;
	result = true;

	if (node->left_hand != NULL)
		result = heredoc(node->left_hand, d);
	if (result && node->right_hand != NULL)
		result = heredoc(node->right_hand, d);
	if (result == false)
		return (false);
	if (node->type == PS_COMMAND)
		return (heredoc_redirect_list(node->command_list, d));
	return (true);
}

