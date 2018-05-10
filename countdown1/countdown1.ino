#define INTERVAL_COUNTER 1000 //satuan ms

unsigned long previousMillis = 0;        // 32 bit
int detik, menit, jam, hari;
boolean run;

void tampilkanSisa() {

  String data;
  data = "Hari = " + (String)hari + "; Jam = " + (String)jam + "; Menit = " + (String)menit + "; Detik = " + (String)detik + "; run = " + (String)run;
  //Serial.println("Data Waktu :");
  Serial.println(data);
}

void triggerAlarm() {
  Serial.println("Waktu Habis");
}


boolean countdown() {
  detik--;
  if (detik < 0) {
    menit--;
    detik = 59;
  }
  if (menit < 0) {
    jam--;
    menit = 59;
  }
  if (jam < 0) {
    hari--;
    jam = 23;
  } 

  if (hari < 0) {
    hari = 0;
    triggerAlarm();
    return false; // nandain kalau waktu sudah habis
  }
return 1;
}

void setTimerDanMulai()
{
  hari=1;
  jam=0;
  menit=0;
  detik=0;
  run=true; // menjalankan countdown
}
void setup() {
  Serial.begin(9600);
  setTimerDanMulai();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL_COUNTER) {
    previousMillis = currentMillis;

    // disini fungsi dijalankan 1000ms sekali (1 detik)

    ////////////fungsi countdown/////////////////
    if (run) {    // countdown sudah dimulai?
      run = countdown();
      tampilkanSisa();
    }
    /////////////////////////////////////////////
    
  }
}
