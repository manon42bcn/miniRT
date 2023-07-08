
#include "parse.h"

static inline void	ft_safe_free(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

static inline void	clean_objects(t_mrt *mrt)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		node = node->next;
		mrt->obj = NULL;
		ft_safe_free(mrt->obj);
		mrt->obj = node;
	}
}

static inline void	clean_lights(t_mrt *mrt)
{
	t_light	*node;

	node = mrt->scn.light;
	while (node)
	{
		node = node->next;
		ft_safe_free(mrt->scn.light);
		mrt->scn.light = node;
	}
	mrt->scn.light = NULL;
}

static inline void	clean_cameras(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	while (node)
	{
		node = node->next;
		ft_safe_free(mrt->cmr);
		mrt->cmr = node;
	}
	mrt->main_cam = NULL;
}

t_bool	parse_clean_all(t_mrt *mrt, int status)
{
	clean_objects(mrt);
	clean_lights(mrt);
	clean_cameras(mrt);
	ft_clear_tabs(mrt->tab);
	ft_safe_free(mrt->aux);
	return (status);
}
