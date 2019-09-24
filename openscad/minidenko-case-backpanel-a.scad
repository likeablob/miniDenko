$fn=40;

include <minidenko-case-base.scad>

BODY_BOTTOM_Z = 1.4;

translate([0, 0, 10]) 
difference(){
  backPanel(inset=0.5, h=1.2);
  screws(1.8);
  translate([0, 0, 9-0.4])
  screws(3);

  translate([-15, -2, BODY_Z-0.6]) 
  linear_extrude(height=1, center=false, convexity=10, twist=0)
  rotate([0, 0, -90])
  resize([55, 0, 0], auto=true)
  import("minidenko-logo-mono.dxf");
}
