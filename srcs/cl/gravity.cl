
#define GRAVITY_FACTOR 1.
#define G (GRAVITY_FACTOR * 9.81)
#define DT 0.04

struct velocity_field {
	double  weight;
	double  sum;
	double  val;
	double  oldVal;
};

void kernel gravity(global struct velocity_field *grid_v) {
	int idx = get_global_id(0);
//	printf("%i ", grid_v[idx].val);
	if (grid_v[idx].weight > 0) {
		grid_v[idx].val += -(G * DT);
	//	printf("%lf ",grid_v[idx].val);
	} 

//	printf("%lf ",grid_v[idx].val);
}