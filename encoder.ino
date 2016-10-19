
void process_encoder() {
  enc_pos = myEnc.read();
  if (enc_pos != old_enc_pos) {
    curr_len = enc_trans_q * enc_pos ;
    old_enc_pos = enc_pos;
    scr_flag = true;
    if  (curr_len >= set_len + len_err)     {
      myEnc.write(0);
      if (isRunning) {
        Cut();
        curr_pcs++;
        if (curr_pcs >= set_pcs) {
          curr_pcs = 0;
          Stop();
        }
      }
    }
  }
}
