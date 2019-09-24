$fn=40;

include <minidenko-case-base.scad>

BODY_BOTTOM_Z = 1.4;

difference(){
  body();
  backPanel(h=1.5);
  screws(1.4);
}
