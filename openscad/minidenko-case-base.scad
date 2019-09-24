$fn=40;

include <scad-utils/morphology.scad>
include <scad-utils/mirror.scad>

// include <charging_board_microb.scad>
include <charging_board_typec.scad>

LED_X=32;
LED_Y=130;
LED_Z=13.0;

BODY_X=LED_X+5;
BODY_Y=LED_Y+10;
// BODY_BOTTOM_Z = 1.4;
BODY_BOTTOM_Z = 0.3;
BODY_Z=LED_Z+11+0.8*2 + BODY_BOTTOM_Z;

STAND_X=3;

BACKPANEL_Z=1.2;

// LED Matrix
*%translate([0, 0, LED_Z/2 + BODY_BOTTOM_Z])
color("red")
cube(size=[LED_X, LED_Y, LED_Z], center=true);

module body(){
  difference(){
    linear_extrude(height=BODY_Z, center=!true, convexity=10, twist=0)
    rounding(r=3)
    square(size=[BODY_X, BODY_Y], center=true);

    // inner space
    translate([0, 0, (BODY_Z)/2 + BODY_BOTTOM_Z]) 
    cube(size=[LED_X + 1, LED_Y + 1, BODY_Z], center=true);

    // edge();
    // USB
    translate([0, LED_Y/2, LED_Z + BODY_BOTTOM_Z + 0.8]) {
      USB_TYPEC_BOARD(diff=true);
      // USB PLUG
      translate([0, 1.5, 0])
      translate([0, 0, 5/2])  
      rotate([-90, 0, 0]) 
      linear_extrude(height=10, center=!true, convexity=10, twist=0)
      hull(){
        mirror_x()
        translate([4, 0, 0])
        circle(d=7);
      }
    }

    // sw
    translate([0, -BODY_Y/2+3, LED_Z + BODY_BOTTOM_Z +  12/2 + 0.8 * 2]) {
      translate([0, 15/2, 0])
      cube(size=[14, 15, 12], center=true);

      translate([0, -5/2, 0]) 
      cube(size=[15.2+1, 5, 12], center=true);
    }


  }
  // stand
  mirror_y()
  translate([0, BODY_Y/4, 3]) 
  translate([-BODY_X/2, 0, 0]) 
  difference(){
    linear_extrude(height=6, center=!true, convexity=10, twist=0)
    difference(){
      rounding(r=2)
      square(size=[STAND_X*2, 10], center=true);

      translate([STAND_X/2, 0, 0]) 
      square(size=[STAND_X, 10], center=true);
    }
    translate([-7*cos(50), 0, 0]) 
    rotate([0, 50, 0]) 
    cube(size=[7, 10, 7], center=true);

  }

}

// screws
module screws(d=1.4) {
  mirror_x()
  mirror_y()
  translate([-(BODY_X/2 - 5), BODY_Y/2 - 3, BODY_Z-9])
  cylinder(d=d, h=10, center=!true);
}


module backPanel(inset=0, h=1.2) {
  difference(){
    translate([0, 0, BODY_Z]) 
    hull() {
      linear_extrude(height=0.01, center=true, convexity=10, twist=0)
      inset(d=1+inset)
      rounding(r=3)
      square(size=[BODY_X, BODY_Y], center=true);

      translate([0, 0, -h]) 
      linear_extrude(height=0.01, center=true, convexity=10, twist=0)
      inset(d=1+inset)
      rounding(r=3)
      square(size=[BODY_X, BODY_Y], center=true);  
    }

    // power switch
    translate([0, -BODY_Y/2+3, LED_Z + BODY_BOTTOM_Z +  12/2 + 0.8]) {
      translate([0, -5/2, 0]) 
      cube(size=[15.2+1, 5, 12], center=true);
    }
  }
}
