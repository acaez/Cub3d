/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:26:20 by acaes             #+#    #+#             */
/*   Updated: 2025/04/10 21:26:20 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "gnl.h"
# include "ptf.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//=============== base ===============//
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *str, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *str, int fd);
char				**ft_split(const char *str, char c);

//=============== isas ===============//
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

//=============== list ===============//
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);

//=============== memo ===============//
void				ft_bzero(void *str, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memset(void *str, int c, size_t n);

//=============== str ===============//
char				*ft_strchr(const char *str, int a);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *str);
void				ft_striteri(char *str, void (*f)(unsigned int, char *));
char				*ft_strjoin(const char *s1, const char *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(const char *str, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strnstr(const char *str, const char *find, size_t len);
char				*ft_strrchr(const char *str, int a);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_substr(const char *str, unsigned char start,
						size_t len);

#endif
