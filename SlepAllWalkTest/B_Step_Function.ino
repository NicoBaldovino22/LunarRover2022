void Step(int s, int e, int h, int k, int iter) {
  if (FIRST == false)
  {
    Serial.println("Non-First Step");
    for (int i = 0; i <= iter; i++) {
      ps = Smooth(ps, s);
      pe = Smooth(pe, e);
      ph = Smooth(ph, h);
      pk = Smooth(pk, k);
      Shoulder(ps);
      Elbow(pe);
      Hip(ph);
      Knee(pk);
      delay(10);
    }
    ps = s;
    pe = e;
    ph = h;
    pk = k;
  }
  else
  {
    Serial.println("First Step");
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
