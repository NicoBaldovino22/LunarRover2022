int DeadZone(int Value, double ZP, int Mid) {
  if (Value > (Mid - Mid * (ZP / 2)) && Value < (Mid + Mid * (ZP / 2))) //Dead Zone Application
  {
    return Mid;
  }
  else {
    return Value;
  }
}
