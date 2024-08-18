/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkorkut <bkorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:43:32 by bdemirbu          #+#    #+#             */
/*   Updated: 2024/08/18 18:14:48 by bkorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
/*
 *	typedef unsigned long size_t
 */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_track_malloc
{
	void					*p;
	struct s_track_malloc	*next;
}				t_track_malloc;

size_t			ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
t_list			*ft_lstmap(t_list *lst,
					void *(*f)(void *), void (*del)(void *));
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
char			**ft_split(char const *s, char c);
size_t			ft_strarrlen(char **arr);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strrchr(const char *s, int c);
char			*ft_strchr(const char *s, int c);
char			*ft_lowercase(char *str);
char			*ft_strdup(const char *s1);
char			*ft_itoa(int n);
void			*ft_memmove(void *st, const void *src, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_calloc(size_t count, size_t size);
long			ft_atoi(const char *str);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_putendl_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_bzero(void *s, size_t n);
void			ft_strfree(char **a);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				get_next_line(int fd, char **line);
int				ft_lstsize(t_list *lst);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int a);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

/* v track_malloc/ v */
//track_malloc_utils.c
t_track_malloc	*track_malloc_lstlast(t_track_malloc *ptr);
void			track_malloc_lstadd_back(t_track_malloc **ptr,
					t_track_malloc *new);
int				settrack_varible(t_track_malloc *track, void *value);

void			*track_malloc(int size, t_track_malloc **holder);
int				track_malloc_add(void *p, t_track_malloc **holder);
void			track_malloc_free(t_track_malloc *ptr);
t_track_malloc	*get_track(t_track_malloc *track, void *needle);
/* ^ track_malloc/ ^ */
#endif
