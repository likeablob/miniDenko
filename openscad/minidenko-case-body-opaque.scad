$fn=40;

include <minidenko-case-base.scad>

BODY_BOTTOM_Z = 0.3;

difference(){
  body();
  backPanel(h=1.5);
  screws(1.4);
}

// dummy for partial printing
*intersection(){
  translate([0, (BODY_Y - 20) * -1 * 0, BODY_Z*1.2/2]) 
  cube(size=[BODY_X*1.2, BODY_Y, BODY_Z*1.2], center=true);

  difference(){
    body();
    backPanel(h=1.5);
    screws(1.4);
  }
}
