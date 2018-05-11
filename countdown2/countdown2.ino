#define INTERVAL_COUNTER 1000 //satuan ms
#define INT_PIN 2

unsigned long previousMillis = 0;        // 32 bit
int detik, menit, jam, hari;
boolean run;
int settingStatus = 0;

void tampilkanSisa() {

  String data;
  data = "Hari = " + (String)hari + "; Jam = " + (String)jam + "; Menit = " + (String)menit + "; Detik = " + (String)detik + "; run = " + (String)run +" SettingStatus = "+ (String)settingStatus;
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
return true;
}

void setTimerDanMulai(int hr, int jm, int mn,int dt)
{
  hari=  hr;
  jam= jm;
  menit= mn;
  detik= dt;
  run=true; // menjalankan countdown
}

void setup() {
  Serial.begin(9600);
  setTimerDanMulai(1,0,0,0);
  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), startStopCountdown, RISING);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL_COUNTER) {
    // disini fungsi dijalankan 1000ms sekali (1 detik)
    ////////////fungsi countdown/////////////////
    previousMillis = currentMillis;
    if (run) {    // countdown sudah dimulai?
      run = countdown();
      tampilkanSisa();
    }
    
  }/////////////////////////////////////////////

  if(settingStatus==1)
  {
   pengaturanWaktu();
  }
}

void pengaturanWaktu()
{
   setTimerDanMulai(0,0,1,0);
   settingStatus=0;
}


////// jalan ketika interupt////////////
void startStopCountdown()
{
  run=!run;
  settingStatus=1;
}
//////////////////////////////
