
void process_btns() {
  btn_dt = timestamp - millis_val;

  if (btn_dt > 150) {
    p_btn = pressed_button(analogRead(A2));

    if (p_btn == 0) {
      btn_flag = false;
    }
    else {
      millis_val = millis();
      process_btn1_hold();
      process_btn23_hold();
    }

    if (!btn_flag) {
      switch (p_btn) {
        case 1:
          if (!isRunning) {
            lcd_next_item();
          }
          break;
        case 2:
          if (!isRunning) {
            change_param(-1);
          }
          break;
        case 3:
          if (!isRunning) {
          change_param(1); 
          }
          break;
        case 4:
          Run(); break;
        case 5:
          Stop(); break;
      }
    }
  }
  else {
    btn_flag = true;
  }
}

void process_btn1_hold() {
  if (p_btn == 1) {
    hold_btn++;
    if (hold_btn == 30) {
      hold_btn = 0;
      menu_state = 4;
      scr_flag = true;
    }
  }
}

void process_btn23_hold() { 
  if (p_btn == 2 || p_btn == 3) {
    btn_flag = false;
  }
}

int pressed_button(int a2_volt) {
  if ((a2_volt > 340) && (a2_volt < 350)) {
    return 1;
  }
  else if ((a2_volt > 405) && (a2_volt < 415)) {
    return 2;
  }
  else if ((a2_volt > 495) && (a2_volt < 505)) {
    return 3;
  }
  else if ((a2_volt > 655) && (a2_volt < 665)) {
    return 4;
  }
  else if ((a2_volt > 895) && (a2_volt < 910)) {
    return 5;
  }
  else {
    return 0;
  }
}
