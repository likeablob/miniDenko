USB_X = 18;
USB_Y = 15;
module USB_BOARD_DIF(scZ) {

  // BOARD
  difference() {
    translate([0, 0, 1.5/2])
    cube(size=[USB_X, USB_Y, 1.5], center=true);

    copy_mirror([1,0,0])
    translate([USB_X/2-3.3/2-1, -USB_Y/2+3.3/2+4, 0])
    cylinder(d=3.3, h=10, center=true);
  }

  // PORT
  USB_P_Y_OFFSET = 10;
  USB_P_Y = 8+USB_P_Y_OFFSET;
  translate([0, USB_Y/2-USB_P_Y/2 + USB_P_Y_OFFSET, 1.5-0.3]){
    hull() {
      //top
      translate([0, 0, 3.2])
      cube(size=[6.2+0.2, USB_P_Y, 0.01], center=true);

      // middle
      translate([0, 0, 1.55])
      cube(size=[8.0+0.2, USB_P_Y, 0.5], center=true);

      //bottom
      translate([0, 0, 0])
      cube(size=[5.2+1, USB_P_Y, 0.01], center=true);
    }
  }

  //screws
  copy_mirror([1,0,0])
  translate([USB_X/2-3.3/2-1, -USB_Y/2+3.3/2+4, -scZ/2])
  cylinder(d=2.2, h=scZ, center=true);
}
