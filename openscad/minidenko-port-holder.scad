$fn=40;

include <scad-utils/mirror.scad>

BODY_X=23;
BODY_Y=8;
BODY_Z=7;

difference(){
  //body
  translate([0, 0, BODY_Z/2]) 
  cube(size=[BODY_X, BODY_Y, BODY_Z], center=true);

  // PCB
  translate([0, 0, 2.5/2-0.01]) 
  cube(size=[18, BODY_Y+1, 2.5], center=true);

  // usb connector
  translate([0, -BODY_Y/2 + 7/2 - 0.01, 5/2-0.01]) 
  cube(size=[10, 7, 5], center=true);

  // PCB(rear)
  translate([0, BODY_Y/2 - 3/2 + 0.01, 2/2-0.01]) 
  cube(size=[BODY_X+1, 3, 2], center=true);

  // screw holes
  mirror_x()
  translate([20.5/2, -BODY_Y/2+3, -1]) 
  cylinder(d=1.5, h=BODY_Z, center=!true);
}
