double takeMeanValue(int sensorVec[], const int length) {
  int tempSum = 0;

  for (int i = 0; i < length; i++) {
    tempSum += sensorVec[i];
  }
  return (double)tempSum / length;
}

void swap(int *sensorVec, int p1, int p2) {
  int pitstop = sensorVec[p1];
  sensorVec[p1] = sensorVec[p2];
  sensorVec[p2] = pitstop;
}


void sort(int *sensorVec, const int length) {

  for (int i = 0; i < (length-1); i++) {
    for (int j = i + 1; j < length; j++) {
      if (sensorVec[i] > sensorVec[j]) {
        swap(sensorVec, i, j);
      }
    }
  }
}

double takeMedian(int *sensorVec, const int length) {
  int res = 0;
  sort(sensorVec, length);

  if (length % 2 == 0) {
    res = (sensorVec[(length/2)-1] + sensorVec[length/2]) / 2;
  }
  else {
    res = sensorVec[(length - 1) / 2];
  }
  return res;
}

void tempWarning(int indoorTemp, int outdoorTemp) {

  if (indoorTemp-outdoorTemp > 20 || indoorTemp > 25) {
    *burningShip = true;
  }
  else if (indoorTemp < 5) {
    *frozenShip = true;
  }
}


