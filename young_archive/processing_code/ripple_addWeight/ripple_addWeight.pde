int diam = 10;
float centX, centY;
float weight = 1.0;

void setup(){
  size(500, 300);
  frameRate(24);
  smooth();
  background(180);
  centX = width/2;
  centY = height/2;
  stroke(0);
  strokeWeight(weight);
  noFill();
}

void draw(){
  if(diam <= 400){
    ellipse(centX, centY, diam, diam);
    diam += 10;
    weight += 0.1;
    strokeWeight(weight);
  }
}