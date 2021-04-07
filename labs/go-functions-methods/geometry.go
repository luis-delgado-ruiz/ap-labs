// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"sort"
	"strconv"
	"time"
)

type Point struct{ x, y float64 }

func (p Point) X() float64 {
	return p.x
}

func (p Point) Y() float64 {
	return p.y
}

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

//!-point

//!+path

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
		}
	}
	return sum
}

type TwoArrays struct {
	a []Point
	b []float64
}

type SortByAngle TwoArrays

func (sba SortByAngle) Len() int {
	return len(sba.a)
}

func (sba SortByAngle) Swap(i, j int) {
	sba.a[i], sba.a[j] = sba.a[j], sba.a[i]
	sba.b[i], sba.b[j] = sba.b[j], sba.b[i]
}

func (sba SortByAngle) Less(i, j int) bool {
	return sba.b[i] < sba.b[j]
}

func getPolygon(sides int) Path {
	rand.Seed(time.Now().UnixNano())
	points := make([]Point, sides)
	polygon := make(Path, sides+1)
	var xAvg int = 0
	var yAvg int = 0

	for i := 0; i < sides; i++ {
		x := rand.Intn(100+100) - 100
		y := rand.Intn(100+100) - 100
		xAvg += x
		yAvg += y
		points[i] = Point{float64(x), float64(y)}
	}

	origin := Point{float64(xAvg) / float64(sides), float64(yAvg) / float64(sides)}
	angles := make([]float64, sides)

	for j := 0; j < sides; j++ {
		angles[j] = math.Atan((points[j].y-origin.y)/(points[j].x-origin.x)) * (108 / math.Pi)
	}

	awp := TwoArrays{a: points, b: angles}

	sort.Sort(SortByAngle(awp))

	for k := 0; k < len(awp.a); k++ {
		polygon[k] = awp.a[k]
	}
	polygon[sides] = awp.a[0]

	return polygon
}

func main() {
	if len(os.Args) == 2 {
		sides, _ := strconv.Atoi(os.Args[1])
		if sides > 2 {
			fmt.Printf("- Generating a [%d] sides figure \n", sides)
			poly := getPolygon(3)
			fmt.Printf("- Generating a [%d] sides figure\n", sides)
			fmt.Println("- Figure's vertices")
			for i := 0; i < sides; i++ {
				fmt.Printf("  - (%f, %f)\n", poly[i].x, poly[i].y)
			}
			fmt.Printf("- Figure's Perimeter\n  -")
			for i := 0; i < sides-1; i++ {
				fmt.Printf(" %f +", poly[i].Distance(poly[i+1]))
			}
			fmt.Printf(" %f", poly[sides-1].Distance(poly[0]))
			fmt.Printf(" = %f\n", poly.Distance())
		} else {
			fmt.Printf("Polygon needs to have 3 or more sides \n", sides)
		}
	} else {
		fmt.Printf("ERROR! \n")
	}
}
