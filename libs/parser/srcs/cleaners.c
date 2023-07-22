
#include "parse.h"

void ft_safe_free(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

static inline void    clean_objects(t_mrt *mrt)
{
	t_obj   *node;

	node = mrt->obj;
	while (node)
	{
		node = node->next;
		mrt->obj = NULL;
		ft_sec_free(mrt->obj);
		mrt->obj = node;
	}
}

static inline void    clean_lights(t_mrt *mrt)
{
	t_light   *node;

	node = mrt->scn.light;
	while (node)
	{
		node = node->next;
		ft_sec_free(mrt->scn.light);
		mrt->scn.light = node;
	}
	mrt->scn.light = NULL;
}

static inline void	clean_cameras(t_mrt *mrt, int (*img)(void *, void *))
{
	t_cmr   *node;

	node = mrt->cmr;
	while (node)
	{
		node = node->next;
		if (img)
			img(mrt->mlx, mrt->cmr->img_ptr);
//		ft_safe_free(mrt->cmr->addr);
		mrt->cmr->img_ptr = NULL;
		ft_sec_free(mrt->cmr);
		mrt->cmr = node;
	}
	mrt->main_cam = NULL;
}

int	clear_all(t_mrt *mrt, int status, int (*win)(void *, void *), int (*img)(void *, void *))
{
	clean_objects(mrt);
	clean_lights(mrt);
	clean_cameras(mrt, img);
	ft_clear_tabs(mrt->tab);
	ft_sec_free(mrt->aux);
	if (win)
		win(mrt->mlx, mrt->mlx_win);
	if (mrt->fd)
		close(mrt->fd);
	ft_sec_free(mrt);
//	exit(status);
	return (status);
}
