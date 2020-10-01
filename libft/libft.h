/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:50:15 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/06 22:07:25 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

/*
**	Macros to fulfill spesific UNIX/Windows standards.
**	Purely there so it's easier to work with multiple devices.
*/
# if _WIN64
# define	read(X, Y, Z)	_read(X, Y, Z)
# define	write(X, Y, Z)	_write(X, Y, Z)
#endif

int		ft_abs(int num);
int		ft_atoi(const char *str);
int		ft_intsize(int n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isblank(int c);
int		ft_isdigit(int c);
int		ft_isextascii(int n);
int		ft_isnegative(int n);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strequ(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_wordlen(char const *str, char del);

double	ft_fabs(double num);

char	*ft_itoa(int n);
char	*ft_quadjoin(char *s1, char *s2, char *s3, char *s4);
char	*ft_setword(char const *s, int len);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *str, int c);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
char	*ft_strfjoin(char* s1, char* s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strncat(char *dest, const char *src, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strnew(size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *str, int c);
char	**ft_strsplit(char const *s, char c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s);

size_t	ft_doublesize(double num);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);

void	ft_bzero(void *s, size_t n);
void	*ft_memalloc(size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	ft_memdel(void **ap);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl(char const *s);
void	ft_putendl_fd(const char *s, int fd);
void	ft_puthex(int num);
void	ft_putnbr(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbrln(int n);
void	ft_putstr(char const *s);
void	ft_putstr_fd(const char *s, int fd);
void	*ft_replace(char* str, char s, char r, size_t max);
void	ft_sleep(int sleep);
void	ft_strclr(char *s);
void	ft_strdel(char **as);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

#endif
