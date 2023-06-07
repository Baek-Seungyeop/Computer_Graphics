static const float	PI = 3.14159F;
static const float	RED = 1.0F;
static const float	GREEN = 1.0F;
static const float	BLUE = 1.0F;

static const int	WIN_WIDTH = 600;
static const int	WIN_HEIGHT = 800;
static const int	win_left = 0;
static const int	win_bottom = 0;
static const int	win_right = win_left + WIN_WIDTH;
static const int	win_top = WIN_HEIGHT - win_bottom;

static int			stick_size = 100;
static const int	stick_left = WIN_WIDTH / 2 - stick_size / 2;
static const int	stick_right = WIN_WIDTH / 2 + stick_size / 2;
static const int	stick_bottom = 50;
static const int	stick_top = 70;
static const int	delta_stick_x = 10;

static const int	max_brick_num = 100;
static const int	brick_size = 40;
static const int	brick_width = brick_size;
static const int	brick_height = brick_size;

static const float	velocity_x = 0.0F;
static const float	velocity_y = -200.0F;
static const float  velocity_ratio = 1.04F;

static const float	ball_radius = 10.0F;
static float		ball_velocity_angle = 90.0F;

static const int	UI_HEIGHT = 100;