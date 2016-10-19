void lcd_next_item() {
  save_param(menu_state);
  menu_state++;

  if ((menu_state == 4) || (menu_state == 15)) {
    menu_state = 0;
  }
  scr_flag = true;
  lcd.clear();
}

void update_screen() {
  if (scr_flag) {
    scr_flag = false;

    lcd.noBlink();
    lcd.setCursor(0, 0);

    switch (menu_state) {
      case 0:
        lcd_main(); break;
      case 1:                                                                                      //ДЛИНА ПРУТКА
        lcd_len_pcs (false); break;
      case 2:                                                                                      //КОЛИЧЕСТВО ПРУТКОВ
        lcd_len_pcs (true); break;
      case 3:                                                                                      //ПОГРЕШНОСТЬ
        lcd_error (); break;
      case 4:                                                                                      //ДИАМЕТР РОЛИКА
        lcd_roll_encoder(false); break;
      case 5:                                                                                      //РАЗРЕШЕНИЕ ЭНКОДЕРА
        lcd_roll_encoder(true); break;
      case 6:                                                                                      //ЗАДЕРЖКИ РУБКИ
        lcd_dts("Rezka (sec):", false, dt_cutter_on, dt_cutter_off); break;
      case 7:
        lcd_dts("Rezka (sec):", true, dt_cutter_on, dt_cutter_off); break;
      case 8:                                                                                      //ЗАДЕРЖКИ СБРОСА
        lcd_dts("Sbros (sec):", false, dt_ejector_on, dt_ejector_off); break;
      case 9:
        lcd_dts("Sbros (sec):", true, dt_ejector_on, dt_ejector_off); break;
      case 10:                                                                                     //ЗАДЕРЖКИ ПРАВИЛКИ
        lcd_dts("Pravilka (sec):", false, dt_straightener_on, dt_straightener_off); break;
      case 11:
        lcd_dts("Pravilka (sec):", true, dt_straightener_on, dt_straightener_off); break;
      case 12:                                                                                     //ЗАДЕРЖКИ ПОДАЧИ
        lcd_dts("Podacha (sec):", false, dt_feeder_on, dt_feeder_off ); break;
      case 13:
        lcd_dts("Podacha (sec):", true, dt_feeder_on, dt_feeder_off ); break;
      case 14:                                                                                     //ДЛИТЕЛЬНОСТЬ ТОРМОЖЕНИЯ
        lcd_brake(); break;
    }
  }
}

void lcd_main() {
  lcd.print("L cm: ");
  lcd.print(curr_len);
  lcd.print("/");
  lcd.print(set_len);
  lcd.print("      ");
  lcd.setCursor(0, 1);
  lcd.print("K sht: ");
  lcd.print(curr_pcs);
  lcd.print("/");
  lcd.print(set_pcs);
  lcd.print("      ");
}

void lcd_len_pcs(bool pcs) {
  lcd.print("L: ");
  lcd.print(set_len);
  lcd.print(" cm     ");
  lcd.setCursor(0, 1);
  lcd.print("K: ");
  lcd.print( set_pcs);
  lcd.print(" sht    ");
  if (pcs) {
    lcd.setCursor(15, 1);
  }
  else {
    lcd.setCursor(15, 0);
  }
  lcd.blink();
}

void lcd_error() {
  lcd.print("dL: ");
  lcd.print(len_err);
  lcd.print(" mm       ");
  lcd.setCursor(15, 0);
  lcd.blink();
}

void lcd_roll_encoder(bool set_ppr) {
  lcd.print("Rolik D: ");
  lcd.print(roll_diam );
  lcd.print(" mm     ");
  lcd.setCursor(0, 1);
  lcd.print("Enc PPR: ");
  lcd.print(enc_ppr_list[enc_res_index]);
  lcd.print("        ");
  if (set_ppr) {
    lcd.setCursor(15, 1);
  }
  else {
    lcd.setCursor(15, 0);
  }
  lcd.blink();
}

void lcd_brake() {
  lcd.print("Tormojenie:     ");
  lcd.setCursor(0, 1);
  lcd.print((float)dt_brake / 1000, 1);
  lcd.print(" sec       ");
  lcd.setCursor(15, 1);
  lcd.blink();
}

void lcd_dts(char text[], bool set_second_parameter, int on, int off) {
  lcd.print(text);
  lcd.setCursor(0, 1);
  lcd.print("On: ");
  lcd.print((float)on / 1000, 1);
  lcd.print(" Off: ");
  lcd.print((float)off / 1000, 1);
  if (set_second_parameter) {
    lcd.setCursor(15, 1);
  }
  else {
    lcd.setCursor(7, 1);
  }
  lcd.blink();
}
