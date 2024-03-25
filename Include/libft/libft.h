/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:56:27 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 14:54:00 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef enum s_identifier_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}						t_identifier_type;
typedef struct s_list
{
	void				*content;
	t_identifier_type	type;
	struct s_list		*next;
}						t_list;

typedef struct s_word_parse_state
{
	int					start;
	int					word_length;
	int					i;
}						t_word_parse_state;

int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
size_t					ft_strlen(const char *str);
void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
char					*ft_strncat(char *dest, const char *src, size_t n);
int						ft_toupper(int c);
int						ft_tolower(int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strcmp(char *s1, char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
char					*ft_strstr(char *str, char *to_find);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
int						ft_isspecial(char symbol);
int						atoi(const char *str);
void					*ft_calloc(size_t nitems, size_t size);
char					*ft_strdup(const char *s);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strncpy(char *dest, char *src, unsigned int n);
char					*ft_strndup(const char *s, size_t n);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s1, char const *set);
char					**ft_split(char const *s, char c);
char					**ft_split_quotes(const char *str, char c);
int						unleah(char **str, int size);
char					*ft_itoa(int n);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
void					*ft_realloc(void *ptr, size_t newsize);
char					*ft_strtok(char *str, char sepa);
// ft_printf
int						ft_printf(const char *s, ...);
int						pf_putchar(char c);
int						pf_putstr(char *s);
int						pf_putnbr(int n);
int						pf_unsigned_putnbr(unsigned int n);
int						pf_print_hex(unsigned long long n, int upr_case);
int						pf_putptr(unsigned long long n);
int						pf_print_pointer(unsigned long long n);

// get_next_line
char					*get_next_line(int fd);

#endif
