
package main

import (
	"math"
	"fmt"
)

func pi_langrange(x float64, y float64, pts[]point, k int) float64{
	var res float64

	res = 1
	for i, pt := range pts {
		if (i != k && pt.y != pts[k].y) {
			res *= (y - pt.y) / (pts[k].y - pt.y)
		}
		if (i != k && pt.x != pts[k].x) {
			res *= (x - pt.x) / (pts[k].x - pt.x)
		}
	}
	return (res)
}

func sigma_lagrange(x float64, y float64, pts[]point) float64 {
	var res float64

	res = 0
	for k, pt := range pts {
		res += pt.z * pi_langrange(x, y, pts, k)
		//res /= (math.Sin(pt.x / 300) * math.Sin(pt.y / 300) * math.Sin((300-pt.x) / 300) * math.Sin((300-pt.y) / 300))
//		res /= ((pt.x / 300) * math.Sin(pt.y / 300) * math.Sin((300-pt.x) / 300) * math.Sin((300-pt.y) / 300))
	}
		//res *= (math.Sin(x / 300) * math.Sin(y / 300) *math.Sin((300-x) / 300) * math.Sin((300-y) / 300))
	return (res)
}

func lagrange(grid*[300][300][601]float64, pts[]point, env * env) {
	var carte [300][300]float64
	for i, grid_x := range grid {
		for j, _ := range grid_x {
			carte[i][j] = sigma_lagrange(float64(i), float64(j), pts)
			//fmt.Printf("carte i j is %f\n",carte[i][j])
		}
	}
	var max float64

	max = 0
	for _, grid_x := range carte {
		for _, alt := range grid_x {
			if (math.Abs(alt) > max) {
				max = math.Abs(alt)
			}
		}
	}
	fmt.Printf("max is %f\n", max)
	div := 1.0
	div = max / 300
	max /= div
	fmt.Printf("max is new %f\n", max)
	for i, grid_x := range carte {
		for j, _ := range grid_x {
			carte[i][j] /= div

			grid[i][j][int(carte[i][j]) + 300] = 1

			if j > 0 && (carte[i][j - 1] - carte[i][j]) >= 0 {
				for k := int(carte[i][j]); k <= int(carte[i][j - 1]); k++ {
					grid[i][j][k + 300] = 1
				}
			}
			if j > 0 && (carte[i][j - 1] - carte[i][j]) <= 0 {
				for k := int(carte[i][j]); k >= int(carte[i][j - 1]); k-- {
					grid[i][j][k + 300] = 1
				}
			}

			if i > 0 && (carte[i - 1][j] - carte[i][j]) >= 0 {
				for k := int(carte[i][j]); k <= int(carte[i - 1][j]); k++ {
					grid[i][j][k + 300] = 1
				}
			}
			if i > 0 && (carte[i - 1][j] - carte[i][j]) <= 0 {
				for k := int(carte[i][j]); k >= int(carte[i - 1][j]); k-- {
					grid[i][j][k + 300] = 1
				}
			}
		}
	}

	for i, grid_x := range grid {
		for j, grid_y := range grid_x {
			for z, is := range grid_y {
//				grid[i][j][carte[i][j]] = 1
	//			if (i > 0)
	//				grid[i - 1][j][carte[i - 1][j]

				if is != 1 {
					continue 
				}
					pot := []float64{float64(i), float64(j), float64(z) - 300}//carte[i][j]}
					project_and_draw(pot, env)
			}
		}
	}
	fmt.Printf("carte[150][150] = [%f] ||  carte[100][200] = [%f]\n", carte[150][150], carte[100][200]);
	fmt.Printf("carte[0][0] = [%f] ||  carte[100][200] = [%f]\n", carte[0][0], carte[100][200]);
}
