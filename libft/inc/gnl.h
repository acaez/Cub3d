#ifndef GNL_H
# define GNL_H

# include "libft.h"
# include <fcntl.h>

# ifndef FD_MAX
#  define FD_MAX 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

#endif
