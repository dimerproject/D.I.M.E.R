
//soporte triangular con agujero
difference(){
    translate([0,0,8.5])
    union(){
        rotate([0,0,60])
        cylinder(r=8, h=20, $fn=3);
        cylinder(r=10, h=20, $fn=3);
        //escuadra corte en angulo
        translate([0,0,-1.75])
        rotate([0,180,180])
        cylinder(r1=10, r2=5, h=3.5, $fn=3, center=true);
        translate([0,0,-1.75])
        rotate([0,180,0])
        cylinder(r1=8, r2=5, h=3.5, $fn=3, center=true);
        //trozo cilindro
        difference(){
            difference(){
        translate([0,0,-6.5])
        cylinder(r=6, h=13, $fn=25, center=true);
        translate([0,0,-7])
        cylinder(r=4, h=7, $fn=25, center=true);}
        translate([-9,-1,-10.5])
        cube([20,2,7]);
        }
    }
    translate([0,0,-20])
    cylinder(r=3, h=100, $fn=25);
}

//segunda parte del soporte del motor
translate([0,0,57])
rotate([0,180,180])
difference(){
    translate([0,0,8.5])
    union(){
        rotate([0,0,60])
        cylinder(r=8, h=20, $fn=3);
        cylinder(r=10, h=20, $fn=3);
        //escuadra corte en angulo
        translate([0,0,-1.75])
        rotate([0,180,180])
        cylinder(r1=10, r2=5, h=3.5, $fn=3, center=true);
        translate([0,0,-1.75])
        rotate([0,180,0])
        cylinder(r1=8, r2=5, h=3.5, $fn=3, center=true);
        //trozo cilindro
        difference(){
            difference(){
        translate([0,0,-6.5])
        cylinder(r=6, h=13, $fn=25, center=true);
        translate([0,0,-7])
        cylinder(r=4, h=7, $fn=25, center=true);}
        translate([-9,-1,-10.5])
        cube([20,2,7]);
        }
    }
    translate([0,0,-20])
    cylinder(r=3, h=100, $fn=25);
}