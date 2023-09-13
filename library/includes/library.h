/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:52:38 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/12 17:04:23 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "init.h"
# include <signal.h>
# include <dirent.h>

// try
void			*try_malloc(size_t size);
void			*try_calloc(size_t count, size_t size);
char			*try_strdup(const char *s1);
char			*try_substr(char const *s, size_t start, size_t len);
char			*try_strjoin(char const *s1, char const *s2);
ssize_t			try_write(int fildes, const void *buf, size_t nbyte, t_data *d);
char			*try_itoa(int n);
char			*try_strjoin_free(char *free_str, const char *str2);
int				try_open(int open_value, char *file, t_data *d);
void			try_close(int fildes, t_data *d);
int				try_dup(int fildes, t_data *d);
void			try_dup2(int fildes, int fildes2, t_data *d);
bool			try_chdir(const char *og_path, const char *path, t_data *d);
bool			try_stat(const char *path, struct stat *sb, t_data *d);
char			*ft_strchr(const char *s, int c);
void			try_pipe(int *pipefd);
pid_t			try_fork(void);
pid_t			try_waitpid(pid_t pid, int *wstatus, int options, t_data *d);
void			try_unlink(const char *pathname, t_data *d);
int				try_sigaction(int signum, const struct sigaction *act,
					struct sigaction *oldact, t_data *d);
DIR				*try_opendir(const char *name, t_data *d);
struct dirent	*try_readdir(DIR *dirp, t_data *d);
void			try_closedir(DIR *dirp, t_data *d);

// ft
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *str);
bool			ft_is_operator(char c);
int				ft_isspace(char c);
bool			ft_is_special_char(char c);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *b, int c, size_t len);
bool			ft_isupper(char c);
bool			ft_islower(char c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strcmp_ignorecase(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
int				ft_isdigit(char c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strrchr(const char *s, int c);

#endif
