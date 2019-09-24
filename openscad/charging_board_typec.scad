
USB_TYPEC_BOARD_X = 17.1;
USB_TYPEC_BOARD_Y = 28.1;
USB_TYPEC_BOARD_Z = 1.0;

module USB_TYPEC_BOARD(diff=false) {
  translate([0, -USB_TYPEC_BOARD_Y/2, 0])   
  linear_extrude(height=USB_TYPEC_BOARD_Z, center=!true, convexity=10, twist=0) 
  square(size=[USB_TYPEC_BOARD_X, USB_TYPEC_BOARD_Y], center=true);

  translate([0, 1.5, USB_TYPEC_BOARD_Z])
  translate([0, -7.3, 3/2])
  rotate([-90, 0, 0]) 
  linear_extrude(height=diff ? 20 : 7.3, center=!true, convexity=10, twist=0)
  hull(){
    offset(r= diff ? 0.3 : 0)
    mirror_x()
    translate([9/2-3/2, 0, 0])
    circle(d=3);
  }
}