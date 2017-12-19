
#define GRAVITY_FACTOR 1.
#define G (GRAVITY_FACTOR * 9.81)
#define DT 0.04

struct velocity_field {
	float  weight;
	float  sum;
	float  val;
	float  oldVal;
};

void kernel gravity(global struct velocity_field *grid_v) {
	int idx = get_global_id(0);
	if (grid_v[idx].weight > 0) {
		grid_v[idx].val += -(G * DT);
	}
}