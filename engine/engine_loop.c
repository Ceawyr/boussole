#include "../cub3d.h"

void	engine_loop(void *setting)
{
	t_resources	*resources;
	
	resources = setting;

	handle_keypress_input(resources);
	render_frame(resources);

}