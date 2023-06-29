#include "minirt.h"

	// static char *dictionary[] = {"Sphere", "Plane", "Cylinder", "Square",
	//                              "Triangle", "Cube", 
	//                              "Pyramid", "Resolution", "Ambient",
	//                              "Camera", "Light", NULL};

void debug_print_v3d(t_v3d *v3d, char *msg)
{
	printf("%s -> [x: %f] [y: %f] [z: %f]\n", msg, v3d->x, v3d->y, v3d->z);
}

void debug_print_light(t_light *light)
{
	t_light *node;
	node = light;
	while (node)
	{
		printf("LIGHT\n\t");
		debug_print_v3d(&light->origin, "CENTRE");
		printf("\tRATIO %f\n", light->bright);
		printf("\tColor %d\n", light->color);
		node = node->next;
	}
}

void debug_print_camera(t_cmr *cam)
{
	t_cmr *node;
	node = cam;
	while (node)
	{
		printf("CAMERA\n\t");
		debug_print_v3d(&node->position, "CENTRE");
		printf("\t");
		debug_print_v3d(&node->dir, "ORIENTATION");
		printf("\tFOV %d\n", node->inp_fov);
		printf("\tFOV tan %f\n", node->fov);
		node = node->next;
	}
}

void debug_print_tab(char **str, char *title, char *subtitle)
{
	if (!str[0])
		return ;
	printf("%s\n", title);
	printf("=======================================\n");
	for (size_t i = 0; str[i]; i++)
		printf("%s -> %zu -> %s\n", subtitle, i, str[i]);
}

void debug_print_struct(t_mrt *rt)
{
	// printf("mlx %p\n", &rt->mlx);
	// printf("scene %p\n", &rt->scn);
	// printf("first element %p\n", rt->obj);
	printf("aux x -> %d y -> %d\n", rt->x, rt->y);
	printf("aux char %p\n", rt->aux);
	printf("bonus %d\n", rt->bonus);
}

void degub_print_old_wrap(t_mrt *mrt)
{
	printf("BASE OLD STRUCT\n");
	printf("SCENE:\n");
	printf("\t[X] %d [Y] %d\n", mrt->scn.w_x, mrt->scn.w_y);
	if (mrt->scn.res_init == 1)
		printf("LOADED = TRUE\n");
	else
		printf("LOADED = FALSE\n");
	printf("AMBIENT %f\n", mrt->scn.bright);
	printf("\tColor %d\n", mrt->scn.amb_rgb);
	printf("BGR %d\n", mrt->scn.bgr);
}

void debug_print_new_wrap(t_mrt *mrt)
{
	printf("BASE NEW STRUCT\n");
	printf("SCENE:\n");
	printf("\t[X] %d [Y] %d\n", mrt->scn.w_x, mrt->scn.w_y);
	printf("AMBIENT %f\n", mrt->scn.bright);
	printf("\tColor %d\n", mrt->scn.amb_rgb);
	debug_print_light(mrt->light);
	debug_print_camera(mrt->cmr);
}

void debug_print_common_old(t_obj *obj)
{
	printf("ID %d\n", obj->id);
	printf("COLOR %d\n", obj->color);
	printf("SPECULAR %d\n", obj->specular);
	printf("REFLEX %f\n", obj->reflex);
	printf("REFRACT %f\n", obj->refract);
	printf("TEXTURE %d\n", obj->texture);
	debug_print_v3d(&obj->normal, "Normal");
	printf("WAVELENGHT %f\n", obj->wavelength);
}

void debug_print_sph(t_obj *sph)
{
	printf("--------------------------------\n");
	printf("SPHERE\n");
	debug_print_v3d(&sph->elm.sph.centre, "CENTRE");
	printf("RADIUS %f\n", sph->elm.sph.radius);
	printf("INSIDE %d\n", sph->elm.sph.inside);
	debug_print_common_old(sph);
	printf("--------------------------------\n");
}

void debug_print_common_new(t_obj *obj)
{
	printf("ID %d\n", obj->type);
	printf("COLOR %d\n", obj->color);
	printf("SPECULAR %d\n", obj->specular);
	printf("REFLEX %f\n", obj->reflex);
	printf("REFRACT %f\n", obj->refract);
	printf("TEXTURE %d\n", obj->texture);
	debug_print_v3d(&obj->normal, "Normal");
	printf("WAVELENGHT %f\n", obj->wavelength);
}

void debug_print_sph_new(t_obj *sph)
{
	printf("--------------------------------\n");
	printf("SPHERE NEW\n");
	debug_print_v3d(&sph->elm.sph.centre, "CENTRE");
	printf("RADIUS %f\n", sph->elm.sph.radius);
	printf("INSIDE %d\n", sph->elm.sph.inside);
	debug_print_common_new(sph);
	printf("--------------------------------\n");
}

void debug_print_plane_old(t_obj *pl)
{
	printf("--------------------------------\n");
	printf("PLANE\n");
	debug_print_v3d(&pl->elm.pl.centre, "CENTRE");
	debug_print_common_old(pl);
	printf("--------------------------------\n");
}

void debug_print_plane_new(t_obj *pl)
{
	printf("--------------------------------\n");
	printf("PLANE NEW\n");
	debug_print_v3d(&pl->elm.pl.centre, "CENTRE");
	debug_print_v3d(&pl->elm.pl.orient, "ORIENTATION");
	debug_print_common_new(pl);
	printf("--------------------------------\n");
}

void debug_print_cyl_old(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("CYLINDER\n");
	debug_print_v3d(&obj->elm.cyl.centre, "CENTRE");
	debug_print_v3d(&obj->elm.cyl.dir, "ORIENTATION");
	printf("RADIUS %f\n", obj->elm.cyl.radius);
	printf("HEIGHT %f\n", obj->elm.cyl.height);
	debug_print_common_old(obj);
	printf("--------------------------------\n");
}

void debug_print_cyl_new(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("CYLINDER NEW\n");
	debug_print_v3d(&obj->elm.cyl.centre, "CENTRE");
	debug_print_v3d(&obj->elm.cyl.dir, "ORIENTATION");
	printf("RADIUS %f\n", obj->elm.cyl.radius);
	printf("HEIGHT %f\n", obj->elm.cyl.height);
	debug_print_common_new(obj);
	printf("--------------------------------\n");
}

void debug_print_sq_old(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("SQUARE\n");
	debug_print_v3d(&obj->elm.sq.centre, "CENTRE");
	printf("SIDE %f\n", obj->elm.sq.side);
	debug_print_common_old(obj);
	printf("--------------------------------\n");
}

void debug_print_sq_new(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("SQUARE NEW\n");
	debug_print_v3d(&obj->elm.sq.centre, "CENTRE");
	debug_print_v3d(&obj->elm.sq.orient, "ORIENTATION");
	printf("SIDE %f\n", obj->elm.sq.side);
	debug_print_common_new(obj);
	printf("--------------------------------\n");
}

void debug_print_trg_old(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("TRIANGLE\n");
	debug_print_v3d(&obj->elm.trg.v1, "P1");
	debug_print_v3d(&obj->elm.trg.v2, "P2");
	debug_print_v3d(&obj->elm.trg.v3, "P3");
	debug_print_common_old(obj);
	printf("--------------------------------\n");
}

void debug_print_trg_new(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("TRIANGLE NEW\n");
	debug_print_v3d(&obj->elm.trg.v1, "P1");
	debug_print_v3d(&obj->elm.trg.v2, "P2");
	debug_print_v3d(&obj->elm.trg.v3, "P3");
	debug_print_v3d(&obj->elm.trg.orient, "Normal");
	debug_print_common_new(obj);
	printf("--------------------------------\n");
}

void debug_print_cub_old(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("CUBE\n");
	debug_print_v3d(&obj->elm.sq.centre, "CENTRE");
	printf("SIDE %f\n", obj->elm.sq.side);
	debug_print_common_old(obj);
	printf("--------------------------------\n");
}

void debug_print_cub_new(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("CUBE NEW\n");
	debug_print_v3d(&obj->elm.sq.centre, "CENTRE");
	printf("SIDE %f\n", obj->elm.sq.side);
	debug_print_common_new(obj);
	printf("--------------------------------\n");
}

void debug_print_pyr_old(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("PYRAMID\n");
	debug_print_v3d(&obj->elm.sq.centre, "CENTRE");
	printf("SIDE %f\n", obj->elm.sq.side);
	debug_print_common_old(obj);
	printf("--------------------------------\n");
}

void debug_print_pyr_new(t_obj *obj)
{
	printf("--------------------------------\n");
	printf("PYRAMID NEW\n");
	debug_print_v3d(&obj->elm.sq.centre, "CENTRE");
	printf("SIDE %f\n", obj->elm.sq.side);
	debug_print_common_new(obj);
	printf("--------------------------------\n");
}

void debug_print_elem(void *elem, int mode)
{
	if (mode == 0)
	{
		t_obj *obj = (t_obj *)elem;
		switch (obj->type)
		{
	    case SPHERE:
	        debug_print_sph(obj);
	        break;
	    case PLANE:
	    	debug_print_plane_old(obj);
	    	break;
	    case CYLINDER:
	    	debug_print_cyl_old(obj);
	    	break;
	    case SQUARE:
	    	debug_print_sq_old(obj);
	    	break;
	    case TRIANGLE:
	    	debug_print_trg_old(obj);
	    	break;
	   	case CUBE:
	    	debug_print_cub_old(obj);
	    	break;
	    case PYRAMID:
	    	debug_print_pyr_old(obj);
	    	break;
	    default:
	        break;
		}
	}
	else
	{
		t_obj *obj = (t_obj *)elem;
		switch (obj->type)
		{
	    case SPHERE:
	        debug_print_sph_new(obj);
	        break;
	    case PLANE:
	    	debug_print_plane_new(obj);
	    	break;
	    case CYLINDER:
	    	debug_print_cyl_new(obj);
	    case SQUARE:
	    	debug_print_sq_new(obj);
	    	break;
	    case TRIANGLE:
	    	debug_print_trg_new(obj);
	    	break;
	   	case CUBE:
	    	debug_print_cub_new(obj);
	    	break;
	    case PYRAMID:
	    	debug_print_pyr_new(obj);
	    	break;
	    default:
	        break;
		}
	}
}