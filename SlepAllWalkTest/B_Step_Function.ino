void Step(int s, int e, int h, int k) {
  Serial.println("What Are You Doing Step-Function");
  if (FIRST == false)
  {
    int ds = abs(ps - s);
    int de = abs(pe - e);
    int dh = abs(ph - h);
    int dk = abs(pk - k);
    int iter = 0;

    while (ds > 1 || de > 1 || dh > 1 || dk > 1) {  //loops until all servos are within 1 degree of their goal position
      ps = Smooth(ps, s);
      pe = Smooth(pe, e);
      ph = Smooth(ph, h);
      pk = Smooth(pk, k);
      Shoulder(ps);
      Elbow(pe);
      Hip(ph);
      Knee(pk);
      ds = abs(ps - s);
      de = abs(pe - e);
      dh = abs(ph - h);
      dk = abs(pk - k);
      iter++;
      delay(10);
      if (iter > 1000) {
        Serial.println("Help Step-Function, I'm stuck");
        return;
      }
    }
    Serial.print(iter);
    Serial.println(" Iterations");
  }

  else
  {
    Shoulder(s);
    Elbow(e);
    Hip(h);
    Knee(k);
    ps = s;
    pe = e;
    ph = h;
    pk = k;
    FIRST = false;
  }
}
