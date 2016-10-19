void change_param(int k) {
  switch (menu_state) {
    case 1:
      set_len += k;
      if (set_len > 10000 || set_len < 1000) {
        set_len = 1000;
      }
      break;
    case 2:
      set_pcs += k; break;

    case 3:
      len_err += k; break;

    case 4:
      roll_diam += k; break;

    case 5:
      enc_res_index += k;
      if (enc_res_index == 21) {
        enc_res_index = 0;
      }
      if (enc_res_index == 255) {
        enc_res_index = 20;
      }
      enc_ppr = enc_ppr_list[enc_res_index] * 4;
      break;

    case 6:
      change_dt(dt_cutter_on, k); break;
    case 7:
      change_dt(dt_cutter_off, k); break;
    case 8:
      change_dt(dt_ejector_on, k); break;
    case 9:
      change_dt(dt_ejector_off, k); break;
    case 10:
      change_dt(dt_straightener_on, k); break;
    case 11:
      change_dt(dt_straightener_off, k); break;
    case 12:
      change_dt(dt_feeder_on, k); break;
    case 13:
      change_dt(dt_feeder_off, k); break;
    case 14:
      change_dt(dt_brake, k); break;
  }
  scr_flag = true;
}

void change_dt(int & dly, int k) {
  dly += k * 100;
  if (dly < 0) {
    dly = 4900;
  }
  if (dly > 4900) {
    dly = 0;
  }
}

void save_param(int param) {
  param -= 1;
  switch (menu_state) {
    case 0:
      break;
    case 1:                                                                                      //ДЛИНА ПРУТКА
      int2eeprom(0, set_len); break;
    case 2:                                                                                      //КОЛИЧЕСТВО ПРУТКОВ
      int2eeprom(2, set_pcs); break;
    case 3:                                                                                      //ПОГРЕШНОСТЬ
      int2eeprom(4, len_err); break;
    case 4:                                                                                      //ДИАМЕТР РОЛИКА
      EEPROM.update(6, roll_diam); break;
    case 5:                                                                                      //РАЗРЕШЕНИЕ ЭНКОДЕРА
      EEPROM.update(7, enc_res_index); break;
    case 6:                                                                                      //ЗАДЕРЖКИ РУБКИ
      EEPROM.update(8, (byte)(dt_cutter_on / 100)); break;
    case 7:
      EEPROM.update(9, (byte)(dt_cutter_off / 100)); break;
    case 8:                                                                                      //ЗАДЕРЖКИ СБРОСА
      EEPROM.update(10, (byte)(dt_ejector_on / 100)); break;
    case 9:
      EEPROM.update(11, (byte)(dt_ejector_off / 100)); break;
    case 10:                                                                                     //ЗАДЕРЖКИ ПРАВИЛКИ
      EEPROM.update(12, (byte)(dt_straightener_on / 100)); break;
    case 11:
      EEPROM.update(13, (byte)(dt_straightener_off / 100)); break;
    case 12:                                                                                     //ЗАДЕРЖКИ ПОДАЧИ
      EEPROM.update(14, (byte)(dt_feeder_on / 100)); break;
    case 13:
      EEPROM.update(15, (byte)(dt_feeder_off / 100)); break;
    case 14:                                                                                     //ДЛИТЕЛЬНОСТЬ ТОРМОЖЕНИЯ
      EEPROM.update(16, (byte)(dt_brake / 100)); break;
  }
}

void int2eeprom(int index, int value) {
  byte hi = value >> 8;
  byte low = value;
  EEPROM.update(index, hi);
  EEPROM.update(index + 1, low);
}

void load_params() {

  set_len = word(EEPROM.read(0), EEPROM.read(1)); //ДЛИНА ПРУТКА

  set_pcs = word(EEPROM.read(2), EEPROM.read(3)); //КОЛИЧЕСТВО ПРУТКОВ
  len_err = word(EEPROM.read(4), EEPROM.read(5)); //ПОГРЕШНОСТЬ
  roll_diam = EEPROM.read(6);  //ДИАМЕТР РОЛИКА
  enc_res_index = EEPROM.read(7);  //РАЗРЕШЕНИЕ ЭНКОДЕРА
  dt_cutter_on = (int)EEPROM.read(8) * 100; //ЗАДЕРЖКИ РУБКИ
  dt_cutter_off = (int)EEPROM.read(9) * 100;
  dt_ejector_on = (int)EEPROM.read(10) * 100; //ЗАДЕРЖКИ СБРОСА
  dt_ejector_off = (int)EEPROM.read(11) * 100;
  dt_straightener_on = (int)EEPROM.read(12) * 100; //ЗАДЕРЖКИ ПРАВИЛКИ
  dt_straightener_off = (int)EEPROM.read(13) * 100;
  dt_feeder_on = (int)EEPROM.read(14) * 100; //ЗАДЕРЖКИ ПОДАЧИ
  dt_feeder_off = (int)EEPROM.read(15) * 100;
  dt_brake = (int)EEPROM.read(16) * 100; //ДЛИТЕЛЬНОСТЬ ТОРМОЖЕНИЯ
}

