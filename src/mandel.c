
#include "../includes/fractol.h"

int       man_iter(t_env *env)
{
  int     i;

  i = 0;
  while (i < env->man->maxi)
  {
    env->man->oldre = env->man->newre;
    env->man->oldim = env->man->newim;
    env->man->newre = env->man->oldre * env->man->oldre
      - env->man->oldim * env->man->oldim + env->man->rep;
    env->man->newim = env->man->oldre * env->man->oldim * 2 + env->man->imp;
    if ((env->man->newim * env->man->newim
      + env->man->newre * env->man->newre) > 4)
      return (i);
    i++;
  }
  return (i);
}

int mandel_keys(int key, t_env *env)
{
  if (key == 53)
  {
    mlx_destroy_window(env->mlx, env->win);
    exit(0);
  }
  return (key);
}

int mandel_mouse(int key, int x, int y, t_env *env)
{
  double    mx;
  double    my;

  fractal_circle(x, y, &mx, &my);
  if (key == 5)
  {
    env->man->zoom *= 1.01;
    env->man->mx = mx;
    env->man->my = my;
  }
  if (key == 4)
  {
    env->man->zoom /= 1.01;
    env->man->mx = mx;
    env->man->my = my;
  }
  return (key + x + y);
}

int       howie_mandel(t_env *env)
{
  int       i;
  int       x;
  int       y;

  set3to0(&i, &x, &y);
  env->image = make_img(env->mlx);
  while(y < WIN_HGT)
  {
    x = 0;
    while(x < WIN_WDT)
    {
      env->man->rep = 1.5 * (x - WIN_WDT / 2)
        / (0.5 * env->man->zoom * WIN_WDT) + env->man->mx;
      env->man->imp = (y - WIN_HGT / 2)
        / (0.5 * env->man->zoom * WIN_HGT) + env->man->my;
      set4to0(&env->man->oldre, &env->man->oldim,
        &env->man->newre, &env->man->newim);
      put_image_pixel(env->image, x, y, color_juli(man_iter(env)));
      x++;
    }
    y++;
  }
  mlx_put_image_to_window(env->mlx, env->win, env->image.img, 0, 0);
  mlx_mouse_hook(env->win, mandel_mouse, env);
  mlx_hook(env->win, 2, 0, mandel_keys, env);
  return (1);
}

t_mandel  *make_mandel()
{
  t_mandel    *mandel;

  if (!(mandel = (t_mandel *)malloc(sizeof(t_mandel))))
    return (NULL);
  mandel->rep = 0;
  mandel->imp = 0;
  mandel->mx = -0.5;
  mandel->my = 0;
  mandel->zoom = 1.0;
  mandel->maxi = 128;
  return (mandel);
}
