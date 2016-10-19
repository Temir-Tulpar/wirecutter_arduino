#include <EEPROM.h>
#include <Encoder.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
bool scr_flag = true;

Encoder myEnc(0, 1);
int enc_ppr_list[] = {10, 20, 30, 40, 50, 60, 100, 200, 300, 360, 400, 500, 600, 720, 800, 1000, 1024, 1200, 1500, 1800, 2000};
int enc_ppr;
long enc_pos;
long old_enc_pos ;
float enc_trans_q ;
byte enc_res_index = 16;
byte roll_diam = 70;


byte out_spare = 8;  // Резерв     - реле
byte out_feed = 9;   // Подача     - реле
byte out_str = 10;   // Правилка   - реле
byte out_brake = 16; // Торможение - реле
byte out_cut = 14;   // Рубка      - симистор
byte out_eject = 15;  // Сброс      - симистор

bool feeder_disabled = true;
bool straightener_disabled = true;
bool brake_disabled = true;
bool spare_disabled = true;
bool cutter_enabled = false;
bool ejector_enabled = false;



byte menu_state = 0;

int curr_len = 0;
int set_len = 100;
int curr_pcs = 0;
int set_pcs =  5;
int len_err = 0;


bool isRunning = false;

int p_btn = 0;
int hold_btn = 0;
unsigned long millis_val = 0;
unsigned long btn_dt = 0;
bool btn_flag = false;

int dt_straightener_on = 2000;
int dt_straightener_off = 2000;
int dt_feeder_on = 1000;
int dt_feeder_off = 1000;
int dt_cutter_on = 2000;
int dt_cutter_off = 2000;
int dt_ejector_on = 1000;
int dt_ejector_off = 1000;
int dt_brake = 4000;

long timestamp, millis_started, millis_cut, millis_stopped;
bool flag_started, flag_cut, flag_eject, flag_stopped;

byte memtest;

void setup() {
  set_outputs();
  reset_outputs();
  pinMode(out_spare, OUTPUT);
  pinMode(out_feed, OUTPUT);
  pinMode(out_str, OUTPUT);
  pinMode(out_brake, OUTPUT);
  pinMode(out_cut, OUTPUT);
  pinMode(out_eject, OUTPUT);

  lcd.init();
  lcd.backlight();
  load_params();
  enc_ppr = enc_ppr_list[enc_res_index] * 4;
  enc_trans_q = roll_diam * 3.1416;
  enc_trans_q /= enc_ppr;
  Serial.begin(9600);
}

void loop() {
  timestamp = millis();
  process_encoder();
  process_timings();
  process_btns();
  set_outputs();
  update_screen();
}

void Run() {
  if (!isRunning && menu_state == 0) {
    millis_started = millis();
    isRunning = true;
    flag_started = true;
  }
}

void Cut() {
  millis_cut = millis();
  flag_eject = true;
  flag_cut = true;
}

void Stop() {
  millis_stopped = millis();
  flag_stopped = true;
  menu_state = 0;
  scr_flag = true;
  isRunning = false;
}

void process_timings() {
  if (flag_started) {
    if (timestamp - millis_started >= dt_feeder_on) {
      feeder_disabled = false;
    }
    if (timestamp - millis_started >= dt_straightener_on) {
      straightener_disabled = false;
    }
    if (!feeder_disabled && !straightener_disabled) {
      flag_started = false;
      Cut();
    }
  }

  if (flag_cut)
  {
    if (timestamp  - millis_cut >= dt_cutter_on) {
      cutter_enabled = true;
    }
    if (timestamp  - millis_cut >= dt_cutter_on + dt_cutter_off) {
      cutter_enabled = false;
      flag_cut = false;
    }
  }

  if (flag_eject)
  {
    if (timestamp  - millis_cut >= dt_ejector_on) {
      ejector_enabled = true;
    }
    if (timestamp  - millis_cut >= dt_ejector_on + dt_ejector_off) {
      ejector_enabled = false;
      flag_eject = false;
    }
  }

  if (flag_stopped) {
    if (timestamp  - millis_stopped >= dt_feeder_off) {
      feeder_disabled = true;
    }
    if (timestamp  - millis_stopped >= dt_straightener_off) {
      straightener_disabled = true;
      brake_disabled = false;
    }
    if (timestamp  - millis_stopped >= dt_straightener_off + dt_brake) {
      brake_disabled = true;
    }
    if (feeder_disabled && straightener_disabled && brake_disabled) {
      flag_stopped = false;
    }
  }
}
